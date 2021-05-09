///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Back Track Algorithms
//
///////////////////////////////////////////////////

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
bool* include;
string* a;
int n;
vector<string>v;

bool flag = 0;
void print(){
	if(flag){
		
		string s= "";
		for(int i=1; i<=n; i++){
			if(include[i] == 1){
				s += a[i];
				s += " ";
			}
		}
		if(find(v.begin(), v.end(), s) == v.end()){
				cout << s << endl;
				v.push_back(s);
		}
	}
	flag = 1;
}
void subset(int i){
	if(i == 1)
		print();
	else{
		include[i-1] = 0;
		subset(i-1);
		include[i-1] = 1;
		subset(i-1);
	}	
}

int main(){
	cin >> n;
	a = new string[n+1];
	for(int i=1; i<=n; i++)
		cin >> a[i];
	include = new bool[n+1];
	subset(n+1);
}

