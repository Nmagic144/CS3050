#include "bst.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    BSTNode *node = createNode(key);
    if (node == NULL) {
      fprintf(stderr, "insertBST: createNode failed\n");
      return NULL;
    }
    return node;
  }
  if (root->key == key) {
    fprintf(stderr, "insertBST: duplicate key\n");
    return root;
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

// Splitmix64 was reccomended by a friend when I was rambling
// https://rosettacode.org/wiki/Pseudo-random_numbers/Splitmix64
// Was accessed to better understand and implement this task
uint64_t rng_next(rng_t *state) {
  uint64_t z = (*state += 0x9E3779B97F4A7C15ULL);
  z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
  z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
  return z ^ (z >> 31);
}

uint64_t random_below(rng_t *state, uint64_t m) {
  uint64_t threshold = (0 - m) % m;
  uint64_t r;
  do {
    r = rng_next(state);
  } while (r < threshold);
  return r % m;
}

/* Fisher-Yates shuffle */
void FYShuffle(int *a, size_t n, rng_t *state) {
  for (size_t i = n; i > 1; i--) {
    size_t j = random_below(state, i);
    int tmp = a[i - 1];
    a[i - 1] = a[j];
    a[j] = tmp;
  }
}
