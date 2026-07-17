#include "../header.h"
#include <coroutine>
#include <generator>

//   A
//  / \
// B   C

template <typename T> struct BinaryTree;

template <typename T> struct Node
{
    T value = T();
    Node<T> *left{nullptr}, *right{nullptr};

    Node(T value, Node<T> *left, Node<T> *right)
        : value(value), left(left), right(right) {}

    ~Node()
    {
        if (left) delete left;
        if (right) delete right;        
    }
};

template <typename T> struct BinaryTree
{
    Node<T>* root{nullptr};

    BinaryTree(Node<T> *root) : root(root) {}

    ~BinaryTree() { delete root; }

    std::generator<Node<T>*> post_order()
    {
        return post_order_impl(root);
    }
    // there was no recursion in the previous file
private:
    std::generator<Node<T>*> post_order_impl(Node<T>* node)
    {
        if (!node) co_return;
        for (auto x : post_order_impl(node->left)) co_yield x;
        for (auto y : post_order_impl(node->right)) co_yield y;
        co_yield node;
    }
};

int main()
{
    //      me
    //     /  \
    //  mom   dad
    //  /  \
    // gma gpa

    BinaryTree<string> family_tree(new Node<string>("me",
        new Node<string>("mom",
            new Node<string>("gma", nullptr, nullptr),
            new Node<string>("gpa", nullptr, nullptr)),
        new Node<string>("dad", nullptr, nullptr)));

    for (auto it : family_tree.post_order()) {
        cout << it->value << endl;
    }
    
    return 0;
}
