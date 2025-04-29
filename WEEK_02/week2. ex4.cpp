#include <iostream>
using namespace std;
int Check(int weight, int arr[], int n) {
	int day = 0;
	int Sum = 0;
	int i = 0;
	while (i != n) {
		if (Sum + arr[i] <= weight) {
			Sum += arr[i];
		}
		else {
			day++;
			Sum = arr[i];
		}
		i++;
	}
	return ++day;
}
int LeastWeight(int max, int min, int arr[], int n) {
	int wei[100];
	for (int i = 0; i < (max - min + 1); i++) {
		wei[i] = min + i;
	}
	int left = 0;
	int right = max - min;
	while (left < right) {
		int mid = (left + right) / 2;
		cout << "Check: " << Check(wei[mid], arr, n) << endl;
		if (Check(wei[mid], arr, n) == 5) {
			return wei[mid];
		}
		else {
			if (Check(wei[mid], arr, n) > 5) left = mid + 1;
			else right = mid - 1;
		}
	}
}
int main() {
	int arr[100];
	int n;
	cout << "Enter the num of packages: ";
	cin >> n;
	cout << "Enter the weight of each package: " << endl;
	int Sum = 0;
	for (int i = 0; i < n; i++) {
		cout << "Weight of pack " << i << ": ";
		cin >> arr[i];
		Sum += arr[i];
	}
	cout << Sum << " " << arr[n - 1] << endl;
	cout << "The least weight capacity of the ship: " << LeastWeight(Sum, arr[n-1], arr, n);
	return 0;
}