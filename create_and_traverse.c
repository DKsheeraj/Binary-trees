#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int max(int a, int b)
{
    return (a > b) ? a:b;
}

struct node
{
    int key;
    int height;
    struct node *left;
    struct node *right;
};

struct node *newnode(int key)
{
    struct node* root = (struct node*)malloc(sizeof(struct node));
    
    root->key = key;

    root->right = NULL;

    root->left = NULL;

    return root;
}

struct node *getmin(struct node *root)
{
    while(root->left != NULL) root = root->left;

    return root;
}

int getheight(struct node *node)
{
    if(node == NULL) return -1;
    else return node->height;
} 

void preorder(struct node *root)
{
    if(root == NULL) return;

    printf("%d\n", root->key);

    preorder(root->left);

    preorder(root->right);
}
void inorder(struct node *root)
{
    if(root == NULL) return;

    inorder(root->left);

    printf("%d ", root->key);

    inorder(root->right);
}
void postorder(struct node *root)
{
    if(root == NULL) return;

    postorder(root->left);

    postorder(root->right);

    printf("%d\n", root->key);
}

struct node *leftrotate(struct node *prt)
{
    struct node *chd = prt->right;

    prt->right = chd->left;
    prt->height = 1 + max(getheight(prt->left), getheight(prt->right));

    chd->left = prt;
    chd->height = 1 + max(getheight(chd->left), getheight(chd->right));

    return chd;
}

struct node *rightrotate(struct node *prt)
{
    struct node *chd = prt->left;

    prt->left = chd->right;
    prt->height = 1 + max(getheight(prt->left), getheight(prt->right));

    chd->right = prt;
    chd->height = 1 + max(getheight(chd->left), getheight(chd->right));

    return chd;
}

struct node *retrace(struct node *node)
{
    if(node == NULL) return node;

    if(getheight(node->left) - getheight(node->right) > 1)
    {
        if(getheight(node->left->left) < getheight(node->left->right)) node->left = leftrotate(node->left);

        node = rightrotate(node);
    }

    else if(getheight(node->left) - getheight(node->right) < -1)
    {
        if(getheight(node->right->left) > getheight(node->right->right)) node->right = rightrotate(node->right);

        node = leftrotate(node);

    }

    node->height = 1 + max(getheight(node->left), getheight(node->right));

    return node;
}

struct node *insert(struct node *root, int key)
{
    if(root == NULL) return retrace(newnode(key));

    if(root->key == key) printf("KEY ALREADY EXISTS\n");

    else if(key < root->key) root->left = insert(root->left, key);

    else root->right = insert(root->right, key);

    return retrace(root);
}

struct node *search(struct node *root, int key)
{
    if(root == NULL || root->key == key) return root;

    if(root->key < key) return search(root->right, key);

    else return search(root->left, key);
}

struct node *Delete(struct node *root, int key)
{
    if(root == NULL) return NULL;

    if(key < root->key) root->left = Delete(root->left, key);

    else if(key > root->key) root->right = Delete(root->right, key);

    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        else if(root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }

        else if(root->right = NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        else
        {
            struct node *temp = getmin(root->right);
            root->key = temp->key;
            root->right = Delete(root->right, temp->key);
        }

    }
    return root;

}

void printBT(struct node *node, int level)
{
    if(node == NULL) return;

    printBT(node->left, level+1);

    printf("%d[%d]\n", node->key, level);
    printBT(node->right, level+1);
}

int main()
{
    struct node *root = newnode(5);

    root->left = newnode(4);

    root->right = newnode(6);

    root->left->left = newnode(3);


    // struct node *temp = getmin(root);

    // cout << temp->key;

    root = insert(root, 10);
    root = insert(root, 1);
    root = insert(root, 2);

    inorder(root);

    root = Delete(root, 5);

    printf("\n");

    inorder(root);

    return 0;
}
