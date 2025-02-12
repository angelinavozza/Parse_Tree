/**
 * @file main.c
 * @author Angelina Vozza
 * @section 1
 * @date 2024-04-23
 * @note I completed Part 1, including the extra credit by adding the '/' and '-' operators.
 *       I completed Part 2.
 *       I completed the first task of Part 3 by converting an infix expression to postfix.
 * @assingnment 8
 */
#include"tree.h"

int main(){

  //Part 1
  char prefix[20];
  char postfix1[20];
  char infix[20];
  int index = 0;
  StackPtr sp=initStack();
  BinaryTreePtr tp=initBinaryTree();

  printf("Please enter a prefix expression with only the '+', '*', '-', '/' operators (no spaces)\n");
  scanf("%s", prefix);
  tp->root=buildBT(prefix);

  printf("\nPrefix: ");
  printBinaryTree_preorder(tp->root,0);
  printf("\nInfix: ");
  printBinaryTree_inorder(tp->root,0);
  printf("\nPostfix: ");
  printBinaryTree_postorder(tp->root,0);
  printf("\n");

  //Part 2
  pre_to_post(tp->root, &index, postfix1);
  postfix1[index] = '\0';
  printf("\nThe Value of the Expression: %d\n", evaluate(sp, postfix1));

  //Part 3
  char postfix2[20];

  printf("\nPlease enter an infix expression to be converted into postfix (no spaces)\n");
  scanf("%s", infix);
  in_to_post(sp, infix, postfix2);
  printf("\nPostfix Expression: ");
  for(int i = 0; postfix2[i]; i++){
    printf("%c", postfix2[i]);
  }
  printf("\n");

  delete_tree(tp->root, 0);
  free(sp);
  free(tp);

  return 0;
}
