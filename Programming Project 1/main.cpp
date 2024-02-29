#include <iostream>
#include <iomanip>
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

    int priorityValue(){
        switch(getOp()){
            case ')':
                return 0;
            case '(':
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            default:
                return 3;
        }
    }

    bool isHigherPriority(TreeNode *toCompare){
        if(!tag && op == '('){return true;}
        return priorityValue() >= toCompare->priorityValue();
    }
};

queue<TreeNode*> convertToNode(string expression){
    queue<TreeNode*> exp;
    string numbers = ".0123456789";
    string operators = "()+-*/";
    string logOp = "!<>=&|";
    string num;
    bool isNum = false;
    bool error = false;

    string::iterator it = expression.begin();

    while(it != expression.end()){
        if(numbers.find(*it) != string::npos){
            num += *it;
            isNum = true;
        }
        else if(operators.find(*it) != string::npos){
            if(isNum){
                exp.push(new TreeNode(true, stof(num), '#'));
                num = "";
                isNum = false;
            }
            exp.push(new TreeNode(false, 0, *it));
        }
        else if(logOp.find(*it) != string::npos){
            switch(*it){
                case('!'):
                    exp.push(new TreeNode(false, 0, *it));
                    break;
                case('<'):
                    if(*(it+1) == '='){
                        exp.push(new TreeNode(false, 0, 'L'));
                        ++it;
                    }
                    else{exp.push(new TreeNode(false, 0, 'l'));}
                    break;
                case('>'):
                    if(*(it+1) == '='){
                        exp.push(new TreeNode(false, 0, 'G'));
                        ++it;
                    }
                    else{exp.push(new TreeNode(false, 0, 'g'));}
                    break;
                case('='):
                    if(*(it+1) == '='){
                        exp.push(new TreeNode(false, 0, '='));
                        ++it;
                    }
                    else{
                        cout << "A single '=' is not a valid expression." << endl;
                        error = true;
                    }
                    break;
                case('&'):
                    if(*(it+1) == '&'){
                        exp.push(new TreeNode(false, 0, 'a'));
                        ++it;
                    }
                    else{
                        cout << "This program doesn't support bitwise operator '&'." << endl;
                        error = true;
                    }
                    break;
                case('|'):
                    if(*(it+1) == '|'){
                        exp.push(new TreeNode(false, 0, 'o'));
                        ++it;
                    }
                    else{
                        cout << "This program doesn't support bitwise operator '|'." << endl;
                        error = true;
                    }
                    break;
            }
            if(error){return (queue<TreeNode*>());}
        }
        ++it;
    }

    if(isNum) {exp.push(new TreeNode(true, stof(num), '#'));}
    
    return exp;
}

TreeNode* buildTree(queue<TreeNode*> exp){
    stack<TreeNode*> numbers;
    stack<TreeNode*> operators;
    stack<TreeNode*> logOps;
    TreeNode *root, *front;
    while(!(exp.empty())){
        front = exp.front();
        if(front->getTag()){
            numbers.push(front);
            exp.pop();
        }
        else if(front->priorityValue() == 3){
            logOps.push(front);
        }
        else{
            if(operators.empty()){
                operators.push(front);
                exp.pop();
            }
            else if(front->isHigherPriority(operators.top())){
                operators.push(front);
                exp.pop();
            }
            else{
                while(!(operators.empty() || front->isHigherPriority(operators.top()))){
                    if(operators.top()->getOp() == '(' && front->getOp() == ')'){
                        exp.pop();
                        operators.pop();
                        break;
                    }
                    else if(numbers.size() >= 2){
                        TreeNode *tmp = operators.top();
                        operators.pop();
                        tmp->setRight(numbers.top());
                        numbers.pop();
                        tmp->setLeft(numbers.top());
                        numbers.pop();
                        numbers.push(tmp);
                    }
                    else {
                        cout << "There isn't enough numbers" << endl;
                        return new TreeNode(false, 0, '~');
                    }
                }
            }
        }
    }
    while(!(operators.empty())){
        if(numbers.size() >= 2){
            TreeNode *tmp = operators.top();
            operators.pop();
            tmp->setRight(numbers.top());
            numbers.pop();
            tmp->setLeft(numbers.top());
            numbers.pop();
            numbers.push(tmp);
        }
        else{
            cout << "There is a left over operator: " << operators.top()->getOp() << endl;
            return new TreeNode(false, 0, '~');
        }
    }
    while(!(logOps.empty())){
        if(numbers.size() >= 2){
            TreeNode *tmp = logOps.top();
            logOps.pop();
            tmp->setRight(numbers.top());
        }
    }
    if(numbers.size() == 1)
        root = numbers.top();
    else{
        cout << "Tree ended up with too many numbers" << endl;
        return new TreeNode(false, 0, '~');
    }

    cout << "Got to the end!" << endl;
    return root;
}

float calculator(TreeNode *root){
    if(root->getOp() == '~'){return -1;}

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

string inorderTraversal(TreeNode* root) {
    if (root == nullptr || root->getOp() == '~') {return "Syntax error.";}

    ostringstream fString;
    if(root->getTag())
        fString << root->getValue();
    else
        fString << '(' << inorderTraversal(root->getLeft()) << root->getOp() << inorderTraversal(root->getRight()) << ')';
    
    return fString.str();
}

string preorderTraversal(TreeNode* root){
    if (root == nullptr) {return "";}
    if (root->getOp() == '~') {return "Syntax error.";}

    ostringstream fString;

    if(root->getTag())
        fString << root->getValue() << ' ';
    else 
        fString << root->getOp() << ' ';

    fString << preorderTraversal(root->getLeft());
    fString << preorderTraversal(root->getRight());

    return fString.str();
}

string postorderTraversal(TreeNode* root){
    if (root == nullptr) {return "";}
    if (root->getOp() == '~') {return "Syntax error.";}

    ostringstream fString;

    fString << postorderTraversal(root->getLeft());
    fString << postorderTraversal(root->getRight());

    if(root->getTag())
        fString << root->getValue() << ' ';
    else 
        fString << root->getOp() << ' ';

    return fString.str();
}

int main(){
    ifstream inFile;
    string tmp;
    inFile.open("tests.txt");
    while(getline(inFile, tmp)){
        if(tmp == ""){
            continue;
        }
        queue<TreeNode*> exp = convertToNode(tmp);
        TreeNode *root = buildTree(exp);
        if(root->getOp() != '~'){
            cout << "Evaluation:\t" << calculator(root) << endl;
            cout << "In-order:\t" << inorderTraversal(root) << endl;
            cout << "Pre-order:\t" << preorderTraversal(root) << endl;
            cout << "Post-order:\t" << postorderTraversal(root) << endl;
        }
        cout << endl;
    }
    
    return 0;
}