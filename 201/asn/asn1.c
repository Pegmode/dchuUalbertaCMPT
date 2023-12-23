//CMPUT201 Assignment #1

//SUBMITTING STUDENT: Daniel Chu 1493374
//Collaborating classmates: None
//Other collaborators
//References:
//

#include<stdio.h>
#include<string.h>

#define MAX_SEQUENCE_LENGTH 1005  //Assignment stated that we are expexted to handle inputs up to 1000

char LCSString[MAX_SEQUENCE_LENGTH];

int findHighest(int val1,int val2){//given 2 values, return the highest
  if(val1 >= val2){
    return val1;
  }
  else{
    return val2;
  }
}

int checkSequence(char currentSequence[]){// function to check if a given character array is only comprised of digits
  for(int i = 0;i < strlen(currentSequence);i++){//scan each char in char array
    if(!(0 <= ((int)currentSequence[i] - 48)&& ((int)currentSequence[i] - 48) <= 9)){//check if current char is a digit (Assembly CMPUT229 ascii trick)
      return 0;//return false if incorrect char found
    }
  }
  return 1;//if no non digits are found return true
}

int main(){
  //variable declarization and initialization
  char sequence1[MAX_SEQUENCE_LENGTH],sequence2[MAX_SEQUENCE_LENGTH];

  //question 1. and 2.
  printf("To compute an LCS,\nenter the first sequence: ");
  for(;;){//loop while input is incorrect
    scanf("%s",sequence1);
    if (checkSequence(sequence1)){//check if the input is correct
      break;
    }
    printf("\nError, non-digit character detected!\n\nTo compute an LCS,\nenter the first sequence: ");//Display reprompt if incorrect
  }
  printf("enter the second sequence: ");
  for(;;){
    scanf("%s",sequence2);
    if (checkSequence(sequence2)){//check if the input is correcT
      break;
    }
    printf("\nError, non-digit character detected!\n\nTo compute an LCS,\nenter the second sequence: ");//Display repromt if incorrect
  }

  //question 3.
  printf("\n# Two input sequences (length = %lu, %lu) are:\n%s\n%s\n",strlen(sequence1),strlen(sequence2),sequence1,sequence2);
  //question 4.

  //was previously in it's own function but I had issues appending a char to a string
  int horLen = strlen(sequence2) ,vertLen = strlen(sequence1);//we are going to be using the horzizontal legnth and vertical length a lot.
  int LCSTable [horLen+1][vertLen+1];//build empty table of size seq1 x eq2 with first entry empty, table lengths must be 1 greater because of zeroes rows, col

  //fill first row/col with only zeroes
  for(int i = 0; i <= horLen;i++){
    LCSTable[i][0] = 0;
  }
  for(int i = 0; i <= vertLen; i++){
    LCSTable[0][i] = 0;
  }

  //scan entire table
  for(int i = 1; i <= horLen;i++){
    for(int j = 1; j <= vertLen; j++){
      if(sequence2[i - 1] == sequence1[j - 1]){// if current row/col match (- 1 because we added an extra col/row for zeroes)
        LCSTable[i][j] = LCSTable[i-1][j-1] + 1;//Take upper left and add 1 to it
        LCSString[strlen(LCSString) + 1] = sequence2[i-1];//horizontal movement means current char is in LCS
      }
      else{
        LCSTable[i][j] = findHighest(LCSTable[i][j - 1],LCSTable[i - 1][j]);//take highest left or upper value in table
      }
    }
  }
  printf("\n# an LCS (length = %i) is:\n",LCSTable[horLen][vertLen]);//print value from bottom right of table

  //part 5, work backwards to find LCS string
  int y = vertLen;//start in bottom right corner
  for(int x = horLen; x > 0; x--){
    if(LCSTable[x-1][y] < LCSTable[x][y] ){//if current value was from a horizontal move. it's part of LCS
      printf("%c",sequence2[x-1]);
      y--;
    }
  }
  printf("\n");//formatting
  return 0;
}
