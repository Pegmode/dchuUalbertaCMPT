//Daniel Chu
//1493374
//CMPUT 201
//Lab2
//Program that shows hot to pay an ammount in USD using the smallest number of $20,$10,$5 and $1 bills

#include<stdio.h>
int main(){
  //initialization/declarations
  int dollarAmt,twenties,tens,fives,ones,remaining;

  //user i/o prompts
  printf("Enter a dollar amount: ");
  scanf("%i",&dollarAmt);


  //bill amount calculations
  remaining = dollarAmt;//$20 bills
  twenties = remaining / 20;

  remaining = remaining - (twenties * 20);//$10 bills
  tens = remaining / 10;

  remaining = remaining - (tens * 10);//5$ bills
  fives = remaining / 5;

  remaining = remaining - (fives * 5);//1$ bills
  ones = remaining;

  //print final bill amounts
  printf("\n$20 bills: %i\n$10 bills: %i\n$5 bills: %i\n$1 bills: %i\n",twenties,tens,fives,ones);

  return 0;
}
