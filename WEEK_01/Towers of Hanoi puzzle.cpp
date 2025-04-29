#include <iostream>
using namespace std;
void HanoiTower(int n, char from_rod, char to_rod, char aux_rod) {
	if (n == 1) {
		cout << "Move 1 disk from " << from_rod << " to " << to_rod << endl;
		return;
	}
	HanoiTower(n - 1, from_rod, aux_rod, to_rod);
	cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
	HanoiTower(n - 1, aux_rod, to_rod, from_rod);
}
int main() {
	int n;
	cout << "Enter a number of the disks: ";
	cin >> n;
	cout << "The movement: " << endl;
	HanoiTower(n, 'A', 'C', 'B');
	return 0;
}