struct Node{
    char letter;
    int freq;
    Node* left;
    Node* right;
    Node(int f, char c = 0, Node* l = nullptr, Node* r = nullptr){
        freq = f;
        letter = c;
        left = l;
        right = r;
    }
};

struct Compare{
    bool operator()(Node* a, Node* b){
        return a->freq > b->freq;
    }
};