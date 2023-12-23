//Daniel Chu
//1493374
//CMPUT 201
//Lab2
//Program that calculates the remaining balance on a loan after the first, 2nd and third monthly payments:

#include<stdio.h>

int main(){

  //declarations
  float interestRate,monthlyPayment; //working
  float balance[4];//array containing balance for month, index 0 is initial ballance aka loan amount, month = i

  //user io
  printf("Enter amount of loan: ");
  scanf("%f",&balance[0]);
  printf("Enter interest rate: ");
  scanf("%f",&interestRate);
  printf("Enter monthly payment: ");
  scanf("%f",&monthlyPayment);

  //calculate first 3 balances after payment
  for(int i = 1 ; i <= 3 ; i++){ // balance[0] is inital balance therefore start at i =1
    balance[i] = balance[i-1] - monthlyPayment + (balance[i-1] * (interestRate/1200));
  }

  //Display first 3 month balances
  printf("\n\nBalance remaining after first payment : $%.2f",balance[1]);
  printf("\nBalance remaining after second payment : $%.2f",balance[2]);
  printf("\nBalance remaining after third payment : $%.2f\n",balance[3]);

//debug
  //printf("\n\nDEBUG\n\nloan: %f\ninterest: %f\npayment: %f\n",loanAmt,interestRate,monthlyPayment);

  return 0;
}
