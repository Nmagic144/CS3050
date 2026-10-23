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

size_t BSTRange(BSTNode *root, int low, int high) {
  if (low > high) {
    return 0;
  }
  if (root == NULL) {
    return 0;
  }
  if (root->min_key > high || root->max_key < low) { // FULLY OUT
    return 0;
  }
  if (root->min_key >= low && root->max_key <= high) { // FULLY IN
    return root->count;
  }
  // Here means we are partly within the range
  if (root->key >= low && root->key <= high) {
    return 1 + BSTRange(root->left, low, high) +
           BSTRange(root->right, low, high);
  } else {
    return BSTRange(root->left, low, high) + BSTRange(root->right, low, high);
  }
}

size_t getHeight(const BSTNode *root) {
  if (root == NULL) {
    return 0;
  }
  size_t left = getHeight(root->left);
  size_t right = getHeight(root->right);
  return 1 + (left > right ? left : right);
}
