#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    vector<vector<int>> state;
    Node* parent;
    int cost;
    int heuristic;
    Node* next;
    Node* child;
    Node(vector<vector<int>> state, int cost, int heuristic, Node* parent) {
        this->cost = cost;
        this->heuristic = heuristic;
        this->state = state;
        this->parent = parent;
        next = NULL;
        child = NULL;
    }
};

vector<vector<int>> target = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};
Node* OPEN = NULL;
Node* CLOSED = NULL;

int get_heuristic(vector<vector<int>> puzzle) {
    int h = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            h += abs(target[i][j] - puzzle[i][j]);
        }
    }
    return pow(h,0.5);
}

void push(Node* head) {
    if (OPEN == NULL) {
        OPEN = head;
        return;
    }
    int p = head->heuristic;
    Node* start = OPEN;
    while (start->next != NULL && start->next->heuristic < p) {
        start = start->next;
    }
    head->next = start->next;
    start->next = head;
}

void push_closed(Node* head){
    if (CLOSED == NULL) {
        CLOSED = head;
        return;
    }
    int p = head->heuristic;
    Node* start = CLOSED;
    while (start->next != NULL && start->next->heuristic < p) {
        start = start->next;
    }
    head->next = start->next;
    start->next = head;
}

void get_neighbors(Node* node) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (node->state[i][j] == 0) {
                for (int k = 0; k < 4; k++) {
                    if (0 <= i + dx[k] && i + dx[k] < 3 && 0 <= j + dy[k] && j + dy[k] < 3) {
                        vector<vector<int>> new_state = node->state;
                        swap(new_state[i][j], new_state[i + dx[k]][j + dy[k]]);
                        push(new Node(new_state, node->cost + 1, get_heuristic(new_state), node));
                    }
                }
            }
        }
    }
}

void del(Node* node) {
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

Node* a_star(Node* start) {
    push(start);
    while (OPEN != NULL) {
        Node* temp = OPEN;
        OPEN = OPEN->next;
        if (temp->state == target) {
            return temp;
        }
        push_closed(temp);
        get_neighbors(temp);
        del(temp);
    }
    return nullptr;
}

int main() {
    vector<vector<int>> puzzle(3, vector<int>(3, 0));
    cout << "Enter initial 8-puzzle position:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> puzzle[i][j];
        }
    }
    cout << "Initial state of puzzle is:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
    Node* node = new Node(puzzle, 0, get_heuristic(puzzle), NULL);
    Node* ans = a_star(node);
    cout << "The Goal state has been reached with cost of " << ans->cost << endl;
    cout << "All the OPEN iterations look like" << endl;
    Node* iter = OPEN;
    cout<<"OPEN"<<"->";
    while (iter != NULL) {
        cout << iter->heuristic << "->";
        iter = iter->next;
    }
    cout<<"NULL"<<endl;
    cout << "All the CLOSED iterations look like" << endl;
    iter = CLOSED;
    cout<<"CLOSED->";
    while (iter != NULL) {
        cout << iter->heuristic << "->";
        iter = iter->next;
    }
    cout <<"NULL"<< endl;
}
