#include <bits/stdc++.h>
using namespace std;
//typedef long long ll;
typedef __int128 ll;
#define GRID_A 2
#define GRID_B 5
const int GRID_SIZE = 2*GRID_A + GRID_B;
#define fr(i, a, b) for(int i=a; i<b; i++)
map< ll, int > dp;
int dr[] = {-2, 0, 2, 0};
int dc[] = {0, 2, 0, -2};

ll state  = 0LL;

inline ll get(int r, int c){ return state & (1LL<<(GRID_SIZE*r + c)); }

inline void st(int r, int c){ state |= (1LL<<(GRID_SIZE*r + c)); }

inline void unst(int r, int c){ state &= ~(1LL<<(GRID_SIZE*r + c)); }

inline int valid(int r, int c){ return (r>=0 && r<GRID_SIZE && c>=0 && c<GRID_SIZE && (abs(r-GRID_SIZE/2) <= GRID_B/2 || abs(c-GRID_SIZE/2) <= GRID_B/2)); }

inline int validMove(int r, int c, int d){ return ( valid(r+dr[d], c+dc[d]) && get(r, c) && get(r+dr[d]/2, c+dc[d]/2) && !get(r+dr[d], c+dc[d]) ); }

void display(){
	for(int i=0; i<GRID_SIZE; i++){
		for(int j=0; j<GRID_SIZE; j++) cout << (valid(i, j) ? get(i, j) ? "X" : "O" : " ");
		cout << endl;
	}
	cout << endl;
}

int solve(int k){
	if(k==1) return 0;
	if(dp.find(state) != dp.end())return dp[state];
	int ans = -1;
	fr(i, 0, GRID_SIZE) fr(j, 0, GRID_SIZE) {
		if(!valid(i, j))continue;
		fr(d, 0, 4){
			if(!validMove(i, j, d))continue;
			unst(i, j);	unst(i+dr[d]/2, j+dc[d]/2);	st(i+dr[d], j+dc[d]);
			if(solve(k-1) == k-2){
				display();
				st(i, j);	st(i+dr[d]/2, j+dc[d]/2);	unst(i+dr[d], j+dc[d]);
				return k-1;
			}
			st(i, j);	st(i+dr[d]/2, j+dc[d]/2);	unst(i+dr[d], j+dc[d]);
		}
	}
	cout << k << endl;
	dp[state] = ans;
	return ans;
}

int main(){
	fr(i,0,GRID_SIZE) fr(j,0,GRID_SIZE) st(i, j);
	unst(GRID_SIZE/2, GRID_SIZE/2);
//	display();
//	cout << validMove(1, 3, 3) << endl;
	int marbles = GRID_B*GRID_B + 4*GRID_B*GRID_A - 1;
	if(solve(marbles) == marbles-1) display();
	else cout << "No_solution_possible\n";

}
