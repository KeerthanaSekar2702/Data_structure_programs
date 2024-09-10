#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

QueueNode* createQueueNode(Node* treeNode) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    newQueueNode->treeNode = treeNode;
    newQueueNode->next = NULL;
    return newQueueNode;
}

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, Node* treeNode) {
    QueueNode* newQueueNode = createQueueNode(treeNode);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newQueueNode;
        return;
    }
    queue->rear->next = newQueueNode;
    queue->rear = newQueueNode;
}

Node* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    QueueNode* temp = queue->front;
    Node* treeNode = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return treeNode;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

void levelOrderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        Node* current = dequeue(queue);
        printf("%d ", current->data);

        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }

    printf("\n");
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
        printf("5. Print Original Tree (Level Order)\n");
        printf("6. Print Mirrored Tree (Level Order)\n");
        printf("7. Exit\n");
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
                printf("Original Tree (Level Order Traversal): ");
                levelOrderTraversal(root);
                break;
            case 6:
                printf("Mirrored Tree (Level Order Traversal): ");
                if (mirroredRoot != NULL) {
                    levelOrderTraversal(mirroredRoot);
                } else {
                    printf("No mirrored tree created yet.\n");
                }
                break;
            case 7:
                while (root != NULL) {
                    root = deleteNode(root, root->data);
                }
                while (mirroredRoot != NULL) {
                    mirroredRoot = deleteNode(mirroredRoot, mirroredRoot->data);
                }
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 7.\n");
        }
    }

    return 0;
}
