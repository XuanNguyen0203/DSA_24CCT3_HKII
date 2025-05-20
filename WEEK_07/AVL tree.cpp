#include <iostream>
#include <vector>
using namespace std;


struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};
// Hàm chính
NODE* createNode(int data);
void Insert(NODE*& pRoot, int x);
void Remove(NODE*& pRoot, int x);
bool isAVL(NODE* pRoot);
//Hàm phụ

NODE* createNode(int data) {
	NODE* newNode = new NODE();
	if (newNode != nullptr) {
		newNode->key = data;
		newNode->p_left = newNode->p_right = nullptr;
	}
	return newNode;
}

int Height(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	return max(Height(pRoot->p_right), Height(pRoot->p_left)) + 1;
}

int getBalace(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	return Height(pRoot->p_left) - Height(pRoot->p_right);
}

void updateHeight(NODE* pRoot) {
	if (pRoot != nullptr)
		pRoot->height = 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));
}

void rightRotate(NODE*& p) {
	NODE* x = p->p_left;
	NODE* y = p->p_right;

	x->p_right = p;
	p->p_left = y;
	p = x;

	updateHeight(p->p_right);
	updateHeight(p);

}

void leftRotate(NODE*& p) {
	NODE* y = p->p_right;
	NODE* x = y->p_left;

	y->p_left = p;
	p->p_right = x;
	p = y;

	updateHeight(p->p_left);
	updateHeight(p);
}

void Insert(NODE*& pRoot, int x) {
	NODE* p = createNode(x);
	if (pRoot == nullptr) {
		pRoot = p;
		return;
	};
	if (pRoot->key > x) Insert(pRoot->p_left, x);
	else if (pRoot->key < x) Insert(pRoot->p_right, x);
	else return;

	updateHeight(pRoot);
	int balance = getBalace(pRoot);
	if (balance > 1 && x < pRoot->p_left->key)
		rightRotate(pRoot);
	else if (balance < -1 && x > pRoot->p_right->key)
		leftRotate(pRoot);
	else if (balance > 1 && x > pRoot->p_left->key) {
		leftRotate(pRoot->p_left);
		rightRotate(pRoot);
	}
	else if (balance < -1 && x < pRoot->p_right->key) {
		rightRotate(pRoot->p_right);
		leftRotate(pRoot);
	}
}

NODE* findMin(NODE* pRoot) {
	NODE* Min = pRoot;
	while (Min->p_left != nullptr) Min = Min->p_left;
	return Min;
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
	updateHeight(pRoot);
	int balance = getBalace(pRoot);
	if (balance > 1 && getBalace(pRoot->p_left) >= 0)
		rightRotate(pRoot);
	else if (balance < -1 && getBalace(pRoot->p_left) < 0)
		leftRotate(pRoot);
	else if (balance > 1 && getBalace(pRoot->p_right) <= 0) {
		leftRotate(pRoot->p_left);
		rightRotate(pRoot);
	}
	else if (balance < -1 && getBalace(pRoot->p_right) > 0) {
		rightRotate(pRoot->p_right);
		leftRotate(pRoot);
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

bool isBalanced(NODE* pRoot) {
	if (pRoot == nullptr) return true;
	if (abs(getBalace(pRoot)) > 1) return false;
	return isBalanced(pRoot->p_left) && isBalanced(pRoot->p_right);
}

bool isAVL(NODE* pRoot) {
	return isBST(pRoot) && isBalanced(pRoot);
}


