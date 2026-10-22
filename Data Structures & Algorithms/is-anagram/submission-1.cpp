class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length() != t.length()) return false;
        unordered_map<char, int> mp;

        for(auto a: s){
            mp[a]++;
        }

        for(auto a: t){
            mp[a]--;
        }

        for(auto a: mp){
            if(a.second < 0) return false;
        }

        return true;
    }
};
