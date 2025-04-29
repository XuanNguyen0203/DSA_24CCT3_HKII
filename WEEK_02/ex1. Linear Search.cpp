#include <iostream>
using namespace std;
int LinearSearch(int arr[], int n, int key) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == key) {
			return i;
		}
	}
	return -1;
}
int main() {
	int key;
	int n;
	int arr[100];
	cout << "Enter the length of array: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Value of arr[" << i << "]: ";
		cin >> arr[i];
	}
	cout << "Enter a key: ";
	cin >> key;
	if (LinearSearch(arr, n, key) != -1) {
		cout << "The local of key: " << LinearSearch(arr, n, key) + 1;
	}
	else cout << "Not found";
	return 0;
}