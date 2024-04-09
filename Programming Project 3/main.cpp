#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

int main(){
    ifstream file("wordLadder_dictionary.txt");
    string line;
    vector<map<string,vector<string>>> wordList;

    // int count = 50000;
    while(getline(file, line)){
        auto len = line.size();
        if(wordList.size() < len){
            wordList.resize(len);
            cout << "Bigger!: " << len << endl;
        }
        wordList[len-1][line];
    }

    for(size_t i = 0; i < wordList.size(); ++i){
        for(auto word : wordList[i]){
            for(size_t j = 0; j < word.first.size(); ++j){
                string current = word.first;
                for(char a = 'a'; a <= 'z'; ++a){
                    current[j] = a;
                    if(current != word.first && wordList[i].find(current) != wordList[i].end()){
                        word.second.push_back(current);
                    }
                }
            }
        }
    }

    file.close();
    return 0;
}