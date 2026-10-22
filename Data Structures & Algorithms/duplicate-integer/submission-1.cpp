class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        unordered_set<int> set;

        for(auto a: nums){
            if(set.count(a)) return true;
            set.insert(a);
        }
        return false;

    }
};