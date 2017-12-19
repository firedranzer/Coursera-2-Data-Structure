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

    int pos_error = 0;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        //Whenever string starts with "(" or "{" or "["
        if (next == '(' || next == '[' || next == '{') {
            Bracket b(next, position+1);
            opening_brackets_stack.push(b);
        }

        if (next == ')' || next == ']' || next == '}') {
            //for the case like ")"
            if(opening_brackets_stack.empty()){
              pos_error = position + 1;
              break;
            }
            Bracket top = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            //For the cases like "(("
            if(!top.Matchc(next)){
              pos_error = position + 1;
              break;
            }
        }
    }

    // Printing answer, write your code here

    //For the case when string is empty
    if(pos_error == 0 && opening_brackets_stack.empty())
      std::cout << "Success" << '\n';
    else{
      //When the string is nested like "([])"
      if(pos_error == 0){
        while (opening_brackets_stack.size()>1) {
          opening_brackets_stack.pop();
        }
        pos_error = opening_brackets_stack.top().position;
      }
      std::cout<<pos_error;
    }

    return 0;
}
