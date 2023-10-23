#include "Recursion.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Return the sum of the elements in array x[]
 * there are n elements in x[] (x[0] ... x[n-1])
 * solve the problem recursively and
 * use an "n-1" type of decomposition
 *
 * NOTE: This function will NOT be graded and is merely provided for practice.
 */
int sumNums1(int x[], int n, int *calls) {
  *calls += 1;
  // TODO: Your code here
  if(n <= 0) // base case
      return 0;
  else{
      return(x[n] + sumNums1(x, n-1, calls)); // Recursive case
  }
}

/*
 * Return the sum of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * n may be either odd or even
 * solve the problem recursively and
 * use an "n/2" type of decomposition
 *
 * NOTE: This function will NOT be graded and is merely provided for practice.
 */
int sumNums2(int x[], int n, int *calls) {
  *calls += 1;
  // TODO: Your code here
    if(n <= 0) // base case
        return 0;
    else{
        return(sumNums1(x, n/2, calls)); // Recursive case
    }
}

/*
 * Write a recursive function that reverse a positive n-digit integer x.
 * For example, if x = 12345, the function should return 54321.
 * Hint: use pow() from math.h
 */
int reverse(int x, int n, int *calls) {
  *calls += 1;
  // TODO: Your code here

  if(n <= 0){
      return 0; // Based case
  }else{
      int mask = pow(10, n-1);
      int temp1 = x/mask; // Get the 1st index of the int
      int temp2 = reverse(x % mask, n-1, calls);

      // Build it back up
      int result = temp2*10 + temp1;
      return(result);
  }
}

/*
 * Given a linked list, remove all nodes that contain the character val
 * Don't forget to free memory for any nodes you remove
*/
Node* remove_nodes(Node* head, char val, int* calls) {
  *calls += 1;
  // TODO: Your code here

  // Base case:
    if(head == NULL){
      return nullptr;
    }

  // Recurse Two case: if the node == val and node != val
  if(head->data == val){
      Node* next_node = head->next; // Keep next_node before delete
      free(head);
      return(remove_nodes(next_node, val, calls));
  }
  else{ // head-> data != val
      head->next = remove_nodes(head->next, val, calls);
      return head;
  }
}

/* You are given a list of item weights that represent the weight of the ith
 * index item You are also given a maximum weight that your bag can hold.
 * Return the total weight of the subset of items that maximize the total weight
 * of the bag without going over the maximum weight
 */
int knapsack(int weights[], int n, int max_weight, int *calls) {
  *calls += 1;
  // TODO: Your code here
  // Mistake I made:
    /*
     * Compare wrong items
     * Be careful on what am I comparing
     */

    if(n == 0){ // Base case
        return 0;
    }
    // If current item's weight[n-1] >= weight -> skip it
    if(weights[n-1] > max_weight){
        int case2 = knapsack(weights, n-1, max_weight, calls);
        return case2;
    }

    int case1 = knapsack(weights, n-1, max_weight - weights[n-1], calls); // Case1: Choose weights[n-1]
    int case2 = knapsack(weights, n-1, max_weight, calls); // Case2: Not choose weights [n-1]

    // printf("%d| %d, %d\n", n, case1, case2);
    if(case1 + weights[n-1] >= case2){
        return case1 + weights[n-1];
    }
//    else if(case1 + weights[n-1] < case2){
//        return case2;
//    } No need, because I covered all cases
    else{
        return case2;
    }
}

// Given a binary tree, return the weight of the least weight path (the path with the smallest sum of node values)
int least_weight_path(BinaryNode *root, int *calls) {
  *calls += 1;
  // TODO: Your code here

  // 4 cases total: 1. NO node existed, 2. only left, 3. only right, 4. both node
  // 1. No node = Base case:
    if(root->left == nullptr && root->right == nullptr){ // both left & right node = nullptr
        return root->data;
    }
    // Recursive case:
    // 2. Only left
    else if(root->left != nullptr && root->right == nullptr){
        int went_left = (root->data + least_weight_path(root->left, calls));
        return(went_left);
    }
    // 3. Only right
    else if(root->left == nullptr && root->right != nullptr){
        int went_right = (root->data + least_weight_path(root->right, calls));
        return(went_right);
    }
    // 4. Both node
    int go_left = (root->data + least_weight_path(root->left, calls));
    int go_right = (root->data + least_weight_path(root->right, calls));

    if(go_left <= go_right){
      return(go_left);
    }
    else{
      return(go_right);
    }
}

bool is_win(char board[3][3], char player) {
  // (Optional but recommended) TODO: Your code here
  return false;
}

/*
 * Given a tic-tac-toe board, return a Record struct that contains the number of
 * ways that X can win, the number of ways that O can win, and the number of
 * draws from the current board position.
 * The possible values of the board are 'X', 'O', and ' ' (space character for empty)
 */
Record tic_tac_toe(char board[3][3], bool is_x_turn, int *calls) {
  *calls += 1;
  // TODO: Your code here
  return {0, 0, 0};
}
