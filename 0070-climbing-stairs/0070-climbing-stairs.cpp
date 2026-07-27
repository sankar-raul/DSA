class Solution {
public:
    int climbStairs(int n) {
        int steps = 0;
        if (n <= 2) {
            return n;
        }
        int nothing[] = {1, 2};
        for (int i = 3; i <= n; ++i) {
            steps = nothing[0] + nothing[1];
            nothing[0] = nothing[1];
            nothing[1] = steps;
        }
        return steps;
    }
};