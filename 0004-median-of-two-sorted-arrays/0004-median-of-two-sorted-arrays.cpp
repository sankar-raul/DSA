class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size(), i = 0, j = 0;
        int mid = (m + n) / 2;
        for (int k = 0; k < mid; ++k) {
            int left = i < n ? nums1[i] : 1e9;
            int right = j < m ? nums2[j] : 1e9;
            if (left < right) {
                i++;
            } else {
                j++;
            }
        }
        double res;
        if (m+n != 1) {
            if ((m+n) & 1) {
                res = i >= n ? nums2[j] : j >= m ? nums1[i] : min(nums1[i], nums2[j]);
            } else {
                int curr = (i >= n) ? nums2[j] :
                    (j >= m) ? nums1[i] :
                    min(nums1[i], nums2[j]);
                int prev = (i == 0) ? nums2[j - 1] :
                    (j == 0) ? nums1[i - 1] :
                    max(nums1[i - 1], nums2[j - 1]);

                res = (curr + prev) / 2.0;
                }
        } else {
            res = n ? nums1[0] : nums2[0];
        }
        return res;
    }
};