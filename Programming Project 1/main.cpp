#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

bool isValidExpression(string expression){
    stack<char> parSt;
    string paranthesis = "()[]{}";

    for(auto x : expression){
        if(!(paranthesis.find(x) < paranthesis.length())){
            continue;
        }
        if(x=='(' || x=='[' || x=='{'){
            parSt.push(x);
            cout << "Pushed " << x << endl;
        }
        else if(parSt.empty()){
            return false;
        }
        else{
            switch(x){
                case ')':
                    if(parSt.top() != '(')
                        return false;
                    break;
                case ']':
                    if(parSt.top() != '[')
                        return false;
                    break;
                case '}':
                    if(parSt.top() != '{')
                        return false;
                    break;
            }
            parSt.pop();
        }
    }
    return true;
}

int main(){
    ifstream inFile;
    string tmp;
    inFile.open("tests.txt");
    while(getline(inFile, tmp)){
        cout << isValidExpression(tmp) << endl;
    }
    
    return 0;
}