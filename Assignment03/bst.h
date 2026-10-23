#ifndef BST_H
#define BST_H

#include <stdlib.h>

typedef struct BST {
  int key;
  struct BST *left;
  struct BST *right;
  size_t count;
  int min_key;
  int max_key;
} BSTNode;

// Construction and Destruction
BSTNode *createNode(int key);
void freeBST(BSTNode *root);

// Basic Operations
BSTNode *insertBST(BSTNode *root, int key); /* returns new root */
BSTNode *deleteBST(BSTNode *root, int key); /* returns new root */
BSTNode *searchBST(const BSTNode *root, int key);

// Questions
int getHeight(const BSTNode *root);
size_t getSize(const BSTNode *root);
int getMin(const BSTNode *root);
int getMax(const BSTNode *root);

size_t BSTRange(BSTNode *root, int low, int high);
// Utilities
void FYShuffle(int *array, int length); /* Fisher-Yates, in place */
BSTNode *buildBSTFromArray(const int *array, int length);

#endif
