#ifndef TRIE_H
#define TRIE_H
#include<bits/stdc++.h>
using namespace std;


class trieNode{
public:
    char ch; // character that the trieNode represents
    map<char,trieNode*> hMap; // hash map. Not using unordered map because in the future we may use the sorted nature of the map
    bool isEnd;// represents that the word has ended at this node
    trieNode(char ch,bool isEnd=false)
    {
        this->ch=ch;
        this->isEnd=isEnd;
    }
};
void getStrings(trieNode*root, vector<string> &remainingWords,string s);
class Trie
{
    trieNode*root;
    trieNode* state;// optimizations for trie class for advanced lookups
    int numWords;
public:
    Trie();
    void Insert(string s);
    void Delete(string s);
    bool Search(string s);
    vector<string> AdvanceSearch(string s);
};

#endif // TRIE_H
