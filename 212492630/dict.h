// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class TrieNode{
    public:
        long long val=0;
        TrieNode*arr=NULL;
        string data;
        
};
class Trie{
    public:
        TrieNode *root;
        Trie();
        ~Trie();
        void insert(string s);
        TrieNode* search(string s);
};
class Dict {
private:
    
public:
    Trie* dictionary;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    long long get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};