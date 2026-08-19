class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        sort(reservedSeats.begin(), reservedSeats.end());
        int current_idx = 0;
        int prev = reservedSeats[0][0];
        int total = 0;
        int start = 1;
        int distinctRows = 0;
        while (current_idx < reservedSeats.size()) {
            int row = reservedSeats[current_idx][0];
            int seat = reservedSeats[current_idx][1];
            if (row != prev) {
                if (start != 10) {
                    total += (9 - start) / 4;
                }
                start = 1;
                distinctRows++;
            }
            if (seat % 2 == 0) {
                int gap = (seat - 1) - start;
                if (gap >= 4) {
                    total += gap / 4;
                }
            } else {
                int gap = (seat - 1) - start;
                if (gap > 4) {
                    total += gap / 4;
                }
            }
            start = seat;
            prev = row;
            current_idx++;
            // if (start != 10) {
            //     total += (9 - start) / 4;
            // }
        }
         if (start != 10) {
            total += (9 - start) / 4;
        }

        // Every completely empty row can have 2 families
        total += (n - (distinctRows + 1)) * 2;

        return total;
    }
};