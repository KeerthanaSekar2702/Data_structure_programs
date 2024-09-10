#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

Node* mirror(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    Node* mirroredRoot = createNode(root->data);
    mirroredRoot->left = mirror(root->right);
    mirroredRoot->right = mirror(root->left);

    return mirroredRoot;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    Node* mirroredRoot = NULL;
    int choice, value;

    while (1) {
        printf("\nBinary Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Create Mirror Image\n");
        printf("3. Print Original Tree (Inorder)\n");
        printf("4. Print Mirrored Tree (Inorder)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                mirroredRoot = mirror(root);
                printf("Mirror image created.\n");
                break;
            case 3:
                printf("Original Tree (Inorder Traversal): ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Mirrored Tree (Inorder Traversal): ");
                if (mirroredRoot != NULL) {
                    inorder(mirroredRoot);
                    printf("\n");
                } else {
                    printf("No mirrored tree created yet.\n");
                }
                break;
            case 5:
                while (root != NULL) {
                    root = deleteNode(root, root->data);
                }
                while (mirroredRoot != NULL) {
                    mirroredRoot = deleteNode(mirroredRoot, mirroredRoot->data);
                }
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}

   
