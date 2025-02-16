#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    stack()
    {
        arr = new int[50];
        top = -1;
    }
    ~stack() {
        delete[] arr;
    }

    // Push a value onto the stack
    void push(int value)
    {
        if (top == 49)
        {
            cout << "Stack overflow";
        }

        top++;
        arr[top] = value;
    }

    // Pop a value from the stack
    int pop() {
        int res = arr[top];
        top--;
        return res;
    }

    // Perform operation on two values a and b
    int operation(int a, int b, char op)
    {
        if (op == '+')
        {
            return a + b;
        }
        else if (op == '-')
        {
            return a - b;
        }
        else if (op == '*' || op == '×')
        {
            return a * b;
        }
        else if (op == '/')
        {
            return a / b;
        }
        else {
            cout << "Invalid operation symbol, the result will be incorrect" << endl;
            return 0;
        }
    }

    // Return the result (top element in the stack)
    int result() {
        return arr[top];
    }
};

int main()
{
    string postfix;
    string token;
    stack st;

    cout << "Enter the expression in postfix notation: ";
    getline(cin, postfix);

    stringstream ss(postfix);
    while (ss >> token)
    {
        if (isdigit(token[0]))
        {
            st.push(stoi(token));
        }
        else {
            int a = st.pop();
            int b = st.pop();
            int result = st.operation(a, b, token[0]);
            st.push(result);
        }
    }

    cout << "Answer: " << st.result();
}
