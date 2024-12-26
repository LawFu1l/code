#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Node
{
    explicit Node(string in) : data(std::move(in))
    {
        next = nullptr;
    }

    Node* next;
    string data;
};

class ArrayQueue
{
public:
    ArrayQueue(const int& size) : _max_size(size)
    {
        elements.resize(_max_size);
        front = -1;
        rear = -1;
    }

    ~ArrayQueue() = default;

    bool is_full() const
    {
        return front == _max_size - 1;
    }

    bool is_empty() const
    {
        return front == rear;
    }

    bool dequeue()
    {
        if (is_empty()) return false;
        front++;

        return true;
    }

    bool enqueue(const string& input)
    {
        rear++;
        if (rear == _max_size )
            return false;

        elements[rear] = input;
        return true;
    }

    bool print_queue()
    {
        cout << "start" << endl;
        while (!this->is_empty())
        {
            cout << this->get_data() << endl;
            this->dequeue();
        }
    s    cout << "end" << endl;

        return true;
    }

    string get_data()
    {
        return this->elements[front+1];
    }
private:
    int _max_size;
    vector<string> elements;
    int front, rear;
    
};

class Link_queue
{
public:
    // 생성자
    explicit Link_queue(const int& size) : _max_size(size)
    {
        current_size = 0;
    }

    // 새로운 노드 추가
    bool enqueue(const string& input)
    {
        if (rear == nullptr)
        {
            Node* tmp = new Node(input);
            rear = tmp;
            current_size++;
            return true;
        }

        Node* tmp = new Node(input);
        tmp->next = rear->next;
        rear = tmp;
        current_size++;

        return true;
    }

    // 가장 앞선 노드 삭제
    bool dequeue()
    {
        if (rear == nullptr)
            return false;

        Node* tmp = rear;
        while (tmp->next != nullptr)
        {
            tmp = tmp -> next;
        }
        front = tmp;
        delete tmp;
        current_size--;

        return true;
    }

    bool is_full()
    {
        if (_max_size == current_size)
            return true;

        return false;
    }

    bool is_empty()
    {
        if (current_size == 0)
            return true;

        return false;
    }

    string get_data()
    {
        return this->data;
    }

    bool print()
    {
        cout << "Link Start" << endl;

        while (!is_empty())
        {
            cout << this->get_data() << endl;
            this->dequeue();
        }

        cout << "Link End" << endl;

        return true;
    }

    ~Link_queue() = default;

private:
    int _max_size;
    string data;
    Node* front = nullptr;
    Node* rear = nullptr;
    int current_size;
};

int main()
{
    /*
    ArrayQueue ArrayQueue(5);

    for (int i = 1 ; i < 6; i++)
    {
        ArrayQueue.enqueue(to_string(i));
    }
    `*/
    Link_queue link_queue(5);

    for (int i = 1; i < 6; i++)
    {
        link_queue.enqueue(to_string(i));
    }

    link_queue.print();
   // ArrayQueue.print_queue();
    return 0;
}

