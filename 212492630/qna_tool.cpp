#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

#define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"

QNA_tool::QNA_tool(){
   se=new SearchEngine();
   
}

QNA_tool::~QNA_tool(){
    delete se;
    
}
void insertcorpus(SearchEngine *se,int n);
void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // static int c=0;
    // c++;
    // if(c==1){
    //     for(int i=1;i<=98;i++){
    //         insertcorpus(se,i);
    //     }
    // }
    se->insert_sentence(book_code, page, paragraph,sentence_no,sentence);
    
}
vector<string> convertword(string &sentence){
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
Node* QNA_tool::get_top_k_para(string question, int k) {
    // for(int i=1;i<=98;i++){
    //         insertcorpus(se,i);
    //     }
    vector<string> pattern=convertword(question);
    int n_matches=0;
    
    se->search(pattern,n_matches);
    //return new Node();
    return se->he->getTopK(k);
    
}

void insertcorpus(SearchEngine *se,int n){
    ifstream read_works;
    string ins;
    int arr[4];
    read_works.open("txtfiles/mahatma-gandhi-collected-works-volume-"+to_string(n)+".txt");
        while (read_works.peek() != EOF) {
            getline(read_works, ins);
            string info = "";
            string to_insert = "";
            int arrc = 0;
            bool flag1 = false, flag2 = false;

            for (auto c: ins) {
                if (flag1) {
                    if (flag2) {
                        to_insert = to_insert + c;
                    }
                    else
                        flag2 = true;
                } else {
                    if (c == ',') {
                        if (arrc == 0) {
                            arr[arrc] = stoi(info.substr(2, info.length() - 2));}
                        else {
                            arr[arrc] = stoi(info);
                        }
                        info = "";
                        arrc++;
                    } else {
                        info = info + c; 
                        if (c == ')')
                            flag1 = true;
                    }
                }
            }
            se->insert_sentence(arr[0], arr[1], arr[2], arr[3], to_insert);
        }
}
void QNA_tool::query(string question, string filename){
    // for(int i=1;i<=98;i++){
    //         insertcorpus(se,i);
    //     }
        vector<string> pattern=convertword(question);
    int n_matches=0;
    
    se->search(pattern,n_matches);
    //return new Node();
    query_llm(filename,se->he->getTopK(7),7,"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",question);
    // insertcorpus(se);
    // int n=0;
    // se->search(convertWord(question),n);
    // query_llm("api_call.py",se->he->getTopK(10),10,"s");
    // std::cout << "Q: " << question << std::endl;
    // std::cout << "A: Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}
// int main(){
//     QNA_tool* s=new QNA_tool();
//     Node* head=s->get_top_k_para("What were Gandhi's views on the manner of how one should eat?",8);
//     //cout<<"hi";
//     while(head!=NULL){
//         cout<<head->book_code<<" "<<head->page<<" "<<head->paragraph<<"\n";
//         head=head->right;
//     }
    
    
// }