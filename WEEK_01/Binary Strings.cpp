#include <iostream>
#include <string>
using namespace std;
void BinaryStrings(int n, string str) {
	if (n == 0) {
		cout << str << endl;
		return;
	}
	BinaryStrings(n - 1, str + '0');
	BinaryStrings(n - 1, str + '1');
}
int main() {
	int n;
	cout << "Enter a number: ";
	cin >> n;
	cout << "Output: " << endl;
	BinaryStrings(n,"");
	return 0;
}
