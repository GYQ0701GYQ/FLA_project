#include <stdio.h>
#include <iostream>
#include <sstream>
#include <algorithm> //for find
#include "machine.h"

Machine::Machine()
{
    this->a = 99;
    vector<string> temp;
    for(int i=0;i<5;i++){
        this->delta.push_back(temp);
    }
}
void Machine::print()
{
    cout<<"the value of a is "<<this->a<<endl;
}
int Machine::ini_equal(string left, string right){
    if(left=="#q0")
        this->q0 = right;
    else if(left=="#B")
        this->B = right[0];
    else if(left=="#N")
        this->num = right;
    else{
        string tok;
        string temp_str="";
        vector<string> temp_result;
        stringstream s1(right);  //去掉左括号
        while(getline(s1,tok,'{'))
            if(tok > "")
                temp_str += tok;
        stringstream s2(temp_str);  //去掉右括号
        temp_str="";
        while(getline(s2,tok,'}'))
            if(tok > "")
                temp_str += tok;
        stringstream s3(temp_str);  //根据逗号分隔
        temp_str="";
        while(getline(s3,tok,','))
            if(tok > "")
                temp_result.push_back(tok);
        if(left=="#Q")
            this->Q = temp_result;
        else if(left=="#S")
            this->S = temp_result;
        else if(left=="#G")
            this->G = temp_result;
        else if(left=="#F")
            this->F = temp_result;
        else 
            return 0;
    }
    return 1;
}
int Machine::ini_delta(vector<string> a){
    // this->delta的size已经被初始化为5，a的大小
    for(int i=0;i<5;i++)
        this->delta[i].push_back(a[i]);  //纵向把每一个转移步骤push到delta
    // cout<<this->delta[0].size()<<endl;
    return 1;
}
int Machine::check(){
    // 合法性检查：S必须在G中，B必须在G中，B不能在S中
    // q0必须在Q中,F必须在Q中
    // num必须是数字符号且大于0
    // 不能有读头均不移动且在同一状态的情况（陷入循环）
    // 每个移动的当前状态和下一状态必须都在Q中
    // 每个移动的内容长度不能超过num
    vector<string>::iterator it = this->G.begin();
    vector<string>::iterator it2 = this->G.begin();
    for(auto iter:this->G){
        it = find(this->G.begin(), this->G.end(), iter);
        if(it==this->G.end())
            return 0;
    }
    it = find(this->G.begin(), this->G.end(), this->B);
    if(it==this->G.end())
            return 0;
        // else cout<<"Yep!"<<endl;
    it = find(this->S.begin(), this->S.end(), this->B);
    if(it!=this->S.end())
            return 0;
    // else cout<<"Nope"<<endl;
    it = find(this->Q.begin(), this->Q.end(), this->q0);
    if(it==this->Q.end())
            return 0;
    // else cout<<"Yep!"<<endl;
    for(auto iter:this->F){
        it = find(this->Q.begin(), this->Q.end(), iter);
        if(it==this->Q.end())
            return 0;
        // else cout<<"Yep!"<<endl;
    }
     // string a="4";
    // stringstream s1;
    // int c;
    // s1<<a;
    // s1>>c;
    // cout<<c<<endl;
    stringstream ss;
    int num_int=-1;
    if(this->num != ""){
        ss<<this->num;
        ss>>num_int;
        if(num_int<=0)
            return 0;
        else
        {
            for(int i=0;i<this->delta[0].size();i++){
                it=find(this->Q.begin(), this->Q.end(), this->delta[0][i]);
                it2=find(this->Q.begin(), this->Q.end(), this->delta[4][i]);
                if(it==this->Q.end() || it2==this->Q.end())
                    return 0;
                // if(this->delta[0][i]==this->delta[4][i] && this->delta[3][i]=="**")
                //     return 0;
                if(this->delta[1][i].length()!=num_int || this->delta[2][i].length()!=num_int || this->delta[3][i].length()!=num_int)      
                    return 0;  
            }
        }
    }
    return 1;
}