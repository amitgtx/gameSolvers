#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 7

bool state[7][7];
int dr[] = {-2, 0, 2, 0};
int dc[] = {0, 2, 0, -2};

int validPos(int r, int c){
	return (r >=0 && r<MAX && c>=0 && c<MAX && (abs(r-3) < 2 || abs(c-3) < 2));
}

void display(){
	for(int i=0; i<MAX; i++){
		for(int j=0; j<MAX; j++) if(!validPos(i,j)) cout << " "; else cout << ((state[i][j] == 1) ? "X" : "O");
		cout << endl;
	}
	cout << endl;
}

int validMove(int r, int c, int d ){
	return (validPos(r+dr[d], c+dc[d]) && state[r+dr[d]/2][c+dc[d]/2] == 1 && state[r][c] == 1 && state[r+dr[d]][c+dc[d]] == 0);
}


int solve(int k){
	if(k == 1) return 0;
	int ans = -1;
	for(int i=0; i<MAX; i++) for(int j=0; j<MAX; j++){
		if(!validPos(i,j))continue;
		for(int d=0; d<4; d++){
			if(!validMove(i,j,d))continue;
			state[i][j] = 0;	state[i+dr[d]/2][j+dc[d]/2] = 0;	state[i+dr[d]][j+dc[d]] = 1;
			if(solve(k-1) == k-2){
				display();
				state[i][j] = 1;	state[i+dr[d]/2][j+dc[d]/2] = 1;	state[i+dr[d]][j+dc[d]] = 0;
				return k-1;
			}
			state[i][j] = 1;	state[i+dr[d]/2][j+dc[d]/2] = 1;	state[i+dr[d]][j+dc[d]] = 0;
		}
	}
	cout << k << endl;
	return ans;
}

int main(){
	for(int i=0; i<MAX; i++) for(int j=0; j<MAX; j++) state[i][j] = 1;
	state[3][3] = 0;
	if(solve(32) == 31) display() ;

}
