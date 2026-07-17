#include "../header.h"

//   A
//  / \
// B   C
//
// A preorder iterator visits nodes in this order:
// 1. current node
// 2. left subtree
// 3. right subtree
//
// Example:
//     me
//    /  \
//  mom  dad
//  / \
// gma gpa
//
// True preorder for that tree is:
// me, mom, gma, gpa, dad
//
// Note: the iterator below is named PreOrderIterator, but the current
// begin()/operator++() behavior does not actually produce preorder output.
// It starts at the leftmost node and currently prints:
// gma, mom, gpa, me, dad

template <typename T> struct BinaryTree;

template <typename T> struct Node
{
    T value = T();
    Node<T> *left{nullptr}, *right{nullptr}, *parent{nullptr};
    BinaryTree<T> *tree{nullptr};

    Node(T value, Node<T> *left, Node<T> *right)
        : value(value), left(left), right(right) {
            if (this->left) {
                this->left->tree = tree;
                this->left->parent = this;
            }
            if (this->right) {
                this->right->tree = tree;
                this->right->parent = this;
            }
        }

    void set_tree(BinaryTree<T>* t)
    {
        tree = t;
        if (left) left->set_tree(t);
        if (right) right->set_tree(t);
    }

    ~Node()
    {
        if (left) delete left;
        if (right) delete right;        
    }
};

template <typename T> struct BinaryTree
{
    Node<T>* root{nullptr};

    BinaryTree(Node<T> *root) : root(root), pre_order(this)
    {
        this->root->set_tree(this);
    }

    ~BinaryTree() { delete root; }

    template <typename U> struct PreOrderIterator
    {
        Node<U> *current;

        PreOrderIterator(Node<U> *current) : current(current) {}

        PreOrderIterator<U> &operator++()
        {
            if (current->right) {
                current = current->right;
                while (current->left)
                    current = current->left;
            }
            else {
                Node<U>* p = current->parent;
                while (p && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        bool operator!=(const PreOrderIterator<U> &other) const
        {
            return current != other.current;
        }

        Node<U> &operator*() { return *current; }
    }; // PreOrderIterator

    typedef PreOrderIterator<T> iterator;

    iterator begin() { 
        Node<T>* n = root;
        if (n) {
            while (n->left) n = n->left;
        }
        return iterator(n);
    }

    iterator end() { return iterator(nullptr); }

    class PreOrderTraversal
    {
        BinaryTree<T> *tree;
    public:
        PreOrderTraversal(BinaryTree<T> *tree) : tree(tree) {}
        iterator begin() { return tree->begin(); }
        iterator end() { return tree->end(); }
    } pre_order;
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

    for (auto it = family_tree.begin(); it != family_tree.end(); ++it) {
        cout << (*it).value << endl;
    }

    for (const auto &it : family_tree.pre_order) {
        cout << it.value << endl;
    }
    
    return 0;
}
