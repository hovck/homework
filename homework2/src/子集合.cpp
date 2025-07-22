#include <iostream>
using namespace std;

int spacecount=0;
const int MN = 20;
string input[MN];
string current[MN];
int n=0;
void set(int in, int cs, int ts) {
    if (in == n) {
        if (cs == ts) {
            cout << "(";
            for (int i = 0; i < cs; ++i) {
                cout << "\"" << current[i] << "\"";
                if (i < cs - 1) cout << ",";
            }
			cout << ")" << endl;}
        return;}
    current[cs] = input[in];
    set(in + 1, cs + 1, ts);
    set(in + 1, cs, ts);
}
int main() {
	while (cin >> input[n]) {
		++n;
		if (cin.peek() == '\n') break; // °»´ú¬O§_´«¦æ
	}
    for (int size = 0; size <= n; ++size) {
        cout << "Size=" << size << endl;
        set(0, 0, size);
    }
    return 0;
}


