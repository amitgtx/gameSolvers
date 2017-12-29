#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 7
#define fr(i, a, b) for(int i=a; i<b; i++)

int dr[] = {-2, 0, 2, 0};
int dc[] = {0, 2, 0, -2};

ll state  = 0LL;

ll get(int r, int c){ return state & (1LL<<(MAX*r + c)); }

void st(int r, int c){ state |= (1LL<<(MAX*r + c)); }

void unst(int r, int c){ state &= ~(1LL<<(MAX*r + c)); }

int valid(int r, int c){ return (r>=0 && r<MAX && c>=0 && c<MAX && (abs(r-3)<2 || abs(c-3)<2)); }

int validMove(int r, int c, int d){ return ( valid(r+dr[d], c+dc[d]) && get(r, c) && get(r+dr[d]/2, c+dc[d]/2) && !get(r+dr[d], c+dc[d]) ); }

void display(){
	for(int i=0; i<MAX; i++){
		for(int j=0; j<MAX; j++) cout << (valid(i, j) ? get(i, j) ? "X" : "O" : " ");
		cout << endl;
	}
	cout << endl;
}

int solve(int k){
	if(k==1) return 0;
	int ans = -1;
	fr(i, 0, MAX) fr(j, 0, MAX) {
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
	return ans;
}

int main(){
	fr(i,0,MAX) fr(j,0,MAX) st(i, j);
	unst(3,3);
//	display();
//	cout << validMove(1, 3, 3) << endl;
	if(solve(32) == 31) display();

}
