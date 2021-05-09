///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : back Track Algorithms
//
///////////////////////////////////////////////////

#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
bool* include;
string p;
vector<string> v;

int closeNum(string p){
	int c;
	for(int i=1; i<=p.size(); i++){
		if(p[i] == ')')
			c++;
	}
	return c;
	
}

bool promissing(int i, int close, int open){
	
	if(i==0){
		return 1;
	}
	
	if(p[i] == ')'){
		if(open >= close)
			return 1;
		else
			return 0;	
	}
	else
		return 1;
	
}
int m = 0;
void push_in(){
	
	
	string s="";
	for(int i=1; i<=p.size(); i++){
		if(include[i] == 1){
			s += p[i];
		}

	}
		
	if(find(v.begin(), v.end(), s) == v.end()){
		if(s.size() >= m){
			m = s.size();
			v.push_back(s);
		}
	}
}
void print(){
	
	for(int i=0; i<v.size(); i++){
		if(v[i].size() == m)
			cout  << v[i] << endl;
	}
	
}
void min_remove(int i, int close, int open){
	
	if(promissing(i, close, open)){
		if(i==p.size()){
			if(open == close)
				push_in();
		}
		else{
			if(p[i+1] == ')'){
				
				include[i+1] = 0;
				min_remove(i+1, close, open);
				include[i+1] = 1;
				min_remove(i+1, close+1, open);
				
			}
			else{
				
				include[i+1] = 0;
				min_remove(i+1, close, open);
				include[i+1] = 1;
				min_remove(i+1, close, open+1);
				
			}
		}
	}
}

int main(){
	cin >> p;
	include = new bool[p.size()+1];
	p = "-" + p;
	min_remove(0,0,0);
	print();
}

