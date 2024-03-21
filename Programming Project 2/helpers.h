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
        if(phraseHash[i].find(phrase) == phraseHash[i].end())
            phraseHash[i][phrase] = 1;
        else
            phraseHash[i][phrase] += 1;
        checkTopPhrases(phrase, i);
    }

    void checkTopPhrases(string phrase, int index){
        if(topPhrases[index].empty()){
            topPhrases[index].push_back(make_pair(phrase, phraseHash[index][phrase]));
            return;
        }

        for(size_t i = 0; i < topPhrases[index].size(); ++i){
            // Check if phrase is already in topPhrases
            if(topPhrases[index][i].first == phrase){
                topPhrases[index][i].second = phraseHash[index][phrase];
                return;
            }
            if(topPhrases[index][i].second < phraseHash[index][phrase]){
                topPhrases[index].insert(topPhrases[index].begin() + i, make_pair(phrase, phraseHash[index][phrase]));
                if(topPhrases[index].size() > 10){
                    topPhrases[index].pop_back();
                }
                return;
            }
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