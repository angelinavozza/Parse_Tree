/**
 * @file tree.c
 * @author Angelina Vozza
 * @section 1
 * @date 2024-04-23
 * @note I completed Part 1, including the extra credit by adding the '/' and '-' operators.
 *       I completed Part 2.
 *       I completed the first task of Part 3 by converting an infix expression to postfix.
 * @assingnment 8
 */
#include"tree.h"

/**
 * @brief initializes a tree 
 * 
 * @return BinaryTreePtr 
 */
BinaryTreePtr initBinaryTree(){
  BinaryTreePtr tp=(BinaryTreePtr)malloc(sizeof(BinaryTree));
  tp->root=NULL;
  return tp;
}

/**
 * @brief Creates nodes for each operand and operator and places them in the tree
 * 
 * @param input 
 * @return NodePtr 
 */
NodePtr buildBT(char input[]){
  static int i=0;
  if(input[i]!='\0')
    {
      char t=input[i++];
      NodePtr np=newNode(t);
      if(t=='+' || t=='*' || t=='-' || t=='/')
	    {
	      np->leftChild=buildBT(input);
	      np->rightChild=buildBT(input);
	    }
      return np;
      
    }
    return NULL;
}

/**
 * @brief creates a new node
 * 
 * @param d 
 * @return NodePtr 
 */
NodePtr newNode(DataType d){
  NodePtr np=(NodePtr)malloc(sizeof(Node));
  np->item=d;
  np->leftChild=NULL;
  np->rightChild=NULL;
  return np;
}

/**
 * @brief prints the tree in preorder
 * 
 * @param np 
 * @param level 
 */
void printBinaryTree_preorder(NodePtr np, int level){
  
  if(np==NULL)return;
  printNode(np);
  printBinaryTree_preorder(np->leftChild, level + 1);
  printBinaryTree_preorder(np->rightChild, level + 1);

}

/**
 * @brief prints the tree in inorder
 * 
 * @param np 
 * @param level 
 */
void printBinaryTree_inorder(NodePtr np,int  level){
  
  if(np==NULL)return;
  
  printBinaryTree_inorder(np->leftChild, level+1);
  printNode(np);
  printBinaryTree_inorder(np->rightChild,level+1);

} 

/**
 * @brief prints the tree in postorder
 * 
 * @param np 
 * @param level 
 */
void printBinaryTree_postorder(NodePtr np, int level){
  
  if(np==NULL) return;
  printBinaryTree_postorder(np->leftChild, level+1);
  printBinaryTree_postorder(np->rightChild,level+1);
  printNode(np);

}

/**
 * @brief prints the item in a node
 * 
 * @param np 
 */
void printNode(NodePtr np)
{
  printf("%c ", np->item);
}

/**
 * @brief initializes a stack
 * 
 * @return StackPtr 
 */
StackPtr initStack() {
           StackPtr sp = (StackPtr) malloc(sizeof(StackType));
           sp -> top = -1;
           return sp;
}

/**
 * @brief checks if the stack is empty
 * 
 * @param sp 
 * @return int 
 */
int empty(StackPtr sp) {
           return (sp -> top ==-1);
}

/**
 * @brief pushes a value onto the top of the stack
 * 
 * @param sp 
 * @param input 
 */
void push(StackPtr sp, int input) {
  (sp->top)++;
  if(sp->top<StackMax)
    sp->StackArray[sp->top]=input;
  else
    printf("stack overflow!\n");
}

/**
 * @brief pops the value from the top of the stack off of the stack
 * 
 * @param sp 
 * @return int 
 */
int pop(StackPtr sp) {
           if (empty(sp)) return -1;
           int output = sp ->StackArray[sp->top];
	   --(sp->top);
           return output;
}

/**
 * @brief converts a prefix expression to postfix
 * 
 * @param np 
 * @param index 
 * @param postfix 
 */
void pre_to_post(NodePtr np, int *index, char postfix[]){
  if(np==NULL) return;
  pre_to_post(np->leftChild, index, postfix);
  pre_to_post(np->rightChild,index, postfix);
  postfix[*index] = np->item;
  (*index)++;
}

/**
 * @brief evaluates the expression in the parse tree
 * 
 * @param sp 
 * @param postfix 
 * @return int 
 */
int evaluate(StackPtr sp, char postfix[]){
  int i, a, b;
  for(i = 0; i < strlen(postfix); i++){
    if((postfix[i] >= '0') && (postfix[i] <= '9')){
      push(sp, (postfix[i] - '0'));
    } else {
      if (sp->top <= -1){
        printf("Error: not enough operands.\n");
        return 0; 
      }
      a = pop(sp);
      b = pop(sp);
      switch(postfix[i]){
        case '*':
          push(sp, (b*a));
          break;
        case '+':
          push(sp, (b+a));
          break;
        case '-':
          push(sp, (b-a));
          break;
        case '/':
          push(sp, (b/a));
          break;
      }
    }
  }
  return pop(sp);
}

/**
 * @brief converts an infix expression to postfix
 * 
 * @param sp 
 * @param infix 
 * @param postfix 
 */
void in_to_post(StackPtr sp, char infix[], char postfix[]){
  int i, j=0;
  char symbol, next;
  for(i = 0; i < strlen(infix); i++){
    symbol = infix[i];
    switch(symbol){
      case '(':
        push(sp, symbol);
        break;
      case ')':
        while((next = pop(sp)) != '('){
          postfix[j++] = next;
        }
          break;
      case '+':
      case '-':
      case '*':
      case '/':
        while(!empty(sp) && precedence(sp->StackArray[sp->top]) >= precedence(symbol)){
          postfix[j++] = pop(sp);
        }
        push(sp, symbol);
        break;
      default:
        postfix[j++] = symbol;
    }
  }
  while(!empty(sp)){
    postfix[j++] = pop(sp);
  }
  postfix[j] = '\0';
}

/**
 * @brief assigns precedence to operators
 * 
 * @param symbol 
 * @return int 
 */
int precedence(char symbol){
  switch(symbol){
    case '*':
    case '/':
      return 3;
    case '+':
    case '-':
      return 2;
    default:
      return 0;
  }
}

/**
 * @brief frees all memory allocated for the nodes on the tree
 * 
 * @param np 
 * @param level 
 */
void delete_tree(NodePtr np, int level){
  
  if(np==NULL) return;
  delete_tree(np->leftChild, level+1);
  delete_tree(np->rightChild,level+1);
  free(np);

}