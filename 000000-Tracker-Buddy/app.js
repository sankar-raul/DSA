const STORAGE_KEY = "tracker-buddy-progress-v1";
const STREAK_KEY = "tracker-buddy-activity-v1";
const TOPICS_KEY = "tracker-buddy-show-topics-v1";
const SOUND_KEY = "tracker-buddy-sounds-v1";

const state = {
  problems: [],
  completed: loadJson(STORAGE_KEY, {}),
  activity: loadJson(STREAK_KEY, []),
  showTopics: localStorage.getItem(TOPICS_KEY) === "true",
  soundOn: localStorage.getItem(SOUND_KEY) !== "false",
  filter: "all",
  topic: "all",
  search: "",
  sort: "number"
};

const elements = {
  particleCanvas: document.querySelector("#cursor-particles"),
  list: document.querySelector("#problem-list"),
  empty: document.querySelector("#empty-state"),
  resultCount: document.querySelector("#result-count"),
  search: document.querySelector("#search-input"),
  sort: document.querySelector("#sort-select"),
  topic: document.querySelector("#topic-select"),
  solved: document.querySelector("#solved-count"),
  total: document.querySelector("#total-count"),
  remaining: document.querySelector("#remaining-count"),
  streak: document.querySelector("#streak-count"),
  ring: document.querySelector("#progress-ring"),
  ringValue: document.querySelector("#ring-value"),
  note: document.querySelector("#daily-note"),
  reset: document.querySelector("#reset-button"),
  topicsToggle: document.querySelector("#topics-toggle"),
  topicsToggleLabel: document.querySelector("#topics-toggle-label"),
  soundToggle: document.querySelector("#sound-toggle"),
  soundIcon: document.querySelector("#sound-icon"),
  soundLabel: document.querySelector("#sound-label")
};

function initCursorParticles() {
  const canvas = elements.particleCanvas;
  const canAnimate = window.matchMedia("(min-width: 641px) and (pointer: fine) and (prefers-reduced-motion: no-preference)").matches;
  if (!canvas || !canAnimate) return;
  const context = canvas.getContext("2d");
  const particles = [];
  const ripples = [];
  let pointer = { x: -100, y: -100 };
  let previousPointer = { x: -100, y: -100 };
  let frameRequested = false;

  function resize() {
    const pixelRatio = Math.min(window.devicePixelRatio || 1, 2);
    canvas.width = window.innerWidth * pixelRatio;
    canvas.height = window.innerHeight * pixelRatio;
    canvas.style.width = `${window.innerWidth}px`;
    canvas.style.height = `${window.innerHeight}px`;
    context.setTransform(pixelRatio, 0, 0, pixelRatio, 0, 0);
  }

  function addParticles(distance) {
    const amount = Math.min(Math.ceil(distance / 8), 5);
    for (let index = 0; index < amount; index += 1) {
      const progress = (index + 1) / amount;
      const x = previousPointer.x + (pointer.x - previousPointer.x) * progress;
      const y = previousPointer.y + (pointer.y - previousPointer.y) * progress;
      const dust = Math.random() < .48;
      particles.push({
        x: x + (Math.random() - .5) * 3,
        y: y + (Math.random() - .5) * 3,
        previousX: x,
        previousY: y,
        dust,
        size: Math.random() * 2.4 + 1,
        spark: !dust && Math.random() < .2,
        rotation: Math.random() * Math.PI,
        life: 1,
        decay: dust ? Math.random() * .009 + .009 : Math.random() * .01 + .018,
        driftX: (Math.random() - .5) * (dust ? .18 : .32),
        driftY: (Math.random() - .5) * (dust ? .18 : .32)
      });
    }
    if (particles.length > 90) particles.splice(0, particles.length - 90);
  }

  function draw() {
    frameRequested = false;
    context.clearRect(0, 0, window.innerWidth, window.innerHeight);
    for (let index = particles.length - 1; index >= 0; index -= 1) {
      const particle = particles[index];
      particle.previousX = particle.x;
      particle.previousY = particle.y;
      particle.life -= particle.decay;
      particle.x += particle.driftX;
      particle.y += particle.driftY;
      if (particle.life <= 0) {
        particles.splice(index, 1);
        continue;
      }
      context.globalAlpha = particle.life * .5;
      context.strokeStyle = "#c4ff3d";
      context.lineWidth = particle.size * .75;
      context.lineCap = "round";
      context.shadowBlur = 10;
      context.shadowColor = "#c4ff3d";
      context.beginPath();
      context.moveTo(particle.previousX, particle.previousY);
      context.lineTo(particle.x, particle.y);
      context.stroke();
      context.globalAlpha = particle.life * (particle.dust ? .28 : .78);
      context.fillStyle = particle.dust ? "#a9c978" : "#ddff8b";
      context.beginPath();
      context.arc(particle.x, particle.y, particle.dust ? particle.size * .55 : particle.size, 0, Math.PI * 2);
      context.fill();
      if (particle.spark) {
        const flare = particle.size * 4.5 * particle.life;
        const cosine = Math.cos(particle.rotation);
        const sine = Math.sin(particle.rotation);
        context.globalAlpha = particle.life * .82;
        context.strokeStyle = "#f1ffc7";
        context.lineWidth = .8;
        context.beginPath();
        context.moveTo(particle.x - cosine * flare, particle.y - sine * flare);
        context.lineTo(particle.x + cosine * flare, particle.y + sine * flare);
        context.moveTo(particle.x + sine * flare, particle.y - cosine * flare);
        context.lineTo(particle.x - sine * flare, particle.y + cosine * flare);
        context.stroke();
      }
    }
    for (let index = ripples.length - 1; index >= 0; index -= 1) {
      const ripple = ripples[index];
      ripple.life -= .035;
      ripple.radius += 2.8;
      if (ripple.life <= 0) {
        ripples.splice(index, 1);
        continue;
      }
      context.globalAlpha = ripple.life * .62;
      context.strokeStyle = "#c4ff3d";
      context.lineWidth = 1.2;
      context.shadowBlur = 14;
      context.shadowColor = "#c4ff3d";
      context.beginPath();
      context.arc(ripple.x, ripple.y, ripple.radius, 0, Math.PI * 2);
      context.stroke();
      context.globalAlpha = ripple.life * .32;
      context.beginPath();
      context.arc(ripple.x, ripple.y, ripple.radius * .58, 0, Math.PI * 2);
      context.stroke();
      for (let drop = 0; drop < 4; drop += 1) {
        const angle = ripple.rotation + drop * (Math.PI / 2);
        const dropDistance = ripple.radius * .82;
        context.fillStyle = "#efffc1";
        context.beginPath();
        context.arc(ripple.x + Math.cos(angle) * dropDistance, ripple.y + Math.sin(angle) * dropDistance, 1.4 * ripple.life, 0, Math.PI * 2);
        context.fill();
      }
    }
    context.globalAlpha = 1;
    context.shadowBlur = 0;
    if (particles.length || ripples.length) requestAnimationFrame(draw);
  }

  window.addEventListener("resize", resize, { passive: true });
  window.addEventListener("mousemove", (event) => {
    previousPointer = pointer.x < 0 ? { x: event.clientX, y: event.clientY } : pointer;
    pointer = { x: event.clientX, y: event.clientY };
    const distance = Math.hypot(pointer.x - previousPointer.x, pointer.y - previousPointer.y);
    addParticles(distance);
    if (!frameRequested) {
      frameRequested = true;
      requestAnimationFrame(draw);
    }
  }, { passive: true });
  window.addEventListener("click", (event) => {
    ripples.push({ x: event.clientX, y: event.clientY, radius: 3, life: 1, rotation: Math.random() * Math.PI });
    if (ripples.length > 8) ripples.shift();
    if (!frameRequested) {
      frameRequested = true;
      requestAnimationFrame(draw);
    }
  }, { passive: true });
  resize();
}

