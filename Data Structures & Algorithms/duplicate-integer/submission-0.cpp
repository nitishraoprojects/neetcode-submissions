class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        unordered_map<int, int> mp;

        for(auto a: nums){
            if(mp[a] > 0) return true;
            mp[a]++;
        }
        return false;

    }
};