#include <iostream>
#include <string>

using namespace std;

int getNumber(string& s){
    int number = 0;
    for(int i = 1; i < s.size(); ++i){
        number*=10;
        number += s[i] - '0';
    }
    return number;
}

int main(){
    int position = 50;
    int password = 0;
    string instruction;
    while(cin>>instruction){
        int steps = getNumber(instruction)%100;
        position = instruction[0] == 'R'? (position+steps)%100 : (position-steps+100)%100;
        if(position == 0)
            ++password; 
    }
    cout<<password<<endl;
}

