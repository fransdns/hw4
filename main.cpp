//Marcia Gutiérrez Castillo
//Frans Trujillo Flores
//Frank Calef Bustamante Mauricio

#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    int height;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    TreeNode* root;

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getHeight(TreeNode* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int updateHeight(TreeNode* N) {
        if (N == nullptr)
            return 0;
        return N->height = 1 + max(getHeight(N->left), getHeight(N->right));
    }

    int getBalance(TreeNode* N) {
        if (N == nullptr)
            return 0;
        return getHeight(N->left) - getHeight(N->right);
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr)
            return new TreeNode(value);

        if (value < node->val)
            node->left = insert(node->left, value);
        else if (value > node->val)
            node->right = insert(node->right, value);
        else 
            return node;

        updateHeight(node);

        int balance = getBalance(node);

        // Rotación simple a la derecha
        if (balance > 1 && value < node->left->val)
            return rightRotate(node);

        // Rotación simple a la izquierda
        if (balance < -1 && value > node->right->val)
            return leftRotate(node);

        // Rotación izquierda derecha
        if (balance > 1 && value > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Rotación derecha izquierda
        if (balance < -1 && value < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void inOrder(TreeNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->val << " ";
            inOrder(node->right);
        }
    }

    void printInOrder() {
        inOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree tree;
    tree.insert(-10);
    tree.insert(-3);
    tree.insert(0);
    tree.insert(5);
    tree.insert(9);

    std::cout << "Inorder traversal of the constructed AVL tree is \n";
    tree.printInOrder();

    return 0;
}
