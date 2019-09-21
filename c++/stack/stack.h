#include <iostream>
#include <string>

class StackNode {
private:
  int data;
  StackNode *next;

public:
  StackNode(int item);
  int getData();
  void setNext(StackNode *next);
  StackNode *getNext();
};

class Stack {
private:
  int size;
  StackNode *top;

public:
  int pop();
  void push(int data);
  int peek();
  bool isEmpty();
  int getSize();
};
