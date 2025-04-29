#include <iostream>
using namespace std;
bool SortAscending(int arr[], int n) {
	if (n == 1) {
		return true;
	}
	if (arr[n-1] >= arr[n - 2]) {
		SortAscending(arr, n - 1);
	}
	else {
		return false;
	}
}
bool SortDescending(int arr[], int n) {
	if (n == 1) {
		return true;
	}
	if (arr[n - 1] <= arr[n - 2]) {
		SortDescending(arr, n - 1);
	}
	else {
		return false;
	}
}
int main() {
	int arr1[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int arr2[7] = { 0,1,5,2,3,6,9 };
	int n1 = sizeof(arr1) / sizeof(arr1[0]);
	int n2 = sizeof(arr2) / sizeof(arr2[0]);
	cout << "Arr 1: ";
	if ((SortAscending(arr1, n1) == true) || (SortDescending(arr1, n1) == true)) {
		cout << "Already sort!" << endl;
	}
	else {
		cout << "Not sort yet!" << endl;
	}
	cout << "Arr 2: ";
	if ((SortAscending(arr2, n2) == true) || (SortDescending(arr2, n2) == true)) {
		cout << "Already sort!" << endl;
	}
	else {
		cout << "Not sort yet!" << endl;
	}
	return 0;
}