//*****************************************************************/
//
//		Creator : Sara Baradaran
//		Creation Date : Fall 2019
//		Poject Title : Matrix Calculator
//
//*****************************************************************/

#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include <bits/stdc++.h>

using namespace std;

class matrix{

	
public:
	string name;
	float** mat;
	int col_num;
	int row_num;
	
	matrix(vector<string>&v){
		definition(v);
	}
	matrix():name("empty"){
		
	}
	matrix(int row, int col):row_num(row), col_num(col){
		
		mat = new float* [row_num];
		for(int i=0; i<row_num; i++)
			mat[i] = new float[col_num];
	}
	void definition(vector<string>&v){
		
		name = v[1];
		int col = 0, row = 1;
		bool flag = 1;
		for(int i=3; i<v.size(); i++){
			if(v[i] != "#" && flag)
				col++;
			else if(v[i] == "#")
			{
				flag = 0;
				row++;
			}
		}
		
		col_num = col;
		row_num = row;

		mat = new float* [row_num];
		for(int i=0; i<row_num; i++)
			mat[i] = new float[col_num];

		int k = 3;	
		for(int i=0; i<row_num; i++){
			for(int j=0; j<col_num+1; j++){
				if(v.size() > k && v[k] != "#")
					mat[i][j] = stof(v[k]);
				k++;
			}		
		}
	}
	void show(){
		
		cout << name << " :" << endl;
		for(int i=0; i<row_num; i++){
			for(int j=0; j<col_num; j++)
				cout << mat[i][j] << " ";
			cout << endl;
		}
		cout << endl;	
	}
	matrix operator+(matrix a){

		if(a.col_num == col_num && a.row_num == row_num)
		{
			matrix res(row_num, col_num);
			for(int i=0; i<row_num; i++)
				for(int j=0; j<col_num; j++)
					res.mat[i][j] = mat[i][j] + a.mat[i][j];
					
			return res;
		}
		else{
			cout << "dimentioanal is wrong " << endl;
			matrix empty;
			return empty;
		}
	}

	matrix operator-(matrix a){

		if(a.col_num == col_num && a.row_num == row_num)
		{
			matrix res(row_num, col_num);
			for(int i=0; i<row_num; i++)
				for(int j=0; j<col_num; j++)
					res.mat[i][j] = mat[i][j] - a.mat[i][j];
					
			return res;
		}
		else{
			cout << "dimentioanal is wrong " << endl;
			matrix empty;
			return empty;
		}
	}
	
	matrix operator*(matrix a){

		if(col_num == a.row_num)
		{
			matrix res(row_num, a.col_num);
			for(int i=0; i<row_num; i++){
				for(int j=0; j<a.col_num; j++){
					
					res.mat[i][j] = 0;
					
					for(int k=0; k<col_num; k++){
						res.mat[i][j] += mat[i][k] * a.mat[k][j];
					}
				}
			}
	
			return res;
		}
		else{
			cout << "dimentioanal is wrong " << endl;
			matrix empty;
			return empty;
		}
	}
	
	matrix operator/(matrix a){

		if(a.col_num == col_num && a.row_num == row_num)
		{
			matrix res(row_num, col_num);
			for(int i=0; i<row_num; i++)
				for(int j=0; j<col_num; j++)
					res.mat[i][j] = mat[i][j] / a.mat[i][j];
					
			return res;
		}
		else{
			cout << "dimentioanal is wrong " << endl;
			matrix empty;
			return empty;
		}
	}
	matrix operator^(matrix a){

		if(a.col_num == col_num && a.row_num == row_num)
		{
			matrix res(row_num, col_num);
			for(int i=0; i<row_num; i++)
				for(int j=0; j<col_num; j++)
					res.mat[i][j] = pow(mat[i][j], a.mat[i][j]);
					
			return res;
		}
		else{
			cout << "dimentioanal is wrong " << endl;
			matrix empty;
			return empty;
		}
	}
	
