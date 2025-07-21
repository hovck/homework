#include <iostream>
using namespace std;
unsigned int ack(unsigned int m, unsigned int n) {
	if (m == 0) {return n + 1;}
	if (n == 0) {return ack(m-1,1);}
	return ack(m-1, ack(m,n-1));
}
 int main() {
	int m,n;
	cin >> m >>n;
	cout << "A(" << m << ", " << n << ") = " << ack(m, n) << "\n";
}
