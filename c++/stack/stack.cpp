#include "stack.h"
#include <iostream>
#include <string>

using namespace std;

StackNode::StackNode(int data) { this->data = data; }

int StackNode::getData() { return this->data; }
void StackNode::setNext(StackNode *next) { this->next = next; }
StackNode *StackNode::getNext() { return this->next; }

int Stack::pop() {
  if (this->top == NULL) {
    throw "empty stack";
  }

  int item = this->top->getData();
  this->top = this->top->getNext();
  this->size--;

  return item;
}

void Stack::push(int item) {
  StackNode *node = new StackNode(item);
  node->setNext(this->top);
  this->top = node;
  this->size++;
}

int Stack::peek() {
  if (this->top == NULL) {
    throw "empty stack";
  }

  return this->top->getData();
}

bool Stack::isEmpty() { return this->size == 0; }

int Stack::getSize() { return this->size; };

int main() {
  Stack *stack = new Stack();
  stack->push(23);
  stack->push(12);
  stack->push(13);

  cout << stack->pop() << endl;
  cout << stack->pop() << endl;
  cout << stack->pop() << endl;

  cout << stack->getSize() << endl;
}