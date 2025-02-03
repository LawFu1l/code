#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct Node
{
    explicit Node(const string &input)
    {
        data = input;
        next = nullptr;
    }

    Node(const Node& rhs)
    {
        if (this != &rhs)
        {
            data = rhs.data;
            next = rhs.next;
        }
    }

    string data;
    Node* next;
};

class Stack
{
public:
    Stack() = default;

    Stack(const Stack& rhs)
    {
        if (this == &rhs)
            return;

        auto oc  = rhs._top;
        _top = nullptr;
        auto nc = _top;

        while (oc != nullptr)
        {
            auto n = new Node(oc->data);
            if (_top == nullptr)
                _top = n;
            else
               nc->next = n;

            nc = n;
            oc = oc->next;
        }

    }

    Stack& operator=(const Stack& rhs)
    {
        if (this != &rhs)
        {
            Stack tmp(rhs);
            std::swap<Node*>(_top, tmp._top);
        }

        return *this;
    }

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

    void print_all()
    {
        cout << "start" << endl;
        auto tmp = this->_top;

        while (tmp != nullptr)
        {
            cout << tmp->data << endl; // (*_top).next
            tmp = tmp->next;          // _top = (*_top).next;
        }
        delete tmp;
        cout << "end" << endl;
    }

private:
    Node* _top{nullptr};
};

Stack reverse(Stack& in)
{
    Stack reversed;

    while (!in.is_empty())
    {
        auto val = in.top();
        reversed.push(val);
        in.pop();
    }

    return reversed;
}

int main()
{
    Stack A;
    for (int i = 0; i < 23; i++)
        A.push(to_string(i));

    A.print_all();

    Stack reversed_A;
    reversed_A = reverse(A);
    reversed_A.print_all();

    return 0;
}
