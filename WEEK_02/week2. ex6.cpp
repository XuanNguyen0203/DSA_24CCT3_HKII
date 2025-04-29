#include <iostream>
using namespace std;
bool SumEqualTarget(int arr[], int n, int target) {
	int left = 0;
	int right = n - 1;
	while (left<right) {
		int sum = arr[left] + arr[right];
		if ( sum == target)
			return true;
		else {
			if (sum < target) {
				left++;
			}
			else {
				right--;
			}
		}
	}
	return false;
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
	if (SumEqualTarget(arr, n, target)) cout << "YES!";
	else cout << "NO!";
	return 0;
}