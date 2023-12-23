//Daniel chu
//1493374
//Lab 3 CMPUT201
//Q2 page 71

#include<stdio.h>

#include<stdio.h>

int main(){

  //initalize variables
  int num,num1st,num2nd,num3rd;//number, first int, 2nd int


  //User I/O
  printf("Enter a three-digit number: ");
  scanf("%i",&num);
  //split integer
  num1st = num/100;
  num2nd = (num/10)%10;
  num3rd = num%10;

  //Display reversed halves
  printf("The Revsersal is: %i%i%i\n",num3rd,num2nd,num1st);

  return 0;
}
