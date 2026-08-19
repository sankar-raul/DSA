class Solution {
public:
    vector<int> toggleLightBulbs(vector<int>& bulbs) {
        map<int, int> freq;
        for (int bulb : bulbs) {
            freq[bulb] ^= 1;
        }
        vector<int> ons;
        for (auto& pair : freq) {
            if (pair.second) ons.push_back(pair.first); 
        }
        return ons;
    }
};