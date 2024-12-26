#include <iostream>
#include <string>

using namespace std;

struct Node
{
    explicit Node(const string &input)
    {
        data = input;
        next = nullptr;
    }

    string data;
    Node* next;
};

class Stack
{
public:
    Stack() = default;

    ~Stack()
    {
       while (_top != nullptr)
       {
            auto temp = _top;
           _top = temp->next;
           delete temp;
       }
    }

    bool push(const string& in)
    {
        const auto tmp = new Node(in);
        tmp->next = _top;
        _top = tmp;

        return true;
    }

    bool pop()
    {
        if (_top == nullptr)
            return false;

        auto tmp = _top;
        _top = _top->next;
        delete tmp;
        return true;
    }

    string top()
    {
        if (_top == nullptr) throw runtime_error("Stack is empty");

        return _top->data;
    }

    bool is_empty() const
    {
        return _top == nullptr;
    }

    void print()
    {
        cout << "start" << endl;
        while (_top != nullptr)
        {
            cout << _top->data << endl; // (*_top).next
            _top = _top->next;          // _top = (*_top).next;
        }
        cout << "end" << endl;
    }

private:
    Node* _top{nullptr};
};


int main()
{
    Stack a;
    for (int i = 0; i < 5; i++)
        a.push(to_string(i));

    for (int i = 0; i < 3; i++)
        a.pop();

    a.print();

    return 0;
}