// Do NOT add any other includes
#include "dict.h"
#include <chrono>
Trie::Trie(){
    root=new TrieNode();
    root->arr=new TrieNode[54];
}
Trie::~Trie(){

}
int index(char a){
    int k;
    int asci=(int)a;
    if(a=='#'){
        k=0;
    }
    else if(a=='$'){
        k=1;
    }
    else if(a=='%'){
        k=2;
    }
    else if(a=='&'){
        k=3;
    }
    else if(a=='*'){
        k=4;
    }
    else if(a=='+'){
        k=5;
    }
    else if(a=='/'){
        k=6;
    }
    else if(asci>=48 && asci<58){
        k=asci-41;
    }
    else if(a=='<'){
        k=17;
    }
    else if(a=='='){
        k=18;
    }
    else if(a=='>'){
        k=19;
    }
    else if(asci>=65 && asci<=90){
        k=asci-45;
    }
    else if(a=='\\'){
        k=46;
    }
    else if(a=='^'){
        k=47;
    }
    else if(a=='_'){
        k=48;
    }
    else if(a=='`'){
        k=49;
    }
    else if(asci>=97 && asci<=122){
        k=asci-77;
    }
    else if(asci>=123 && asci<=126){
        k=asci-73;
    }
    return k;
}
void Trie::insert(string s){
     for(int i=0;i<s.size();i++){
        if(s[i]>='A' and s[i]<='Z'){
            s[i]=s[i]+32;
        }
    }
    TrieNode *curr=root;
    TrieNode* parent;
    parent=root;
    for(auto x:s){
        int k;
        k=index(x);
        if(curr->arr[k].arr!=NULL){
            parent=curr;
            curr=&(curr->arr[k]);
        }
        else{
            curr->arr[k].arr=new TrieNode[54];
            parent=curr;
            curr=&(curr->arr[k]);
        }
    }
    curr->val+=1;
    string d;
    
    curr->data=s;
}
TrieNode* Trie::search(string s){
    TrieNode *curr=root;
    int ans;
    for(auto x:s){
        int k;
        k=index(x);
        if(curr->arr[k].arr!=NULL){
            ans=curr->val;
            curr=&(curr->arr[k]);
        }
        else{
            ans=0;
            return NULL;
        }
    }
    return curr;
}

void delete_trie(TrieNode *root){
    if(root->arr==NULL or root==NULL){
        return;
    }
    for(int i=0;i<54;i++){
        TrieNode *curr=&(root->arr[i]);
        delete_trie(curr);
    }
    delete [] root->arr;
    // string *c= &root->data;
    // delete c;
}
Dict::Dict(){
    dictionary=new Trie();
}

Dict::~Dict(){
    delete_trie(dictionary->root);
    delete dictionary->root;
    delete dictionary;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string s;
    for(auto x:sentence){
        if(x=='.'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x==','){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x=='-'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x==':'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x=='!'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x=='\"'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x=='\''){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x=='('){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x==')'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x=='?'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x==']'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x=='['){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x==';'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x=='@'){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else if(x==' '){
            if(s!=""){
                dictionary->insert(s);
            }
            s="";
        }
        else{
            s+=x;
        }
    }
    if(s!=""){
        dictionary->insert(s);
    }
}

long long Dict::get_word_count(string word){
    TrieNode *e=dictionary->search(word);
    if (e==NULL){
        return 0;
    }
    return e->val;
}

void Dict::dump_dictionary(string filename){
    vector<TrieNode*> stk;
    ofstream file;
    file.open(filename);
    
    stk.push_back(dictionary->root);
    while(!stk.empty()){
        TrieNode * c=stk.back();
        stk.pop_back();
        if(c->data!=""){
            file<<c->data<<","<<c->val<<endl;
        }
        for(int i=0;i<54;i++){
            if(c->arr[i].arr!=NULL){
                stk.push_back(&(c->arr[i]));
            }
            
        }
    }
    file.close();
}

// int main(){
//     Dict *e=new Dict();
//     e->insert_sentence(0,0,0,0,"a");
//     e->insert_sentence(0,0,0,0,"a");
//     e->insert_sentence(0,0,0,0,"abc");
//     e->insert_sentence(0,0,0,0,"ANd 0,0 1/2d 3983 99");
//     // e->insert_sentence(0,0,0,0,"and mandy sandy candy andy and and mandy");
//     // e->insert_sentence(0,0,0,0,"and mandy sandy candy andy and and mandy");
//     // e->insert_sentence(0,0,0,0,"and mandy sandy candy andy and and mandy");
//     // e->insert_sentence(0,0,0,0,"and mandy syyuyuyuyuuyuyuyyuyuyuyuyuyuyuyuyuyuyuyuyuyuyu candy andy and and mandy");
//     e->dump_dictionary("hi.txt");
//     delete e;
// }