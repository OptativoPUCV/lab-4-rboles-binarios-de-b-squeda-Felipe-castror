#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap * mapa = (TreeMap *)malloc(sizeof(TreeMap));
    if (mapa == NULL)return NULL;

    mapa -> root = NULL;
    mapa -> current = NULL;
    mapa ->lower_than = lower_than;

    return mapa;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree -> root == NULL)
    {
        tree -> root = NULL;
        tree -> root = createTreeNode(key , value);
        tree -> current = tree-> root;
        return;
    }

    TreeNode *current = tree -> root;
    TreeNode *padre = NULL;

    while (current != NULL)
    {
        padre = current;

        if (is_equal(tree , key , current ->pair -> key))return;


        if (tree -> lower_than(key , current -> pair -> key ))
        {
            current = current -> left;

        }
        else current = current -> right;

    }

    TreeNode * nuevo = createTreeNode(key , value);
    nuevo -> parent = padre;

    if (tree->lower_than(key , padre -> pair -> key))
    {
        padre -> left = nuevo;


    }

    else padre -> right = nuevo;

    tree -> current = nuevo;


}

TreeNode * minimum(TreeNode * x)
{
    while ( x -> left != NULL)
    {
        x = x->left;

    }

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    if (node -> left == NULL && node -> right == NULL)
{
    if (node -> parent == NULL)tree -> root = NULL;

    else
    {
        if (node -> parent -> left == node )
        {
            node -> parent -> left = NULL;
        }

        else node -> parent -> right = NULL;
    }

    free(node);

    return;


    if (node -> left == NULL || node -> right == NULL)
    {
        TreeNode *hijo;

        if (node -> left != NULL)hijo = node -> left;

        else hijo = node -> right;

        if (node -> parent == NULL)
        {
            tree -> root = hijo;
        }
        
        else
        {
            if (node -> parent -> left == node)
            {
                node -> parent -> left = node
            }
            else node -> parent -> left = node;
        }

        hijo -> parent = node -> parent;

        free(node);
        return;

    }

    if (node -> left != NULL && node-> right != NULL)
    {
        TreeNode *minimoNode = minimum(node->right);
        node->pair->key = minimoNode->pair->key;
        node->pair->value = minimoNode->pair->value;

        if (minimoNode -> parent -> left == minimoNode )
        {
            minimoNode -> parent -> left = minimoNode -> right;
            minimoNode -> right -> parent = minimoNode -> right;


        }
    }

    

}

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    if (tree -> root == NULL ) return NULL;

    TreeNode *current = tree -> root;

    while (current != NULL)
    {
        if (is_equal(tree , key , current -> pair -> key))
        {
            tree ->current = current;
            return current -> pair;
        }
        
        if (tree -> lower_than(key , current -> pair -> key))
        {
            current = current -> left;

        }
        else current = current -> right;
    }

    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
