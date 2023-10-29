#include "Recursion.h"
#include "story.h"
#include <stdio.h>
#include <stdlib.h>

int testIntro() {
  int calls1 = 0, calls2 = 0;
  int shelf1[] = {1, 4, 0, 5, 6, 17, 12, 9, 15};
  int shelf2[] = {31, 4, 39, 58, 19, 47, 63, 91, 45, 1, 22};
  int magic1 = sumNums1(shelf1, 9, &calls1);
  int magic2 = sumNums2(shelf2, 11, &calls2);

  printf("The first magic number is: %d (calls: %d)\n", magic1, calls1);
  printf("The second magic number is: %d (calls: %d)\n\n", magic2, calls2);

  if (magic1 == 69 && magic2 == 420) { //
    if (calls1 == 10 && calls2 == 21) { // Change calls1 == 17 -> 10
      return 0;
    } else {
      return 2;
    }
  } else {
    return 1;
  }
}

bool testReverse() {
  int dummy = 0;
  bool testReverse = 1;
  testReverse &= (reverse(17, 2, &dummy) == 71);
  testReverse &= (reverse(12345, 5, &dummy) == 54321);
  testReverse &= (reverse(3141, 4, &dummy) == 1413);
  testReverse &= (reverse(565656, 6, &dummy) == 656565);
  testReverse &= (reverse(101, 3, &dummy) == 101);
  testReverse &= (reverse(987654321, 9, &dummy) == 123456789);
  return testReverse;
}

bool testRemove() {
  int dummy = 0;
  int testRemove = 1;
  Node *head = (Node *)malloc(sizeof(Node));
  head->data = 'P';
  head->next = NULL;
  Node *curr = head;
  for (int i = 1; i < 11; i++) {
    Node *next = (Node *)malloc(sizeof(Node));
    next->data = (char)(i + 'P');
    next->next = NULL;
    curr->next = next;
    curr = next;
  }
  head = remove_nodes(head, 'X', &dummy);
  int list_length = 0;
  curr = head;
  while (curr != NULL) {
    list_length++;
    testRemove &= (curr->data != 'X');
    curr = curr->next;
  }
  testRemove &= (list_length == 10);
  for (int i = 0; i < 8; i++) {
    head = remove_nodes(head, (char)(i + 'P'), &dummy);
  }
  list_length = 0;
  curr = head;
  while (curr != NULL) {
    list_length++;
    curr = curr->next;
  }
  testRemove &= (list_length == 2);
  head = remove_nodes(head, 'Y', &dummy);
  head = remove_nodes(head, 'Z', &dummy);
  head = remove_nodes(head, 'Z', &dummy);
  testRemove &= (head == NULL);
  return testRemove;
}

bool testWeight() {
  int dummy = 0;
  int weights[] = {1, 5, 7, 9, 10, 11, 4, 3};
  bool testWeight = 1;
  testWeight &= (knapsack(weights, 8, 2, &dummy) == 1);
  testWeight &= (knapsack(weights, 8, 16, &dummy) == 16);
  testWeight &= (knapsack(weights, 8, 50, &dummy) == 50);
  testWeight &= (knapsack(weights, 8, 0, &dummy) == 0);
  testWeight &= (knapsack(weights, 8, 1000, &dummy) == 50);
  return testWeight;
}

bool testTree() {
  int calls = 0;
  BinaryNode a = {5, NULL, NULL};

  BinaryNode b = {10, NULL, NULL};
  BinaryNode c = {2, NULL, NULL};
  a.left = &b;
  a.right = &c;

  BinaryNode d = {500, NULL, NULL};
  BinaryNode e = {15, NULL, NULL};
  b.left = &d;
  b.right = &e;

  BinaryNode f = {1, NULL, NULL};
  BinaryNode g = {20, NULL, NULL};
  c.left = &f;
  c.right = &g;

  BinaryNode h = {14, NULL, NULL};
  e.left = &h;

  BinaryNode i = {11, NULL, NULL};
  g.left = &i;

  BinaryNode j = {3, NULL, NULL};
  i.left = &j;

  int test = least_weight_path(&a, &calls);
  return test == 8;
}

int main(void) {
  PrintIntro();
  PrintTutorial();

  int intro = testIntro();
  if (intro == 0) {
    PrintTutorialSumSuccess();
  } else if (intro == 1) {
    PrintTutorialSumFailValue();
    return 0;
  } else {
    PrintTutorialSumFailCount();
    return 0;
  }

  PrintChapterOne();
  int reverse = testReverse();
  if (!reverse) {
    PrintReverseFail();
    return 0;
  } else {
    PrintReverseSuccess();
  }

  PrintChapterTwo();
  int remove = testRemove();
  if (!remove) {
    PrintRemoveFail();
    return 0;
  } else {
    PrintRemoveSuccess();
  }

  PrintChapterThree();
  int weight = testWeight();
  if (!weight) {
    PrintWeightFail();
    return 0;
  } else {
    PrintWeightSuccess();
  }

  PrintChapterFour();
  int tree = testTree();
  if (!tree) {
    PrintTreeFail();
    return 0;
  } else {
    PrintTreeSuccess();
  }

  PrintConclusion();

  return 0;
}

int main_test(void){
    int x[] = {1, 2, 3, 4, 5};
    int calls = 0;

    int result = sumNums1(x, 4, &calls); // Calculate the sum of the first 5 elements (0-based index)

    printf("Sum: %d\n", result);
    printf("Number of recursive calls: %d\n", calls);

    return 0;
}

