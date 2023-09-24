#include <iostream>

using namespace std;

int main()
{
    string x;
    cout<<"Enter your input : ";
    cin>>x;

    if(x>="A" && x<="Z"){
        cout<<"Not Numeric.";
    }
    else if(x>="a" && x<="z"){
        cout<<"Not Numeric.";
    }
    else{
        cout<<"Numeric";
    }

}

