#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

node *make_node(int data);
node *insert_recursive(node *np, int dato);
void follow_in_order(node *np);
void follow_per_level(node *np, int level);
node *search(node *np, int val);
node *search_min(node *np);
node *remove_node(node *np, int val);
int tree_height(node *np);
void print_bfs_tree(node *root);

int main(void)
{
    printf("Arbol binario de busqueda.\n");
    int vals[15] = {20, 10, 30, 5, 15, 25, 40, 4, 7, 12, 18, 22, 27, 35, 45};
    node *bst = NULL;
    for(int i=0; i<15; i++)
        bst = insert_recursive(bst, vals[i]);
    print_bfs_tree(bst);
    follow_in_order(bst);
    
    int a = 26;
    printf("Buscando %d en el arbol\n", a);
    
    node *p = search(bst, a);
    if(p != NULL)
        printf("Encontramos %d!\n", a);
    else
        printf("%d no esta en el arbol\n", a);
    return 0;
}


node *make_node(int data)
{
    node *np = malloc(sizeof(node)); // falta manejar el caso en que malloc retorna NULL
    np->key = data;
    np->left = NULL;
    np->right = NULL;
    return np;    
}

node *insert_recursive(node *np, int dato)
{
    if(np == NULL) {
        return make_node(dato);
    }
    if(np->key == dato)
        return np;
    if(dato < np->key)
        np->left = insert_recursive(np->left, dato);
    else
        np->right = insert_recursive(np->right, dato);
    return np;  // es necesario?
}


void follow_in_order(node *np)
{
    if(np != NULL) {
        follow_in_order(np->left);
        printf("%d \n", np->key);
        follow_in_order(np->right);
    }
}

node *search(node *np, int val) {
    while(np != NULL) {
        if(np->key == val)
            return np;
        else {
            if(val > np->key)
                np = np->right;
            else
                np = np->left;
        }
    }
    return NULL;
}


//////////////////////////////////////////////////////////////////////////////
void print_spaces(int n) {
    for(int i = 0; i < n; i++) 
        putchar(' ');
}

int tree_height(node *np) {
    int n_left, n_right;
    if (np == NULL) 
        return 0;
    n_left = tree_height(np->left);
    n_right = tree_height(np->right);
    if(n_left > n_right)  // Retorna max(n_left,n_right)+1
        return (n_left + 1);
    else
        return (n_right + 1);       
}

void print_bfs_tree(node *root) {
    if (!root) return;

    int h = tree_height(root);
    int max_width = (1 << h) * 2;

    node **level_nodes = malloc(sizeof(node*) * (1 << h));
    int count = 1;
    level_nodes[0] = root;

    for (int level = 0; level < h; level++) {
        int nodes_in_level = 1 << level;
        int spacing = max_width / nodes_in_level;
        int branch_offset = spacing / 4;

        // Print nodes
        for (int i = 0; i < nodes_in_level; i++) {
            if (i == 0) print_spaces(spacing / 2);
            else print_spaces(spacing);

            if (level_nodes[i] != NULL) {
                printf("%2d", level_nodes[i]->key);
            } else {
                printf("  ");
            }
        }
        printf("\n");

        // Print branches
        if (level < h - 1) {
            for (int i = 0; i < nodes_in_level; i++) {
                if (i == 0) print_spaces(spacing / 2);
                else print_spaces(spacing);

                if (level_nodes[i] != NULL) {
                    printf("%c", level_nodes[i]->left ? '/' : ' ');
                    print_spaces(1);
                    printf("%c", level_nodes[i]->right ? '\\' : ' ');
                } else {
                    print_spaces(3);
                }
            }
            printf("\n");
        }

        // Prepare next level
        node **next_level = malloc(sizeof(node*) * (1 << h));
        for (int i = 0; i < nodes_in_level; i++) {
            next_level[i * 2] = (level_nodes[i] ? level_nodes[i]->left : NULL);
            next_level[i * 2 + 1] = (level_nodes[i] ? level_nodes[i]->right : NULL);
        }
        free(level_nodes);
        level_nodes = next_level;
    }
    free(level_nodes);
}