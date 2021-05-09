///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Divide & Conquer Algorithms
//
///////////////////////////////////////////////////

#include <iostream>
using namespace std;

void megre(int a[], int b[], int first1, int last1, int last2){
	
	int i = first1;
	int j = last1 + 1;
	
	int current = 0;
	
	while(i <= last1 && j <= last2)
	{
		if(a[i] <= a[j])
		{
			b[current] = a[i];
			i++;
		}
		else
		{
			b[current] = a[j];
			j++;
		}
		current++;
	}
	for(i; i <= last1; i++)
	{
		b[current] = a[i];
		current++;
	}
	for(j; j <= last2; j++)
	{
		b[current] = a[j];
		current++;
	}
	
	for(int i = first1, j=0; i <= last2 && j <= current; i++, j++)
		a[i] = b[j];
}


void MergeSort(int a[], int b[], int min, int max){
	if(min < max)
	{
		MergeSort(a, b, min, (min + max)/2);
		MergeSort(a, b, ((min + max)/2)+1, max);
		megre(a, b, min, (min + max)/2, max);
	}
		
}

bool BinarySearch(int a[], int key, int min, int max){

	int mid = (min + max)/2;
	
	if (key == a[mid])
		return 1;
	else if (key < a[mid])	
		max = mid - 1;
	else
		min = mid + 1;
		
	if(min <= max)
		return BinarySearch(a, key, min, max);
	return 0; 
}

int main()
{
	int n, q, key, positives = 0;
	cin >> n >> q;
	
	int *a = new int [n];
	int *b = new int [n];
	
	for(int i = 0; i < n; i++)
		cin >> a[i];
	
	MergeSort(a, b, 0, n-1);	
		
	
	for(int i = 0; i < q; i++)
	{
		cin >> 	key;
		positives += BinarySearch(a, key, 0, n-1);
	}
	cout << positives;
}


