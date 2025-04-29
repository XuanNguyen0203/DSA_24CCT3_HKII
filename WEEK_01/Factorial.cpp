#include <iostream>
using namespace std;
int Factorial(int n) {
	if (n == 1) return 1;
	if (n == 0) return 1;
	return Factorial(n-1) * n;
}
int main() {
	int n;
	cout << "Enter a number: ";
	cin >> n;
	cout << "Factorial of a number " << Factorial(n);
	return 0;
}