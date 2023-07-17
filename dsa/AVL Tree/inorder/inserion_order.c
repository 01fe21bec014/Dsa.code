#include <stdio.h>
#include <stdlib.h>

// Structure for a node of the AVL tree
struct Node {
    int age;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of a node
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node with the given age
struct Node* createNode(int age) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->age = age;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to perform a right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return the new root
    return x;
}

// Function to perform a left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return the new root
    return y;
}

// Function to get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a node into the AVL tree
struct Node* insertNode(struct Node* node, int age) {
    // Perform the normal BST insertion
    if (node == NULL)
        return createNode(age);

    if (age < node->age)
        node->left = insertNode(node->left, age);
    else if (age > node->age)
        node->right = insertNode(node->right, age);
    else // Duplicate ages are not allowed in this AVL tree implementation
        return node;

    // Update the height of the current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Check the balance factor and rebalance if needed
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && age < node->left->age)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && age > node->right->age)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && age > node->left->age) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && age < node->right->age) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to perform inorder traversal of the AVL tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->age);
        inorderTraversal(root->right);
    }
}

// Function to perform preorder traversal of the AVL tree
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->age);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to perform postorder traversal of the AVL tree
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->age);
    }
}

int main() {
    struct Node* root = NULL;
    int age, choice;

    do {
        printf("Enter age (or -1 to exit): ");
        scanf("%d", &age);

        if (age != -1) {
            root = insertNode(root, age);
        }
    } while (age != -1);

    printf("\nTraversal Options:\n");
    printf("1. Inorder Traversal\n");
    printf("2. Preorder Traversal\n");
    printf("3. Postorder Traversal\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Age(s) in the tree: ");
    switch (choice) {
        case 1:
            inorderTraversal(root);
            break;
        case 2:
            preorderTraversal(root);
            break;
        case 3:
            postorderTraversal(root);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    printf("\n");

    return 0;
}
