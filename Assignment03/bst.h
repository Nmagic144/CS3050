#ifndef BST_H
#define BST_H

#include <stddef.h>

typedef struct BST {
  int key;
  struct BST *left;
  struct BST *right;
  int count;
  int size;
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
int getSize(const BSTNode *root);
int getMin(const BSTNode *root);
int getMax(const BSTNode *root);

int BSTLE(const BSTNode *root, int key);
int BSTGE(const BSTNode *root, int key);

// Utilities
void FYShuffle(int *array, int length); /* Fisher-Yates, in place */
BSTNode *buildBSTFromArray(const int *array, int length);

#endif
