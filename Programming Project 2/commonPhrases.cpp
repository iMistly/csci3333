#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <fstream>
using namespace std;

vector<string> getSentences(string filename){
    fstream file;
    vector<string> sentences;
    string fileStr = "";
    string endPunc = ".!?";
    string specialPunc = "\"{}[]()~";
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

void mergeSort(vector<tuple<string, int>>& left, vector<tuple<string, int>>& right, vector<tuple<string, int>>& phrases){
    int leftSize = left.size();
    int rightSize = right.size();
    // Counters
    int i{}, j{}, k{};

    while (j < leftSize && k < rightSize) 
    {
        if (get<1>(left[j]) < get<1>(right[k])) {
            phrases[i] = left[j];
            j++;
        }
        else {
            phrases[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < leftSize) {
        phrases[i] = left[j];
        j++; i++;
    }
    while (k < rightSize) {
        phrases[i] = right[k];
        k++; i++;
    }
}

void sort(vector<tuple<string, int>>& phrases){
    int size = phrases.size();
    if(size <= 1){
        return;
    }

    int mid = size /2;
    vector<tuple<string, int>> left;
    vector<tuple<string, int>> right;

    for(size_t i = 0; i < mid; ++i){
        left.push_back(phrases[i]);
    }
    for(size_t i = 0; i < size-mid; ++i){
        left.push_back(phrases[mid+i]);
    }

    sort(left);
    sort(right);
    mergeSort(left, right, phrases);
}

vector<tuple<string, int>> commonPhrases(unordered_map<string, int>& phrases, int num){
    vector<tuple<string, int>> mostCommon;

    // Sorting algorithm 
    for(int i = 0; i<num; ++i){
        tuple<string, int> maxPhrase;
        int max{}; // Initialize max outside the loop
        for(auto x : phrases){
            if(x.second > max){
                maxPhrase = make_tuple(x.first, x.second);
                max = x.second;
            }
        }
        mostCommon.push_back(maxPhrase);
        phrases.erase(get<0>(maxPhrase));
    }

    return mostCommon;
}

int main(){
    clock_t start = clock();

    ofstream file("out.txt");
    string fileName = "huckleberryFinn.txt";
    file << "This file is finding the most common phrases in '" << fileName << "'\n\n";
    vector<string> sentences = getSentences(fileName);

    for(int i = 1; i <= 3; ++i){
        unordered_map<string, int> phrases = getPhrases(sentences, i);
        // for(auto x : phrases){
        //     file << x.second << "\t\t\t" << x.first << endl;
        // }
        // vector<tuple<string, int>> vecPhrases;
        // for(auto x : phrases){
        //     vecPhrases.push_back(make_pair(x.first, x.second));
        //     phrases.erase(x.first);
        // }
        // sort(vecPhrases);

        // for(auto x : vecPhrases){
        //     file << get<1>(x) << "\t\t\t" << get<0>(x) << endl;
        // }

        auto mostCommon = commonPhrases(phrases, 10);
        file << "Most common " << i << " word phrases." << endl;
        file << "------------------------" << endl;
        for(auto x : mostCommon){
            file << get<1>(x) << "\t\t\t" << get<0>(x) << endl;
        }
        file << endl;
    }

    clock_t end = clock();
    std::cout << "Time computed: " << (double)(end - start) / 1000 << " seconds" << endl;
    file << "\nTime computed: " << (double)(end - start) / 1000 << " seconds" << endl;
    file.close();

    return 0;
}