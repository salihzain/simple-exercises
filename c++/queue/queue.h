#include <iostream>
#include <string>

class QueueNode {
private:
  int data;
  QueueNode *next;

public:
  QueueNode(int item);
  int getData();
  void setNext(QueueNode *next);
  QueueNode *getNext();
};

class Queue {
private:
  int size;
  QueueNode *first;
  QueueNode *last;

public:
  int remove();
  void add(int data);
  int peek();
  bool isEmpty();
  int getSize();
};
