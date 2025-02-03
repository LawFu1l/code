#include <iostream>
#include <string>

using namespace std;

struct Node
{
    Node(const string& in)
        : data(in)
    {}
    string data;
    Node* next;
};

//GPT 이용
template <typename... Args>
Node* make_linked_list(Args... args)
{
    Node* head;
    Node* current;

    if (head == nullptr)
    {
        head = current = new Node(args);
    }
    else
    {
        current->next = new Node(args);
    }

    return head;
}

template <typename... Args>
Node* reverse(Args ...args)
{

    Node* result;
    return result;
}

int main()
{
    Node block1(to_string(1));
    Node block2(to_string(2));
    Node block3(to_string(3));
    Node block4(to_string(4));
    Node block5(to_string(5));

    Node* head = make_linked_list(block1,block2,block3,block4,block5);
     
    return 0;
}