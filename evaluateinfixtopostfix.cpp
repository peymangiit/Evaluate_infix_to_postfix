#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

// Function to check the precedence of operators
int precedence(char op) {
  if (op == '^') return 3;
  else if (op == '*' || op == '/') return 2;
  else if (op == '+' || op == '-') return 1;
  else return -1;
}

// Function to convert infix expression to postfix expression
string infixToPostfix(string infix) {
  stack<char> s; // Stack to store operators and parentheses
  string postfix = ""; // String to store the postfix expression
  for (int i = 0; i < infix.length(); i++) {
    char c = infix[i]; // Current character
    if (c == ' ') continue; // Ignore whitespace
    if (isdigit(c)) { // If the character is a digit
      postfix += c; // Add it to the postfix expression
    }
    else if (c == '(') { // If the character is an opening parenthesis
      s.push(c); // Push it to the stack
    }
    else if (c == ')') { // If the character is a closing parenthesis
      while (!s.empty() && s.top() != '(') { // Pop and append all the operators until an opening parenthesis is found
        postfix += s.top();
        s.pop();
      }
      if (!s.empty() && s.top() == '(') { // Pop and discard the opening parenthesis
        s.pop();
      }
    }
    else { // If the character is an operator
      while (!s.empty() && precedence(c) <= precedence(s.top())) { // Pop and append all the operators with higher or equal precedence
        postfix += s.top();
        s.pop();
      }
      s.push(c); // Push the current operator to the stack
    }
  }
  while (!s.empty()) { // Pop and append the remaining operators in the stack
    postfix += s.top();
    s.pop();
  }
  return postfix; // Return the postfix expression
}

int evaluatePostfix(string postfix) {
  stack<int> s; // Stack to store operands
  for (int i = 0; i < postfix.length(); i++) {
    char c = postfix[i]; // Current character
    if (c == ' ') continue; // Ignore whitespace
    if (isdigit(c)) { // If the character is a digit
      s.push(c - '0'); // Push it to the stack
    }
    else { // If the character is an operator
      int a = s.top(); s.pop(); // Pop two operands from the stack
      int b = s.top(); s.pop();
      switch (c) { // Perform the operation and push the result to the stack
        case '+': s.push(b + a); break;
        case '-': s.push(b - a); break;
        case '*': s.push(b * a); break;
        case '/': s.push(b / a); break;
        case '^': s.push(pow(b, a)); break;
      }
    }
  }
  return s.top(); // Return the final result
}

// Main function
int main() {
   string infix; // String to store the infix expression
  cout << "Enter an infix expression: ";
  getline(cin, infix); // Read the infix expression from the user
  string postfix = infixToPostfix(infix); // Convert the infix expression to postfix expression
  cout << "The postfix expression is: " << postfix << endl; // Print the postfix expression
  int result = evaluatePostfix(postfix); // Evaluate the postfix expression
  cout << "The result is: " << result << endl; // Print the result
  return 0;
}
