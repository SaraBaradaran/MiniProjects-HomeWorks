///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Dynamic Programming Algorithms
//
///////////////////////////////////////////////////

#include <iostream>

using namespace std;
int min(int x, int y, int z){
	
	int m = x;
	if(y < m)
		m = y;
	if(z < m)
		m = z;
	return m;
}

int main(){
	
	int row, col;
	cin >> row >> col;
	bool** a = new bool* [row + 1];
	
	for(int i=0; i<= row; i++)
		a[i] = new bool[col+1];
	
	for(int i=1; i<= row; i++)
		for(int j=1; j<= col; j++)
			cin >> a[i][j];
	
	
	int** c = new int* [row + 1];
	for(int i=0; i<= row; i++)
		c[i] = new int[col+1];
		
	for(int i=0; i<= row; i++)	
		c[i][0] = 0;
	for(int j=0; j<= col; j++)	
		c[0][j] = 0;
		
	int	max = 0;
	for(int i=1; i<= row; i++){
	
		for(int j=1; j<= col; j++){
			
			if(a[i][j] == 1)
				c[i][j] = 0;
			else
				c[i][j] = min(c[i-1][j-1], c[i][j-1], c[i-1][j]) + 1;	
				
			if(c[i][j] > max)
				max = c[i][j];
		}	
		
	}
				
	cout << max;			
	
}

