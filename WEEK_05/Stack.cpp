#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct Stack {
	NODE* top;
};
NODE* createNode(int val);
bool isEmpty(Stack s);
Stack* initializeStack();
void push(Stack& s, int key);
int pop(Stack& s);
int size(Stack s);
NODE* createNode(int val) {
	NODE* p = new NODE();
	if (p != nullptr) {
		p->key = val;
		p->p_next = nullptr;
	}
	return p;
}
bool isEmpty(Stack s) {
	if (s.top == nullptr) return true;
	return false;
}
Stack* initializeStack() {
	Stack* s = new Stack();
	if(s != nullptr){
		s->top = nullptr;
	}
	return s;
}
void push(Stack& s, int key) {
	NODE* p = createNode(key);
	if (p == nullptr) {
		return;
	}
	if (isEmpty(s)) {
		s.top = p;
		p->p_next = nullptr;
	}
	else {
		p->p_next = s.top;
		s.top = p;
	}
}
int pop(Stack& s) {
	if (isEmpty(s)) {
		return 0;
	}
	if (s.top->p_next == nullptr) {
		int result = s.top->key;
		delete s.top;
		s.top = nullptr;
		return result;
	}
	int result = s.top->key;
	NODE* temp = s.top->p_next;
	delete s.top;
	s.top = temp;
	return result;
}
int size(Stack s) {
	if (isEmpty(s)) {
		return 0;
	}
	NODE* runNode = s.top;
	int count = 0;
	while (runNode != nullptr) {
		count++;
		runNode = runNode->p_next;
	}
	return count;
}
void printStack(Stack* s) {
	if (isEmpty(*s)) cout << "EMPTY" << endl;
	else {
		NODE* curNode = s->top;
		while (curNode != nullptr) {
			cout << curNode->key << " ";
			curNode = curNode->p_next;
		}
		cout << endl;
	}
}
int main() {
	char input[100];
	ifstream inputFile("inputStack.txt");
	if (inputFile.fail()) {
		cout << "Failed to open this file!";
		return 0;
	}
	Stack* s = nullptr;
	string sentence;
	while (getline(inputFile, sentence)) {
		if (sentence == "init") {
			s = initializeStack();
		}
		else if (sentence.substr(0, 4) == "push") {
			int value = 0;
			int i = 5;
			while (i < sentence.length()) {
				value = value * 10 + (sentence[i] - '0');
				i++;
			}
			push(*s, value);
		}
		else if (sentence == "pop") {
			pop(*s);
		}
		printStack(s);
	}
}
