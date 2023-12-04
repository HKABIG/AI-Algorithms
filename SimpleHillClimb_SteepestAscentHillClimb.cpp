#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> target = {{1,2,3},{8,0,4},{7,6,5}};

void printPuzzle(vector<vector<int>>& puzzle, int heuristic) {
    cout << "--------------------------" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Heuristic value is " << heuristic << endl;
}

int getHeuristic(vector<vector<int>>& puzzle) {
    int h =  0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            h += abs(puzzle[i][j] - target[i][j]);
        }
    }
    return h;
}

void simpleHillClimb(vector<vector<int>>& puzzle, int x, int y, int heuristic) {
    int dx[] = {0, -1, 0, 1};
    int dy[] = {1, 0, -1, 0};
    vector<vector<vector<int>>> moves;
    vector<vector<int>> ans;
    int n;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            vector<vector<int>> move = puzzle;
            swap(move[x][y], move[nx][ny]);
            int h = getHeuristic(move);
            moves.push_back(move);
            if (h < heuristic) {
                ans = move;
                n = h;
                break;
            }
        }
    }

    if (ans.size() == 0) {
        cout << "You have reached a local maximum" << endl;
        printPuzzle(moves[0], n);
    }
    printPuzzle(ans, n);
}

void simpleAscentHillClimb(vector<vector<int>>& puzzle, int& x, int& y, int& heuristic) {
    int dx[] = {0, -1, 0, 1};
    int dy[] = {1, 0, -1, 0};
    bool improved = true;

    while (improved) {
        improved = false;
        vector<vector<int>> bestMove = puzzle;
        int bestHeuristic = heuristic;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3 && (puzzle[nx][ny] == 0 || puzzle[x][y] == 0)) {
                vector<vector<int>> move = puzzle;
                swap(move[x][y], move[nx][ny]);
                int h = getHeuristic(move);
                if (h < bestHeuristic) {
                    bestMove = move;
                    bestHeuristic = h;
                    x = nx; // Update the empty tile's new position
                    y = ny;
                    improved = true;
                }
            }
        }

        if (improved) {
            puzzle = bestMove; // Update the puzzle to the new state
            heuristic = bestHeuristic; // Update the heuristic value
            printPuzzle(puzzle, heuristic);
        } else {
            cout << "Local maximum reached" << endl;
        }
    }
}

int main() {
    vector<vector<int>> puzzle(3, vector<int>(3, 0));
    int x, y;
    int heuristic = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num;
            cin >> num;
            if (num == 0) {
                x = i;
                y = j;
            }
            heuristic += abs(puzzle[i][j] - target[i][j]);
            puzzle[i][j] = num;
        }
    }

    cout << "-------------------------" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Choose the algorithm:" << endl;
    cout << "1. Simple Hill Climb" << endl;
    cout << "2. Simple Ascent Hill Climb" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            simpleHillClimb(puzzle, x, y, heuristic);
            break;
        case 2:
            simpleAscentHillClimb(puzzle, x, y, heuristic);
            break;
        default:
            cout << "Invalid choice" << endl;
    }

    return 0;
}
