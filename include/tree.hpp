#include <iostream>
#include <istream>
#include <sstream>

template <typename KeyT>
class AVLTree {
private:
    struct Node {
        KeyT key;
        Node* left;
        Node* right;
        int height;

        Node(KeyT value) : key(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x; 
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

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

        updateHeight(node);

        int balanceFactor = balance(node);

        // Левый левый случай
        if (balanceFactor > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        // Правый правый случай
        if (balanceFactor < -1 && key > node->right->key) {
            return leftRotate(node);
        }

        // Левый правый случай
        if (balanceFactor > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Правый левый случай
        if (balanceFactor < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(Node* node, std::ostream &out = std::cout) {
        if (node) {
            inOrder(node->left, out);
            out << node->key << " ";
            inOrder(node->right, out);
        }
    }

    int countInRange(Node* node, KeyT lower, KeyT upper) const {
        if (!node) return 0;

        // Если текущий узел находится в диапазоне, увеличиваем счетчик
        if (node->key >= lower && node->key <= upper) {
            return 1 + countInRange(node->left, lower, upper) + countInRange(node->right, lower, upper);
        }

        // Если текущий узел меньше нижней границы, ищем только в правом поддереве
        else if (node->key < lower) {
            return countInRange(node->right, lower, upper);
        }

        // Если текущий узел больше верхней границы, ищем только в левом поддереве
        else {
            return countInRange(node->left, lower, upper);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(KeyT key) {
        root = insert(root, key);
    }

    void inOrder(std::ostream &out = std::cout) {
        inOrder(root, out);
    }

    int countInRange(KeyT lower, KeyT upper) const {
        return countInRange(root, lower, upper);
    }

    void run (std::istream &inp = std::cin, std::ostream &out = std::cout) {
        
        char command = 0;
        while (inp >> command) {
            switch(command) {
                case 'k': {
                    KeyT key;
                    inp >> key;
                    insert(key);
                    break;
                }
                case 'q': {
                    KeyT low, up;
                    inp >> low; inp >> up;
                    out << countInRange(low, up) << ' ';
                    break;
                }
            }
        }
    }
};