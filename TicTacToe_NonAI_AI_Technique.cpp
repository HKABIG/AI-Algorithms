#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int checkWin(vector<int> arr) {
    // Check rows
    if (arr[0] == 1 && arr[1] == 1 && arr[2] == 1) {
        return 1;
    }
    if (arr[3] == 1 && arr[4] == 1 && arr[5] == 1) {
        return 1;
    }
    if (arr[6] == 1 && arr[7] == 1 && arr[8] == 1) {
        return 1;
    }

    // Check columns
    if (arr[0] == 1 && arr[3] == 1 && arr[6] == 1) {
        return 1;
    }
    if (arr[1] == 1 && arr[4] == 1 && arr[7] == 1) {
        return 1;
    }
    if (arr[2] == 1 && arr[5] == 1 && arr[8] == 1) {
        return 1;
    }

    // Check diagonals
    if (arr[0] == 1 && arr[4] == 1 && arr[8] == 1) {
        return 1;
    }
    if (arr[2] == 1 && arr[4] == 1 && arr[6] == 1) {
        return 1;
    }

    return 0;
}

int checkBlock(vector<int> arr) {
    // Check block rows
    if (arr[0] == 2 && arr[1] == 2 && arr[2] == 1) {
        return 1;
    }
    if (arr[0] == 2 && arr[1] == 1 && arr[2] == 2) {
        return 1;
    }
    if (arr[0] == 1 && arr[1] == 2 && arr[2] == 2) {
        return 1;
    }

    if (arr[3] == 2 && arr[4] == 2 && arr[5] == 1) {
        return 1;
    }
    if (arr[3] == 2 && arr[4] == 1 && arr[5] == 2) {
        return 1;
    }
    if (arr[3] == 1 && arr[4] == 2 && arr[5] == 2) {
        return 1;
    }

    if (arr[6] == 2 && arr[7] == 2 && arr[8] == 1) {
        return 1;
    }
    if (arr[6] == 2 && arr[7] == 1 && arr[8] == 2) {
        return 1;
    }
    if (arr[6] == 1 && arr[7] == 2 && arr[8] == 2) {
        return 1;
    }

    // Check block columns
    if (arr[0] == 2 && arr[3] == 2 && arr[6] == 1) {
        return 1;
    }
    if (arr[0] == 2 && arr[3] == 1 && arr[6] == 2) {
        return 1;
    }
    if (arr[0] == 1 && arr[3] == 2 && arr[6] == 2) {
        return 1;
    }

    if (arr[1] == 2 && arr[4] == 2 && arr[7] == 1) {
        return 1;
    }
    if (arr[1] == 2 && arr[4] == 1 && arr[7] == 2) {
        return 1;
    }
    if (arr[1] == 1 && arr[4] == 2 && arr[7] == 2) {
        return 1;
    }

    if (arr[2] == 2 && arr[5] == 2 && arr[8] == 1) {
        return 1;
    }
    if (arr[2] == 2 && arr[5] == 1 && arr[8] == 2) {
        return 1;
    }
    if (arr[2] == 1 && arr[5] == 2 && arr[8] == 2) {
        return 1;
    }

    // Check block diagonals
    if (arr[0] == 2 && arr[4] == 2 && arr[8] == 1) {
        return 1;
    }
    if (arr[0] == 2 && arr[4] == 1 && arr[8] == 2) {
        return 1;
    }
    if (arr[0] == 1 && arr[4] == 2 && arr[8] == 2) {
        return 1;
    }

    if (arr[2] == 2 && arr[4] == 2 && arr[6] == 1) {
        return 1;
    }
    if (arr[2] == 2 && arr[4] == 1 && arr[6] == 2) {
        return 1;
    }
    if (arr[2] == 1 && arr[4] == 2 && arr[6] == 2) {
        return 1;
    }

    return 0;
}

int main() {
    int n = 3;
    vector<vector<char>> matrix(n, vector<char>(n));
    int xCount = 0;
    int oCount = 0;
    int zeroCount = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
            if (matrix[i][j] == 'x') xCount++;
            if (matrix[i][j] == 'o') oCount++;
            if (matrix[i][j] == '0') zeroCount++;
        }
    }

    if (abs(xCount - oCount) > 1) {
        cout << "Invalid matrix input" << endl;
        return 0;
    }

    cout << "The provided matrix looks like" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> vec;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'x') vec.push_back(1);
            if (matrix[i][j] == 'o') vec.push_back(2);
            if (matrix[i][j] == '0') vec.push_back(0);
        }
    }

    cout << "The 1D vector looks like" << endl;
    for (int i = 0; i < (n * n); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    int index = 0;
    int power = 1;
    for (int i = (n * n) - 1; i >= 0; i--) {
        index += vec[i] * (power);
        power *= 3;
    }

    cout << "The index is " << index << endl;
    cout << endl;

    // Lab Assignment 1.2 Begins from here
    cout << "Using AI Techniques for the best possible move" << endl;
    vector<pair<vector<int>, int>> possibleMoves;
    for (int i = 0; i < zeroCount; i++) {
        possibleMoves.push_back({vec, 0});
    }

    int j = 0;
    vector<int> answer;
    int score = 0;
    for (int i = 0; i < zeroCount; i++) {
        while (j < 9) {
            if (possibleMoves[i].first[j] == 0) {
                possibleMoves[i].first[j] = 1;
                if (checkWin(possibleMoves[i].first)) possibleMoves[i].second = 100;
                else if (checkBlock(possibleMoves[i].first)) possibleMoves[i].second = 50;
                else if (j == 4) possibleMoves[i].second = 4;
                else if (j % 2 == 1) possibleMoves[i].second = 2;
                else if (j % 2 == 0) possibleMoves[i].second = 3;
                j++;
                break;
            }
            j++;
        }
    }

    for (int i = 0; i < zeroCount; i++) {
        if (possibleMoves[i].second > score) {
            score = possibleMoves[i].second;
            answer = possibleMoves[i].first;
        }
        for (int j = 0; j < 9; j++) {
            cout << possibleMoves[i].first[j] << " ";
        }
        cout << possibleMoves[i].second << " ";
        cout << endl;
    }

    cout << "The possible move needs to be" << endl;
    for (auto it : answer) {
        cout << it << " ";
    }
    cout << endl;

    cout << "With a score of " << score << endl;
    return 0;
}
