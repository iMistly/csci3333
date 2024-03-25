#include <iostream>
#include <string>
#include<bits/stdc++.h>
#include <map>
#include <vector>
using namespace std;

struct BookDoc{
    string file;
    vector<pair<string, int>> topPhrases[10];
    map<string, int> phraseHash[10];
    
    BookDoc(string inFile = "none"){
        file = inFile;
    }

    void insertPhrase(string phrase, int length){
        int i = length-1;
        if(phraseHash[i].find(phrase) == phraseHash[i].end()){
            phraseHash[i][phrase] = 1;
        }
        else{
            phraseHash[i][phrase] += 1;
        }
    }

    void clearMemory(){
        for(int i = 0; i < 10; ++i){
            phraseHash[i].clear();
            topPhrases[i].clear();
        }
    }
};

string getSentence(string& current){
    size_t length = current.length();
    string endPunc = ".!?", ans = "";
    for(size_t i = 0; i < length; ++i) {
        if(endPunc.find(current[i]) != string::npos) {
            if(i != 0){ // If the first character is not an ending punctuation.
                ans = current.substr(0, i);
            }
            current = current.substr(i + 1, current.length() - i);
            break;
        }
    }
    return ans;
}

void cleanSentence(string& sentence){
    string specialPunc = "\"/\\~";
    string erasePunc = ",:;(){}[]*_";

    if(sentence.size() > 0){
        for(size_t j = 0; j < sentence.size(); ++j){
            char c = sentence[j];
            if(c < 0 || 127 < c || (specialPunc.find(c) != string::npos)){
                sentence[j] = ' ';
            }
            else if(erasePunc.find(c) != string::npos){
                sentence.erase(j, 1);
                --j;
            }
            else if(c == ' ' && sentence[j+1] == ' '){
                sentence.erase(j, 1);
                --j;
            }
        }
        size_t doubleSpace = sentence.find("  ");
        while(doubleSpace != string::npos)
        {
            sentence.erase(doubleSpace, 1);
            doubleSpace = sentence.find("  ");
        }
        size_t doubleHyphen = sentence.find("--");
        while(doubleHyphen != string::npos){
            sentence[doubleHyphen] = ' ';
            sentence.erase(doubleHyphen+1, 1);
            doubleHyphen = sentence.find("--");
        }
        while(sentence[0] == ' '){
            sentence = sentence.substr(1, sentence.size());
        }
    }
}

vector<string> getWords(string sentence){
    string current = "";
    vector<string> words;

    for(auto x : sentence){
        x = tolower(x);
        if(x != ' '){
            current += x;
        }
        else{
            if(current.length() > 0)
                words.push_back(current);
            current = "";
        }
    }
    if(current.length()>0){
        words.push_back(current);
    }
    return words;
}

map<string, int>* getCommonPhrases(BookDoc b1, BookDoc b2) {
    map<string, int>* commonPhrases = new map<string, int>[10];

    for(int i = 0; i < 10; ++i){
        for(auto& phrase : b1.phraseHash[i]){
            if(b2.phraseHash[i].find(phrase.first) != b2.phraseHash[i].end()){
                int minFrequency = min(phrase.second, b2.phraseHash[i][phrase.first]);
                if(minFrequency != 0){
                    commonPhrases[i][phrase.first] = minFrequency;
                }
            }
        }
    }
    return commonPhrases;
}

vector<pair<string, int>>* topPhrases(map<string, int>* myHash){
    vector<pair<string, int>>* topPhrases = new vector<pair<string, int>>[10];
    int max = 0;
    pair<string, int> tmp;
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){ // Sort the phrases by frequency
            int max = 0;
            pair<string, int> tmp;
            for(auto it = myHash[i].rbegin(); it != myHash[i].rend(); ++it){
                if(it->second > max){
                    max = it->second;
                    tmp = *it;
                }
            }
            if(max != 0){
                topPhrases[i].push_back(tmp);
                myHash[i].erase(tmp.first);
            }
        }
    }
    // Add the top phrase back into myHash
    for(int i = 0; i < 10; ++i){
        for(auto& x : topPhrases[i]){
            myHash[i][x.first] = x.second;
        }
    }
    return topPhrases;
}