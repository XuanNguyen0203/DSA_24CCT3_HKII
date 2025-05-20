#include <iostream>
#include <vector>
using namespace std;


struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
// Hàm chính
NODE* Search(NODE* pRoot, int x);
void Insert(NODE*& pRoot, int x);
void Remove(NODE*& pRoot, int x);
NODE* createTree(int a[], int n);
void removeTree(NODE*& pRoot);
int Height(NODE* pRoot);
int countLess(NODE* pRoot, int x);
int countGreater(NODE* pRoot, int x);
bool isBST(NODE* pRoot);
bool isFullBST(NODE* pRoot);
// Hàm phụ

NODE* createNode(int data) {
	NODE* newNode = new NODE();
	if (newNode != nullptr) {
		newNode->key = data;
		newNode->p_left = newNode->p_right = nullptr;
	}
	return newNode;
}

NODE* Search(NODE* pRoot, int x) {
	NODE* runNode = pRoot;
	while (runNode != nullptr) {
		if (runNode->key == x)
			return runNode;
		else if (x < runNode->key)
			runNode = runNode->p_left;
		else
			runNode = runNode->p_right;
	}
	return nullptr;
}

void Insert(NODE*& pRoot, int x) {
	NODE* p = createNode(x);
	if (pRoot == nullptr) {
		pRoot = p;
		return;
	}
	NODE* runNode = pRoot;
	while (true) {
		if (runNode->key < x) {
			if (runNode->p_right == nullptr) {
				runNode->p_right = p;
				return;
			}
			runNode = runNode->p_right;
		}
		else {
			if (runNode->p_left == nullptr) {
				runNode->p_left = p;
				return;
			}
			runNode = runNode->p_left;
		}
	}
}

NODE* findMin(NODE* pRoot) {
	NODE* Min = pRoot;
	while (Min->p_left != nullptr) Min = Min->p_left;
	return Min;
}

NODE* findNode(NODE* pRoot, int value) {
	if (pRoot == nullptr) return nullptr;
	if (pRoot->key == value) return pRoot;
	NODE* leftNode = findNode(pRoot->p_left, value);
	if (leftNode != nullptr) return leftNode;
	return findNode(pRoot->p_right, value);
}

bool isLeaf(NODE* p) {
	if (p->p_left == nullptr && p->p_right == nullptr) return true;
	return false;
}

void Remove(NODE*& pRoot, int x) {
	if (pRoot == nullptr) return;
	if (pRoot->key > x) Remove(pRoot->p_left, x);
	else if (pRoot->key < x) Remove(pRoot->p_right, x);
	else {
		if (isLeaf(pRoot)) {
			delete pRoot;
			pRoot = nullptr;
		}
		else if (pRoot->p_left == nullptr) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_right;
			delete temp;
		}
		else if (pRoot->p_right == nullptr) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_left;
			delete temp;
		}
		else {
			NODE* Min = findMin(pRoot->p_right);
			pRoot->key = Min->key;
			Remove(pRoot->p_right, Min->key);
		}
	}
}

NODE* createTree(int a[], int n) {
	NODE* pRoot = nullptr;
	for (int i = 0; i < n; i++) {
		Insert(pRoot, a[i]);
	}
	return pRoot;
}

void removeTree(NODE*& pRoot) {
	if (pRoot == nullptr) return;
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = nullptr;
}

int Height(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	return max(Height(pRoot->p_right), Height(pRoot->p_left)) + 1;
}

int countNode(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	return countNode(pRoot->p_left) + countNode(pRoot->p_right) + 1;
}

int countLess(NODE* pRoot, int x) {
	if (pRoot == nullptr) return 0;
	if (pRoot->key >= x) return countLess(pRoot->p_left, x);
	else {
		return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
	}
}

int countGreater(NODE* pRoot, int x) {
	if (pRoot == nullptr) return 0;
	if (pRoot->key <= x) return countGreater(pRoot->p_right, x);
	else {
		return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
	}
}

bool isBSTtutil(NODE* pRoot, int max, int min) {
	if (pRoot == nullptr) return true;
	if (pRoot->key <= min || pRoot->key >= max) return false;
	return isBSTtutil(pRoot->p_left, pRoot->key, min) && isBSTtutil(pRoot->p_right, max, pRoot->key);
}

bool isBST(NODE* pRoot) {
	return isBSTtutil(pRoot, INT_MAX, INT_MIN);
}

int LevelMax(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	return max(LevelMax(pRoot->p_right), LevelMax(pRoot->p_left)) + 1;
}

int Level(NODE* pRoot, NODE* p) {
	if (pRoot == nullptr || p == nullptr) return -1;
	if (pRoot == p) return 0;
	int leftLevel = Level(pRoot->p_left, p);
	if (leftLevel != -1) return leftLevel + 1;
	int rightLevel = Level(pRoot->p_right, p);
	if (rightLevel != -1) return rightLevel + 1;
	return -1;
}

bool isFull(NODE* pRoot) {
	if (pRoot == nullptr) return true;
	if (pRoot->p_left == nullptr && pRoot->p_right != nullptr || pRoot->p_left != nullptr && pRoot->p_right == nullptr) return false;
	return isFull(pRoot->p_left) && isFull(pRoot->p_right);
}

bool isFullBST(NODE* pRoot) {
	if (isBST(pRoot) && isFull(pRoot)) return true;
	return false;
}




