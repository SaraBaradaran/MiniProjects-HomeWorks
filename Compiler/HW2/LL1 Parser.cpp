#include<iostream>
#include<stack>
#include<stack>
using namespace std;
string rules[6] = {"S$","AcB","aA","","bBS",""};
string input;
int la = 0;
stack<char> PS;
void next_char(){
	if(la < input.size()-1){
		la++;
	}
}
void push_to_stack(int rule_no){
	
	string x = rules[rule_no];
	int i = x.size()-1;
	for(i; i >= 0; i--)
		PS.push(x[i]);
}
int index(char x){
	if(x == 'a' || x == 'S')
		return 0;
	if(x == 'b' || x == 'A')
		return 1;
	if(x == 'c' || x == 'B')
		return 2;
	if(x == '$')
		return 3;			
}

int main(){
	
	enum terminal{a, b, c, $};
	char t[4] = {'a','b','c','$'};
	enum noneterminal{S, A, B};
	char nt[3] = {'S','A','B'};
	
	int PT[3][4]={0};
	PT[S][a] = PT[S][c] = 1; //first(AcB)={a,c}
	PT[A][a] = 2; //first(aA)={a}
	PT[A][c] = 3; //fallow(A)={c}
	PT[B][b] = 4; //first(bBS)={b}
	PT[B][a] = PT[B][c] = PT[B][$] = 5; //fallow(B)={a,c,$}
	
	
	//print rools
	cout << "GRAMMER : \n\n      S'->S$\n1   ) S->AcB\n3,2 ) A->aA | epsilon\n5,4 ) B->bBS | epsilon\n\n";
	//print(pars table)
	cout << "PARS TABLE :\n\n  ";
	for(int i=0; i<4; i++)
		cout << t[i] << " ";
	cout << endl;	
		
	for(int i=S; i<=B; i++){
		cout << nt[i] << " ";
		for(int j=a; j<=$; j++){
			cout << PT[i][j] << " ";
		}
		cout << endl;	
	}

	cout << "\nEnter input : \n";
	cin >> input;
	input = input + '$';
	
	PS.push('$');
	PS.push('S');
	
	char LA, top;
	int rule_no;
	
	while(LA != '$'|| top != '$'){
		
		LA = input[la];
		top = PS.top();
		cout << "STACK TOP = " << top << "     LA = " << LA;
		if(LA == top){
			cout << "    match\n";
			PS.pop();
			next_char();	
		}
			
		else{
			
			if(top == '$' || top == 'a' || top == 'b' || top == 'c'){
				cout << "\nError" << endl;
				break;
			}
			rule_no = PT[index(top)][index(LA)];
			cout << "     PT [ " << top << " , " << LA << " ] = " << rule_no << endl;
			if(rule_no != 0){
				PS.pop();
				push_to_stack(rule_no);
			}
			else{
				cout << "Error" << endl;
				break;
			}
				
		}
	}
	
}
