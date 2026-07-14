#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int N, M;
vector<string> grid;

// 检查现有黑色地毯是否相邻
bool check_initial() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'B') {
                for (int k = 0; k < 4; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < N && nj >= 0 && nj < M) {
                        if (grid[ni][nj] == 'B') {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

// 检查水平对称是否可行
bool check_horizontal() {
    vector<vector<char>> temp(N, vector<char>(M, '.'));
    
    // 应用水平对称规则
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int sym_i = N - i - 1;
            if (grid[i][j] == 'B' || grid[sym_i][j] == 'B') {
                temp[i][j] = 'B';
                temp[sym_i][j] = 'B';
            }
        }
    }
    
    // 检查是否有相邻的B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (temp[i][j] == 'B') {
                for (int k = 0; k < 4; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < N && nj >= 0 && nj < M) {
                        if (temp[ni][nj] == 'B') {
                            return false;
                        }
                    }
                }
            }
        }
    }
    
    return true;
}

// 检查垂直对称是否可行
bool check_vertical() {
    vector<vector<char>> temp(N, vector<char>(M, '.'));
    
    // 应用垂直对称规则
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int sym_j = M - j - 1;
            if (grid[i][j] == 'B' || grid[i][sym_j] == 'B') {
                temp[i][j] = 'B';
                temp[i][sym_j] = 'B';
            }
        }
    }
    
    // 检查是否有相邻的B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (temp[i][j] == 'B') {
                for (int k = 0; k < 4; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < N && nj >= 0 && nj < M) {
                        if (temp[ni][nj] == 'B') {
                            return false;
                        }
                    }
                }
            }
        }
    }
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N >> M;
    grid.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    
    // 检查初始状态是否合法
    if (!check_initial()) {
        cout << "No" << endl;
        return 0;
    }
    
    // 检查水平对称或垂直对称是否可行
    if (check_horizontal() || check_vertical()) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}