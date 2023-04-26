#include <stdlib.h>
#include <stdio.h>

struct Node {
    int key;
    int max;
    struct Node *left;
    struct Node *right;
};


struct Node *createNode(int key) {
    struct Node *p = (struct Node *) malloc(sizeof(struct Node));
    p->key = key;
    p->max = key;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void displayTree(struct Node *root) {
    if (root != NULL) {
        printf("(key=%2d,max=%2d): ", root->key, root->max);
        printf("left=");
        if (root->left == NULL) {
            printf("/");
        } else {
            printf("(%2d,%2d)", root->left->key, root->left->max);
        }
        printf(", right=");
        if (root->right == NULL) {
            printf("/");
        } else {
            printf("(%2d,%2d)", root->right->key, root->right->max);
        }
        printf("\n");
        displayTree(root->left);
        displayTree(root->right);
    }
    return;
}

void deleteTree(struct Node *root) {
    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

struct Node *insertNode(struct Node *root, int newkey) {
    if (root == NULL) {
        return createNode(newkey);
    } else if (newkey < root->key) {
        root->left = insertNode(root->left, newkey);
    } else if (newkey > root->key) {
        root->right = insertNode(root->right, newkey);
    }
    if (root->left != NULL) {
        if (root->left->max > root->max) {
            root->max = root->left->max;
        }
    }

    if (root->right != NULL) {
        if (root->right->max > root->max) {
            root->max = root->right->max;
        }
    }

    return root;
}

struct Node *min(struct Node *node) {
    struct Node *current = node;

    while(current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
// This function deletes the node pointed to by the key and frees it @TODO currently does not work, make it work
struct Node *deleteNode(struct Node *root, int key) {
    if(root == NULL) {
        return root;
    }
    if(key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if(key > root->key) {
        root->right = deleteNode(root->right, key);
    } else if(key == root->key) {
        if(root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if(root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        struct Node *temp = min(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);

    }
    return root;
}


int main() {
    struct Node *root = NULL; /* Correction:  initialize root */
    root = insertNode(root, 7);
    root = insertNode(root, 2);
    root = insertNode(root, 9);
    root = insertNode(root, 0);
    root = insertNode(root, 5);
    root = insertNode(root, 8);
    root = insertNode(root, 12);
    root = insertNode(root, 4);
    root = insertNode(root, 10);
    root = insertNode(root, 13);
    root = insertNode(root, 11);
    printf("Links of the tree\n");
    displayTree(root);

    printf("\nLinks of the tree after deleting 5\n");
    root = deleteNode(root, 5);
    displayTree(root);

    printf("\nLinks of the tree after deleting 9\n");
    root = deleteNode(root, 9);
    displayTree(root);

    deleteTree(root);

    return 0;
}
