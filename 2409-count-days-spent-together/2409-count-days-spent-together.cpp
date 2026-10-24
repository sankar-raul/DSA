class Solution {
public:
    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int get_day_count(string& date) {
        int month = (date[0] - '0') * 10 + (date[1] - '0');
        int day = (date[3] - '0') * 10 + (date[4] - '0');
        int count = days[month - 1] + day;
        return count;
    }
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        for (int i = 1; i < 13; ++i) {
            days[i] += days[i-1];
        }
        int alice[] = {get_day_count(arriveAlice), get_day_count(leaveAlice)};
        int bob[] = {get_day_count(arriveBob), get_day_count(leaveBob)};
        int start = max(alice[0], bob[0]);
        int end = min(alice[1], bob[1]) + 1;
        int gap = end - start;
        return gap > 0 ? gap : 0;
    }
};