	matrix new_operator(matrix a){
		
		if(a.col_num == col_num && a.row_num == row_num)
		{
			matrix res(row_num, col_num);
			for(int i=0; i<row_num; i++)
				for(int j=0; j<col_num; j++)
					res.mat[i][j] = mat[i][j] * a.mat[i][j];

			return res;
		}
		else{
			cout << "dimentioanal is wrong " << endl;
			matrix empty;
			return empty;
		}
	}
	matrix trans(){
		
		matrix res(col_num, row_num);
		for(int i=0; i<row_num; i++)
			for(int j=0; j<col_num; j++)
				res.mat[j][i] = mat[i][j];
				
		return res;	
	}
	float trace(){
		
		if(col_num == row_num){
			float sum = 0;
			
			for(int i=0; i<row_num; i++)
				for(int j=0; j<col_num; j++)
					if(i==j)
						sum += mat[i][j];
					
			return sum;
		}
		else{
			cout << "dimentioanal is wrong " << endl;
			return -100;
		}
	}
	int symetric(){
		
		if(col_num == row_num){

			for(int i=0; i<row_num; i++)
				for(int j=0; j<col_num; j++)
					if(mat[i][j] != mat[j][i])
						return 0;
					
			return 1;
		}
		else{
			cout << "dimentioanal is wrong " << endl;
			return -1;
		}
	}
	
	void getCofactor(float** A, float** temp, int p, int q, int n){ 
	
	    int i = 0, j = 0; 
	    for (int row = 0; row < n; row++){ 
	        for (int col = 0; col < n; col++){ 
	            if (row != p && col != q){ 
	                temp[i][j++] = A[row][col]; 
	                if (j == n - 1){ 
	                    j = 0; 
	                    i++; 
	                } 
	            } 
	        } 
	    } 
	}
	float determinant(){
		
		if(row_num == col_num)
			return determinant(mat, row_num);
		else{
			cout << "dimentioanal is wrong " << endl;
			return -100;
		}
	}
	
	float determinant(float** A, int n){ 
	
	    float det = 0;
	    if(n == 1) 
	        return A[0][0]; 
	  
	    float** temp = new float*[n];
	    for(int i=0; i<n; i++)
			temp[i] = new float[n]; 
	  
	    int sign = 1;
	    for (int i=0; i< n; i++){ 
	        getCofactor(A, temp, 0, i, n); 
	        det += sign * A[0][i] * determinant(temp, n-1); 
	        sign = -sign; 
	    } 
	  
	    return det; 
	} 

	void adjoint(float** A,float** adj, int n){ 
	
	    if (n == 1){ 
	        adj[0][0] = 1; 
	        return; 
	    }
	  
	    int sign = 1;
	    
	    float** temp = new float*[n];
	    for(int i=0; i<n; i++)
			temp[i] = new float[n]; 
	  
	    for (int i=0; i<n; i++){ 
	        for (int j=0; j<n; j++){ 
	            getCofactor(A, temp, i, j, n); 
	            if((i+j)%2 == 0)
	            	sign = 1;
				else
					sign -1; 
	            adj[j][i] = sign*(determinant(temp, n-1)); 
	        } 
	    } 
	} 

	matrix inverse(){
		
		matrix inv(row_num, col_num);
	    int det = determinant();
	    if (det != 0 && det != -100){ 
		    float** adj = new float*[row_num];
			for(int i=0; i<row_num; i++)
				adj[i] = new float[row_num];
				
		    adjoint(mat, adj, row_num); 
		  
		    for (int i=0; i<row_num; i++) 
		        for (int j=0; j<row_num; j++) 
		            inv.mat[i][j] = adj[i][j]/det;
		  
		    return inv; 
		}
		else{
			cout << "Singular matrix, can't find its inverse" << endl;
			matrix empty;
			return empty;
		}
	} 

};
vector<string> &split(string s, string r, vector<string> &output){
	
	char* comp;
	char* buffer = new char[strlen(s.c_str())];

	strcpy(buffer, s.c_str());
	comp = strtok(buffer, r.c_str());
	while( comp != NULL){
		output.push_back(comp);
		comp = strtok(NULL, r.c_str());
	}
	delete [] comp;
	delete [] buffer;
	return output;
}
vector<string> split(string str, string delimiters){
	
	vector<string> output;
	return split(str, delimiters, output);
}


