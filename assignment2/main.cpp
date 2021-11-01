#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Node
{
    public:
    int height,con;
    Node* l;
    Node* r;
};

Node* make_node(int content){
    Node* nn=new Node();
    nn->l=NULL;
    nn->r=NULL;
    nn->con=content;
    nn->height=1;
    return nn;
}

int hi_get(Node* n){
    return (n)?  n->height : 0;    
}

int baln(Node* n){
    return (n)? hi_get(n->l)-hi_get(n->r) : 0; 
}

int max_find(int a, int b){
    return (a > b)? a : b;
}  

Node * r_ro(Node * n){
    Node* nr = n->l;
    Node* or_r = nr->r;
    //n->l=nr->r;
    nr->r = n;
    n->l = or_r;
    //update the old node height
    //n->height= (hi_get(n->r) > hi_get(n->l))? hi_get(n->r)+1 : hi_get(n->l)+1;
    n->height = max_find(hi_get(n->l),hi_get(n->r))+1;
    //update new node height
    //nr->height = (hi_get(nr->r) > hi_get(nr->l))? hi_get(nr->r)+1 : hi_get(nr->l)+1;
    nr->height = max_find(hi_get(nr->l),hi_get(nr->r))+1;
    return nr;
}
Node * l_ro(Node * n){
    Node* nr = n-> r;
    Node* or_r = nr->l;
    
    nr->l = n;
    n->r = or_r;
    //update old node height
    n->height = max_find(hi_get(n->l),hi_get(n->r))+1;
    nr->height = max_find(hi_get(nr->l),hi_get(nr->r))+1;
    //n->height= (hi_get(n->r) > hi_get(n->l))? hi_get(n->r)+1 : hi_get(n->l)+1;
    //update new node height
    //nnr->height = (hi_get(nr->r) > hi_get(nr->l))? hi_get(nr->r)+1 : hi_get(nr->l)+1;
    return nr;
}

Node* push(Node *n,int num){
    // if(num>99 || num<0){
    //     return n;
    // }
    if (n == NULL)
    {
        return make_node(num);
    }
    if(num == n->con){
        return n;
    }
    //test
    if(num < n->con ){ 
        n->l = push(n->l, num);
    }else if (num > n->con){
        n->r = push(n->r,num);
    }
    n->height = 1 + max_find(hi_get(n->l),hi_get(n->r));
    
    if (baln(n) > 1){
        if (num < n->l->con ){
            return r_ro(n);
        }
        if (num > n->l->con ){
            n->l = l_ro(n->l);
            return r_ro(n);
        } else return n;

    } 
    if ( baln(n) < -1 ){
        if (num > n->r->con ){
            return l_ro(n);
        }else if (num < n->r->con ){
            n->r = r_ro(n->r);
            return l_ro(n);
        }
        return n;        
    }
    return n;
}

Node* max(Node* n){
    if(!n){
        return n;
    }
    while(n->r != NULL){
        n=n->r;
    } 
    return n; 
}

Node* kill(Node* n,int num){
    //     if(num>99 || num<0){
    //     return n;
    // }
    if (n == NULL){
        return n;
    }
    if(num > n->con){
        n->r = kill(n->r,num);
    }else if (num < n->con){
        n->l = kill(n->l,num);
    } else{
        // found in this n
        if (n->r == NULL && n->l == NULL){
            return NULL;
        }
        if (n->l == NULL || n->r == NULL)
        {
            Node* contan;
            contan = (n->l)? n->l:n->r;

            *n = *contan;

        } else{

            ////testtt///////
            Node* contan=max(n->l);
            n->con = contan->con;
            n->l= kill(n->l,n->con);
        }
    }

    if ( n == NULL )return n;
    n->height = 1+ max_find(hi_get(n->l),hi_get(n->r));
    int balance = baln(n);

    if(balance >1){
       if (baln(n->l)>=0){
           return r_ro(n);
       }
       if (baln(n->l)<0){
           n->l = l_ro(n->l);
           return r_ro(n);
       }
    }
    if (balance <-1){
        if (baln(n->r)<=0)
        {
            return l_ro(n);
        }
        if(baln(n->r)>0){
            n->r = r_ro(n->r); 
            return l_ro(n);
        }
      return n;  
    }
    return n;

}


void pre(Node* n){
    if (n == NULL){

    }else {
        cout<<n->con<<" ";
        pre(n->l);
        pre(n->r);
    }
}
void in(Node* n){
    if (n == NULL){

    }else {
        in(n->l);
        cout<<n->con<<" ";
        in(n->r);
    }
}
void po(Node* n){
    if (n == NULL){

    }else {
        po(n->l);
        po(n->r);
        cout<<n->con<<" ";
        
    }
}

void show(Node* n,string order){
    if (order == "PRE"){
        pre(n);
    }else if ( order == "IN"){
        in(n);
    }else if ( order == "POST"){
        po(n);
    }
}

// void print2DHelper(Node* node, int padding) {
//     if (!node) {return;}

//     print2DHelper(node->r, padding + 1);
//     for (int i = 0; i < padding; ++i) {
//         cout << "\t";
//     }
//     cout << node->con << endl;
//     print2DHelper(node->l, padding + 1);
// }
// void print2D(Node* root) {

// 		print2DHelper(root, 0);
// }

int main(){
    Node *root=NULL;
    vector<string> collect;
    string input;
    while (cin >> input){
        collect.push_back(input);
        if(cin.get() == '\n') break;
    }


    //int len = collect.size();

    for (int i=0; i<collect.size()-1; i++){
        string tem = collect[i];
        // string number = tem.substr(1);
        // int num = stoi(number);
        if (tem[0]== 'A'){
            root = push(root,stoi(tem.substr(1)));
        }
        if (tem[0]=='D'){
            root = kill(root,stoi(tem.substr(1)));
        }
        // cout << tem << endl;
        // print2D(root);
        // cout << "------------\n";
    }
    if(root != NULL){
        string last_word = collect[collect.size()-1];
        show(root,last_word);
    } else {
        cout<<"EMPTY"<<endl;
        }
    return 0;
}