#include "queue.h"
#include <iostream>
#include <string>

using namespace std;

QueueNode::QueueNode(int data) { this->data = data; }

int QueueNode::getData() { return this->data; }
void QueueNode::setNext(QueueNode *next) { this->next = next; }
QueueNode *QueueNode::getNext() { return this->next; }

int Queue::remove() {
  if (this->first == NULL) {
    throw "empty queue";
  }

  int data = this->first->getData();

  first = first->getNext();
  if (first == NULL) {
    this->last = first;
  }

  return data;
}

void Queue::add(int item) {
  QueueNode *n = new QueueNode(item);

  if (this->last != NULL) {
    this->last->setNext(n);
  }

  this->last = n;

  if (first == NULL) {
    first = last;
  }
}

int Queue::peek() {
  if (this->first == NULL) {
    throw "empty queue";
  }

  return this->first->getData();
}

bool Queue::isEmpty() { return this->size == 0; }

int Queue::getSize() { return this->size; };

int main() {
  Queue *queue = new Queue();

  queue->add(1);
  queue->add(2);
  queue->add(3);

  int expected[3] = {1, 2, 3};

  for (int i = 0; i < 3; i++) {
    int actual = queue->remove();

    if (actual != expected[i]) {
      cout << "bad implementation: expected: " << expected[i]
           << " got: " << actual << endl;
      continue;
    }

    cout << "as expected " << actual << endl;
  }
}