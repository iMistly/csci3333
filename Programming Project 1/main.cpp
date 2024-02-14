#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

class TreeNode{
    private:
        bool tag;
        float value;
        char op;
        TreeNode *left;
        TreeNode *right;
    public:
    TreeNode(bool inTag, float inValue, char inOp, TreeNode *inLeft = nullptr, TreeNode *inRight = nullptr){
        tag = inTag;
        value = inValue;
        op = inOp;
        left = inLeft;
        right = inRight;
    }
    
    bool getTag(){
        return tag;
    }

    float getValue(){
        return value;
    }

    char getOp(){
        return op;
    }

    TreeNode* getLeft(){
        return left;
    }

    TreeNode* getRight(){
        return right;
    }

    void setLeft(TreeNode *inLeft){
        left = inLeft;
    }

    void setRight(TreeNode *inRight){
        right = inRight;
    }
};

queue<TreeNode*> convertToNode(string expression){
    queue<TreeNode*> exp;
    string numbers = ".0123456789";
    string operators = "()+-*/";
    string num;
    bool isNum = false;

    for(auto c : expression){
        if(numbers.find(c) != string::npos){
            num += c;
            isNum = true;
        }
        else if(operators.find(c) != string::npos){
            if(isNum){
                exp.push(new TreeNode(true, stof(num), '#'));
                num = "";
                isNum = false;
            }
            exp.push(new TreeNode(false, 0, c));
        }
    }

    if(isNum) {exp.push(new TreeNode(true, stof(num), '#'));}
    
    return exp;
}



// True if op1 is higher priority
// False if op2 is higher priority
bool compareOperators(char op1, char op2){
    string priority = ")(+-*/";
    cout << "Comparing: " << op1 << " & " << op2 << endl;
    if(priority.find(op1) > priority.find(op2)){
        cout<<"true"<<endl;
        return true;
    }
    else {cout<<"false"<<endl;return false;}
}

TreeNode* buildTree(queue<TreeNode*> exp){
    stack<TreeNode*> numbers;
    stack<TreeNode*> operators;
    TreeNode *root;
    while(!(exp.empty())){
        if(exp.front()->getTag()){
            numbers.push(exp.front());
            exp.pop();
        }
        else{
            if(operators.empty()){
                operators.push(exp.front());
                exp.pop();
            }
            else if(compareOperators(exp.front()->getOp(), operators.top()->getOp())){
                operators.push(exp.front());
                exp.pop();
            }
            else{
                while(!(operators.empty() || compareOperators(exp.front()->getOp(), operators.top()->getOp()))){
                    if(operators.top()->getOp() == '(' && exp.front()->getOp() == ')'){
                        exp.pop();
                        operators.pop();
                        break;
                    }
                    else if(numbers.size() >= 2){
                        TreeNode *tmp = operators.top();
                        operators.pop();
                        tmp->setLeft(numbers.top());
                        numbers.pop();
                        tmp->setRight(numbers.top());
                        numbers.pop();
                        numbers.push(tmp);
                    }
                    else {
                        cout << "Invalid expression" << endl;
                        break;
                        // return new TreeNode(false, 0, '!');
                    }
                }
            }
        }
    }
    cout << "Got to the end!" << endl;
    return root;
}

float calculator(TreeNode *root){
    if(root->getTag()){
        return root->getValue();
    }
    else{
        float left = calculator(root->getLeft());
        float right = calculator(root->getRight());
        switch(root->getOp()){
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                return left / right;
        }
    }
    return 0;
}



int main(){
    ifstream inFile;
    string tmp;
    inFile.open("tests.txt");
    while(getline(inFile, tmp)){
        queue<TreeNode*> exp = convertToNode(tmp);
        TreeNode *root = buildTree(exp);
        cout << calculator(root) << endl;
    }
    
    return 0;
}