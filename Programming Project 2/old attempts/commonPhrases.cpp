#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <time.h>
#include<bits/stdc++.h>
#include <fstream>
using namespace std;

struct WordDoc{
    string fileName;
    vector<pair<int, string>> sortedPhrases[10];

    WordDoc(string inFileName){
        fileName = inFileName;
    }

    void addVector(vector<pair<int, string>> vec, int index){
        sortedPhrases[index] = vec;
    }

    void writeToFile(){
        string newFile = fileName.substr(0, fileName.length()-4) + "_phrases.txt";
        ofstream file(newFile);

        for(int i = 0; i<10; ++i){
            file << "Top 10 " << i+1 << " word phrases." << endl;
            file << "===========================" << endl;
            for (int i = 0; i < 10; ++i) {
                priority_queue<pair<int, string>> pq;
                for (const auto& phrase : sortedPhrases[i]) {
                    pq.push(phrase);
                    if (pq.size() > 10) {
                        pq.pop();
                    }
                }
                file << "Top 10 " << i + 1 << " word phrases." << endl;
                file << "===========================" << endl;
                while (!pq.empty()) {
                    pair<int, string> current = pq.top();
                    pq.pop();
                    file << current.first << "\t\t\t" << current.second << endl;
                }
            }
        }
        file.close();
    }
};

vector<string> getSentences(string filename){
    fstream file;
    vector<string> sentences;
    string fileStr = "";
    string endPunc = ".!?";
    string specialPunc = "\"/\\{}[]()~";
    string erasePunc = ",:;";
    string line;

    file.open(filename);

    // Convert the file into lines ending with something in endPunc string.
    while(!file.eof()) {
        getline(file, line);
        if(line.empty()) {
            continue; // Skip empty lines
        }
        fileStr += " " + line;
        for(size_t i = 0; i < fileStr.length(); ++i) {
            if(endPunc.find(fileStr[i]) != string::npos) {
                if(i != 0){ // If the first character is not an ending punctuation.
                    sentences.push_back(fileStr.substr(0, i));
                }
                fileStr = fileStr.substr(i + 1, fileStr.length() - i);
                break;
            }
        }
    }

    // Strip the sentences.
    // Remove non-ASCII characters, leading spaces, double dashes, and double spaces.
    for(size_t i = 0; i < sentences.size(); ++i){
        if(sentences[i].length() > 0){
            for(size_t j = 0; j < sentences[i].length()-1; ++j){
                char c = sentences[i][j];
                if(c < 0 || 128 < c || (specialPunc.find(c) != string::npos)){
                    sentences[i][j] = ' ';
                }
                else if(erasePunc.find(c) != string::npos){
                    sentences[i].erase(j, 1);
                    --j;
                }
                else if(c == '-' && sentences[i][j+1] == '-'){
                    sentences[i].erase(j, 2);
                    j -= 1;
                }
            }
            while(sentences[i][0] == ' '){
                sentences[i] = sentences[i].substr(1, sentences[i].length());
            }
        }
    }
    return sentences;
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

unordered_map<string, int> getPhrases(vector<string>& sentences, int length){
    unordered_map<string, int> table;

    for(auto s : sentences){
        vector<string> words = getWords(s);
        if(words.size() < length){
            continue;
        }
        for(int i = 0; i < words.size()-length+1; ++i){
            string phrase = words[i];
            for(int j = 1; j < length; ++j){
                phrase += " " + words[i+j];
            }
            if(phrase == " " || phrase.length() <= 0){
                continue; // Do not add blank spaces to the table.
            }
            if(table.find(phrase) == table.end()){
                table[phrase] = 1;
            }
            else{
                table[phrase] += 1;
            }
        }
    }

    return table;
}

vector<pair<string, int>> commonPhrases(unordered_map<string, int>& phrases, int num){
    vector<pair<string, int>> mostCommon;

    // Sorting algorithm 
    for(int i = 0; i<num; ++i){
        pair<string, int> maxPhrase;
        int max{};
        for(auto x : phrases){
            if(x.second > max){
                maxPhrase = make_pair(x.first, x.second);
                max = x.second;
            }
        }
        mostCommon.push_back(maxPhrase);
        phrases.erase(maxPhrase.first);
    }

    return mostCommon;
}

int main(){
    clock_t start = clock();

    vector<string> files = {"huckleberryFinn.txt"};
    // vector<WordDoc> computed;
    
    for(auto file : files){
        vector<string> sentences = getSentences(file);
        WordDoc tmp(file);
        for(int i = 1; i <= 10; ++i){
            unordered_map<string, int> phrases = getPhrases(sentences, i);
            vector<pair<int, string>> vecPhrases;
            for (auto phrase : phrases) {
                vecPhrases.push_back(make_pair(phrase.second, phrase.first));
            }
            sort(vecPhrases.begin(), vecPhrases.end());
            clock_t mid = clock();
            cout << i << ": Time - " << (double)(mid - start) / 1000 << " seconds" << endl;
            tmp.addVector(vecPhrases, i-1);
        }
        // computed.push_back(tmp);
        tmp.writeToFile();
    }

    clock_t end = clock();
    cout << "Time computed: " << (double)(end - start) / 1000 << " seconds" << endl;

    return 0;
}