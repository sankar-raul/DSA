class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end());
        int count = 0;
        for (int price : costs) {
            if (coins - price >= 0) {
                coins -= price;
                count++;
                if (!price) return count;
            } else {
                return count;
            }
        }
        return count;
    }
};