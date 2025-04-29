#include <iostream>
using namespace std;
int MinElement(int arr[], int n, int left, int right) {
	while (left < right) {
		int mid = (left + right) / 2;
		if (arr[mid] < arr[left] && arr[mid] < arr[right]) {
			if (arr[mid - 1] > arr[mid]) {
				return arr[mid];
			}
			else {
				right = mid - 1;
			}
		}
		else {
			left = mid + 1;
		}
	}
}
int main() {
	int n;
	int arr[100];
	cout << "Enter the length of array: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Value of arr[" << i << "]: ";
		cin >> arr[i];
	}
	cout << "The min value of array: " << MinElement(arr, n,0,n-1);
	return 0;
}