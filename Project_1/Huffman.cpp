//
// Created by beans on 2017/10/16.
//
#include <cstring>
#include <iostream>
#include <deque>
#include <fstream>

using namespace std;
string input;

struct Node {
    bool have_value;
    double v;
    string code;
    Node *left, *right;

    Node() : have_value(false), left(NULL), right(NULL) {}
};

bool compare(Node *a, Node *b) {
    return a->v < b->v;
}

Node *root;
deque<Node *> forest;
int cnt = 0;

/// add node to forest
/// \param code
/// \param pro
void add_node(string code, double pro) {
    cnt++;
    Node *tmp = new Node();
    tmp->have_value = true;
    tmp->v = pro;
    tmp->code = code;
    forest.push_back(tmp);
}

/// reslove the input data
/// \param start_pos
/// \param end_pos
void init(int start_pos, int end_pos) {
    string tmp = input.substr(start_pos, end_pos - start_pos + 1);
    int offset = tmp.find(",");
    string code = tmp.substr(0, offset);
    double pro = atof(tmp.substr(offset + 1, tmp.size() - offset).c_str());
    printf("%-10s\t%lf\n",code.c_str(),pro);                                     //print
    add_node(code, pro);
}

///
/// \param tmp
/// \param huffman_code
void dfs(Node *tmp, string huffman_code) {
    if (tmp->left == NULL && tmp->right == NULL) {
       // cout << tmp->code << " " << huffman_code << endl;
        printf("%-10s\t%s\n",tmp->code.c_str(),huffman_code.c_str());
    } else {
        if (tmp->left != NULL) {
            //huffman_code.append("0");
            dfs(tmp->left, huffman_code + "0");
            //huffman_code.
        }
        if (tmp->right != NULL) {
            dfs(tmp->right, huffman_code + "1");
        }
    }
}



void getHuffmanTree() {
    for (int i = 0; i < cnt - 1; i++) {
        sort(forest.begin(), forest.end(), compare);
        Node *ptr = new Node;
        ptr->v = forest[0]->v + forest[1]->v;
        ptr->left = forest[0];
        ptr->right = forest[1];
        forest.pop_front();
        forest.pop_front();
        forest.push_back(ptr);
    }
    root = forest.front();
}

int main() {
    int start_pos, end_pos;

    string tmp_input;
    /*
    ifstream fin;
    fin.open("test.in");
    cin.rdbuf(fin.rdbuf());
     */
    while (cin >> tmp_input) {
        input += tmp_input;

    }
    cout << "----------input------------" << endl;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '{')
            continue;
        if (input[i] == '(')
            start_pos = i + 1;
        if (input[i] == ')') {
            end_pos = i - 1;
            init(start_pos, end_pos);
        }
    }
    cout << "----------output------------" << endl;
    getHuffmanTree();
    dfs(root, "");
}