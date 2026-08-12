class Solution {
public:
    bool checkPerfectNumber(int num) {
        int i = 1;
        int sum = 0;
        while(i < num/2 + 1){
            if(num % i == 0){
                sum += i;
            }
            i++;
        }
        return num == sum;
    }
};