string modify(string s){
	
	char* temp = new char[s.size()+10];
	int  k=0;
 	for(int i=0; i<s.size(); i++, k++){
 		
 		if(s[i] == ';'){
			temp[k++] = ' ';
			temp[k++] = '#';
			temp[k] = ' ';
		}
		else if(s[i] == '+'){
			temp[k++] = ' ';
			temp[k++] = '+';
			temp[k] = ' ';
		}
		else if(s[i] == '='){
			temp[k++] = ' ';
			temp[k++] = '=';
			temp[k] = ' ';
		}
		else if(s[i] == '*'){
			temp[k++] = ' ';
			temp[k++] = '*';
			temp[k] = ' ';
		}
		else if(s[i] == '-'){
			temp[k++] = ' ';
			temp[k++] = '-';
			temp[k] = ' ';
		}
		else if(s[i] == '^'){
			temp[k++] = ' ';
			temp[k++] = '^';
			temp[k] = ' ';
		}
		else if(s[i] == '/'){
			temp[k++] = ' ';
			temp[k++] = '/';
			temp[k] = ' ';
		}
		else if(s[i] == '@'){
			temp[k++] = ' ';
			temp[k++] = '@';
			temp[k] = ' ';
		}
		else
			temp[k] = s[i];
	}
	temp[k] = '\0';
	return string(temp);

}
matrix serach(vector<matrix>&matrixes , string name){
	
	for(int i=0; i<matrixes.size(); i++){
		if(matrixes[i].name == name){
			return matrixes[i];
		}
	}
	
	matrix empty;
	return empty;
}

bool IsLetter(string a){
	
	if(( a >= "a" && a <= "z") || ( a >= "A" && a <= "Z"))
		return 1;
	return 0;
}

bool IsOperator(string a){
	if(a == "+" || a == "-" || a == "*" || a == "^" || a == "/" || a == "@")
		return 1;
	return 0;
}
matrix calculate(matrix a, matrix b, string opt){
	
	if(opt == "+")
		return a + b;
	if(opt == "-")
		return a - b;
	if(opt == "/")
		return a / b;
	if(opt == "^")
		return a ^ b;
	if(opt == "*")
		return a * b;
	if(opt == "@")
		return a.new_operator(b);	
}

