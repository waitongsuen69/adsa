#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Lower case alphabet   Len<=10
// Use last alphabet

// 26 slot (a…z) [never_used]
class slot
{
public:
    slot(){
        state = 1;
    }
    void insert_element(string input){
        state = 3; 
        content = input;
    }
    void delete_element(){
        state = 2;
    }

    string content;
    // Slot state: never_used  tombstone occupied
    int state;
    // the state is stand for 
        // 1: never used
        // 2 tombstone 
        // 3:occupied
};

void insertion(slot* list[],string input){\
    //cout<<"get"<<input.substr(1)<<endl;
    string word = input.substr(1);
    //int round = 0;
    int start_point = input.back()-97;
    int found=0;
    for(int i = 0; i <26 ; i++){
        if(list[i]->content == input.substr(1) && list[i]->state == 3 ){
            found=1;
            //cout<<"found in list, kill"<<endl;
        }
    }
    if(found == 1 ){}else{
    int found_before = 0;
    for(int i = start_point; i<26 ; i++){
        if(list[i]->state < 3 ) {
            //cout<<"insert to "<<i<<endl;
            list[i]->insert_element(input.substr(1));
            found_before=1;
            break;
            
        }
    }
    if(found_before==0){
        for(int i=0;i<start_point ; i++)
        {
            if(list[i]->state < 3 ) {
            //cout<<"insert to "<<i<<endl;
            list[i]->insert_element(input.substr(1));
            break;    
            }
        }
    }
    }
}

void deletion(slot* list[],string input ){
    // cout<<"Deletion"<<endl;
    // return;
//int round=0;
    string word = input.substr(1);
    int start_point = input.back()-97;
    int i = start_point;
    
    for(int i=0;i<25;i++)
    {
        if(list[i]->content == input.substr(1) && list[i]->state == 3 ){
            //cout<<"found delete"<<endl;
            list[i]->state=2;
            break;
        }else{}
    }

int main(){
    slot *slot_list[26];
    for (int i=0; i<26; i++){
        slot_list[i]=  new slot();
    }
    string input;
    vector<string> input_collection;

    while (cin >> input){
        input_collection.push_back(input);
        if(cin.get() == '\n') break;
    }
    for(int i = 0; i < input_collection.size();i++){
        //cout<< word << " ";
        (input_collection[i][0] == 'A') ?  insertion(slot_list,input_collection[i]): deletion(slot_list,input_collection[i]);
    }
    
    for (int i = 0; i <26 ; i++){
        if(slot_list[i]->state == 3){
            cout<<slot_list[i]->content <<" ";
        }
    }
    return 0;
    // "Aword"  add words
    // "Dword" delete words
    // print with " "
}