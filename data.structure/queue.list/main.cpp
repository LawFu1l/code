#include<iostream>
#include<string>

using namespace std;

template<typename T>
struct Node
{
    explicit Node(T d) : data(move(d)), next{nullptr}
    {}

    Node* next;
    T data;
};

template<typename T>
class ListQueue
{
public:
    ListQueue() = default;

    ~ListQueue()
    {
        if (empty())
            return;

        while (_front != _rear)
        {
            auto const tmp = _front->next;
            delete _front;
            _front = tmp;
        }

        delete _front;
        _front = _rear = nullptr;
    }

    bool empty() const
    {
        return _front == nullptr && _rear == nullptr;
    }

    int size() const
    {
        if (empty())
            return 0;

        auto tmp = _front;
        int count = 1;
        while (tmp != _rear)
        {
            tmp = tmp->next;
            count++;
        }

        return count;
    }

    void push(const T& in)
    {
        const auto tmp = new Node<T>(in);
        if (empty())
        {
            _front = _rear = tmp;
            return;
        }

        _rear->next = tmp;
        _rear = tmp;
    }

    void pop()
    {
        if (_front == _rear && !empty())
        {
            delete _front;
            _front = _rear = nullptr;
            return;
        }

        const auto tmp = _front->next;
        delete _front;

        _front = tmp;
    }

    T front() const
    {
        if (empty())
            throw runtime_error("queue is empty");

        return _front->data;
    }

    T back() const
    {
        if (empty())
            throw runtime_error("queue is empty");

        return _rear->data;
    }

private:
    Node<T>* _front{nullptr};
    Node<T>* _rear{nullptr};
};

int main()
{
    {
        ListQueue<double> q;
        for (int i = 0; i < 5; i++)
        {
            q.push(i * 1.1);
        }

        for (int i = 0; i < 5; i++)
        {
            cout << q.front() << endl;
            q.pop();
        }

        cout << q.size() << endl;
    }

    return 0;
}