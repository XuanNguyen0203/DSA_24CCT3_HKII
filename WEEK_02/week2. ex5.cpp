#include <iostream>
using namespace std;
int IsTarget(int arr[], int n, int target) {
	int left = 0, sum = 0, length = INT_MAX;
	for (int right = 0; right < n; right++) {
		sum += arr[right];
		while (sum >= target) {
			if (sum == target) {
				if (length > (right - left + 1))
					length = right - left + 1;
			}
			sum -= arr[left];
			left++;
		}
	}
	if (length != INT_MAX) return length;
	else return 0;
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
	int target;
	cout << "Enter the target: ";
	cin >> target;
	if (IsTarget(arr, n, target) != 0) {
		cout << "Minimal length of a subarray: " << IsTarget(arr, n, target);
	}
	else {
		cout << "Not found";
	}
	return 0;
}