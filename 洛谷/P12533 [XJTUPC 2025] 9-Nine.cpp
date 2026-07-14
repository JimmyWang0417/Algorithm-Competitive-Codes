#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

struct State {
    vector<string> A, B;
    vector<string> ops;
    State(vector<string> a, vector<string> b) : A(a), B(b) {}
    bool operator<(const State& other) const {
        if (A != other.A) return A < other.A;
        return B < other.B;
    }
};

vector<string> rotate_left(const vector<string>& mat) {
    vector<string> res(3, "000");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            res[2-j][i] = mat[i][j];
        }
    }
    return res;
}

vector<string> rotate_right(const vector<string>& mat) {
    vector<string> res(3, "000");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            res[j][2-i] = mat[i][j];
        }
    }
    return res;
}

vector<string> swap_col(const vector<string>& A, const vector<string>& B, int col) {
    vector<string> resA = A, resB = B;
    for (int i = 0; i < 3; ++i) {
        swap(resA[i][col], resB[i][col]);
    }
    return resA;
}

vector<string> swap_col_B(const vector<string>& A, const vector<string>& B, int col) {
    vector<string> resB = B;
    for (int i = 0; i < 3; ++i) {
        resB[i][col] = A[i][col];
    }
    return resB;
}

bool is_goal(const vector<string>& A, const vector<string>& B) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (A[i][j] != '0' || B[i][j] != '1') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<string> A(3), B(3);
    for (int i = 0; i < 3; ++i) {
        cin >> A[i];
    }
    for (int i = 0; i < 3; ++i) {
        cin >> B[i];
    }
    
    queue<State> q;
    map<pair<vector<string>, vector<string>>, bool> visited;
    
    q.push(State(A, B));
    visited[{A, B}] = true;
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        if (is_goal(curr.A, curr.B)) {
            cout << curr.ops.size() << endl;
            for (const string& op : curr.ops) {
                cout << op << endl;
            }
            return 0;
        }
        
        // 操作1：旋转A向左
        vector<string> newA = rotate_left(curr.A);
        if (!visited[{newA, curr.B}]) {
            visited[{newA, curr.B}] = true;
            State next_state(newA, curr.B);
            next_state.ops = curr.ops;
            next_state.ops.push_back("AL");
            q.push(next_state);
        }
        
        // 操作1：旋转A向右
        newA = rotate_right(curr.A);
        if (!visited[{newA, curr.B}]) {
            visited[{newA, curr.B}] = true;
            State next_state(newA, curr.B);
            next_state.ops = curr.ops;
            next_state.ops.push_back("AR");
            q.push(next_state);
        }
        
        // 操作1：旋转B向左
        vector<string> newB = rotate_left(curr.B);
        if (!visited[{curr.A, newB}]) {
            visited[{curr.A, newB}] = true;
            State next_state(curr.A, newB);
            next_state.ops = curr.ops;
            next_state.ops.push_back("BL");
            q.push(next_state);
        }
        
        // 操作1：旋转B向右
        newB = rotate_right(curr.B);
        if (!visited[{curr.A, newB}]) {
            visited[{curr.A, newB}] = true;
            State next_state(curr.A, newB);
            next_state.ops = curr.ops;
            next_state.ops.push_back("BR");
            q.push(next_state);
        }
        
        // 操作2：交换列
        for (int col = 0; col < 3; ++col) {
            vector<string> swapA = curr.A;
            vector<string> swapB = curr.B;
            for (int i = 0; i < 3; ++i) {
                swap(swapA[i][col], swapB[i][col]);
            }
            if (!visited[{swapA, swapB}]) {
                visited[{swapA, swapB}] = true;
                State next_state(swapA, swapB);
                next_state.ops = curr.ops;
                next_state.ops.push_back("C" + to_string(col + 1));
                q.push(next_state);
            }
        }
    }
    
    return 0;
}