class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length() != t.length()) return false;
        unordered_map<char, int> mp;
        unordered_map<char, int> mp1;
        for(auto a: s){
            mp[a]++;
        }

        for(auto a: t){
            mp1[a]++;
        }

        for(auto a: mp){
            if(mp[a.first] != mp1[a.first]) return false;
        }

        return true;
    }
};
