#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;

typedef struct StackNode {
    Node *treeNode;
    struct StackNode *next;
} StackNode;

void push(StackNode **stack, Node *treeNode) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->treeNode = treeNode;
    newNode->next = *stack;
    *stack = newNode;
}

Node *pop(StackNode **stack) {
    if (*stack == NULL) return NULL;
    StackNode *temp = *stack;
    Node *treeNode = temp->treeNode;
    *stack = temp->next;
    free(temp);
    return treeNode;
}
Node *createNode(char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *buildExpressionTree(const char *postfix) {
    StackNode *stack = NULL;
    Node *node, *left, *right;

    for (int i = 0; postfix[i]; ++i) {
        if (isalnum(postfix[i])) {
            node = createNode(postfix[i]);
            push(&stack, node);
        } else {
            node = createNode(postfix[i]);
            right = pop(&stack);
            left = pop(&stack);
            node->left = left;
            node->right = right;
            push(&stack, node);
        }
    }

    return pop(&stack);
}

int evaluate(Node *root) {
    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL) {
        return root->data - '0'; 
    }

    int leftEval = evaluate(root->left);
    int rightEval = evaluate(root->right);

    switch (root->data) {
        case '+': return leftEval + rightEval;
        case '-': return leftEval - rightEval;
        case '*': return leftEval * rightEval;
        case '/': return leftEval / rightEval;
    }

    return 0;
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    const char *postfix = "53+82-*";
    Node *root = buildExpressionTree(postfix);

    printf("Postfix Expression: %s\n", postfix);
    printf("Evaluated Result: %d\n", evaluate(root));

    freeTree(root);
    return 0;
}
