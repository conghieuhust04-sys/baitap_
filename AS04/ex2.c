#include <stdio.h>
#include <stdlib.h>

struct tnode
{
    int data;
    struct tnode* left;
    struct tnode* right;
};

/* Allocate a new tree node */
struct tnode* talloc(int data)
{
    struct tnode* p = (struct tnode*)malloc(sizeof(struct tnode));
    if (p != NULL)
    {
        p->data = data;
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

/* Add node to binary search tree (Lec06 recursive style) */
struct tnode* addnode(struct tnode* root, int data)
{
    if (root == NULL)
    {
        root = talloc(data);
        return root;
    }
    else if (data < root->data)
    {
        root->left = addnode(root->left, data);
    }
    else
    {
        root->right = addnode(root->right, data);
    }

    return root;
}

/* Pre-order traversal: root, left, right */
void preorder(struct tnode* root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

/* In-order traversal: left, root, right */
void inorder(struct tnode* root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/* Delete tree using post-order traversal */
int deltree(struct tnode* root)
{
    int count;

    if (root == NULL)
        return 0;

    count = 0;
    count += deltree(root->left);
    count += deltree(root->right);

    free(root);
    count++;

    return count;
}

/* Test code */
int main(void)
{
    struct tnode* root = NULL;
    int values[] = {3, 1, 0, 2, 8, 6, 5, 9};
    int i;
    int n = sizeof(values) / sizeof(values[0]);
    int deleted;

    for (i = 0; i < n; i++)
        root = addnode(root, values[i]);

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    deleted = deltree(root);
    root = NULL;

    printf("Deleted nodes: %d\n", deleted);

    return 0;
}
