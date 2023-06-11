class Solution {
public:
    bool isAnagram(string s, string t) {

    if (s.size()!=t.size()) return false;

    map<char, int> first;
    map<char, int> second;

    int i;
    for (i = 0; i<s.size();i++)
    {
        first[s[i]]++;    // Incrementing the value for the key
        second[t[i]]++;   //  Incrementing the value for the key
    }
    auto it1 = first.begin();   // Iterators
    auto it2 = second.begin();
    while(it1!=first.end()&&it2!=second.end())
    {
        if (it1->second!=it2->second ||it1->first!=it2->first) return false;
        it1++;
        it2++;
    }

    return true;
    }
};
