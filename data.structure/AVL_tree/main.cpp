#include <iostream>
#include <vector>

using namespace std;

/*
 *  BST 제대로 구현하기
 *
 */

struct Node
{
    Node(int val)
        : m_val{val}, m_height{0}, left{nullptr}, right{nullptr} {}

    // 이 노드의 값이 더 크면 true
    bool compare(int val) const { return m_val >= val;}
    bool l_not_null()        const { return left != nullptr;}
    bool r_not_null()       const { return right != nullptr;}
    // 자식 노드가 없는 경우
    bool is_alone() const {return right == nullptr && left == nullptr;}

    Node* left_final()
    {
        auto tmp = this;
        while (tmp->left != nullptr)
        {
            tmp = tmp->left;
        }
        return tmp;
    }

    void balance_factor()
    {
        Node* curr = this;
        int left_val = 0, right_val = 0;

        if (curr->left == nullptr && curr->right == nullptr)
        {
            bf = 0;
            return;
        }
        if (curr->right == nullptr) right_val = 0;
        if (curr->right != nullptr) right_val = curr->right->m_height;
        if (curr->left == nullptr) left_val = 0;
        if (curr->left != nullptr) left_val = curr->left->m_height;

        bf = left_val - right_val;
    }

    int m_val, m_height;
    int bf = 0;
    Node* left;
    Node* right;
};

class BST
{
public:
    BST()
    {
        _root = nullptr;
    }

    void add(vector<int>& in)
    {
        for (int i : in)
            add(i);
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
        int distance = 0;
        while (true)
        {
            if (curr->compare(val) && curr->l_not_null())
            {
                distance++;
                curr = curr->left;
            }

            if (curr->compare(val) && !curr->l_not_null())
            {
                distance++;
                curr->left = new Node(val);
                height(distance,val);
                make_balance();
                break;
            }

            if (!curr->compare(val) && !curr->r_not_null())
            {
                distance++;
                curr->right = new Node(val);
                height(distance,val);
                make_balance();
                break;
            }

            if (!curr->compare(val) && curr->r_not_null())
            {
                distance++;
                curr = curr->right;
            }
        }
    }

    void height(int dist, int val)
    {
        auto curr = _root;
        while (curr->m_val != val)
        {
            if (curr->m_val > val)
            {
                if (curr->m_height < dist) curr->m_height = dist;
                curr = curr->left;
                dist--;
            }

            if (curr->m_val < val)
            {
                if (curr->m_height < dist) curr->m_height = dist;
                curr = curr->right;
                dist--;
            }
        }
    }

    void remove(int val)
    {
        auto curr = _root;

        // curr 을 val 노드까지 옮겨준다.
        do
        {
            if (curr->m_val > val)
            {
                curr = curr->left;
            }
            if (curr->m_val < val)
            {
                curr = curr->right;
            }
            if (curr->m_val == val)
            {
                if (curr->right != nullptr)
                {
                    // 후계 노드
                    auto tmp = curr->right->left_final();
                    // curr->right가 왼쪽자식이 없는경우
                    if (tmp == curr->right)
                    {
                        curr->right->left = _root->left;
                        _root = curr->right;
                    }
                    renew_height_of(tmp);
                    make_balance();
                    return;
                }
                if (curr->left != nullptr && curr->right == nullptr)
                {
                    auto tmp = curr->left;
                    _root = tmp;
                    delete curr;
                    make_balance();
                    return;
                }
                if (curr->left == nullptr && curr->right == nullptr)
                {
                    delete curr;
                    make_balance();
                }
            }
        }while (curr->m_val != val);
    }

    void preorder()
    {
        preorder(_root);
        cout << endl;
    }


private:

    void make_balance()
    {
        _root->balance_factor();

        switch (_root->bf)
        {
            //
            case 2:

                _root->left->balance_factor();
                if (_root->left->bf == 1)
                {
                    right_rotation();
                }
                if (_root->left->bf == -1)
                {


                }
                break;

            case -2:
                if (_root->right->bf == 1)
                {

                }
                if (_root->right->bf == -1)
                {

                }
                break;
            default:
                break;
        }
    }

    // BF = 2
    void right_rotation(Node* problem_node)
    {
        if (problem_node->left->right != nullptr)
        {
            auto r = problem_node;
            auto tmp = problem_node->left->right;
            auto t = problem_node->left;
            problem_node->left = tmp;
            t->right = r;
            problem_node = t;
             //가장 높이가 낮은 노드 순으로 갱신
            renew_height_of(tmp);
            renew_height_of(r);
            renew_height_of(t);
        }
    }

    void left_rotation(Node* problem_node)
    {

    }

    // 회전이후 회전에 동원된 노드를 낮은 위치 순으로 높이 갱신
    void renew_height_of(Node* low)
    {
        if (low->left == nullptr && low->right == nullptr) low->m_height = 0;
        if (low->left == nullptr && low->right != nullptr)
        {
            low->m_height = low->right->m_height + 1;
        }
        if (low->left != nullptr && low->right == nullptr)
        {
            low->m_height = low->left->m_height + 1;
        }
        if (low->left != nullptr && low->right != nullptr)
        {
            low->m_height = max(low->left->m_height, low->right->m_height) + 1;
        }
    }

    void preorder(Node* in)
    {
        if (in != nullptr)
        {
            cout <<"node value : " << in->m_val <<" node height : " << in->m_height << endl;
            preorder(in->left);
            preorder(in->right);
        }
    }

    Node* _root;
};

int main()
{
    BST tree;
    vector<int> values{3,7,2,1,77,45};
    tree.add(values);
    tree.preorder();
    tree.remove(3);
    tree.preorder();

    return 0;
}  