let audioContext;

function playSound(kind) {
  if (!state.soundOn) return;
  if (!window.AudioContext && !window.webkitAudioContext) return;
  audioContext ??= new (window.AudioContext || window.webkitAudioContext)();
  if (audioContext.state === "suspended") audioContext.resume();
  const settings = {
    complete: { start: 520, end: 760, duration: .18, volume: .08 },
    undo: { start: 360, end: 250, duration: .16, volume: .06 },
    select: { start: 680, end: 820, duration: .12, volume: .05 },
    reset: { start: 280, end: 170, duration: .24, volume: .08 }
  }[kind] || { start: 500, end: 650, duration: .14, volume: .06 };
  const oscillator = audioContext.createOscillator();
  const gain = audioContext.createGain();
  const now = audioContext.currentTime;
  oscillator.type = "triangle";
  oscillator.frequency.setValueAtTime(settings.start, now);
  oscillator.frequency.exponentialRampToValueAtTime(settings.end, now + settings.duration);
  gain.gain.setValueAtTime(0, now);
  gain.gain.linearRampToValueAtTime(settings.volume, now + .01);
  gain.gain.exponentialRampToValueAtTime(.001, now + settings.duration);
  oscillator.connect(gain).connect(audioContext.destination);
  oscillator.start(now);
  oscillator.stop(now + settings.duration + .02);
}

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
    const problemTopics = [...new Set([...(problem.tags || []), ...(problem.topics || [])])];
    const matchesTopic = state.topic === "all" || problemTopics.includes(state.topic);
    const searchableText = [problem.title, problem.slug, problem.source, ...(problem.tags || []), ...(problem.topics || [])].join(" ").toLowerCase();
    const matchesSearch = !query || searchableText.includes(query) || String(problem.number).includes(query);
    return matchesDifficulty && matchesTopic && matchesSearch;
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

function formatDate(value) {
  if (!value) return "Unknown date";
  const date = new Date(value);
  return Number.isNaN(date.getTime()) ? value : date.toLocaleDateString(undefined, { year: "numeric", month: "short", day: "numeric" });
}

