///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Dynamic Programming Algorithms
//
///////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void find_subset(int* num, int size, int sum, int** table)
{
	for (int i = 0; i < size; i++)
	    table[i][0] = num[i];

	for (int i = 0; i < size; i++)
	{
	    if (!i)
	    {
	      for (int j = 1; j <= sum; j++)
	      {
	        if (table[i][0] == j)
	          table[0][j] = j;
	        else
	          table[0][j] = 0;
	      }
	      continue;
		}
	
	    for (int j = 1; j <= sum; j++)
	    {
	      
			if (table[i][0] == j || table[i - 1][j - table[i][0]]  ==  j - table[i][0] || table[i - 1][j] == j)
	        	table[i][j] = j;
	      	else
	        	table[i][j] = 0;
	
	    }
  	}

}

void print_sums(const vector<int>& v , int *sets)
{
	int sum = 0;
	for (int i = 0; i < v.size(); i++)
		sum += v[i];
	
	int* numbers = new int[v.size()];	
	int ** tab = new int*[v.size()];
	for (int i = 0; i < v.size(); i++)
	{
		tab[i] = new int[sum+1];
		numbers[i] = v[i];
	}
	
		
	find_subset(numbers, v.size(), sum, tab);
	
	for (int i = 0; i <= sum; i++)
		if (tab[v.size() - 1][i] > 0)
			sets[tab[v.size() - 1][i]] = tab[v.size() - 1][i];
}

void find_sums(int**tab, int* arr, int index, int subset_sum, vector<int> &subset, int* sum)
{
	if (!index && subset_sum && tab[0][subset_sum])
	{
	    subset.push_back(arr[index]);
	    print_sums(subset, sum);
	}

	else if (!index && !subset_sum)
	    print_sums(subset, sum);
	    
	else
	{
		if (tab[index - 1][subset_sum])
		{
		    vector<int> b = subset;
		    find_sums(tab, arr, index - 1, subset_sum, b, sum);
		}
		
		if (subset_sum >= arr[index] && tab[index - 1][subset_sum - arr[index]])
		{
		    subset.push_back(arr[index]);
			find_sums(tab, arr, index - 1, subset_sum - arr[index], subset, sum);
		}
	}
}


int main()
{
	int n, k;
	  
	cin >> n >> k;
	  
	int** table = new int*[n];
	for (int i = 0; i < n; i++)
	    table[i] = new int[k + 1];
	    
	int* num = new int[n];
	for (int i = 0; i < n; i++)
		cin >> num[i];
	
	sort(num, num + n);
	  
	find_subset(num, n, k, table);
	
	vector<int> v;
	  
	int* sum = new int[k + 1];
	for (int i = 0; i <= k; i++)
	    sum[i] = 0;
	    
	find_sums(table, num, n - 1, k, v, sum);
	  
	for (int i = 1; i <= k; i++)
	    if (sum[i])
	    	cout << sum[i] << " ";

}

