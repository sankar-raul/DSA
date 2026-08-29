class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int costA = 0;
        vector<int> refunds;
        for (auto &cost : costs) {
            costA += cost[0];
            refunds.push_back(cost[1] - cost[0]);
        }
        sort(refunds.begin(), refunds.end());
        int n = costs.size() / 2;
        for (int i = 0; i < n; ++i) {
            costA += refunds[i];
        }
        return costA;
    }
};