#include <iostream>

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

    // Обновить высоту узла
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

    // Рекурсивная вставка
    Node* insert(Node* node, KeyT key) {
        // Выполнить стандартную вставку
        if (!node) return new Node(key);

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node; // Дубликаты не допускаются
        }

        // Обновить высоту узла
        updateHeight(node);

        // Проверка баланса
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

        return node; // Возвращаем (неизмененный) указатель
    }

    // Рекурсивный вывод дерева (инфиксный)
    void inOrder(Node* node) {
        if (node) {
            inOrder(node->left);
            std::cout << node->key << " ";
            inOrder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(KeyT key) {
        root = insert(root, key);
    }

    // Инфиксный вывод дерева
    void inOrder() {
        inOrder(root);
        std::cout << std::endl;
    }
};