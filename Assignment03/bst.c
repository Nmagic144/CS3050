#include "bst.h"
#include <stdio.h>

BSTNode *createNode(int key) {
  BSTNode *node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "createNode: out of memory\n");
    return NULL;
  }
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->count = 1; // Includes itself and all the ones below it
  node->min_key = key;
  node->max_key = key;

  return node;
}

static size_t countOf(const BSTNode *n) { return n ? n->count : 0; }

static void update(BSTNode *n) {
  n->count = countOf(n->left) + 1 + countOf(n->right);
  n->min_key = n->left ? n->left->min_key : n->key;
  n->max_key = n->right ? n->right->max_key : n->key;
}

BSTNode *insertBST(BSTNode *root, int key) {
  if (root == NULL) {
    return createNode(key);
  }
  if (root->key == key) {
    fprintf(stderr, "insertBST: duplicate key");
  } else if (root->key > key) { // Add to the left
    root->left = insertBST(root->left, key);
  } else {
    root->right = insertBST(root->right, key);
  }
  update(root);
  return root;
}

void freeBST(BSTNode *root) {
  if (root == NULL) {
    return;
  }
  freeBST(root->left);
  freeBST(root->right);
  free(root);
  return;
}
