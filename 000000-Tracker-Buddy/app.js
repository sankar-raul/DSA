const STORAGE_KEY = "tracker-buddy-progress-v1";
const STREAK_KEY = "tracker-buddy-activity-v1";

const state = {
  problems: [],
  completed: loadJson(STORAGE_KEY, {}),
  activity: loadJson(STREAK_KEY, []),
  filter: "all",
  search: "",
  sort: "number"
};

const elements = {
  list: document.querySelector("#problem-list"),
  empty: document.querySelector("#empty-state"),
  resultCount: document.querySelector("#result-count"),
  search: document.querySelector("#search-input"),
  sort: document.querySelector("#sort-select"),
  solved: document.querySelector("#solved-count"),
  total: document.querySelector("#total-count"),
  remaining: document.querySelector("#remaining-count"),
  streak: document.querySelector("#streak-count"),
  ring: document.querySelector("#progress-ring"),
  ringValue: document.querySelector("#ring-value"),
  note: document.querySelector("#daily-note"),
  reset: document.querySelector("#reset-button")
};

function loadJson(key, fallback) {
  try {
    return JSON.parse(localStorage.getItem(key)) ?? fallback;
  } catch {
    return fallback;
  }
}

function saveProgress() {
  localStorage.setItem(STORAGE_KEY, JSON.stringify(state.completed));
  localStorage.setItem(STREAK_KEY, JSON.stringify(state.activity));
}

function escapeHtml(value) {
  return String(value).replace(/[&<>'"]/g, (character) => ({
    "&": "&amp;", "<": "&lt;", ">": "&gt;", "'": "&#039;", '"': "&quot;"
  })[character]);
}

function getVisibleProblems() {
  const query = state.search.trim().toLowerCase();
  const filtered = state.problems.filter((problem) => {
    const matchesDifficulty = state.filter === "all" || problem.difficulty === state.filter;
    const matchesSearch = !query || problem.title.toLowerCase().includes(query) || String(problem.number).includes(query) || problem.slug.includes(query);
    return matchesDifficulty && matchesSearch;
  });

  return filtered.sort((first, second) => {
    if (state.sort === "title") return first.title.localeCompare(second.title);
    if (state.sort === "difficulty") return difficultyRank(first.difficulty) - difficultyRank(second.difficulty) || first.number - second.number;
    if (state.sort === "status") return Number(Boolean(state.completed[second.id])) - Number(Boolean(state.completed[first.id])) || first.number - second.number;
    return first.number - second.number;
  });
}

function difficultyRank(difficulty) {
  return { easy: 1, medium: 2, hard: 3 }[difficulty] ?? 4;
}

function renderProblems() {
  const visibleProblems = getVisibleProblems();
  elements.resultCount.textContent = `${visibleProblems.length} ${visibleProblems.length === 1 ? "problem" : "problems"}`;
  elements.list.innerHTML = visibleProblems.map((problem) => {
    const isDone = Boolean(state.completed[problem.id]);
    return `
      <article class="problem-row${isDone ? " is-done" : ""}">
        <span class="problem-number">#${String(problem.number).padStart(4, "0")}</span>
        <div class="problem-info">
          <h3 class="problem-title"><a class="problem-title-link" href="${escapeHtml(problem.url)}" target="_blank" rel="noreferrer">${escapeHtml(problem.title)}</a></h3>
          <span class="problem-slug">${escapeHtml(problem.slug)}</span>
        </div>
        <span class="difficulty difficulty-${escapeHtml(problem.difficulty)}">${escapeHtml(problem.difficulty)}</span>
        <a class="open-link" href="${escapeHtml(problem.url)}" target="_blank" rel="noreferrer">Open ↗</a>
        <button class="check-button${isDone ? " is-checked" : ""}" type="button" data-problem-id="${escapeHtml(problem.id)}" aria-label="Mark ${escapeHtml(problem.title)} ${isDone ? "as incomplete" : "as complete"}" aria-pressed="${isDone}">${isDone ? "✓" : ""}</button>
      </article>`;
  }).join("");
  elements.empty.hidden = visibleProblems.length > 0;
}

