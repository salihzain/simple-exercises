### Nondeterministic Finite Automaton (NFA)

### Motivation:

I got to learn about the theory behind DFAs, NFAs, and Regular Expressions in Spring 2019. Back then, I had to implement a DFA and an NFA in `C`. My code was extremley horrible, especially for the NFA execution part, even though it worked. 

So, I wanted to learn `c++` by revisiting my horrible NFA `c` code and rewrite that in `c++` with a much more elegant execution algorithm that I formalized recently. I use Depth First Search to explore all possible paths, hoping to find a path that results in an accepting final state or fail.





### Task:

Build an NFA in `C++` that implements the following functions: 

```cpp
  void addTransitiation(int src, char sym, int dst);
  void addAllTransition(int src, int dst);
  vector<int> getTransitions(int src, char sym);

  void setAccepting(int state);
  bool getAccepting(int state);

  bool execute(int currState, string input);
```

Read about NFAs here: [https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton](https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton)




