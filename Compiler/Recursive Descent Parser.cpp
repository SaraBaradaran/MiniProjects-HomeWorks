#include<iostream>
using namespace std;

string input;

int la = 0;
char LA ;
bool error = 0;

void A();
void B();
void S();

bool next_char(){
	
	if(la < input.size()){
		la++;	
		LA = input[la];
		return 1;
	}
	return 0;
}

bool match(char x){
	
	if(x == LA){
		cout << x << " matched\n";
		if(!next_char())
			return 0;
		else
			return 1;	
		
	}
	else{
		error = 1;	
		return 0;
	}
		
}

int main(){
	
	
	//print rools
	cout << "GRAMMER : \n\n      S'->S$\n1   ) S->AcB\n3,2 ) A->aA | epsilon\n5,4 ) B->bBS | epsilon\n\n";
	cout << "Enter input\n";
	cin >> input;
	input = input + '#';
	LA = input[0];
	S();
	if(la == input.size()-1 && error == 0)
		cout << "Accept\n";
	else
		cout << "Reject\n";	
	
}
void A(){
	if(LA == 'a'){
		if(match('a'))
			A();
	}
	else
		return;
}
void S(){
	if(LA == 'a'){
		A();
		if(match('c'))
			B();
		else
			error = 1;	
	}
	else if(LA == 'c'){
		if(match('c'))
			B();
		else
			error = 1;	
	}
	else
		error = 1;	
}
void B(){
	if(LA == 'b'){
		
		if(match('b')){
			B();
			S();
		}
		else
			error = 1;	
	}
	else
		return;	
}
