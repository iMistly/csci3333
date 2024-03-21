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
        // test << sentence << endl;
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
                b2.insertPhrase(phrase, i);
            }
        }
        sentence = "";
    }

    file2.close();

    clock_t end = clock();

    ofstream test("doc.txt");
    for(int i = 0; i < 10; ++i){
        test << "Top " << i+1 << " phrases\n";
        for(auto p : b1.topPhrases[i]){
            test << p.second << '\t' << p.first << endl;
        }
        test << "=================\n";
    }


    // Combine the topPhrases from both books.
    // Use the common frequency of the phrase in both books.
    // map<string, int> combined[10];
    // for(int i = 0; i < 10; ++i){
    //     for(auto p : b1.topPhrases[i]){
    //         if(b2.phraseHash[i].find(p.first) != b2.phraseHash[i].end())
    //             combined[i][p.first] = p.second;
    //     }
    //     for(auto p : b2.topPhrases[i]){
    //         if(b1.phraseHash[i].find(p.first) != b1.phraseHash[i].end() && combined[i].find(p.first) == combined[i].end())
    //             combined[i][p.first] = p.second;
    //         else if(combined[i][p.first] > p.second)
    //             combined[i][p.first] = p.second;
    //     }
    // }

    // // Sort the combined phrases by frequency.
    // vector<pair<string, int>> combinedVec[10];
    // for(int i = 0; i < 10; ++i){
    //     for(auto p : combined[i]){
    //         if(combinedVec[i].empty()){
    //             combinedVec[i].push_back(make_pair(p.first, p.second));
    //             continue;
    //         }
    //         for(size_t j = 0; j < combinedVec[i].size(); ++j){
    //             if(combinedVec[i][j].second < p.second){
    //                 combinedVec[i].insert(combinedVec[i].begin() + j, make_pair(p.first, p.second));
    //                 if(combinedVec[i].size() > 10){
    //                     combinedVec[i].pop_back();
    //                 }
    //                 break;
    //             }
    //         }
    //     }
    // }

    // Print the top 10 phrases for each length.
    for(int i = 0; i < 10; ++i){
        test << "Top " << i+1 << " phrases\n";
        for(auto p : combinedVec[i]){
            test << p.second << '\t' << p.first << endl;
        }
        test << "=================\n";
    }

    test.close();
    cout << "Time computed: " << (double)(end - start) / 1000 << " seconds" << endl;

    return 0;
}