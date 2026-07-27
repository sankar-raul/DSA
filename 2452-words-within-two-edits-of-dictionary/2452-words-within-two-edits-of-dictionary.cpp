class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        vector<string> words;
       for (string q : queries) {
        for (string d : dictionary) {
            int wordDiff = 0;
            for (int i = 0; i < q.size(); ++i) {
                if (q[i] != d[i]) {
                    ++wordDiff;
                }
            }
            if (wordDiff <= 2) {
                words.push_back(q);
                break;
            }
        }
       }
       return words;
    }
};