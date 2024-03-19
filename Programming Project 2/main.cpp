#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
using namespace std;

// Return array of sentences from file
vector<string> getSentencesFromFile(string fileName){
    // Open file
    ifstream file(fileName);
    string line;
    vector<string> sentences;
    string fileString;

    // File into string
    getline(file, line);
    fileString += line;
    while(getline(file, line)){
        fileString += " " + line;
    }

    // Remove non-ASCII characters
    for(int i = 0; i < fileString.length(); i++){
        if(fileString[i] < 0 || fileString[i] > 127){
            fileString.erase(i, 1);
        }
    }
    // Remove quotes, double hyphens
    for(int i = 0; i < fileString.length(); i++){
        if(fileString[i] == '\"'){
            fileString.erase(i, 1);
            i--;
        }
        else if(fileString[i] == '-' && fileString[i + 1] == '-'){
            fileString.erase(i, 2);
            i--;
        }
    }

    // Read string character by character until . or ! or ? is found
    int start = 0;
    for(int i = 0; i < fileString.length(); i++){
        if(fileString[i] == '.' || fileString[i] == '!' || fileString[i] == '?'){
            sentences.push_back(fileString.substr(start, i - start + 1));
            start = i + 1;
        }
    }

    // Remove empty strings, leading and trailing spaces
    for(int i = 0; i < sentences.size(); i++){
        if(sentences[i].length() == 0){
            sentences.erase(sentences.begin() + i);
            i--;
        }
        else if(sentences[i][0] == '.' || sentences[i][0] == '!' || sentences[i][0] == '?'){
            sentences.erase(sentences.begin() + i);
            i--;
        }
        else{
            while(sentences[i][0] == ' '){
                sentences[i] = sentences[i].substr(1);
            }
            while(sentences[i][sentences[i].length() - 1] == ' '){
                sentences[i] = sentences[i].substr(0, sentences[i].length() - 1);
            }
        }
    }

    // Close file
    file.close();

    return sentences;
}

vector<string> getWordsFromSentence(string sentence){
    vector<string> words;
    string word = "";
    string punctuation = ".,!?()[]{};:\"";
    for(int i = 0; i < sentence.length(); i++){
        if(sentence[i] == ' '){
            if(word.length() > 0){
                words.push_back(word);
            }
            word = "";
        }
        else if(punctuation.find(sentence[i]) != string::npos){
            continue;
        }
        else{
            word += sentence[i];
        }
    }
    if(word.length() > 0){
        words.push_back(word);
    }
    return words;
}

// Function to generate hash table of phrases
void generateHashTable(vector<string> sentences){
    // Open file
    ofstream file("phrases.txt");
    // Hash table
    vector<vector<string>> hashTable(1000);
    // Iterate through sentences
    for(int i = 0; i < sentences.size(); i++){
        vector<string> words = getWordsFromSentence(sentences[i]);
        // Iterate through words
        for(int j = 0; j < words.size() - 2; j++){
            string phrase = words[j] + " " + words[j + 1] + " " + words[j + 2];
            int index = 0;
            for(int k = 0; k < phrase.length(); k++){
                index += (int)phrase[k];
            }
            index %= 1000;
            hashTable[index].push_back(phrase);
        }
    }
    // Write hash table to file
    for(int i = 0; i < hashTable.size(); i++){
        for(int j = 0; j < hashTable[i].size(); j++){
            file << hashTable[i][j] << endl;
        }
    }
    // Close file
    file.close();
}



int main(){
    // Start timer
    clock_t start = clock();
    // Check if phrases.txt exists then delete it
    ifstream checkFile("phrases.txt");
    if(checkFile){
        remove("phrases.txt");
    }

    vector<string> sentences = getSentencesFromFile("huckleberryFinn.txt");
    generateHashTable(sentences);
    // End timer
    clock_t end = clock();
    cout << "Time: " << (double)(end - start) / 1000 << " seconds" << endl;
    
    return 0;
}