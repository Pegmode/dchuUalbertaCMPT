//Daniel Chu 1493374
//cmput201
//lab 6
//#3 page 256
//based off of q3.c from lab 4

#include <stdio.h>


void reduce(int,int,int*,int*);


int main(){
  int num1,num2,numerator,denominator;

  printf("Enter a fraction: ");
  scanf("%i%*c%i",&num1,&num2);//skip character

  reduce(num1,num2,&numerator,&denominator);
  printf("In lowest terms: %i/%i\n",numerator,denominator);

  return 0;
}


//Euclids algorithm
//num1 = m, num2 = n
void reduce(int num1, int num2,int *numerator,int *denominator){//calculates GCD of 2 ints and returns GCD
  int origNum1 = num1,origNum2 = num2;
  int swapBuffer;//temp value for storing num2
  for(;;){//infinite loop till return val
    if(num2  == 0){
      *numerator = origNum1 / num1;
      *denominator = origNum2 / num1;
      return;
    }
    swapBuffer = num2;//we will overwrite num2 so we need to temporarily save its value
    num2 = num1 % num2;//store remainder of num1/num2 in num2
    num1 = swapBuffer;//store num2(buffer) in num1
  }
}
