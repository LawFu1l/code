#include <iostream>
#include <string>

using namespace std;

struct Node
{
    Node(const string& name)
        : _name(name)
    {
        left_child = right_child = nullptr;
    }

    string _name;
    Node* left_child;
    Node* right_child;
};

class Binary_tree
{
public:
    Binary_tree()
    {

    }

    void visit(const Node* in)
    {
        if (in != nullptr)
            cout << in->_name << endl;
    }

    void preorder(const Node* in)
    {
        if (in != nullptr)
        {
            visit(in);
            preorder(in->left_child);
            preorder(in->right_child);
        }
    }

    // 노드 삽입 함수
    

private:

};


int main()
{

    return 0;
}