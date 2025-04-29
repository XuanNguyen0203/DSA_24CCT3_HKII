#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct Queue {
	NODE* head;
	NODE* tail;
};
Queue* initializeQueue();
NODE* createNode(int val);
void enqueue(Queue& q, int key);
int dequeue(Queue& q);
int size(Queue q);
bool isEmpty(Queue q);
Queue* initializeQueue() {
	Queue* q = new Queue();
	if (q != nullptr) {
		q->head = q->tail = nullptr;
	}
	return q;
}
NODE* createNode(int val) {
	NODE* p = new NODE();
	if (p != nullptr) {
		p->key = val;
		p->p_next = nullptr;
	}
	return p;
}
void enqueue(Queue& q, int key) {
	NODE* p = createNode(key);
	if (p == nullptr) {
		return;
	}
	if (isEmpty(q)) {
		q.head = q.tail = p;
		p->p_next = nullptr;
	}
	else {
		NODE* runNode = q.head;
		while (runNode != q.tail) {
			runNode = runNode->p_next;
		}
		runNode->p_next = p;
		p->p_next = nullptr;
		q.tail = p;
	}
}
int dequeue(Queue& q) {
	if (isEmpty(q)) return 0;
	if (q.head == q.tail) {
		int result = q.head->key;
		delete q.head;
		q.head = q.tail = nullptr;
		return result;
	}
	int result = q.head->key;
	NODE* temp = q.head->p_next;
	delete q.head;
	q.head = temp;
	return result;
}
int size(Queue q) {
	if (isEmpty(q)) return 0;
	NODE* runNode = q.head;
	int count = 0;
	while (runNode != nullptr) {
		count++;
		runNode = runNode->p_next;
	}
	return count;
}
bool isEmpty(Queue q) {
	if (q.head == nullptr) return true;
	return false;
}
void printQueue(Queue* q) {
	if (isEmpty(*q)) cout << "EMPTY" << endl;
	else {
		NODE* curNode = q->head;
		while (curNode != nullptr) {
			cout << curNode->key << " ";
			curNode = curNode->p_next;
		}
		cout << endl;
	}
}
int main() {
	char input[100];
	ifstream inputFile("inputQueue.txt");
	if (inputFile.fail()) {
		cout << "Failed to open this file!";
		return 0;
	}
	Queue* q = nullptr;
	string sentence;
	while (getline(inputFile, sentence)) {
		if (sentence == "init") {
			q = initializeQueue();
		}
		else if (sentence.substr(0, 7) == "enqueue") {
			int value = 0;
			int i = 8;
			while (i < sentence.length()) {
				value = value * 10 + (sentence[i] - '0');
				i++;
			}
			enqueue(*q, value);
		}
		else if (sentence == "dequeue") {
			dequeue(*q);
		}
		printQueue(q);
	}
}