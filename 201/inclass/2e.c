//CMPUT 201 in class example
// Calucilating a Brokers comission
// minimum charge 39$
// slides have the commission rats for transaction sizes
#include <stdio.h>
int main(){
  float trade, comission;//trade = value of customers trade, comission = comission for said trade

  printf("Enter the value of the trade:");
  scanf("%f",trade);
  printf(\n);
  //could put checks for missmatch

  if (trade <= 2500){
    comission = 30 + 0.017 * trade; // 1.7%
  }
  else if(trade > 2500 && trade <= 6250){
    comission = 56 + 0.0066 * trade// 0.66%
  }
  else if(trade > 6250 && trade <= 20000){
    comission = 76 + 0.0034 * trade;// 0.34
  }
  else{
    comission = 100 + 0.0022 * trade;//0.22%
  }
printf("Comission: $%.2f\n",comission);

  return 0;
}