function renderStats() {
  const solved = state.problems.filter((problem) => state.completed[problem.id]).length;
  const total = state.problems.length;
  const percentage = total ? Math.round((solved / total) * 100) : 0;
  elements.solved.textContent = solved;
  elements.total.textContent = total;
  elements.remaining.textContent = total - solved;
  elements.streak.textContent = calculateStreak();
  elements.ring.style.setProperty("--progress", `${percentage}%`);
  elements.ringValue.textContent = `${percentage}%`;
  elements.ring.setAttribute("aria-label", `${percentage} percent complete`);
}

function calculateStreak() {
  const days = new Set(state.activity);
  let streak = 0;
  const cursor = new Date();
  while (days.has(toDateKey(cursor))) {
    streak += 1;
    cursor.setDate(cursor.getDate() - 1);
  }
  return streak;
}

function toDateKey(date) {
  return date.toISOString().slice(0, 10);
}

function updateCompletion(problemId) {
  const isCompleting = !state.completed[problemId];
  if (!isCompleting) {
    delete state.completed[problemId];
  } else {
    state.completed[problemId] = true;
    const today = toDateKey(new Date());
    if (!state.activity.includes(today)) state.activity.push(today);
  }
  saveProgress();
  if (state.sort === "status") {
    renderProblems();
  } else {
    const button = [...elements.list.querySelectorAll("[data-problem-id]")]
      .find((item) => item.dataset.problemId === problemId);
    const row = button?.closest(".problem-row");
    if (button && row) {
      row.classList.toggle("is-done", isCompleting);
      button.classList.toggle("is-checked", isCompleting);
      button.setAttribute("aria-pressed", String(isCompleting));
      button.setAttribute("aria-label", `Mark ${button.closest(".problem-row").querySelector(".problem-title").textContent} ${isCompleting ? "as incomplete" : "as complete"}`);
      button.textContent = isCompleting ? "✓" : "";
    }
  }
  renderStats();
}

function setDailyNote() {
  const notes = [
    "Small steps still move the pointer.",
    "One good problem is a good session.",
    "Patterns become visible in the rearview.",
    "Keep the loop short. Keep showing up.",
    "Today is a fine day to untangle one thing."
  ];
  elements.note.textContent = notes[new Date().getDate() % notes.length];
}

function bindEvents() {
  elements.search.addEventListener("input", (event) => {
    state.search = event.target.value;
    renderProblems();
  });
  elements.sort.addEventListener("change", (event) => {
    state.sort = event.target.value;
    renderProblems();
  });
  document.querySelectorAll("[data-filter]").forEach((button) => {
    button.addEventListener("click", () => {
      state.filter = button.dataset.filter;
      document.querySelectorAll("[data-filter]").forEach((item) => item.classList.toggle("active", item === button));
      renderProblems();
    });
  });
  elements.list.addEventListener("click", (event) => {
    const button = event.target.closest("[data-problem-id]");
    if (button) {
      updateCompletion(button.dataset.problemId);
      return;
    }
    if (event.target.closest("a")) return;
    const row = event.target.closest(".problem-row");
    const rowButton = row?.querySelector("[data-problem-id]");
    if (rowButton) updateCompletion(rowButton.dataset.problemId);
  });
  elements.reset.addEventListener("click", () => {
    if (!Object.keys(state.completed).length || window.confirm("Reset all completed problems?")) {
      state.completed = {};
      state.activity = [];
      saveProgress();
      renderProblems();
      renderStats();
    }
  });
}

async function init() {
  try {
    const response = await fetch("data.json");
    if (!response.ok) throw new Error("Could not load data.json");
    state.problems = await response.json();
    bindEvents();
    setDailyNote();
    renderProblems();
    renderStats();
  } catch (error) {
    elements.list.innerHTML = `<div class="loading-state">Could not load the problem set. Open this folder through a local server.</div>`;
    console.error(error);
  }
}

init();
