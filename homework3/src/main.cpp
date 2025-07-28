#include <iostream>
#include <math.h>
using namespace std;

class poly;
class term{
	friend poly;
	private:
		float coef;
		int exp;
};

class poly{
	private:
		term *termarray;
		int capacity;
		int terms;
	public:
		poly();
		poly add(poly b);
		
		float eval(float f);
		void newterm(float coef,int exp);
		void output();
};

int main(){
	int i,j,m,n;
	poly a;
	poly b;
	poly c;
	while(cin >> i >>j){
		for(int k=0;k<i;k++){
			cin >> m >>n;
			a.newterm(m,n);
		}
		for(int k=0;k<j;k++){
			cin >> m >>n;
			b.newterm(m,n);	
		}
		a.add(b);
		a.output();
	}
	return 0;
}

poly::poly(){
};
poly poly::add(poly b){
};
void poly::newterm(float coef,int exp){
	
};
void poly::output(){
};
