#include <iostream>
using namespace std;
void Sort(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
int Check(int arr[], int n, int result[][3]) {
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (i > 0 && arr[i] == arr[i - 1]) continue;
		int sum = 0;
		int left = i + 1;
		int right = n - 1;
		while (left < right) {
			sum = arr[i] + arr[left] + arr[right];
			if (sum == 0) {
				result[j][0] = arr[i];
				result[j][1] = arr[left];
				result[j][2] = arr[right];
				j++;

				while (left < right && arr[left] == arr[left + 1]) left++;
				while (left < right && arr[right] == arr[right - 1]) right--;
				left++;
				right--;
			}
			else {
				if (sum > 0) {
					right--;
				}
				else {
					left++;
				}
			}
		}
	}
	return j;
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
	int result[10][3];
	Sort(arr, n);
	int LengthResult = Check(arr, n, result);
	cout << "Result: " << endl;
	for (int i = 0; i < LengthResult; i++) {
		cout << result[i][0] << " " << result[i][1] << " " << result[i][2] << endl;
	}
	return 0;
}