class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int n = grid.size() * grid.size();
        int sum = n * (n + 1) / 2;
        int totalSum = 0;
        unordered_map<int, int> freq;
        int reapeatingNumber;
        for (vector<int> row : grid) {
            for (int num : row) {
                totalSum += num;
                if (++freq[num] == 2) {
                    reapeatingNumber = num;
                }
            }
        }
        int missingNumber = sum - (totalSum - reapeatingNumber);
        return { reapeatingNumber, missingNumber };
    }
};