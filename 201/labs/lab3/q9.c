//Daniel chu
//1493374
//Lab 3 CMPUT201
//Q9 page 123

#include<stdio.h>
int main(){

  //declarations
  float interestRate,monthlyPayment,numPayments; //working
  float balance;
  //user io
  printf("Enter amount of loan: ");
  scanf("%f",&balance);
  printf("Enter interest rate: ");
  scanf("%f",&interestRate);
  printf("Enter monthly payment: ");
  scanf("%f",&monthlyPayment);
  printf("Enter number of payments: ");
  scanf("%f",&numPayments);
  printf("\n");//formatting

  //calculate and display numPayments balances
  for(int i = 1 ; i <= numPayments ; i++){ //
    balance = balance - monthlyPayment + (balance * (interestRate/1200));
    printf("Balance after month %i: $%.2f\n",i,balance);
  }
  
  return 0;
}
