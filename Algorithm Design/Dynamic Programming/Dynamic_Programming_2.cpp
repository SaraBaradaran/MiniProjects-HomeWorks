///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Dynamic Programming Algorithms
//
///////////////////////////////////////////////////

#include<iostream>
using namespace std;

int max(int a, int b){
	
	if(a>b)
		return a;
	return b;
}
int MaxSum(int a[], int n){
	int currentsum = a[0];
	int maxsum = a[0];

	for(int i=1; i<n ; i++){
		
		currentsum = max(currentsum+a[i], a[i]);
		maxsum = max(maxsum, currentsum);
	}
	
	return maxsum;
}

int MaxsubMatrix(int**a ,int n){

	int currentsum, maxsum=-100000;
	int* c = new int [n];
	for(int i=0; i<n; i++)
		c[i] = 0;
	////////////////////////////////////////
	
	
	for(int left=0; left<n; left++){
		
		for(int right=left; right<n; right++){
				
			for(int i=0; i<n; i++)
				c[i] += a[i][right];
			
			currentsum = MaxSum(c, n);
			if(currentsum > maxsum){
				maxsum = currentsum;
			}
		}
		for(int i=0; i<n; i++)
			c[i] = 0;
		
	}
	
	return maxsum;
	
}



int main(){
	
	int n;
	while(cin >> n){
		
		
		int** a= new int* [n];
		for(int i=0; i<n; i++)
			a[i] = new int [n];
			
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				cin >> a[i][j];	
			
		cout << MaxsubMatrix(a, n) << endl;
	}
}


