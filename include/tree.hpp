#include <iostream>
#include <istream>
#include <sstream>
#include <typeinfo>
#include <vector>

#define CHECK_INPUT(var)                                                \
if (!inp.good() && !inp.eof()) {                                        \
    std::cerr << "Error input, need this as " << typeid(var).name();    \
    exit(-1);                                                           \
} 


template <typename KeyT>
class AVLTree {
private:
    struct Node {
        KeyT key;
        Node* left;
        Node* right;
        int height;

        Node(KeyT value) : key(value), left(nullptr), right(nullptr), height(1) {}

        void updateHeight() {
            int leftHeight = left ? left->height : 0;
            int rightHeight = right ? right->height : 0;
            height = 1 + std::max(leftHeight, rightHeight);
        }
    };

    Node* root;

    static int height(Node* node) { 
        return node ? node->height : 0;
    }

    static int balance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->updateHeight();
        x->updateHeight();

        return x; 
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->updateHeight();
        y->updateHeight();

        return y; 
    }

    Node* insert(Node* node, KeyT key) {

        if (!node) return new Node(key);

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }

        // updateHeight(node);
        node->updateHeight();

        int balanceFactor = balance(node);

        if (balanceFactor > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        if (balanceFactor < -1 && key > node->right->key) {
            return leftRotate(node);
        }

        if (balanceFactor > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balanceFactor < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(Node* node, std::vector<KeyT> &out) {
        if (node) {
            inOrder(node->left, out);
            out.push_back(node->key);
            inOrder(node->right, out);
        }
    }

    int countInRange(Node* node, KeyT lower, KeyT upper) const {
        if (!node) return 0;

        if (node->key >= lower && node->key <= upper) {
            return 1 + countInRange(node->left, lower, upper) + countInRange(node->right, lower, upper);
        }

        else if (node->key < lower) {
            return countInRange(node->right, lower, upper);
        }

        else {
            return countInRange(node->left, lower, upper);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(KeyT key) {
        root = insert(root, key);
    }

    std::vector<KeyT> inOrder() {
        std::vector<KeyT> out;
        inOrder(root, out);
        return out;
    }

    int countInRange(KeyT lower, KeyT upper) const {
        return countInRange(root, lower, upper);
    }
};

template <typename KeyT>
void run (std::istream &inp = std::cin, std::ostream &out = std::cout) {
        
    AVLTree<KeyT> tree;
    char command = 0;
    while (inp >> command) {
        CHECK_INPUT(command)
        KeyT key, low, up;

        switch(command) {
            case 'k': 
                inp >> key;
                CHECK_INPUT(key)
                tree.insert(key);
                break;
            
            case 'q': 
                inp >> low; inp >> up;
                CHECK_INPUT(low);
                if (low <= up)
                    out << tree.countInRange(low, up) << ' ';
                else 
                    out << 0 << ' ';
                break;
            
            default:
                std::cerr << "Error input, need command: \"k\" or \"q\"\n";
                exit(-1);
                break;
        }
    }
}

#undef CHECK_INPUT