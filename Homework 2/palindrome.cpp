#include <cstring> 
#include <string>
#include <iostream>
using namespace std;

bool palindrome(char* str, int s){
    for(int i = 0; i<s/2+1; ++i)
        if(str[i] != str[s-1-i]){return false;}
    return true;
}

int main(){
    string test = "32123";
    char* char_array = new char[test.length()];
    strcpy(char_array, test.c_str());
    cout << char_array << endl;
    cout << palindrome(char_array, test.length()) << endl;
    return 0;
}