#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int winx(vector<int> arr){
    // rows
    if(arr[0]==1 && arr[1]==1 && arr[2]==1){
        return 1;
    }
    if(arr[3]==1 && arr[4]==1 && arr[5]==1){
        return 1;
    }
    if(arr[6]==1 && arr[7]==1 && arr[8]==1){
        return 1;
    }
    
    // cols
    if(arr[0]==1 && arr[3]==1 && arr[6]==1){
        return 1;
    }
    if(arr[1]==1 && arr[4]==1 && arr[7]==1){
        return 1;
    }
    if(arr[2]==1 && arr[5]==1 && arr[8]==1){
        return 1;
    }
    
    // diagonals
    if(arr[0]==1 && arr[4]==1 && arr[8]==1){
        return 1;
    }
    if(arr[2]==1 && arr[4]==1 && arr[6]==1){
        return 1;
    }
    return 0;
}

int blockx(vector<int> arr){
    // block rows
    if(arr[0]==2 && arr[1]==2 && arr[2]==1){
        return 1;
    }
    if(arr[0]==2 && arr[1]==1 && arr[2]==2){
        return 1;
    }
    if(arr[0]==1 && arr[1]==2 && arr[2]==2){
        return 1;
    }
    
    if(arr[3]==2 && arr[4]==2 && arr[5]==1){
        return 1;
    }
    if(arr[3]==2 && arr[4]==1 && arr[5]==2){
        return 1;
    }
    if(arr[3]==1 && arr[4]==2 && arr[5]==2){
        return 1;
    }
    
    if(arr[6]==2 && arr[7]==2 && arr[8]==1){
        return 1;
    }
    if(arr[6]==2 && arr[7]==1 && arr[8]==2){
        return 1;
    }
    if(arr[6]==1 && arr[7]==2 && arr[8]==2){
        return 1;
    }
    
    // block cols
    if(arr[0]==2 && arr[3]==2 && arr[6]==1){
        return 1;
    }
    if(arr[0]==2 && arr[3]==1 && arr[6]==2){
        return 1;
    }
    if(arr[0]==1 && arr[3]==2 && arr[6]==2){
        return 1;
    }
    
    if(arr[1]==2 && arr[4]==2 && arr[7]==1){
        return 1;
    }
    if(arr[1]==2 && arr[4]==1 && arr[7]==2){
        return 1;
    }
    if(arr[1]==1 && arr[4]==2 && arr[7]==2){
        return 1;
    }
    
    if(arr[2]==2 && arr[5]==2 && arr[8]==1){
        return 1;
    }
    if(arr[2]==2 && arr[5]==1 && arr[8]==2){
        return 1;
    }
    if(arr[2]==1 && arr[5]==2 && arr[8]==2){
        return 1;
    }
    
    // block diagonals
    if(arr[0]==2 && arr[4]==2 && arr[8]==1){
        return 1;
    }
    if(arr[0]==2 && arr[4]==1 && arr[8]==2){
        return 1;
    }
    if(arr[0]==1 && arr[4]==2 && arr[8]==2){
        return 1;
    }
    
    if(arr[2]==2 && arr[4]==2 && arr[6]==1){
        return 1;
    }
    if(arr[2]==2 && arr[4]==1 && arr[6]==2){
        return 1;
    }
    if(arr[2]==1 && arr[4]==2 && arr[6]==2){
        return 1;
    }
    return 0;
}

int main()
{
    int n = 3;
// 	char mat[n][n];
    vector<vector<char>> mat(n,vector<char>(n));
	int xcount = 0;
	int ocount = 0;
	int zcount = 0;
	
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>mat[i][j];
            if(mat[i][j]=='x') xcount++;
            if(mat[i][j]=='o') ocount++;
            if(mat[i][j]=='0') zcount++;
        }
    }
    if(abs(xcount-ocount)>1){
        cout<<"Invalid matrix input"<<endl;
        return 0;
    }
    cout<<"The Provided matrix looks like"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
	vector<int> v;
	for(int i=0;i<n;i++){
	    for(int j=0;j<n;j++){
	        if(mat[i][j]=='x') v.push_back(1);
	        if(mat[i][j]=='o') v.push_back(2);
	        if(mat[i][j]=='0') v.push_back(0);
	    }
	}
	cout<<"The 1D vector looks like"<<endl;
	for(int i=0;i<(n*n);i++){
	    cout<<v[i]<<" ";
	}
	cout<<endl;
	int index = 0;
	int pw = 1;
	for(int i=(n*n)-1;i>=0;i--){
	    index += v[i]*(pw);
	    pw*=3;
	}
	cout<<"The index is "<<index<<endl;
	cout<<endl;
 //Lab Assignment 1.2 Begins from here
    cout<<"Using of AI Techniques for best possible move "<<endl;
    vector<pair<vector<int>,int>> possible;
    for(int i=0;i<zcount;i++){
        possible.push_back({v,0});
    }
    int j = 0;
    vector<int> ans;
    int score = 0;
    for(int i=0;i<zcount;i++){
        while(j<9){
            if(possible[i].first[j]==0){
                possible[i].first[j] = 1;
                if(winx(possible[i].first)) possible[i].second=100;
                else if(blockx(possible[i].first)) possible[i].second=50;
                else if(j==4) possible[i].second = 4;
                else if(j%2==1) possible[i].second = 2;
                else if(j%2==0) possible[i].second = 3;
                j++;
                break;
            }
            j++;
        }
    }
    for(int i=0;i<zcount;i++){
        if(possible[i].second>score){
            score = possible[i].second;
            ans = possible[i].first;
        }
        for(int j=0;j<9;j++){
            cout<<possible[i].first[j]<<" ";
        }
        cout<<possible[i].second<<" ";
        cout<<endl;
    }
    
    cout<<"The possible move needs to be"<<endl;
    for(auto it:ans){
        cout<<it<<" ";
    }
    cout<<endl;
    cout<<"With a score of "<<score<<endl;
    return 0;
    
}
