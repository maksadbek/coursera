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
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
                opening_brackets_stack.push(Bracket(next, position+1));
        }

        if (next == ')' || next == ']' || next == '}') {
                if(opening_brackets_stack.size() == 0) {
                        std::cout << position+1;
                        return 0;
                }

                switch(next) {
                        case ')':
                                if(opening_brackets_stack.top().type != '(') {
                                        std::cout << position+1;
                                        return 0;
                                }
                                break;
                        case ']':
                                if(opening_brackets_stack.top().type != '[') {
                                        std::cout << position+1;
                                        return 0;
                                }
                                break;
                        case '}':
                                if(opening_brackets_stack.top().type != '{') {
                                        std::cout << position+1;
                                        return 0;
                                }
                                break;
                }
                opening_brackets_stack.pop();
        }
    }

        if(opening_brackets_stack.size() > 0 ) {
                std::cout << opening_brackets_stack.top().position;
                return 0;
        }

        std::cout << "Success";

    return 0;
}
