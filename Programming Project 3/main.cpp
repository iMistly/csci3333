#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <chrono>
using namespace std;

int main(){
    // Timer
    auto timeStart = chrono::high_resolution_clock::now();

    // Load dictionary
    ifstream file("wordLadder_dictionary.txt");
    string line;
    vector<map<string,string>> wordList;

    while(getline(file, line)){
        // Filter non-ascii characters
        bool flag = false;
        for(auto &c : line){
            if(c < 0 || c > 127){flag = true; break;}
            c = tolower(c);
        }
        if(flag){continue;}

        auto len = line.size();
        if(wordList.size() < len){wordList.resize(len);}
        wordList[len-1][line];
    }
    file.close();

    // Timer
    auto timeEnd = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);
    cout << "Time taken to load dictionary: " << duration.count() << "ms" << endl;

    // Ask for start and end word
    string start{}, end{};

    while(start != "QQQ"){
        cout << "Enter start word (QQQ to quit): ";
        cin >> start;
        if(start == "QQQ"){break;}
        cout << "Enter end word: ";
        cin >> end;

        timeStart = chrono::high_resolution_clock::now();
        int len = start.size();

        if(start.size() != end.size() || wordList[len-1].find(start) == wordList[len-1].end() || wordList[len-1].find(end) == wordList[len-1].end()){
            cout << "No ladder found." << endl;
        }
        else if(start == end){
            cout << "Start and end words are the same." << endl;
        }
        else{
            // Lowercase the words
            for(auto &c : start){c = tolower(c);}
            for(auto &c : end){c = tolower(c);}

            // Find ladder using BFS (Breadth First Search)
            queue<string> q;
            q.push(start);
            map<string,string> parent;
            parent[start] = start;

            while(!q.empty()){
                auto current = q.front();
                q.pop();

                int index = 0;
                for(auto &c : current){
                    auto len = current.size();
                    auto &wordMap = wordList[len-1];
                    auto temp = current;
                    
                    for(char i = 'a'; i <= 'z'; i++){
                        if(i == c){continue;}
                        temp[index] = i;
                        if(wordMap.find(temp) != wordMap.end() && parent.find(temp) == parent.end()){
                            parent[temp] = current;
                            q.push(temp);
                        }
                    }
                    ++index;
                }
            }

            // Check if word is in graph
            if(parent.find(end) == parent.end()){
                cout << "No ladder found." << endl;
            }
            else{
                // Take steps to find ladder
                vector<string> ladder;
                for(auto i = end; i != start; i = parent[i]){
                    ladder.push_back(i);
                }
                ladder.push_back(start);

                // Print ladder
                for(auto i = ladder.rbegin(); i != ladder.rend(); i++){
                    cout << *i << endl;
                }
                cout << "Length: " << ladder.size() << endl; 
            }
        }

        // Timer
        timeEnd = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);
        cout << "Time taken to find ladder: " << duration.count() << "ms" << endl;
    }

    return 0;
}