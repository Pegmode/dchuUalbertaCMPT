//Daniel Chu 1493374
//cmput201
//lab 6
//#7 page 239-240

#include<stdio.h>
#define MAX_DIGITS 10
#define DIGIT_HEIGHT 3 //The book is crazy it's 3 char high
#define INPUT_BUFFER_SIZE 30

void clear_digits_array();
void process_digit(int, int);
void print_digits_array();

char segments[][10][3] = {
  {{" _ "},{"   "},{" _ "},{" _ "},{"   "},{" _ "},{" _ "},{" _ "},{" _ "},{" _ "}},
  {{"| |"},{"  |"},{" _|"},{" _|"},{"|_|"},{"|_ "},{"|_ "},{"  |"},{"|_|"},{"|_|"}},
  {{"|_|"},{"  |"},{"|_ "},{" _|"},{"  |"},{" _|"},{"|_|"},{"  |"},{"|_|"},{"  |"}}
};
char digits[DIGIT_HEIGHT][MAX_DIGITS*4];//row,col


int main(){
  char inputBuffer[INPUT_BUFFER_SIZE];
  clear_digits_array();
  printf("Enter a number :");

  fgets(inputBuffer,INPUT_BUFFER_SIZE,stdin);

  int currentDigit = 0;
  for(int i = 0; i < INPUT_BUFFER_SIZE;i++){//read through input buffer char by char
    if('0' <= inputBuffer[i] && inputBuffer[i] <= '9'){
      process_digit(inputBuffer[i] - '0',currentDigit);
      currentDigit++;
    }
    if(currentDigit >= MAX_DIGITS) break;
  }
  print_digits_array();
  return 0;
}


void process_digit(int digit, int position){
  for(int i = 0;i < 3;i++){//hieght
    for(int j = 0;j < 3;j++){//width
      digits[i][position * 4 + j] = segments[i][digit][j];//
    }
  }
  return;
}

void clear_digits_array(){
  for(int i = 0;i < DIGIT_HEIGHT;i++){
    for(int j =0;j < MAX_DIGITS*4;j++){
      digits[i][j] = ' ';
    }
  }
  return;
}

void print_digits_array(){//col horz
  for(int i = 0;i < DIGIT_HEIGHT;i++){
    for(int j = 0;j< MAX_DIGITS * 4;j++){
      printf("%c",digits[i][j]);
    }
    printf("\n");
  }
  return;
}
