class Solution {
public:
    void reverseAndInvert(vector<int>& arr) {
        int i = 0, j = arr.size() - 1;
        while (i < j) {
            swap(arr[i], arr[j]);
            arr[i] = !arr[i];
            arr[j] = !arr[j];
            i++;
            j--;
        }
        if (i == j)
            arr[i] = !arr[i];
    }
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
        for (int i = 0; i < image.size(); ++i) {
            reverseAndInvert(image[i]);
        }
        return image;
    }
};