#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include <time.h>
#include "helpers.h"
using namespace std;

int main(){
    clock_t start = clock();

    BookDoc b1("tomSawyer.txt"), b2("huckleberryFinn.txt");
    fstream file(b1.file);
    string line{}, currentStr{}, sentence = "";

    while(!file.eof()){ // While not the end of the file
        while(sentence == "" && !file.eof()){
            getline(file, line);
            if(line.empty()) {continue;} // Skip empty lines
            currentStr += " " + line;
            sentence = getSentence(currentStr);
        }
        cleanSentence(sentence);
        if(sentence.empty()) {continue;}
        vector<string> words = getWords(sentence);
        for(int i = 1; i <= min(10, static_cast<int>(words.size())); ++i){ // For phrases of length 1-10
            for(size_t j = 0; j < words.size()-i+1; ++j){
                string phrase = words[j];
                for(int k = 1; k < i; ++k){
                    phrase += " " + words[k+j];
                }
                b1.insertPhrase(phrase, i);
            }
        }
        sentence = "";
    }
    file.close();

    fstream file2(b2.file);
    line = "";
    currentStr = "";
    sentence = "";
    while(!file2.eof()){ // While not the end of the file
        while(sentence == "" && !file2.eof()){
            getline(file2, line);
            if(line.empty()) {continue;} // Skip empty lines
            currentStr += " " + line;
            sentence = getSentence(currentStr);
        }
        cleanSentence(sentence);
        if(sentence.empty()) {continue;}
        // test << sentence << endl;
        vector<string> words = getWords(sentence);
        for(int i = 1; i <= min(10, static_cast<int>(words.size())); ++i){ // For phrases of length 1-10
            for(size_t j = 0; j < words.size()-i+1; ++j){
                string phrase = words[j];
                for(int k = 1; k < i; ++k){
                    phrase += " " + words[k+j];
                }
                if(phrase[0] == ' '){phrase.erase(0, 1);}
                if(phrase[phrase.length()] == ' '){phrase.erase(phrase.length(), 1);}
                b2.insertPhrase(phrase, i);
            }
        }
        sentence = "";
    }
    file2.close();

    map<string, int>* common = getCommonPhrases(b1, b2);
    vector<pair<string, int>>* top = topPhrases(common);
    delete[] common;

    ofstream results("doc.txt");
    for(int i = 0; i < 10; ++i){
        int count = 0;
        results << "Top " << i+1 << " word phrases:\n";
        results << "==============================\n";
        for(auto phrase : *(top+i)){
            if(count >= 10){break;}
            results << phrase.second << '\t' << phrase.first << endl;
            ++count;
        }
        results << '\n';
    }
    results.close();
    delete[] top;

    b1.clearMemory();
    b2.clearMemory();

    clock_t end = clock();
    cout << "Time computed: " << (double)(end - start) / 1000 << " seconds" << endl;

    return 0;
}