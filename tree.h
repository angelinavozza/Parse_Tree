/**
 * @file tree.h
 * @author Angelina Vozza
 * @section 1
 * @date 2024-04-23
 * @note I completed Part 1, including the extra credit by adding the '/' and '-' operators.
 *       I completed Part 2.
 *       I completed the first task of Part 3 by converting an infix expression to postfix.
 * @assingnment 8
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define StackMax 20
typedef char DataType;

typedef struct Node{
  DataType item;
  struct Node* leftChild;
  struct Node* rightChild;
}Node, *NodePtr;

typedef struct{
  NodePtr root;
 
}BinaryTree, *BinaryTreePtr;

typedef struct{
  int top;
  int StackArray[StackMax];
}StackType, *StackPtr;

BinaryTreePtr initBinaryTree();
NodePtr buildBT(char input[]);
NodePtr newNode(DataType d);
void printBinaryTree_preorder(NodePtr np, int level);
void printNode(NodePtr np);void printBinaryTree_inorder(NodePtr, int);
void printBinaryTree_postorder(NodePtr np, int level);
StackPtr initStack();
int empty(StackPtr sp);
void push(StackPtr sp, int input);
int pop(StackPtr sp);
void pre_to_post(NodePtr np, int *index, char postfix[]);
int evaluate(StackPtr sp, char postfix[]);
void in_to_post(StackPtr sp, char infix[], char postfix[]);
int precedence(char symbol);
void delete_tree(NodePtr np, int level);