function formatAcceptance(value) {
  return value == null ? "Acceptance n/a" : `Acceptance ${value}%`;
}

function renderProblems() {
  const visibleProblems = getVisibleProblems();
  elements.resultCount.textContent = `${visibleProblems.length} ${visibleProblems.length === 1 ? "problem" : "problems"}`;
  elements.list.innerHTML = visibleProblems.map((problem) => {
    const isDone = Boolean(state.completed[problem.id]);
    const topics = [...new Set([...(problem.tags || []), ...(problem.topics || [])])];
    const topicMarkup = topics.length ? topics.map((topic) => `<span class="topic-chip">${escapeHtml(topic)}</span>`).join("") : `<span class="topic-empty">No topics</span>`;
    return `
      <article class="problem-row${isDone ? " is-done" : ""}${state.showTopics ? " topics-visible" : ""}" data-source="${escapeHtml(problem.source || "unknown")}" data-created-at="${escapeHtml(problem.created_at || "")}" data-updated-at="${escapeHtml(problem.updated_at || "")}" data-acceptance-rate="${escapeHtml(problem.acceptance_rate ?? "")}" data-tags="${escapeHtml((problem.tags || []).join(","))}" data-topics="${escapeHtml((problem.topics || []).join(","))}">
        <span class="problem-number">#${String(problem.number).padStart(4, "0")}</span>
        <div class="problem-info">
          <h3 class="problem-title"><a class="problem-title-link" href="${escapeHtml(problem.url)}" target="_blank" rel="noreferrer">${escapeHtml(problem.title)}</a></h3>
          <span class="problem-slug">${escapeHtml(problem.slug)} · ${escapeHtml(problem.source || "unknown")}</span>
          <div class="topic-list" aria-label="Topics">${topicMarkup}</div>
        </div>
        <div class="problem-facts"><span class="difficulty difficulty-${escapeHtml(problem.difficulty)}">${escapeHtml(problem.difficulty)}</span><span class="acceptance-rate">${escapeHtml(formatAcceptance(problem.acceptance_rate))}</span><span class="updated-date" title="Created ${escapeHtml(formatDate(problem.created_at))}">Updated ${escapeHtml(formatDate(problem.updated_at))}</span></div>
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
  playSound(isCompleting ? "complete" : "undo");
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
  updateTopicsToggle();
  updateSoundToggle();
  elements.soundToggle.addEventListener("click", () => {
    state.soundOn = !state.soundOn;
    localStorage.setItem(SOUND_KEY, String(state.soundOn));
    updateSoundToggle();
    if (state.soundOn) playSound("select");
  });
  elements.topicsToggle.addEventListener("click", () => {
    state.showTopics = !state.showTopics;
    localStorage.setItem(TOPICS_KEY, String(state.showTopics));
    updateTopicsToggle();
    playSound("select");
    renderProblems();
  });
  elements.search.addEventListener("input", (event) => {
    state.search = event.target.value;
    renderProblems();
  });
  elements.sort.addEventListener("change", (event) => {
    state.sort = event.target.value;
    playSound("select");
    renderProblems();
  });
  elements.topic.addEventListener("change", (event) => {
    state.topic = event.target.value;
    playSound("select");
    renderProblems();
  });
  document.querySelectorAll("[data-filter]").forEach((button) => {
    button.addEventListener("click", () => {
      state.filter = button.dataset.filter;
      document.querySelectorAll("[data-filter]").forEach((item) => item.classList.toggle("active", item === button));
      playSound("select");
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
      playSound("reset");
      renderProblems();
      renderStats();
    }
  });
}

function updateTopicsToggle() {
  elements.topicsToggle.classList.toggle("is-on", state.showTopics);
  elements.topicsToggle.setAttribute("aria-pressed", String(state.showTopics));
  elements.topicsToggleLabel.textContent = state.showTopics ? "Hide topics" : "Show topics";
}

function updateSoundToggle() {
  elements.soundToggle.classList.toggle("is-on", state.soundOn);
  elements.soundToggle.setAttribute("aria-pressed", String(state.soundOn));
  elements.soundIcon.textContent = state.soundOn ? "♫" : "×";
  elements.soundLabel.textContent = state.soundOn ? "Sound on" : "Sound off";
}

async function init() {
  try {
    if ("serviceWorker" in navigator) navigator.serviceWorker.register("sw.js").catch((error) => console.warn("Offline install support unavailable", error));
    const response = await fetch("leetcode_merged.json");
    if (!response.ok) throw new Error("Could not load leetcode_merged.json");
    state.problems = await response.json();
    initCursorParticles();
    const topics = [...new Set(state.problems.flatMap((problem) => [...(problem.tags || []), ...(problem.topics || [])]))].sort();
    elements.topic.insertAdjacentHTML("beforeend", topics.map((topic) => `<option value="${escapeHtml(topic)}">${escapeHtml(topic)}</option>`).join(""));
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
