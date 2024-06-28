// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "dict.h"
//#include "heap.cpp"
using namespace std;
#include<iostream>
#include<vector>
using namespace std;
 #include "Node.h"
class heapnode{
    public:
    int book;
    int pg;
    int paragraph;
    double score;
    heapnode(int b,int p,int pa,double s){
        book=b;
        pg=p;
        paragraph=pa;
        score=s;
    }
};
class heap{
    public:
    vector<heapnode*> arr;
    heap(){

    }
    void swap_(int a,int b){
        heapnode* temp=arr[a];
        arr[a]=arr[b];
        arr[b]=temp;
    }
    // void heapifyUp(int i){
    //     if(i==0){
    //         return;
    //     }
    //     int p=(i-1)/2;
    //     if(arr[p]->score<arr[i]->score){
    //         swap_(p,i);
    //         heapifyUp(p);
    //     }

    // }
    // void insert(heapnode*val){
    //     arr.push_back(val);
    //     heapifyUp(arr.size()-1);
    // }
    void heapifyDown(int i){
        int l=2*i+1;
        int r=2*i+2;
        int large=i;
        if(l>=arr.size()){
            return;
        }
        if(arr[l]->score>arr[large]->score){
            large=l;
        }
        if(r<arr.size() and arr[r]->score>arr[large]->score){
            large=r;
        }
        if(large!=i){
            swap_(large,i);
            heapifyDown(large);
        }

    }

    heapnode* pop(){
        if(arr.size()==0){
            return NULL;
        }
        heapnode* ans=arr[0];
        arr[0]=arr.back();
        arr.pop_back();
        heapifyDown(0);
        return ans;

    }
    void buildheap(vector<heapnode*>&a){
        arr=a;
        int n=arr.size();
        for(int i=n/2 -1;i>-1;i--){
            heapifyDown(i);
        }
    }

    Node * getTopK(int k){
        Node *head=NULL;
        Node *tail=NULL;
        for(int i=1;i<=k;i++){
            heapnode*c=this->pop();
            Node *e=new Node();
            e->book_code=c->book;
            e->page=c->pg;
            e->paragraph=c->paragraph;
            e->right=NULL;
            e->left=NULL;
            if(head==NULL){
                head=e;
                tail=e;
                //head->right=NULL;
                //tail->right=NULL;
            }else{
                tail->right=e;
                //e->left=tail;
                tail=tail->right;
                //tail->right=NULL;
            }
        }
        Node *ans=head;
        return ans;
    }

    

};

// int main(){
//     heapnode* a=new heapnode(1,2,3,2.97);
//     heapnode* b=new heapnode(2,2,3,1.99);
//     heapnode* c=new heapnode(3,2,3,2.99);
//     heap *h=new heap();
//     h->buildheap({a,b,c});
//     for(auto x:h->arr){
//         cout<<x->score<<" ";
//     }
//     cout<<"\n";
//     // cout<<h->pop()->score<<" ";
//     // cout<<h->pop()->score<<" ";
//     Node *head=h->getTopK(2);
//     Node *curr=head;
//     while(curr!=NULL){
//         cout<<curr->book_code<<" ";
//         curr=curr->right;
//     }
// }


struct Node_{
    int book_code; int page; int paragraph; double sentence_no; vector<string> sentence;
};
class SearchEngine {
private:
    Node* head;
    Node *tail;
    Node *sentinel;
    vector<Node_*> l;
public: 
    Dict *dict_std;
    Dict* dict_corp;
    heap * he;
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(vector<string> pattern, int& n_matches);

    /* -----------------------------------------*/
};