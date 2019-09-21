/*
  THIS NFA IMPLEMENTATION SUPPORTS ONLY ASCII CHARACTERS AS INPUT
  ASCII CHARACTERS HAVE INTEGER VALUES 0-127,
  THUS THE TRANSITION TABLE CONSISTS OF:

    0   1   2   3 ........... 127
  0 {} {}  {}  {} ........... {}
  1 {} {}  {}  {} ........... {}
  2 {} {}  {}  {} ........... {}
  .
  .
  n {} {}  {}  {} ........... {}

  where n is number of states
  and {} is a set of transations from state x on input c
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> col;
const int COL = 128; // for ASCII characters

class NFA {

private:
  int nStates;
  vector<col> transitionTable;
  vector<int> acceptingStates;

public:
  NFA(int n);

  void addTransitiation(int src, char sym, int dst);
  void addAllTransition(int src, int dst);
  vector<int> getTransitions(int src, char sym);

  void setAccepting(int state);
  bool getAccepting(int state);

  bool execute(int currState, string input);
};

NFA::NFA(int n) {
  nStates = n;

  transitionTable.resize(n); // allocate space for rows
  for (int i = 0; i < n; i++) {
    transitionTable.at(i).resize(COL); // allocate cols
  }

  acceptingStates.resize(n);
}

void NFA::addTransitiation(int src, char sym, int dst) {
  transitionTable.at(src).at(sym).push_back(dst);
}

// addAllTransitiion adds transition from src to dst on all characters
void NFA::addAllTransition(int src, int dst) {
  for (int i = 0; i < COL; i++) {
    transitionTable.at(src).at(i).push_back(dst);
  }
}

vector<int> NFA ::getTransitions(int src, char sym) {
  return transitionTable.at(src).at(sym);
}

void NFA::setAccepting(int state) { acceptingStates.at(state) = true; }
bool NFA::getAccepting(int state) { return acceptingStates.at(state); }

bool NFA::execute(int currState, string remInput) {
  // base case, if all input is read, check if currState is an accepting one
  if (remInput == "") {
    return getAccepting(currState);
  }

  // get the transitions from the currentState on the first character
  auto transitionSet = getTransitions(currState, remInput[0]);

  // explore all the possible paths
  for (int i = 0; i < transitionSet.size(); i++) {
    string rem = remInput.substr(1, remInput.size());

    // if we ransition to transitionSet[i], will we reach an accepting state?
    bool foundAccepting = execute(transitionSet[i], rem);
    if (foundAccepting) {
      return true;
    }
  }

  // we have explored all paths, and none got us to an accepting one.
  return false;
}

int main() {
  // let's create a NFA that recognizes text that ends with ".com"
  NFA dotcom(5);
  dotcom.addAllTransition(0, 0);
  dotcom.addTransitiation(0, '.', 1);
  dotcom.addTransitiation(1, 'c', 2);
  dotcom.addTransitiation(2, 'o', 3);
  dotcom.addTransitiation(3, 'm', 4);
  dotcom.setAccepting(4);

  // let's try executing the dfa on hello.com
  cout << "This NFA tests text that ends with .com" << endl;
  cout << "Testing hello.com" << endl;
  cout << (dotcom.execute(0, "hello.com") ? "passed" : "failed")
       << endl; // should pass

  // let's enable the user to try our NFA
  string input;
  while (true) {
    cout << "enter a phrase to test, \"quit\" to quit: ";

    cin >> input;
    if (input == "quit")
      break;

    cout << (dotcom.execute(0, input) ? "passed" : "failed") << endl;
  }
}
