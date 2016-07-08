#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    int position;

    char next = 0, current = 0;
    Bracket currentBracket(' ', -1);
    for (position = 0; position < text.length(); ++position) {
        next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            currentBracket = {next, position + 1};
            opening_brackets_stack.push(currentBracket);
        } else if (next != ')' && next != ']' && next != '}'){
          continue;
        }
        else if (opening_brackets_stack.empty())
          break; // no matching opening bracket
        else if (next == ')' || next == ']' || next == '}') {
          currentBracket = opening_brackets_stack.top();
          opening_brackets_stack.pop();
          if (!currentBracket.Matchc(next))
            break; // not a match
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.empty() && position == text.length())
      // test is empty or balanced
      std::cout << "Success" << std::endl;
    else{
      if (position < text.length())
        // there is an unmatched closing bracket
        std::cout << position + 1 << std::endl;
      else{
        // we reached the end of the line, but something unmatched has left in the stack
        currentBracket = opening_brackets_stack.top();
        std::cout << currentBracket.position << std::endl;
      }
    }

    return 0;
}
