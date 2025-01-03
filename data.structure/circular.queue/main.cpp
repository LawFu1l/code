#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CircularQueue
{
public:
    CircularQueue(int size)
        : queue_size(size)
    {
        rear = front = -1;
        elements.resize(size);
    }

    bool is_full() const
    {
        return (rear + 1) % queue_size == front;
    }

    bool is_empty() const
    {
        return rear == front;
    }

    int size() const
    {
        // 큐의 사이즈가 0이 아님
        return (rear + queue_size - front) % queue_size;

    }

    bool enqueue(const string& in)
    {
        if (is_full())
            return false;

        rear = (rear + 1) % queue_size;
        elements[rear] = in;
        
        return true;
    }

    string dequeue()
    {
        if (is_empty()) throw runtime_error("queue is empty");

        front = (front + 1) % queue_size;
        return elements[front];
    }

    string to_s() const
    {
        stringstream ss;
        ss << "size: " << size() << ", front: " << front << ", rear: " << rear << endl;

        return ss.str();
    }

private:
    int queue_size;
    int rear, front;
    vector<string> elements;
};

int main()
{
    CircularQueue q(3);

    try
    {
        q.enqueue(to_string(1));
        q.enqueue(to_string(2));
        auto a = q.dequeue();
        auto b = q.dequeue();
        q.dequeue();
        cout << a << " " << b << endl;

        cout << q.to_s();

    }
    catch (runtime_error& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}