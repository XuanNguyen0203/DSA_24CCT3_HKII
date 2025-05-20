#include <iostream>
#include <vector>
using namespace std;


struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
// De yeu cau
NODE* createNode(int data);
vector<int> NLR(NODE* pRoot);
vector<int> LNR(NODE* pRoot);
vector<int> LRN(NODE* pRoot);
vector<vector<int>> LevelOrder(NODE* pRoot);
int countNode(NODE* pRoot);
int sumNode(NODE* pRoot);
int heightNode(NODE* pRoot, int value);
int Level(NODE* pRoot, NODE* p);
int countLeaf(NODE* pRoot);
// Ham phu
int Height(NODE* pRoot);
int LevelMax(NODE* pRoot);
void GetLevel(NODE* pRoot, int level, vector<int>& nodeLevel);
bool isLeaf(NODE* p);
NODE* findNode(NODE* pRoot, int value);

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
int LevelMax(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	return max(LevelMax(pRoot->p_right), LevelMax(pRoot->p_left)) + 1;
}
void GetLevel(NODE* pRoot, int level, vector<int>& nodeLevel) {
	if (pRoot == nullptr) return;
	if (level == 0) {
		nodeLevel.push_back(pRoot->key);
	}
	else {
		GetLevel(pRoot->p_left, level - 1, nodeLevel);
		GetLevel(pRoot->p_right, level - 1, nodeLevel);
	}
}
vector<vector<int>> LevelOrder(NODE* pRoot) {
	vector<vector<int>> result;
	int level = LevelMax(pRoot);
	for (int i = 0; i < level; i++) {
		vector<int> node_level;
		GetLevel(pRoot, i, node_level);
		result.push_back(node_level);
	}
	return result;
}
bool isLeaf(NODE* p) {
	if (p->p_left == nullptr && p->p_right == nullptr) return true;
	return false;
}
int countNode(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
	return countNode(pRoot->p_left) + countNode(pRoot->p_right) + 1;
}

NODE* findNode(NODE* pRoot, int value) {
	if (pRoot == nullptr) return nullptr;
	if (pRoot->key == value) return pRoot;
	NODE* leftNode = findNode(pRoot->p_left, value);
	if (leftNode != nullptr) return leftNode;
	return findNode(pRoot->p_right, value);
}
int heightNode(NODE* pRoot, int value) {
	NODE* keyNode = findNode(pRoot, value);
	if (keyNode == nullptr) return -1;
	return Height(keyNode);
}
int sumNode(NODE* pRoot) {
	vector<vector<int>> AllNode = LevelOrder(pRoot);
	int sum = 0;
	for (int i = 0; i < AllNode.size(); i++) {
		vector<int> NodeAtLevel = AllNode[i];
		for (int j = 0; j < NodeAtLevel.size(); j++) {
			sum += NodeAtLevel[j];
		}
	}
	return sum;
}
int Level(NODE* pRoot, NODE* p) {
	if (pRoot == nullptr || p == nullptr) return -1;
	if (pRoot == p) return 0;
	int leftLevel = Level(pRoot->p_left, p);
	if (leftLevel != -1) return leftLevel + 1 ;
	int rightLevel = Level(pRoot->p_right, p);
	if (rightLevel != -1) return rightLevel + 1;
	return -1;
}
int countLeaf(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) return 1;
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}
vector<int> NLR(NODE* pRoot) {
	vector<int> result;
	if (pRoot == nullptr) return result;
	result.push_back(pRoot->key);
	vector<int> left = NLR(pRoot->p_left);
	vector<int> right = NLR(pRoot->p_right);
	
	result.insert(result.end(), left.begin(), left.end());
	result.insert(result.end(), right.begin(), right.end());
		
	return result;
}

vector<int> LNR(NODE* pRoot) {
	vector<int> result;
	if (pRoot == nullptr) return result;
	vector<int> left = LNR(pRoot->p_left);
	vector<int> right = LNR(pRoot->p_right);

	result.insert(result.end(), left.begin(), left.end());
	result.push_back(pRoot->key);
	result.insert(result.end(), right.begin(), right.end());

	return result;
}

vector<int> LRN(NODE* pRoot) {
	vector<int> result;
    if (pRoot == nullptr) return result;
	vector<int> left = LRN(pRoot->p_left);
	vector<int> right = LRN(pRoot->p_right);

	result.insert(result.end(), left.begin(), left.end());
	result.insert(result.end(), right.begin(), right.end());

    result.push_back(pRoot->key);
	return result;
}



