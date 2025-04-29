#include <iostream>
using namespace std;
int LinearSearchSentinel(int arr[], int n, int key) {
	int last = arr[n - 1];
	arr[n - 1] = key;
	int i = 0;
	while (arr[i] != key) {
		i++;
	}
	arr[n - 1] = last;
	if (i == n-1 && arr[n - 1] != key) {
		return -1;
	}
	else return i;
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
	if (LinearSearchSentinel(arr, n, key) != -1) {
		cout << "The local of key: " << LinearSearchSentinel(arr, n, key) + 1;
	}
	else cout << "Not found";
	return 0;
}