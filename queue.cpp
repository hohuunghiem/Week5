#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node {
	int key;
	Node* next;
	Node* prev;
};
struct Queue {
	Node* head;
	Node* tail;
};
Queue* initializeQueue() {
	Queue* q = new Queue;
	q->head = nullptr;
	q->tail = nullptr;
	return q;
}
bool isEmpty(Queue* q) {
	if (q->head == nullptr && q->tail == nullptr) return true;
	return false;
}
Node* createNode(int data) {
	Node* temp = new Node;
	temp->key = data;
	temp->prev = nullptr;
	temp->next = nullptr;
	return temp;
}
void enqueue(Queue*& q, int key) {
	Node* temp = createNode(key);
	if (q->head == nullptr) {
		q->head = q->tail = temp;
	}
	else {
		q->tail->next = temp;
		temp->prev = q->tail;
		q->tail = temp;
	}
}
int dequeue(Queue*& q) {
	if (isEmpty(q)) {
		cerr << "Queue is empty ";
		return -1;
	}
	int result = q->head->key;
	Node* temp = q->head;
	q->head = q->head->next;
	if (q->head != nullptr) {
		q->head->prev = nullptr;
	}
	else {
		q->tail = nullptr;
	}
	delete temp;
	return result;
}
void printQueue(Queue* q, ofstream& outfile) {
	if (q->head == nullptr) {
		outfile << "EMPTY" << endl;
		return;
	}
	Node* cur = q->head;
	while (cur->next != nullptr) {
		cur = cur->next;
	}
	while (cur != nullptr) {
		outfile << cur->key << " ";
		cur = cur->prev;
	}
	outfile << endl;
}

void clearQueue(Queue*& q) {
	while (!isEmpty(q)) {
		dequeue(q);
	}
}

int size(Queue* q) {
	if (q->head == nullptr) return 0;
	int result = 0;
	Node* cur = q->head;
	while (cur != nullptr) {
		result++;
		cur = cur->next;
	}
	return result;
}

int main() {
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	if (!infile) {
		cerr << "Can't open input.txt" << endl;
		return -1;
	}
	Queue* q = new Queue;
	string cmd;
	while (infile >> cmd) {
		if (cmd == "init") {
			q = initializeQueue();
		}
		else if (cmd == "enqueue") {
			int x;
			infile >> x;
			enqueue(q, x);
		}
		else if (cmd == "dequeue") {
			dequeue(q);
		}
		printQueue(q, outfile);
	}

	infile.close();
	outfile.close();
	return 0;
}