int main(){
	
	string command;
	vector<matrix> matrixes;

	while(1){
		
		cout << "> ";
		getline(cin, command);
		command = modify(command);

		vector<string>subcommand = split(command, ", []()");
		
		
		////////////////////////////////////////////////
		
		if(subcommand[0] == "clear"){
			
			while(!matrixes.empty())
				matrixes.pop_back();
		}
		///////////////////////////////////////////////
		
		else if(subcommand[0] == "exit")
			return 0;
		////////////////////////////////////////////////
		
		else if(subcommand[0] == "show"){
			
			if(matrixes.size() == 0)
				cout << "there is not any matrixes" << endl;
				
			else{
				
				for(int i=0; i<matrixes.size(); i++)
					matrixes[i].show();
			}
		}
		////////////////////////////////////////////////
		
		else if(subcommand[0] == "sym"){
			int sym;
			matrix a = serach(matrixes, subcommand[1]);
			if(a.name != "empty")
				sym = a.symetric();
			else
				cout << "variable not found" << endl;
			if(sym != -1)
				cout << a.symetric() << endl;
		}
		////////////////////////////////////////////////
		
		else if(subcommand[0] == "det"){
			int det;
			matrix a = serach(matrixes, subcommand[1]);
			if(a.name != "empty")
				det = a.determinant();
			else
				cout << "variable not found" << endl;
			if(det != -100)
				cout << a.determinant() << endl;
		}
		////////////////////////////////////////////////
		
		else if(subcommand[0] == "trace"){
			int sum;
			matrix a = serach(matrixes, subcommand[1]);
			if(a.name != "empty")
				sum = a.trace();
			else
				cout << "variable not found" << endl;
			if(sum != -100)
				cout << a.trace() << endl;
		}
		////////////////////////////////////////////////		
		else if(subcommand[0] == "trans" && subcommand.size() == 2){
			matrix res;
			matrix a = serach(matrixes, subcommand[1]);
			if(a.name != "empty"){
				res = a.trans();
				res.show();		
			}
			else
				cout << "variable not found" << endl;
		}
		////////////////////////////////////////////////
		
		else if(subcommand[0] == "invers" && subcommand.size() == 2){
			matrix res;
			matrix a = serach(matrixes, subcommand[1]);
			if(a.name != "empty")
				res = a.inverse();
			else
				cout << "variable not found" << endl;
				
			if(res.name != "empty")
				res.show();
		}
		////////////////////////////////////////////////
		//def a=[1,2,3...
		//def a=b+....
		//c = a+...
		//a+b...
		//def a=b
		
		else if(subcommand[0] == "def" || subcommand[1] == "=" || IsLetter(subcommand[0])){
			
			if( IsLetter(subcommand[2]) || IsLetter(subcommand[3]) || IsOperator(subcommand[3])){
				
				matrix a, b;
				b.name = "b";
				int k;
				if(subcommand[0] == "def")
					k = 3;
				else if(subcommand[1] == "=")
					k = 2;
				else
					k = 0;
				if(subcommand[k] == "invers"){
					k++;
					a = serach(matrixes, subcommand[k]);
					if(a.name == "empty"){
						cout << "variable not found" << endl;
						continue;
					}
					a = a.inverse();
					if(a.name == "empty")
						continue;
					
				}
				else if(subcommand[k] == "trans"){
					k++;
					a = serach(matrixes, subcommand[k]);
					if(a.name == "empty")
						continue;

					a = a.trans();
				}
	
				else{
				
					a = serach(matrixes, subcommand[k]);

					if(a.name == "empty"){
						cout << "variable not found" << endl;
						continue;
					}
				}
				
				while(k != subcommand.size()-1){
					
					if(subcommand[k+2] == "invers"){
						k++;
						b = serach(matrixes, subcommand[k+2]);
						if(b.name == "empty"){
							cout << "variable not found" << endl;
							break;
						}
						
						b = b.inverse();
						if(b.name == "empty")
							break;

						a = calculate(a, b, subcommand[k]);
						if(a.name == "empty")
							break;
		
					}
					else if(subcommand[k+2] == "trans"){
						k++;
						b = serach(matrixes, subcommand[k+2]);
						if(b.name == "empty"){
							cout << "variable not found" << endl;
							break;
						}
						
						b = b.trans();
						
						a = calculate(a, b, subcommand[k]);
						if(a.name == "empty")
							break;
					}
		
					else{
						
						b = serach(matrixes, subcommand[k+2]);
						if(b.name == "empty"){
							cout << "variable not found" << endl;
							break;
						}
						
						a = calculate(a, b, subcommand[k+1]);
						if(a.name == "empty")
							break;
					}
		
						
					k += 2;
				}
				
				if(a.name != "empty" && b.name != "empty"){
					
					bool find = 0;
					if(subcommand[0] == "def"){
		
						for(int i=0; i<matrixes.size(); i++){
							if(matrixes[i].name == subcommand[1]){
								matrixes[i] = a;
								matrixes[i].name = subcommand[1];
								find = 1;
								break;
							}
						}
						
						if(find == 0){
							a.name = subcommand[1];
							matrixes.push_back(a);
						}
					}
					else if(subcommand[1] == "="){
						
						for(int i=0; i<matrixes.size(); i++){
							if(matrixes[i].name == subcommand[0]){
								matrixes[i] = a;
								matrixes[i].name = subcommand[0];
								find = 1;
								break;
							}
						}
						
						if(find == 0){
							cout << "variable not found " << endl;
						}
					}
					else
						a.show();
				}
			}
			
			else{
				matrix new_(subcommand);
				matrixes.push_back(new_);
			}			
		}
	}
}


