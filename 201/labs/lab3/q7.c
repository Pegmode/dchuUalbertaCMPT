//Daniel chu
//1493374
//Lab 3 CMPUT201
//Q7 page 96

#include<stdio.h>

int main(){
  //Var initialization
  int num;
  int largest,smallest;

  //User I/O
  printf("Enter four integers: ");

  //first number
  scanf("%i",&num);
  largest = num;
  smallest = num;

  for(int i = 0;i <=2;i++){
    scanf("%i",&num);
    if(num > largest){
      largest = num;
    }
    if(num < smallest){
      smallest = num;
    }
  }

  printf("\nLargest: %i\nSmallest: %i\n",largest,smallest);

  return 0;
}
