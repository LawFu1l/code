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

    Node* get_top()
    {
        return this->_top;
    }

private:
    Node* _top{nullptr};
};

string get_data(Node* &in)
{
    return in->data;
}

Stack reverse(Stack& in)
{
    Stack reversed;

    auto tmp_top = in.get_top();

    while (tmp_top != nullptr)
    {
        auto tmp_data = get_data(tmp_top);
        reversed.push(tmp_data);
        tmp_top = tmp_top->next;
    }

    return reversed;
}

int main()
{
    Stack A;


    for (int i = 0; i < 10; i++)
    {
        A.push(to_string(i));
    }

    A.print_all();

    Stack reversed_A = reverse(A);

    reversed_A.print_all();

    return 0;
}