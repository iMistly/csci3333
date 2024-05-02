#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <functional>
#include "node.h"
using namespace std;

// Function to create the huffman codes for each character
void createCodes(Node* root, string code, map<char, string>& codes){
    if(root->left == nullptr && root->right == nullptr){
        codes[root->letter] = code;
        return;
    }
    createCodes(root->left, code + "0", codes);
    createCodes(root->right, code + "1", codes);
}

int main(){
    // Count the frequency of each character in the file
    ifstream text("test.txt");
    if(!text){
        cout << "File not found" << endl;
        return -1;
    }
    map<char, int> freq;
    char c;
    while(text.get(c)){
        freq[c]++;
    }
    text.close();

    // Create a priority queue of nodes. Effectively a min heap
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for(auto i : freq){
        pq.push(new Node(i.second, i.first));
    }
    while(pq.size() > 1){
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        pq.push(new Node(left->freq + right->freq, 0, left, right));
    }

    // Create a map of characters to their huffman codes
    map<char, string> codes;
    createCodes(pq.top(), "", codes);

    // Encode the file
    ofstream encoded("encoded.txt");
    text.open("test.txt");
    while(text.get(c)){
        encoded << codes[c];
    }
    text.close();
    encoded.close();

    // Decode the encoded file
    ifstream encodedText("encoded.txt");
    ofstream decoded("decoded.txt");
    map<string, char> reverseCodes;
    for(auto i : codes){
        reverseCodes[i.second] = i.first;
    }
    string code;
    while(encodedText.get(c)){
        code += c;
        if(reverseCodes.find(code) != reverseCodes.end()){
            decoded << reverseCodes[code];
            code = "";
        }
    }
    encodedText.close();
    decoded.close();

    return 0;
}