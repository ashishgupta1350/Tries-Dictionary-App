#ifndef TRIE_CPP
#define TRIE_CPP
#include"trie.h"


trieNode* createNode(char ch,bool isEnd=false)
{
    trieNode* tn=new trieNode(ch,isEnd);
    return tn;
}

Trie::Trie()
{
    root=createNode('$');
    state=NULL;
    numWords=0;
}
void Trie::Insert(string s){
    trieNode*temp=root;
        for(unsigned int i=0;i<s.length();i++)
        {
            char ch=s[i];
            // cout<<"processing : "<<s[i]<<" ";
            // cout<<temp->hMap.count(ch)<<endl;
            if( temp!=NULL && temp->hMap.count(ch)>0)
            {
                temp=temp->hMap[ch];
            }
            else{
                trieNode* n=createNode(ch);
                temp->hMap[ch]=n;
                temp=temp->hMap[ch];
            }

        }
        // check this
        if(temp!=NULL){
            temp->isEnd=true;
        }
        numWords++;
        return;
}
void Trie::Delete(string s)
{
    trieNode*temp=root;
    for(unsigned int i=0;i<s.length();i++)
    {
        char ch=s[i];
        if(temp->hMap.find(ch)!=temp->hMap.end())
        {
            temp=temp->hMap[ch];
        }
        else return;
    }
    // check this
    if(temp!=NULL && temp->isEnd==true){
        temp->isEnd=false;
        // if(temp->hMap.size()==0)
        // {

        // }
    }
    numWords--;
    return;
}
bool Trie::Search(string s){
    trieNode*temp=root;
    for(unsigned int i=0;i<s.length();i++)
    {
        char ch=s[i];
        if(temp->hMap.find(ch)!=temp->hMap.end())
        {
            temp=temp->hMap[ch];
        }
        else return false;
    }
    // check this
    if(temp!=NULL && temp->isEnd==true){
        return true;
    }
    return false;
}
vector<string> Trie::AdvanceSearch(string s)
{
    trieNode*temp=root;
    vector<string> remainingWords;

    for(unsigned int i=0;i<s.length();i++)
    {
        char ch=s[i];
        if(temp->hMap.find(ch)!=temp->hMap.end())
        {
            temp=temp->hMap[ch];
        }
        else return remainingWords;
    }
    // if(temp!=NULL && temp->isEnd==true){
    // 	remainingWords.push_back(s);
    // }
    // we pushed the last word in the remainingWords, now time to push rest of the words that follow temp;
    getStrings(temp,remainingWords,s);// s + something will be pushed inside it
    return remainingWords;
}


void getStrings(trieNode*root, vector<string> &remainingWords,string s)
{
    if(root->hMap.size()==0)
    {
        if(root->isEnd)
            remainingWords.push_back(s);
        return; // this is return call
    }
    else if(root->isEnd==true)
    {
            remainingWords.push_back(s); // this will push the current string s as well
    }

    for(auto it=root->hMap.begin();it!=root->hMap.end();it++)
    {
        getStrings(root->hMap[it->first],remainingWords,s+it->first);
    }
    return;
}






#endif // TRIE_H

