class Solution {
public:
    int maxNumberOfBalloons(string text) {
        unordered_map<char, int> map;
        for (char ch : text) {
            map[ch]++;
        }
        int min_count = INT_MAX;
        string b = "balon";
        for (char ch : b) {
            min_count = min(min_count, ch == 'l' || ch == 'o' ? map[ch] / 2 : map[ch]);
        }
        return min_count;
    }
};