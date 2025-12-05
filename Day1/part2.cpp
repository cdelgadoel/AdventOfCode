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
        int steps = getNumber(instruction);
        password += steps/100;
        steps %= 100;
        int nextPosition = instruction[0] == 'R'? (position+steps)%100 : (position-steps+100)%100;
        if(instruction[0] == 'R' && nextPosition < position)
            ++password;
        if(instruction[0] == 'L' && (position != 0 && nextPosition > position || nextPosition == 0))
            ++password;
        position = nextPosition;
    }
    cout<<password<<endl;
}

