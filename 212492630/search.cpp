// Do NOT add any other includes
#include <iostream>
#include <fstream>
#include <string>
#include "search.h"

// #include "Node.cpp"


// void Array_Generator( string &str, int* process) {
    
//     for (int i = 0; i < 256; i++) {
//         process[i] = -1; }
 
   
//     for (int i = 0; i < str.size(); i++) {
//         process[(int) str[i]] = i; }
// } 
 
// void AA_search( string &pat, Node_*txt,int *process,int &n_matches,Node*&head,Node *&tail) {

//     int m = pat.size(); 
//     int n = txt->sentence.size(); 
//     int ans = 0; 
//     while(ans <= (n - m)) {
    
//         int j = m - 1; 
//         while(j >= 0 && pat[j] == txt->sentence[ans + j]){ 
//             j--; }
 
//         //cout<<j;
//         if (j < 0) {
        
//             n_matches+=1;
            
//             Node* x=new Node(txt->book_code,txt->page,txt->paragraph,txt->sentence_no,ans);
//             tail->right=x;
//             tail=x;
//             if(n_matches==1){
//                 head=tail;
                
//             }
//             ans += (ans + m < n)? m-process[txt->sentence[ans + m]] : 1; 
 
//         } 
 
//         else{
//             ans += max(1, j - process[txt->sentence[ans + j]]); }
//     } 
// } 
vector<string> convertWord(string &sentence){
     vector<string> ans;
     string s;
     for(auto x:sentence){
        if(x=='.'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x==','){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x=='-'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x==':'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x=='!'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x=='\"'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x=='\''){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x=='('){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x==')'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x=='?'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x==']'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x=='['){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x==';'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x=='@'){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else if(x==' '){
            if(s!=""){
                ans.push_back(s);
            }
            s="";
        }
        else{
            s+=x;
        }
    }
    if(s!=""){
        ans.push_back(s);
    }
    return ans;
}
SearchEngine::SearchEngine(){
    head=new Node();
    tail=head;
    sentinel=head;
    dict_std=new Dict();
    dict_corp=new Dict();
    ifstream file;
    file.open("unigram_freq.csv");
    string line;
    getline(file, line);
    while(getline(file,line)){
        string x;
        string z;
        bool flag=false;
        for(auto y:line){
            if(y==','){
               flag=true;
            }else if(flag){
                z+=y;
            }else{
                x+=y;
            }
        }
        //cout<<x<<" "<<z<<"\n";
        
        dict_std->insert_sentence(0,0,0,0,x);
        
        TrieNode * e=dict_std->dictionary->search(x);
        e->val=stoll(z);
        

    }
    //cout<<dict_std->get_word_count("it");

}

SearchEngine::~SearchEngine(){
    Node *curr=head;
    while(curr!=NULL){
        Node *nxt=curr->right;
        curr->right=NULL;
        delete curr;
        curr=nxt;
    }
    if(head!=sentinel){
        delete sentinel;
    }
    head=NULL;
    tail=NULL;
    sentinel=NULL;
    for(int i=0;i<l.size();i++){
        delete l[i];
    }
    l.clear();
}


void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    Node_* e=new Node_();
     for(int i=0;i<sentence.size();i++){
        if(sentence[i]>='A' and sentence[i]<='Z'){
            sentence[i]=sentence[i]+32;
        }
    }
    e->book_code=book_code;
    e->page=page;
    e->paragraph=paragraph;
    e->sentence_no=0;
    e->sentence=convertWord(sentence);
    l.push_back(e);

    dict_corp->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
}

Node* SearchEngine::search(vector<string> pattern, int& n_matches){
    
    for(int j=0;j<pattern.size();j++){
        for(int i=0;i<pattern[j].size();i++){
            if(pattern[j][i]>='A' and pattern[j][i]<='Z'){
                pattern[j][i]=pattern[j][i]+32;
            }
        }
    }
    
    vector<double> score_words;
    for(auto x:pattern){
        long long freq_std=dict_std->get_word_count(x);
        long long freq_corp=dict_corp->get_word_count(x);
        double score=(double)(freq_corp+1)/(double)(freq_std+1);
        score_words.push_back(score);
    }
    //return new Node();
    
    int process[256];
	// Preprocess the pattern (calculate lps[] array)
	//Array_Generator(string pattern,process);
    //int n_matches=0;
     long double freq_curr=0;
     int cur_para=l[0]->paragraph;
     int cur_book=l[0]->book_code;
     int cur_page=l[0]->page;
     vector<heapnode*> para;
     for(int i=0;i<l.size();i++){
       if((l[i]->paragraph!=cur_para or l[i]->page!=cur_page or l[i]->book_code!=cur_book) and freq_curr>=0){
            heapnode *e=new heapnode(l[i-1]->book_code,l[i-1]->page,l[i-1]->paragraph,freq_curr);
            para.push_back(e);
            freq_curr=0;
            cur_para=l[i]->paragraph;
            cur_book=l[i]->book_code;
            cur_page=l[i]->page;

       }
       for(auto x:l[i]->sentence){
                //cout<<x<<" ";
                for(int j=0;j<pattern.size();j++){
                    //cout<<pattern[j]<<" ";
                    if(x==pattern[j]){
                        //cout<<score_words[j]<<"hehe";
                        freq_curr+=score_words[j];

                    }
                }
       }
     } 
     //cout<<freq_curr;
     if(freq_curr>=0){
            heapnode *e=new heapnode(l[l.size()-1]->book_code,l[l.size()-1]->page,l[l.size()-1]->paragraph,freq_curr);
            para.push_back(e);
            freq_curr=0;
            

       }
    he=new heap();
    he->buildheap(para);
    if(n_matches==0){
        return NULL;
    }

    return head;
}



