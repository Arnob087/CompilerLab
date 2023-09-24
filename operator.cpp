#include<iostream>
using namespace std;

int main(){

    string array[5];

    cout<<"Enter the expression one by one or giving a space :";
    for(int i=0; i<5; i++){
        cin>>array[i];
    }


    int x=1;
    for(int i=0; i<5; i++){

        if(array[i]=="+"){
            cout<<"Operator "<<x<<" : "<<array[i]<<endl;
            x++;
        }
        else if(array[i]=="-"){
            cout<<"Operator "<<x<<" : "<<array[i]<<endl;
            x++;
        }
        else if(array[i]=="%"){
            cout<<"Operator "<<x<<" : "<<array[i]<<endl;
            x++;
        }
        else if(array[i]=="/"){
            cout<<"Operator "<<x<<" : "<<array[i]<<endl;
            x++;
        }
        else if(array[i]=="*"){
            cout<<"Operator "<<x<<" : "<<array[i]<<endl;
            x++;
        }
        else if(array[i]=="="){
            cout<<"Operator "<<x<<" : "<<array[i]<<endl;
            x++;
        }
    }

}