int findLengthOfInteger(int num) {
    int length = 0;

    // Handle the case of a negative number
    if (num < 0) {
        num = abs(num); // Convert the negative number to a positive number
        length++; // Account for the negative sign
    }

    // Handle the case of a number with value 0
    if (num == 0) {
        return 1; // A single digit, which is 0
    }

    while (num > 0) {
        num /= 10;
        length++;
    }

    return length;
}

int main_test1(void){

    int x = 173216;
    int calls = 0;
    int x_length = findLengthOfInteger(x);

    int result = reverse(x, x_length, &calls); // Calculate the sum of the first 5 elements (0-based index)

    printf("The reverse int: %d", result);

    return 0;
}

int main_3(void){
    int x[] = {1, 6 ,8, 3};
    int n = 4;
    int max = 20;
    int calls = 0;

    int max_total_weight = knapsack(x, n, max, &calls);

    printf("Maximum total weight: %d\n", max_total_weight);
    printf("Number of recursive calls: %d\n", calls);

    return 0;

}

// Main to test Tic-tac-toe Problem
bool RecordSame(Record a, int x, int d, int o){
    if ((a.x_wins == x)&&(a.draws==d) &&(a.o_wins==o)) {
        return true;
    }
    else {
        return false;
    }
}

void DUCKINTESTTOE(){
    int calls = 0;
    Record outcome;

    char board1[3][3]= {
            {'X','O','X'},
            {'O',' ',' '},
            {'O','X',' '}
    };
    outcome = tic_tac_toe(board1, true, &calls);

//    printf("X_win Outcome: %d\n", outcome.x_wins);
//    printf("O_win Outcome: %d\n", outcome.o_wins);
//    printf("Draw Outcome: %d\n", outcome.draws);

    if (!RecordSame(outcome, 1,0,0)){
        printf("Test 1 failed\n");
        fflush(stdout);
    }else{
        printf("Test 1 SUCCESS\n");
        fflush(stdout);
    }

    char board2[3][3]= {
            {'X','O','X'},
            {'O','X','O'},
            {'O','X',' '}
    };
    outcome = tic_tac_toe(board2, false, &calls);
    if (!RecordSame(outcome, 0,1,0)){
        printf("Test 2 failed\n");
        fflush(stdout);
    }else{
        printf("Test 2 SUCCESS\n");
        fflush(stdout);
    }

    char board3[3][3]= {//change number
            {' ','O','X'},
            {'O','X','O'},
            {'O','X','O'}
    };
    outcome = tic_tac_toe(board3, true, &calls);//change number
    if (!RecordSame(outcome, 0,1,0)){
        printf("Test 3 failed\n");//change number
        fflush(stdout);
    }else{
        printf("Test 3 SUCCESS\n");//change number
        fflush(stdout);
    }

    char board4[3][3]= {//change number
            {' ','O','X'},
            {'O','X','O'},
            {'O','X','O'}
    };
    outcome = tic_tac_toe(board4, false, &calls);//change number
    if (!RecordSame(outcome, 0,0,1)){
        printf("Test 4 failed\n");//change number
        fflush(stdout);
    }else{
        printf("Test 4 SUCCESS\n");//change number
        fflush(stdout);
    }

    char board5[3][3]= {//change number
            {'X','O','X'},
            {'X','O','X'},
            {'O',' ',' '}
    };
    outcome = tic_tac_toe(board5, true, &calls);//change number
    if (!RecordSame(outcome, 1,1,0)){
        printf("Test 5 failed\n");//change number
        fflush(stdout);
    }else{
        printf("Test 5 SUCCESS\n");//change number
        fflush(stdout);
    }

    char board6[3][3]= {//change number
            {'O','O','X'},
            {'X','O','X'},
            {'O',' ',' '}
    };
    outcome = tic_tac_toe(board6, true, &calls);//change number
    if (!RecordSame(outcome, 1,0,1)){
        printf("Test 6 failed\n");//change number
        fflush(stdout);
    }else{
        printf("Test 6 SUCCESS\n");//change number
        fflush(stdout);
    }

    char board7[3][3]= {//change number
            {'X','O','X'},
            {'O','X','O'},
            {' ',' ',' '}
    };
    outcome = tic_tac_toe(board7, true, &calls);//change number
    if (!RecordSame(outcome, 4,0,0)){
        printf("Test 7 failed\n");//change number
        fflush(stdout);
    }else{
        printf("Test 7 SUCCESS\n");//change number
        fflush(stdout);
    }
    char board8[3][3]= {//change number
            {'X','O','X'},
            {'O','X','O'},
            {' ',' ',' '}
    };
    outcome = tic_tac_toe(board8, false, &calls);//change number
    if (!RecordSame(outcome, 4,2,0)){
        printf("Test 8 failed\n");//change number
        fflush(stdout);
    }else{
        printf("Test 8 SUCCESS\n");//change number
        fflush(stdout);
    }

    char board666[3][3]= {//change number
            {' ',' ',' '},
            {' ',' ',' '},
            {' ',' ',' '}
    };
    outcome = tic_tac_toe(board666, true, &calls);//change number
    if (!RecordSame(outcome, 131184,46080,77904)){
        printf("Test 666 failed\n");//change number
        fflush(stdout);
    }else{
        printf("Test 666 SUCCESS\n");//change number
        fflush(stdout);
    }
}

int main_TicTacToe(void){
    DUCKINTESTTOE();
}