///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Dynamic Programming Algorithms
//
///////////////////////////////////////////////////

#include<iostream>
using namespace std;

int sum(int left, int right, int* a){

	int s = 0;
	for(int i=left; i<= right; i++)
		s += a[i];
	return s;	
}

int func(int n, int** F, int* a){
	
	int max;
	int m;
	for(int j=n-1; j>0; j--){
		
		for(int i=0; i<j; i++){
			
			max = -99999999;
			for(int k=i; k<n-j+i; k++){
				m = sum(i,k,a)-F[k+1][n-j+i];
			//	cout << "sum(" << i <<"," <<k <<")-f(" << k+1<<","<<n-j+i<<")=" <<m<<endl;
				if(max < m)
					max = m;				
			}
			
			for(int k=n-j+i; k>i; k--){
				m = sum(k,n-j+i,a)-F[i][k-1];
			//	cout << "sum(" << k <<"," <<n-j+i <<")-f(" << i <<","<<k-1<<")=" <<m<<endl;
				if(max < m)
					max = m;				
			}
		
			m = sum(i,n-j+i,a);
			if(max < m)
				max = m;
				
			F[i][n-j+i] = max;	
		}
	}
	return F[0][n-1];
		
}
int main(){
	int n;
	cin >> n;
	
	
	while(n){
			
		int* a = new int[n];
		for(int i=0; i<n; i++)
			cin >> a[i];
	
		
		int** F = new int*[n];
		for(int i=0; i<n; i++)
			F[i] = new int[n];//F(1,n) = max diff between A, B
			
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++)
				F[i][j] = 0;		
		}
		for(int i=0; i<n; i++)
			F[i][i] = a[i];	
				
		//F(i,j) = max{sum(i,l) -F(l+1,j),sum(l,j) -F(i,l-1)}
		//i <= l  <= j
		cout << func(n, F,a) << endl;
		
		delete [] a;	
		cin >> n;
		
	}
		
}

