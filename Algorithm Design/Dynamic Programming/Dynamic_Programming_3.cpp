///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Dynamic Programming Algorithms
//
///////////////////////////////////////////////////

#include <iostream>

using namespace std;

int F(int n, int k, int** a){
	
	if( k == 0 || k == 1)
		return k;
	int sum;
	for(int i=1; i<=n; i++){

		for(int j=2; j<k ; j++){
			
			sum = 0;
			for(int r=0; r<=i; r++)
				sum += a[r][j-1];
				
			a[i][j] = sum % 1000000;
				
		}
		
	}
	
	a[n][k] = 0;
	
	for(int r=0; r<=n; r++)
		a[n][k] += a[r][k-1];	
		
	return a[n][k] % 1000000;	
	
}

int main(){			
	
	int n, k;
	cin >> n >> k;
	
	while( n!=0 || k!=0 ){
		
		int** a= new int* [n+1];
		for(int i=0; i<=n; i++)
			a[i] = new int[k+1];
			
		for(int j=0; j<=k; j++) // F(0, k) = 1
			a[0][j] = 1;
		
		for(int i=0; i<=n; i++) // F(n, 0) = 0
			a[i][0] = 0;
			
		for(int i=0; i<=n; i++) // F(n, 1) = 1
			a[i][1] = 1;
		
		cout << F(n, k, a) << endl;
		
		for(int i=0; i<=n; i++)
			delete [] a[i];
		delete [] a;
		
		cin >> n >> k;
		
	}
	
}

