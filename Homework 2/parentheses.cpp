#include <cstring> 
#include <string>
#include <stack>
#include <iostream>
using namespace std;

bool match(const char exp [ ], const int s){
    stack<char> pars;
    char top = ' ';
    for(int i = 0; i<s; ++i){
        if(!pars.empty())
            top = pars.top();
        cout << exp[i] << ':' << top << endl;
        switch(exp[i]){
            case '(':
            case '[':
            case '{':
                pars.push(exp[i]);
                break;
            case ')':
                if(top == '(')
                    pars.pop();
                else
                    return false;
                break;
            case ']':
                if(top == '[')
                    pars.pop();
                else
                    return false;
                break;
            case '}':
                if(top == '{')
                    pars.pop();
                else
                    return false;
                break;
        }
    }
    if(pars.empty())
        return true;
    else
        return false;
}

int main()
{
    string test1 = "12 + { 34 / ( 6 * ) } ";
    char* char_array = new char[test1.length()+1];
    strcpy(char_array, test1.c_str());
    if(match(char_array, test1.length()+1)){
        cout << "All good" << endl;
    }
    return 0;
}