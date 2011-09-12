#include <iostream>
#include <fstream>
#include <queue>
#include "stdlib.h"
#include "string.h"

using namespace std;

typedef struct {
    int depth;
    int nums[10];
} node;

bool is_end(int *nums, int count) {
    bool flag = true;

    for (int i=0; i<count; i++) {
        flag = flag && (nums[i] < 0);
    }

    return flag;
}

void dump(node &n) {
    cout << "depth: " << n.depth << endl;
    for (int i=0; i<10; i++) {
        cout << n.nums[i] << " ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "input file" << endl;
        abort();
    }

    int T, N;
    int nums[10];

    ifstream ifs(argv[1]);

    ifs >> T;

    for (int i=0; i<T; i++) {
        ifs >> N;

        for (int h=0; h<N; h++) {
            ifs >> nums[h];
        }

        queue<node> q;

        node state;

        memcpy(state.nums, nums, sizeof(int)*10);
        state.depth = 0;

        q.push(state);

        while (!q.empty()) {
            node n;
            n = q.front();
            q.pop();

            if (is_end(n.nums, N)) {
                cout << n.depth << endl;
                break;
            }

            for (int h=0; h<N; h++) {
                if (n.nums[h] > 0) {
                    state.nums[h] = n.nums[h] / 2;
                } else {
                    state.nums[h] = n.nums[h];
                }
            }
            state.depth = n.depth + 1;

            q.push(state);

            for (int h=0; h<N; h++) {
                if (n.nums[h] % 5 == 0) {
                    state.nums[h] = -1;
                } else {
                    state.nums[h] = n.nums[h];
                }
            }
            state.depth = n.depth + 1;

            if (memcmp(n.nums, state.nums, sizeof(int)*N) != 0) q.push(state);

        }


    }

    ifs.close();
}
