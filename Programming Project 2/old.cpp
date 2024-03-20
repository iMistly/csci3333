#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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
    string ending_punctuation = ".!?";

    // File into string
    getline(file, line);
    fileString += line;
    while(file.eof() == false){
        getline(file, line);
        while(line.length() == 0){
            if(file.eof() == true){break;}
            getline(file, line);
        }
        if(file.eof() == true){break;}
        fileString += " " + line;

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
            else if(fileString[i] == '*'){
                fileString.erase(i, 1);
                i--;
            }
        }

        // Read string character by character until . or ! or ? is found
        int start = 0;
        for(int i = 0; i < fileString.length(); i++){
            if(ending_punctuation.find(fileString[i]) != string::npos){
                sentences.push_back(fileString.substr(start, i - start + 1));
                start = i + 1;
                fileString = fileString.substr(start);
            }
        }
    }
    if(fileString.length() > 0){
        sentences.push_back(fileString);
    }

    // Remove empty strings, leading and trailing spaces, and sentences that start with punctuation
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

// Return array of words from sentence
vector<string> getWordsFromSentence(string sentence){
    vector<string> words;
    string word = "";
    string punctuation = ".,!?()[]{};:\"";
    for(int i = 0; i < sentence.length(); i++){
        // If space or punctuation, add word to vector and reset word
        if(sentence[i] == ' ' || punctuation.find(sentence[i]) != string::npos){
            if(word.length() > 0){
                // Lowercase word
                for(int j = 0; j < word.length(); j++){
                    word[j] = tolower(word[j]);
                }
                words.push_back(word);
            }
            word = "";
        }
        else{
            // If not punctuation, add to word
            word += sentence[i];
        }
    }
    if(word.length() > 0){
        // Lowercase word
        for(int j = 0; j < word.length(); j++){
            word[j] = tolower(word[j]);
        }
        words.push_back(word);
    }
    return words;
}

// Function to generate hash table of phrases
// Iterate n from 1 to 10 (This is the length of the phrases we are looking for)
    // For each sentence, get words
    // Find all phrases of length n
    // Add to a hash table
    // Write top 10 phrases to file
void generateHashTable(vector<string>& sentences){
    // Open file
    ofstream file("phrases.txt");

    for(int n = 1; n <= 10; n++){
        unordered_map<string, int> phrases;
        for(int i = 0; i < sentences.size(); i++){
            vector<string> words = getWordsFromSentence(sentences[i]);
            for(int j = 0; j < words.size() - n + 1; j++){
                string phrase = "";
                for(int k = 0; k < n; k++){
                    // If single word, dont add space
                    if(n == 1){
                        phrase += words[j + k];
                        break;
                    }
                    else{
                        phrase += words[j + k] + " ";
                    }
                }
                if(phrases.find(phrase) == phrases.end()){
                    phrases[phrase] = 1;
                }
                else{
                    phrases[phrase]++;
                }
            }
        }
        file << "Top phrases of length: " << n << endl;
        file << "-------------------------" << endl;
        int numPhrases = min(10, static_cast<int>(phrases.size()));
        for(int i = 0; i < numPhrases; i++){
            int maxNum = 0;
            string maxPhrase = "";
            for(auto it = phrases.begin(); it != phrases.end(); it++){
                if(it->second > maxNum){
                    maxNum = it->second;
                    maxPhrase = it->first;
                }
            }
            file << i+1 << ". " << maxPhrase << " " << maxNum << endl;
            phrases.erase(maxPhrase);
        }
        file << endl;
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

    vector<string> sentences = getSentencesFromFile("longParagraph.txt");
    generateHashTable(sentences);
    // End timer
    clock_t end = clock();
    cout << "Time: " << (double)(end - start) / 1000 << " seconds" << endl;
    
    return 0;
}