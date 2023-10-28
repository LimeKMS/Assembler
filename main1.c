/************************************************
* Project 3 - Pass 1 Assembly                   *
* Class: COP3404 - Systems Software             *
* Author: Liam Rigney                           *
* 10/30/22                                      *
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TableSize 220 
#define Max 9

int * hexiCon(int input){
  int i = 0;  
  
  static int x[5];
  x[4] = input % 16;
  i = input /16;
  x[3] = i % 16;
  i = i /16;
  x[2] = i % 16;
  i = i / 16;
  x[1] = i % 16;
  i = i / 16;
  x[0] = i % 16;
  
  return x;
}

int * hexiSet(int input){
  int i = 0;  
  
  static int x[5];
  x[4] = input % 10;
  i = input /10;
  x[3] = i % 10;
  i = i /10;
  x[2] = i % 10;
  i = i / 10;
  x[1] = i % 10;
  i = i / 10;
  x[0] = i % 10;
  
  return x;
}

int deciCon(int input){
  int * yu = hexiSet(input);

  int output = yu[4];
  output = (yu[3] * 16) + output;
  output = (yu[2] * 16 * 16) + output;
  output = (yu[1] * 16 * 16 * 16) + output;
  output = (yu[0] * 16 * 16 * 16 * 16) + output;
  
  
  return output;
}

int * addHex(int * x, int * y){  
  x[4] += y[4];
  for(int i = 4; i >= 0; i--){
    if(x[i] >= 16){
      x[i] -= 16;
      x[i - 1]++;
    }
  }  
  return x;
}

void printHex(int * x){
for(int i = 0; i < 5; i++ ){
  if(x[i] <= 9){
   printf("%d", x[i]);  
  } 
  if(x[i] == 10){
   printf("A");  
  }
  if(x[i] == 11){
   printf("B");  
  }  
  if(x[i] == 12){
   printf("C");  
  }
  if(x[i] == 13){
   printf("D");  
  }
  if(x[i] == 14){
   printf("E");  
  }
  if(x[i] == 15){
   printf("F");  
  }
}
  printf("   ");
}

char * SICOPS(char prefix[2],char str[9]){
  
  static char x[4] = {'\0'};

  char compare[9] = {'\0'};
  int hmm = 0;
  

  if(prefix[0] == ' '){

    strcpy(compare,str);
  }
  else{
    compare[0] = prefix[0];
    for(int i = 1; i < 7; i++){
      compare[i] = str[i - 1];
    }
    
  }
  

  FILE *fp2;
  fp2 = fopen("SICOPS.txt", "r");
  if (NULL == fp2) {
        printf("file can't be opened \n");
    }
  int i = 0;

    char sourceLine[21];
    static char labOpt[9] = {'\0'};
    char temp[21] = {'\0'};
    
  do{

      fgets(sourceLine, 22, fp2);
      strncpy(labOpt, sourceLine, 7);
    
    if(i < 128){      

        if(strcmp(labOpt, compare) == 0){

          x[0] = sourceLine[8];
          x[1] = sourceLine[9];
          x[2] = ' ';
          x[3] = sourceLine[14];
          break;
      }
    }
    i++;
    
  }while(!feof(fp2)); 

  fclose(fp2);
  
  return x;
}


int hash(char name[Max]){  //Hash Function
  int key = 0;
  for (int i = 0; name[i] != '\0'; ++i){
    char x = name[i];
    key = key + x;
  }
  key = key % TableSize;
  return key;
}

typedef struct node { //Node struct
    char name[Max];
    int value;
} node;
node array[Max]; //Array initilized

void insert(int index, node *p){ //Insert Function for hash table

  if (array[index].value != 0){ //Checks if index has something in it

    if (index <= TableSize) {
      index++;
      insert(index, p);
      }
    else{
      index = 0;
      insert(index, p);
    }
  }
  else{ //Emtpy index, stores it into the index
    array[index] = *p;
    strcpy(array[index].name, p->name);
  }

} 
void print(){ //Prints Hash table
  printf("%-7s%-7s%-12s\n", "Index", "Label", "Address");
  for(int i = 0; i < TableSize; i++){
    if(array[i].value != 0){
      printf("%5d%10s ", i, array[i].name);
      printHex(hexiCon(array[i].value));
      printf("\n");
    }
  }
}



int main(int argc, char *argv[]) { //main
  int Scnt = 0, Locctr = 0, ENDval = 0, Errorflag = 0;
  char mneu[8] = {'\0'};
  
  FILE *fp;


  fp = fopen(argv[1], "r");
  if (NULL == fp) {
        printf("file can't be opened \n");
    } 

  node * p;  
  p = malloc(sizeof(struct node)); //Memory allocated
  int HaValue;

 do{
   char sourceLine[81];

    fgets(sourceLine, 81, fp);
    int length = strlen(sourceLine);
    if (sourceLine[length - 1] == '\n')
        sourceLine[--length] = '\0';
   
    if(sourceLine[0] != '.'){
      char temp[80] = {'\0'};
      
      char labOpt[9] = {'\0'};
      strncpy(labOpt, sourceLine, 8);
      
      strcpy(temp, &sourceLine[8]);
      char blank[2] = {'\0'};
      strncpy(blank, temp, 1);

      strcpy(temp, &sourceLine[9]);
      char plusOpt[2] = {'\0'};
      strncpy(plusOpt, temp, 1);

      strcpy(temp, &sourceLine[10]);
      strncpy(mneu, temp, 7);
      
      strcpy(temp, &sourceLine[17]);
      char blank2[2] = {'\0'};
      strncpy(blank2, temp, 1);

      strcpy(temp, &sourceLine[18]);
      char symbol[2] = {'\0'};
      strncpy(symbol, temp, 1);

      strcpy(temp, &sourceLine[19]); //optional
      char operand[11] = {'\0'};
      strncpy(operand, temp, 10);

      strcpy(temp, &sourceLine[29]); //optional
      char blank3[3] = {'\0'};
      strncpy(blank3, temp, 2);

      
      char com[50] = {'\0'};
      if(blank3[2] != '\n' && blank3[1] != '\n' && blank3[0] != '\n'){
        strcpy(temp, &sourceLine[32]); //optional
        strncpy(com, temp, 49);
      }
      
      
      if(strcmp (mneu, "START  ") == 0){
        Locctr = deciCon(atoi(operand)); 
        int * tempX = hexiCon(Locctr);
        printHex(tempX);
        printf("%s%s%s%s%s%s%s%s%s\n",labOpt, blank, plusOpt, mneu, blank2, symbol, operand, blank3, com);

        HaValue = hash(labOpt);
        p->value = Locctr;
        strcpy(p->name, labOpt);
        insert(HaValue, p);
        
      }
      else{
       
        int * addr = hexiCon(Locctr);
        printHex(addr);
        printf("%s%s%s%s%s%s%s%s%s\n",labOpt, blank, plusOpt, mneu, blank2, symbol, operand, blank3, com);

        if(strcmp(labOpt, "        ") != 0){
          HaValue = hash(labOpt);
          p->value = Locctr;
          strcpy(p->name, labOpt);
          insert(HaValue, p);
        }
        
        
        
      
        if(strcmp(mneu, "BASE   ") == 0){
        
      }
        else if(strcmp(mneu, "RESW   ") == 0){
        Scnt = atoi(operand);
        Locctr = Locctr + (Scnt * 3); 
      }
        else if(strcmp(mneu, "WORD   ") == 0){
        Scnt = 1;
        Locctr = Locctr + (Scnt * 3); 
      }
        else if(strcmp(mneu, "RESB   ") == 0){
        Scnt = atoi(operand);
        Locctr = Locctr + (Scnt * 3); 
      }
        else if(strcmp(mneu, "BYTE   ") == 0){
        Scnt = 1;
        Locctr = Locctr + (Scnt * 3); 
      }
        else{
          //printf("%s%s.\n", plusOpt, mneu);
        char * x  = SICOPS(plusOpt, mneu);
        char x2 = x[3];
        Scnt = atoi(&x2);
        Locctr = Locctr + Scnt; 
      }
      
        

      }
    }
   else{ //Comment
     printf("%s\n", sourceLine);
   }

  } while(strcmp(mneu, "END    ") != 0);

  printf("\n");

  print();

  
    fclose(fp);
  
  
  return 0;
}