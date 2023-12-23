//Daniel Chu
//1493374
//CMPUT 201
//Lab2
//Program that ask the user to enter the numbers from 1-16 in any order and then display the numbers in a 4 by 4 arrangement
//followed by the sums of the rows, columns, and diagonals

#include<stdio.h>

int main(){

  //init and declarations
  int numbers[16],rowSums[4],columnSums[4],diagSums[2];

  //user i/o
  printf("Enter the numbers from 1 to 16 in any order: \n");
  for(int i = 0;i <= 15;i++){//save space separated integers are entries into array numbers
    scanf("%i",&numbers[i]);
  }

  //print 4x4 arrangement and calculate Row/Col sums
  for(int i = 0 ; i <= 3 ; i++){ //i and j are either rows or columns depending on context because we have a square o/p
    rowSums[i] = 0;//current working entry in array needs to be initialized
    columnSums[i] = 0;
    for (int j = 0 ; j<= 3; j++){
      printf("%i ",numbers[i*4+j]);//print single entry
      rowSums[i] += numbers[i*4+j];//add current entry to current row
      columnSums[i] += numbers[(j*4)+i];//add entry where i and j are reversed to col
    }
    printf("\n");//new line
  }


  //Calculate remaining diag sums
  diagSums[0] = 0;
  for(int i = 0;i <= 3; i++){
    diagSums[0] += numbers[i*5];//diag going down right
  }

  diagSums[1] = 0;
  for(int i = 0;i <= 3; i++){
    diagSums[1] += numbers[3+3*i];//diag going down left
  }


  //print out sums
  printf("\nRow sums: ");
  for(int i = 0; i<=3 ; i++){
    printf("%i ",rowSums[i]);
  }

  printf("\nColumn sums: ");
  for(int i = 0; i<=3 ; i++){
    printf("%i ",columnSums[i]);
  }

  printf("\nDiagonal sums: ");
  for(int i = 0; i<=1 ; i++){
    printf("%i ",diagSums[i]);
  }

  printf("\n");//formatting for console
  return 0;
}
