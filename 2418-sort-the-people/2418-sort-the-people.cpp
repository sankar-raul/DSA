class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        unordered_map<int, string> pos_map;
        vector<string> order;
        for (int i = 0; i < heights.size(); ++i) {
            pos_map[heights[i]] = names[i];
        }
        sort(heights.begin(), heights.end());
        for (int i = heights.size() - 1; i >= 0; --i) {
            order.push_back(pos_map[heights[i]]);
        }
        return order;
    }
};