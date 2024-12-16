#include <bits/stdc++.h>
using namespace std;

#define DIMENSION 3 // Size of board 3X3 formalized to avoid magic numbers

class Node {
public:
    vector<vector<int>> state;
    Node* parent;
    int cost;
    int heuristic;
    Node* next;
    Node* child;
    
    Node(vector<vector<int>> puzzleState, int pathCost, int heuristicValue, Node* parentNode) {
        this->cost = pathCost;
        this->heuristic = heuristicValue;
        this->state = puzzleState;
        this->parent = parentNode;
        next = NULL;
        child = NULL;
    }
};

void printBoard(vector<vector<int>> board, int size)
{
    for(int i = 0; i<size;++i)
    {
        for(int j = 0; j<size;++j)
        {
            cout<<board[i][j]<<' ';
        }
        cout<<'\n';
    }
}

vector<vector<int>> target = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};
Node* OPEN = NULL;
Node* CLOSED = NULL;

int calculateHeuristic(vector<vector<int>> puzzle) {
    int h = 0;
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            h += abs(target[i][j] - puzzle[i][j]);
        }
    }
    return static_cast<int>(pow(h, 0.5));
}

void push(Node* head) {
    if (OPEN == NULL) {
        OPEN = head;
        return;
    }
    int priority = head->heuristic;
    Node* start = OPEN;
    while (start->next != NULL && start->next->heuristic < priority) {
        start = start->next;
    }
    head->next = start->next;
    start->next = head;
}

void pushClosed(Node* head){
    if (CLOSED == NULL) {
        CLOSED = head;
        return;
    }
    int priority = head->heuristic;
    Node* start = CLOSED;
    while (start->next != NULL && start->next->heuristic < priority) {
        start = start->next;
    }
    head->next = start->next;
    start->next = head;
}

void getNeighbors(Node* node) {
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            if (node->state[i][j] == 0) {
                for (int k = 0; k < 4; k++) {
                    if (0 <= i + dx[k] && i + dx[k] < 3 && 0 <= j + dy[k] && j + dy[k] < 3) {
                        vector<vector<int>> newState = node->state;
                        swap(newState[i][j], newState[i + dx[k]][j + dy[k]]);
                        push(new Node(newState, node->cost + 1, calculateHeuristic(newState), node));
                    }
                }
            }
        }
    }
}

void removeNode(Node* node) {
    if (OPEN == NULL) {
        return;
    }
    if (OPEN == node) {
        OPEN = OPEN->next;
        return;
    }
    Node* temp = OPEN;
    while (temp->next != NULL && temp->next != node) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        return;
    }
    temp->next = temp->next->next;
}

Node* aStar(Node* start) {
    push(start);
    while (OPEN != NULL) {
        Node* current = OPEN;
        OPEN = OPEN->next;
        if (current->state == target) {
            return current;
        }
        pushClosed(current);
        getNeighbors(current);
        removeNode(current);
    }
    return nullptr;
}

int main() {
    vector<vector<int>> initialPuzzle(DIMENSION, vector<int>(DIMENSION, 0));
    cout << "Enter initial 8-puzzle position:" << endl;
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            cin >> initialPuzzle[i][j];
        }
    }
    cout << "Initial state of puzzle is:" << endl;
    printBoard(initialPuzzle,DIMENSION);
    Node* startNode = new Node(initialPuzzle, 0, calculateHeuristic(initialPuzzle), NULL);
    Node* goalNode = aStar(startNode);
    cout << "The Goal state has been reached with cost of " << goalNode->cost << endl;
    cout << "All the OPEN iterations look like" << endl;
    Node* iter = OPEN;
    cout << "OPEN" << "->";
    while (iter != NULL) {
        cout << iter->heuristic << "->";
        iter = iter->next;
    }
    cout << "NULL" << endl;
    cout << "All the CLOSED iterations look like" << endl;
    iter = CLOSED;
    cout << "CLOSED" << "->";
    while (iter != NULL) {
        cout << iter->heuristic << "->";
        iter = iter->next;
    }
    cout << "NULL" << endl;
    cout << "Thus solution is - "<<'\n';
    iter = goalNode;
    while(iter!=NULL){
        printBoard(iter->state,DIMENSION);
        cout<<"\n";
        iter = iter->parent;
    }
    cout<<"Initial State\n";
}
