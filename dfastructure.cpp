#include<bits/stdc++.h>
using namespace std;
class node{
	public:
	char data;
	node *next;
};
class stac{
	node *top;
	long l;
	public:
		stac(){
			top=NULL;
			l=0;
		}
		void push(char);
		char pop();
		void display(); 
		//bool palindrome();
	//	void check_expression();
	//	void evaluate_postfix();
};
void stac::push(char ele){
	++l;
	node *temp=new node();
	temp->data=ele;
	if(top==NULL){
		top=temp;
		temp->next=NULL;		
	}
	else{
		temp->next=top;
		top=temp;
	}
}
char stac::pop(){
	char o;
	if(top==NULL){
		cout<<"\n stac is empty1";
		return 0;
	}
	else{
		node *temp;
		temp=top;
		o=temp->data;
		top=top->next;
		delete(temp);
	}
//	cout<<"\n deleted="<<o;
	return o;
}
void stac::display(){
	node *s;
	s=top;
	while(s!=NULL)
	{
		cout<<"\n data="<<s->data;
		s=s->next;
	}
}




//vector < vector<int> > nfa;
char nfa[100][100]={'0'};

static int curr=0;
void dot(stac s){
//	cout<<"in dot curr="<<curr;
	char a = s.pop();
	char b = s.pop();
	::nfa[curr][curr+1]='a';
	::nfa[curr+1][curr+2]='b';
	::nfa[curr][curr]='0';
	::nfa[curr][curr+2]='0';
	::nfa[curr+1][curr]='0';
	::nfa[curr+1][curr+1]='0';
	::nfa[curr+2][curr]='0';
	::nfa[curr+2][curr+1]='0';
	::nfa[curr+2][curr+2]='0';
	for(int i=0;i<=curr+3;i++)
	for(int j=0;j<=curr+3;j++)
		{
			if(::nfa[i][j]!='a'&&::nfa[i][j]!='b'&&::nfa[i][j]!='E')
				::nfa[i][j]='0';
		}
	curr+=2;
} 
void add(stac s){
	char a = s.pop();
	char b = s.pop();
	::nfa[curr][curr+1]='E';
	::nfa[curr][curr+3]='E';
	::nfa[curr+1][curr+2]='a';
	::nfa[curr+2][curr+5]='E';
	::nfa[curr+3][curr+4]='b';
	::nfa[curr+4][curr+5]='E';
	for(int i=0;i<=curr+6;i++)
	for(int j=0;j<=curr+6;j++)
		{
			if(::nfa[i][j]!='a'&&::nfa[i][j]!='b'&&::nfa[i][j]!='E')
				::nfa[i][j]='0';
		}
	curr+=5;
} 
void closure(){
	char temp[curr+1][curr+1];
	for(int i=0;i<=curr;i++){
		for(int j=0;j<=curr;j++){
			temp[i][j]=::nfa[i][j];
		}
	}
	curr=curr+2;
	for(int i=1;i<curr;i++){
		for(int j=1;j<curr;j++){
			::nfa[i][j]=temp[i-1][j-1];
		}
	}
	for(int p=0;p<curr;p++){
		nfa[0][p]='0';
		nfa[p][0]='0';
		nfa[p][curr]='0';
		nfa[curr][p]='0';
	}
	
	::nfa[0][1]='E';
	::nfa[0][curr]='E';
	::nfa[curr-1][1]='E';
	::nfa[curr-1][curr]='E';
	for(int i=0;i<=curr;i++)
	for(int j=0;j<=curr;j++)
		{
			if(::nfa[i][j]!='a'&&::nfa[i][j]!='b'&&::nfa[i][j]!='E')
				::nfa[i][j]='0';
		}
	
	
}
void display(){
	int p=curr;
	for(int i=0;i<=p;i++){
		for(int j=0;j<=p;j++){
			cout<<::nfa[i][j]<<" ";
		}
		cout<<endl;
	}
}
int check(string str,int row,int input){
	int l;
	if(l==1)
		return 1;
	if(input==str.length()){
	//	cout<<" input="<<input<<"length="<<str.length();
		if(row==curr)
			return 1;
		else
			{for(int y=0;y<=curr;y++){
				if(nfa[row][curr]=='E')
					return  1;
				if(nfa[row][y]=='E')
					l=check(str,y,input);
			} }
	}
	else{
		for(int i=0;i<=curr;i++){
			if(nfa[row][i]==str[input]){
				l=check(str,i,++input);
			}
			if(nfa[row][i]=='E'){
				l=check(str,i,input);
			}
			if(l==1)
				break;
		}
	}
	if(l==1)
		return 1;
	
	//return 0;
}
/*
void covertToDfa(){
	int l=vector.size();
	int f=0;
	for(int i =0;i<l;i++){
		if(nfa[f][i]=='E'){
			for(int j=0;j<l;j++){
				if(nfa[i][j]=='a')
					{
					
					}
			}
		}
	}
}


*/
int main(){			
	stac s;
	string exp;
	cin>>exp;
	for(int i=0;i<len(exp);i++){
		s.push(exp[i]);
	}
	for(int i=0;i<exp.length();i++){
		//s.display();
		if(exp[i]=='.'){
		//	cout<<"calling dot";	
		
			dot(s);
		}
		if(exp[i]=='*'){
			//cout<<"calling dot";	
			closure();
		}
		if(exp[i]=='+'){
			add(s);
		}
		if(exp[i]=='a')
			s.push(exp[i]);
		if(exp[i]=='b')
			s.push(exp[i]);
	
	}
	cout<<endl;
	display();
	string str;
	cin>>str;
	int ans=check(str,0,0);
	if(ans==1)
	cout<<"YES!";
	else
	cout<<"NO!";
}
