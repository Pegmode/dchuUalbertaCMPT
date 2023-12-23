//Daniel chu
//1493374
//Lab 3 CMPUT201
//Q1 page 71

#include<stdio.h>

int main(){

  //initalize variables
  int num,num1st,num2nd;//number, first int, 2nd int


  //User I/O
  printf("Enter a two-digit number: ");
  scanf("%i",&num);
  //split integer
  num1st = num/10;
  num2nd = num%10;
  //Display reversed halves
  printf("The Reversal is: %i%i\n",num2nd,num1st);

  return 0;
}
