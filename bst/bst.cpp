#include <iostream>
#include <vector>

/*
 *  Binary Search Tree의 구현
 *  기준 노드에 대해 작은 값은 왼쪽, 큰 값은 오른쪽에 배치한다.
 */
using namespace std;

struct Node
{
    Node(const int& val)
        : _val(val)
    {
        left = right = nullptr;
    }

    // true-> 기존노드가 더 큰 값
    bool compare(int val) const { return _val > val; }
    bool left_ok()        const { return left != nullptr;  }
    bool right_ok()       const { return right != nullptr; }

    int _val;
    Node* left;
    Node* right;
};

class BST
{
public:
    BST() : _root{nullptr}
    {}

    void preorder_traverse()
    {
        preorder(_root);
    }

    void insert(int val)
    {
        _root = insert(_root, val);
    }

    bool search(int val)
    {
        return search(_root, val);
    }

    auto find_min_node(Node* node) ->Node*
    {
        while (node->left_ok()) node = node->left;

        return node;
    }

    void remove(int val)
    {
        _root = remove(_root, val);
    }

    void add(int val)
    {
        // 루트 노드가 없을 경우
        if (_root == nullptr)
        {
            _root = new Node(val);
            return;
        }

        auto curr = _root;
        while (true)
        {
            if (curr->compare(val) && curr->left_ok()) 
                curr = curr->left;

            if (curr->compare(val) && !curr->left_ok())
            {
                curr->left = new Node(val);
                break;
            }

            if (!curr->compare(val) && curr->right_ok())
                curr = curr->right;

            if (!curr->compare(val) && !curr->right_ok())
            {
                curr->right = new Node(val);
                break;
            }
        }
    }

    void preorder()
    {
        preorder(_root);
        cout << endl;
    }

    void insert_range(vector<int> arr)
    {
        for (int i : arr)
            insert(i);
    }

private:

    auto insert(Node* node, int val) -> Node*
    {
        if (node == nullptr) return new Node(val);
        if (val < node->_val)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);

        return node;

    }

    auto remove(Node* node, int val) -> Node*
    {
        if (node == nullptr) return nullptr;
        if (val < node->_val)
            node->left = remove(node->left, val);
        else if (val > node->_val)
            node->right = remove(node->right, val);
        else
        {
            if (!node->left_ok() && !node->right_ok())
            {
                delete node;
                return nullptr;
            }

            if (!node->left_ok())
            {
                auto tmp = node->right;
                delete node;
                return tmp;
            }

            if (!node->right_ok())
            {
                auto tmp = node->left;
                delete node;
                return tmp;
            }

            auto temp = find_min_node(node->right);
            node->_val = temp->_val;
            node->right = remove(node->right, temp->_val);
        }
    }

    auto search(Node* node, int val) -> bool
    {
        if (node == nullptr) return false;

        if (node->_val == val) return true;

        return node->_val < val
            ? search(node->right, val)
            : search(node->left, val);
    }

    void preorder(const Node* in)
    {
        if (in != nullptr)
        {
            cout << in->_val << " ";
            preorder(in->left);
            preorder(in->right);
        }
    }

private:
    Node* _root{nullptr};
};

int main()
{
    /*
     *              5
     *           1      6
     *            3       7
     *                      8
     *                         9
     *
     */

    BST tree;
    vector<int> values{8,3,10,1,6,4,7,14,13};

    tree.insert_range(values);
    tree.preorder_traverse();

    return 0;
}
