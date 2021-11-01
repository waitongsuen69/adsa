#include<iostream>
#include<stdlib.h>
#include<string>
#include <math.h>
#include <algorithm>  

std::string minus(std::string numa,std::string numb,int base){
    if(numa.length()<numb.length()){
        swap(numa,numb);
    }
     long long na = numa.length();
     long long nb = numb.length();
    reverse(numa.begin(),numa.end());
    reverse(numb.begin(),numb.end());
    int carry = 0;
    std::string result;   
    for(int i=0; i<na; i++){
        int b;
        if(nb<i+1){
            b=0;
        }else{
            b=(numb[i]-'0');
        }
        int remain_here=(numa[i]-'0')-carry-b;

        if (remain_here < 0 ){
            carry=1;
            int left=base+remain_here;
            result.push_back(left+'0');
        }else{
            carry=0;
            result.push_back(remain_here+'0');
        }
    }
    reverse(result.begin(),result.end());
    return result;
}

std::string adder(std::string numa,std::string numb,int base){

    if(numa.length()<numb.length()){
        swap(numa,numb);
    }
    int na = numa.length();
    int nb = numb.length();
    reverse(numa.begin(),numa.end());
    reverse(numb.begin(),numb.end());
    int carry = 0;
    std::string sum;
    for(int i=0;i<na;i++){
        int b;
        if(nb<i+1){
            b=0;
        }else{
            b=(numb[i]-'0');
        }
        int sum_here=(numa[i]-'0')+carry+b;
        sum.push_back(sum_here%base+'0');
        if (sum_here/base > 0 ){
            carry=1;
        }else{
            carry=0;
        }

    }
    if(carry== 1){
        sum.push_back('1');
    }
    reverse(sum.begin(),sum.end());
    return sum;
}

std::string get_B(std::string num,int B){
    for(int i=0;i<B;i++){
        num=num+'0';
    }
    return num;
}




std::string multi(std::string numa,std::string numb,int base){
    // if(numa.length()==0 || numb.length()==0){
    //     return 0;
    // }
    // else 
    if(numa.length()==1 && numb.length()==1){
        int inan = ((numb[0]-'0')*(numa[0]-'0'));
        //std::cout<<"a"<<numa<<"b"<<numb <<"inan is "<<inan << std::endl;
        std::string result;
        result.push_back(inan/base+'0');
        result.push_back(inan%base+'0');
        return result;
    }else{
        if(numa.length()<numb.length()){
            swap(numa,numb);
        }
        long long int alen=numa.length();
         long long int blen=numb.length();
        for (int i=0; i<alen-blen; i++){ 
            numb='0'+numb;
        }
        std::string a1=numa.substr(0,alen/2);
        std::string b1=numb.substr(0,alen/2);
        std::string a0=numa.substr(alen/2,alen);
        std::string b0=numb.substr(alen/2,alen);
        std::string a1_b1 = multi(a1,b1,base);
        std::string a0_b0 = multi(a0,b0,base);
        std::string a10_b10 = multi(adder(a1,a0,base),adder(b1,b0,base),base);
        std::string ab1pab0=adder(a1_b1,a0_b0,base);
        std::string middle=minus(a10_b10,ab1pab0,base);
        long int fir= alen - alen/2;
        a1_b1=get_B(a1_b1,2*fir);
        middle=get_B(middle,fir);
        //return a1_b1*(pow(base,2*(alen-alen/2)))+(a10_b10-a1_b1-a0_b0)*(pow(base,alen))+a0_b0;        
        std::string result=adder(adder(a1_b1,middle,base),a0_b0,base);
        for(int i = 0; i < result.length();i++){
            if(result.at(0) == '0'){
                result.erase(result.begin());
            }
        }
        return result;
    }
}


// std::string translater(int number,int base){
//     std::string result;
//     int level=0;
//     while(pow(base,level)<=number){
//         level++;
//     }
//     for(int i=level-1;i>=0;i--){
//         int base_level = pow(base,i);
//         if(number<base_level){
//                 result.push_back('0');
//         }else if (base_level<= number){
//             int level_num=number/base_level;
//             result.push_back(level_num+'0');
//             number=number%base_level;
//         }
//     }
//     return result;
// }
int main(){
    std::string first,second;
    long int base;
    std::cin>>first>>second>>base;
    //std::cout<<minus(first,second,base)<<std::endl;

    std::cout<<adder(first,second,base)<<" "<<multi(first,second,base)<<std::endl;
    // int get=first[1]-48;
    // std::cout<<get<<std::endl;
    return 0;
}


// std::string balance(std::string numa,std::string numb){
//     int alen=numa.length();
//     int blen=numb.length();
//     for (int i=0; i<alen-blen; i++){ 
//         numb='0'+numb;
//     }
//     return numb;
// }

// std::string multiple(std::string numa,std::string numb,int base){
//     if(numa.length()<numb.length()){
//         swap(numa,numb);
//     }
//     numb = balance(numa,numb);

//     return 0;
// }
// std::string sub(std::string numa,std::string numb, int base){
//         if(numa.length()<numb.length()){
//         swap(numa,numb);
//     }
//     numb = balance(numa,numb);
//     int N = numa.length();
//     std::string a1=numa.substr(0,N/2);
// }