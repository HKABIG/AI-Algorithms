#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> target = {{1,2,3},{8,0,4},{7,6,5}};

void bestPoss(vector<vector<int>> move,int n){
    cout<<"--------------------------"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<move[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Heuristic value is"<<" "<<n<<endl;
}

int getheuristic(vector<vector<int>> move){
    int h =  0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            h += abs(move[i][j]-target[i][j]);
        }
    }
    return h;
}

void simple_hill_climb(vector<vector<int>> &puzzle,int x,int y,int heuristic){
    int dx[] = {0,-1,0,1};
    int dy[] = {1,0,-1,0};
    vector<vector<vector<int>>> moves;
    vector<vector<int>> ans;
    int n;
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx>=0 && nx<3 && ny>=0 && ny<3){
            vector<vector<int>> move = puzzle;
            swap(move[x][y],move[nx][ny]);
            int h = getheuristic(move);
            moves.push_back(move);
            if(h<heuristic){
                ans = move;
                n = h;
                break;
            }
        }
    }
    if(ans.size()==0){
        cout<<"You have reached local maximum"<<endl;
        bestPoss(moves[0],n);
    }
    bestPoss(ans,n);
    // pgenPoss(moves);
}

void simple_ascent_hill_climb(vector<vector<int>> &puzzle, int &x, int &y, int &heuristic) {
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
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3 && (puzzle[nx][ny]==0 || puzzle[x][y]==0)) {
                vector<vector<int>> move = puzzle;
                swap(move[x][y], move[nx][ny]);
                int h = getheuristic(move);
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
            bestPoss(puzzle, heuristic);
        }
        else cout << "Local maximum reached" << endl;
    }
}

int main(){
    vector<vector<int>> puzzle(3,vector<int>(3,0));
    int x,y;
    int heuristic = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int num;
            cin>>num;
            if(num==0){
                x = i;y = j;
            }
            heuristic += abs(puzzle[i][j]-target[i][j]);
            puzzle[i][j] = num;
        }
    }
    cout<<"-------------------------"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<puzzle[i][j]<<" ";
        }
        cout<<endl;
    }
    // genPoss(puzzle,x,y);
    //simple_hill_climb(puzzle,x,y,heuristic);
     simple_ascent_hill_climb(puzzle,x,y,heuristic);
}