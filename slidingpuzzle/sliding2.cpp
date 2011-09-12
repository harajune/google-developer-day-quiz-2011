#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <boost/unordered_set.hpp>

using namespace std;

typedef boost::unordered_set<string> memo_set;


typedef struct{
    int position;
    string operation;
    char board[37];
    int cost;
} node;

class node_comp
{
    public:
        bool operator()(const node &lhs, const node &rhs) const
        {
            return lhs.cost > rhs.cost;
        }
};

//typedef queue<node> node_q;
typedef priority_queue<node, vector<node>, node_comp> node_q;

void print_board(const node &n, int w, int h) {
    cout << n.operation << endl;
    cout << n.position << endl;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            cout << n.board[i*w + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int estimate_cost(const node &n1, const node &n2, int w, int h) {
    int cost = 0;

    for (int i=0; i<w*h; i++) {
        if (n1.board[i] == '=' || n1.board[i] == '0') continue;

        for (int j=0; j<w*h; j++) {
            if (n1.board[i] == n2.board[j]) {
                cost += abs((i%w) - (j%w)) + abs(i/w - j/w);
                break;
            }
        }
    }

    return cost + n1.operation.size() / 2;
}


bool is_end(const node &n, int w, int h) {
    char buffer = 0x00;

    for (int i=0; i<w*h-1; i++) {
        if (n.board[i] == '=') continue;
        if (n.board[i] == '0') return false;

        if (n.board[i] < buffer) return false;

        buffer = n.board[i];
    }

    return true;
}

int up(node &n, int w, int h) {
    if (n.position - w < 0 || n.board[n.position - w] == '=') {
        return -1;
    }
        
    n.board[n.position] = n.board[n.position - w];
    n.board[n.position - w] = '0';
    n.operation += "U";
    n.position = n.position - w;

    return n.position;
}

int down(node &n, int w, int h) {
    if (n.position + w >= w*h || n.board[n.position + w] == '=') {
        return -1;
    }
        
    n.board[n.position] = n.board[n.position + w];
    n.board[n.position + w] = '0';
    n.operation += "D";
    n.position = n.position + w;

    return n.position;
}

int right(node &n, int w, int h) {
    if ((n.position % w) + 1 >= w || n.board[n.position + 1] == '=') {
        return -1;
    }
        
    n.board[n.position] = n.board[n.position + 1];
    n.board[n.position + 1] = '0';
    n.operation += "R";
    n.position = n.position + 1;

    return n.position;
}

int left(node &n, int w, int h) {
    if ((n.position % w) - 1 < 0 || n.board[n.position - 1] == '=') {
        return -1;
    }
        
    n.board[n.position] = n.board[n.position - 1];
    n.board[n.position - 1] = '0';
    n.operation += "L";
    n.position = n.position - 1;

    return n.position;
}

void make_answer(int w1, int h1, const node &n1, node &n2) {
    vector<char> v;

    for (int i=0; i<w1*h1; i++) {
        if (n1.board[i] != '0' && n1.board[i] != '=') v.push_back(n1.board[i]);
    }

    vector<char>::iterator it;

    sort(v.begin(), v.end());

    int counter = 0;
    for (vector<char>::iterator i=v.begin(); i != v.end(); i++) {
        while (n1.board[counter] == '=') {
            n2.board[counter] = '=';
            counter++;
        }

        n2.board[counter] = (char)*i;
        counter++;
    }

    n2.board[counter] = '0';
}

int solv_puzzle(int w1, int h1, const node &nn, int &lx, int &rx, int &ux, int &dx) {
    node_q q;
    node n = nn;
    
    memo_set memo;

    node answer;
    make_answer(w1, h1, n, answer);

    n.cost = estimate_cost(n, answer, w1, h1);

    q.push(n);

    //print_board(n, w1, h1);
    cerr << w1 << "\t" << h1 << "\t" << n.board << endl;

    while (!q.empty()) {

        if (memo.size() > 5000000) {
            break;
        }
        node n1;
        //n1 = q.front();
        n1 = q.top();
        q.pop();

        if (is_end(n1, w1, h1)) {
            //print_board(n1, w1, h1);
            cout << n1.operation << endl;
            return n1.operation.size();
        }

        node n2;
        n2 = n1;

        if (n1.operation.size() > w1*h1*4) continue;

        if (up(n2, w1, h1) >= 0 && memo.find(n2.board) == memo.end()) {
            memo.insert(n2.board);
            n2.cost = estimate_cost(n2, answer, w1, h1);
            q.push(n2);
        }
        n2 = n1;
        if (down(n2, w1, h1) >= 0 && memo.find(n2.board) == memo.end()) {
            memo.insert(n2.board);
            n2.cost = estimate_cost(n2, answer, w1, h1);
            q.push(n2);
        }
        n2 = n1;
        if (right(n2, w1, h1) >= 0 && memo.find(n2.board) == memo.end()) {
            memo.insert(n2.board);
            n2.cost = estimate_cost(n2, answer, w1, h1);
            q.push(n2);
        }
        n2 = n1;
        if (left(n2, w1, h1) >= 0 && memo.find(n2.board) == memo.end()) {
            memo.insert(n2.board);
            n2.cost = estimate_cost(n2, answer, w1, h1);
            q.push(n2);
        }

    }
    cout << endl;
    
    return -1;

}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "input filename" << endl;
        abort();
    }

    ifstream input_file(argv[1]);

    int lx, rx, ux, dx, all_number;
    input_file >> lx >> rx >> ux >> dx >> all_number;

    while (all_number--) {
        string line;

        input_file >> line;

        int w1, h1;

        node n;

        sscanf(line.c_str(), "%d,%d,%s", &w1, &h1, n.board);

        for (int i=0; i<w1*h1; i++) {
            if (n.board[i] == '0') {
                n.position = i;
                break;
            }
        }

        //if (w1*h1 > 16) continue;

        solv_puzzle(w1, h1, n, lx, rx, ux, dx);

    }

    input_file.close();

}
