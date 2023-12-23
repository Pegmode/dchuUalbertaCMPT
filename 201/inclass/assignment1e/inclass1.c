//In class example day 4: Dynamic programming LCS(simple 1D array)
//
//create a sequence of coin values (1,5,10). Assuming we can
//only pick staggered sequences eg: +-+- or -+-= choose the
//sequence of taking and ignoring coins for which we will have
//the most money. Explanation in hand written notes.
//
//
//for now assume 10 coins (we don't know arbitrary assignment length yet)
//
#include<stdio>
int main(){

int coing[10]; // integer array of length 10

  printf("Enter a sequence of 10 coins: \n");

  //GENERATE COINS
  for (int = 0;i < 10;i++){
    if (scanf("%d", &coin[i]) != 1){// stores values in array. separated by spaces. If we enter more than 10 values, scnf will ignore them
      return -1; //terminate with error -1 (use negative calues to denote error. Use the value to trace to error)

    }
  }

  //SETUP
  int picked[10], notpicked[10];//Note that in one statement you can declare multiple things
  picked[0] = coin[0];
  notpicked[0] = 0;

  //alg pick coins
  for (int i = 1; i< 10; i++){
    picked[i] = notpicked[i-1] + coin[i];
    notpicked[i] = picked[i-1] > notpicked[i-1] ? //? = check equality if true do
      picked[i-1] : notpicked[i-1];
    }
  printf("The max gain is %d\n",picked[9] > notpicked[9] ?
    picked[9] : notpicked[9];);
  return 0;
}
