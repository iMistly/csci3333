#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

string* shortestPath(map<string, vector<string>> &wordList, string start, string end){
    map<string, string> path;
    queue<string> q;
    q.push(start);
    path[start] = start;
    while(!q.empty()){
        string current = q.front();
        q.pop();
        for(auto word : wordList[current]){
            if(path.find(word) == path.end()){
                path[word] = current;
                q.push(word);
            }
        }
    }

    if(path.find(end) == path.end()){
        return nullptr;
    }

    string* result = new string;
    string current = end;
    while(current != start){
        *result = current + " " + *result;
        current = path[current];
    }
    *result = start + " " + *result;
    return result;
}

int main(){
    ifstream file("wordLadder_dictionary.txt");
    string line;
    vector<map<string,vector<string>>> wordList;

    while(getline(file, line)){
        auto len = line.size();
        if(wordList.size() < len){wordList.resize(len);}
        wordList[len-1][line];
    }

    for(size_t i = 0; i < wordList.size(); ++i){
        for(auto word : wordList[i]){
            for(size_t j = 0; j < word.first.size(); ++j){
                string current = word.first;
                for(char c = 'a'; c <= 'z'; ++c){
                    current[j] = c;
                    if(current != word.first && wordList[i].find(current) != wordList[i].end()){
                        word.second.push_back(current);
                    }
                }
            }
        }
    }

    string start = "five";
    string end = "zero";
    string* result = shortestPath(wordList[start.size()-1], start, end);
    if(result != nullptr){
        cout << *result << endl;
        delete result;
    }else{
        cout << "No path found" << endl;
    }

    file.close();
    return 0;
}