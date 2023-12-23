//Daniel Chu 1493374
//cmput201
//lab 6
//#1 page 256
//based off of PayWithMin.c from lab2
#include<stdio.h>

void pay_amount(int,int*,int*,int*,int*);

int main(){
  //initialization/declarations
  int dollarAmt,twenties,tens,fives,ones;

  //user i/o prompts
  printf("Enter a dollar amount: ");
  scanf("%i",&dollarAmt);

  pay_amount(dollarAmt,&twenties,&tens,&fives,&ones);


  //print final bill amounts
  printf("\n$20 bills: %i\n$10 bills: %i\n$5 bills: %i\n$1 bills: %i\n",twenties,tens,fives,ones);

  return 0;
}
void pay_amount(int dollars,int *twenties, int *tens, int *fives,int *ones){
  //bill amount calculations
  int remaining = dollars;//$20 bills
  *twenties = remaining / 20;

  remaining = remaining - (*twenties * 20);//$10 bills
  *tens = remaining / 10;

  remaining = remaining - (*tens * 10);//5$ bills
  *fives = remaining / 5;

  remaining = remaining - (*fives * 5);//1$ bills
  *ones = remaining;
  return;
}
