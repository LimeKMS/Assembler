/************************************************
* Project 4 - Pass 2 Assembly                   *
* Class: COP3404 - Systems Software             *
* Author: Liam Rigney                           *
* 12/04/22                                      *
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_substring(char*, char*, int);
char* substring(char*, int, int);

#define TableSize 220 
#define Max 9

typedef struct node { //Node struct
    char name[Max];
    int value;
} node;
node array[Max]; //Array initilized

int * hexiCon(int input, int size){
  int j = 0;  

  if(size == 5) {
    static int x[5];
    j = input;
    for(int i = size; i >= 0 ; i--){
      x[i-1] = j % 16;
      j = j /16;
    }
    return x;
  }
  else{
    static int x[6];
    j = input;
    for(int i = size; i >= 0 ; i--){
      x[i-1] = j % 16;
      j = j /16;
    }
    return x;
  }
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

void filePrintHex(int * x, int size, FILE * fp){
for(int i = 0; i < size; i++ ){
  if(x[i] <= 9){
   fprintf( fp,"%d", x[i]);  
  } 
  if(x[i] == 10){
   fprintf(fp,"A");  
  }
  if(x[i] == 11){
   fprintf(fp,"B");  
  }  
  if(x[i] == 12){
   fprintf(fp,"C");  
  }
  if(x[i] == 13){
   fprintf(fp,"D");  
  }
  if(x[i] == 14){
   fprintf(fp,"E");  
  }
  if(x[i] == 15){
   fprintf(fp,"F");  
  }
}
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
          x[4] = '\0';
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

int regis(char in){
  int x = 0;
  if(in == 'A'){
    return 0;
  }
  else if (in == 'X'){
    return 1;
  }
  else if (in == 'L'){
    return 2;
  }
  else if (in == 'B'){
    return 3;
  }
  else if (in == 'S'){
    return 4;
  }
  else if (in == 'T'){
    return 5;
  }
  else if (in == 'F'){
    return 6;
  }
  else if (in == 'P'){
    return 8;
  }
  return x;
}

void NIXPBE(FILE * fp, FILE * Obj, int * OP, int format, char plusOp, char symbol, int currAd, char * Operand){

  char labOpt[9] = {'\0'};
  strncpy(labOpt, Operand, 8);
  
  int * x = hexiCon(0, format * 2);
  if(format == 1){
    filePrintHex(x, format * 2, fp);
    filePrintHex(x, format * 2, Obj);
    fprintf(fp, "                ");
  }
  
  else if(format == 2){
    x[0] = OP[3];
    x[1] = OP[4];
    
    x[3] = regis(plusOp);
    x[2] = regis(Operand[0]);

    filePrintHex(x, format * 2, fp);
    filePrintHex(x, format * 2, Obj);
    
    fprintf(fp, "              ");
  }
  
  else if(format == 3){
    int disp = array[hash(labOpt)].value;
    disp = disp - (currAd + format);
    x[2] = 0;
    
    if(disp < 0){
      disp = 4095 + (disp + 1);
    }

    int * y = hexiCon(disp, 3);
    x[3] = y[0];
    x[4] = y[1];
    x[5] = y[2];
    //if(label[0] == *){ add 0}
    if(plusOp == '*'){
      OP = addHex(OP, hexiCon(0,5));
    }
    //else if(label[0] == #){ add 1} //immediate 
    else if(symbol == '#'){
      OP = addHex(OP, hexiCon(1,5));
    }
      //else if(label[0] == @){ add 2}
    else if(symbol == '@'){
      OP = addHex(OP, hexiCon(2,5));
    }
    //else{ add 3}
    else{
      OP = addHex(OP, hexiCon(3,5));
      x[2] = 2;
    }
    x[0] = OP[3];
    x[1] = OP[4];

    
    filePrintHex(x, format * 2, fp);
    fprintf(fp, "            ");
    filePrintHex(x, format * 2, Obj);
  }
  
  else if(format == 4){
    int disp = array[hash(labOpt)].value;
    //if(label[0] == *){ add 0}
    OP = addHex(OP, hexiCon(0,5));
    
    //else if(label[0] == #){ add 1} //immediate 
    if(symbol == '#'){
      OP = addHex(OP, hexiCon(1,5));
    }
      //else if(label[0] == @){ add 2}
    else if(symbol == '@'){
      OP = addHex(OP, hexiCon(2,5));
    }
    //else{ add 3}
    else{
      OP = addHex(OP, hexiCon(3,5));
      x[2] = 1;
    }
    x[0] = OP[3];
    x[1] = OP[4];
    int * y = hexiCon(disp, 5);
    x[3] = y[0];
    x[4] = y[1];
    x[5] = y[2];
    x[6] = y[3];
    x[7] = y[4];
    
    
    filePrintHex(x, format * 2, fp);
    fprintf(fp, "          ");
    filePrintHex(x, format * 2, Obj);
  }

  
  
  
}


int getAddr(char * label){
  int x = 0;
  int HaValue = hash(label);

  x = array[HaValue].value;

  return x;
}

int hexDigit(char digit){
  int x;
  if(digit == 'A'){
    x = 10;
  }
  else if(digit == 'B'){
    x = 11;
  }
  else if(digit == 'C'){
    x = 12;
  }
  else if(digit == 'D'){
    x = 13;
  }
  else if(digit == 'E'){
    x = 14;
  }
  else if(digit == 'F'){
    x = 15;
  }
  else{
    x = atoi(&digit);
  }
  
  return x;
}

int * OPCon(int one, int two){
  static int x[5];
  x[0] = 0;
  x[1] = 0;
  x[2] = 0;
  x[3] = one;
  x[4] = two;
  
  return x;
}

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
      printHex(hexiCon(array[i].value, 5));
      printf("\n");
    }
  }
}



int main(int argc, char *argv[]) { //main
  int Scnt = 0, Locctr = 0, Errorflag = 0;
  char mneu[8] = {'\0'};
  
  FILE *fp;

  argv[1] = "f1.txt";


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
        int * tempX = hexiCon(Locctr, 5);

        
        /*HaValue = hash(labOpt);
        p->value = Locctr;
        strcpy(p->name, labOpt);
        insert(HaValue, p);*/
      }
      else{        
        char * x  = SICOPS(plusOpt, mneu);
        char temp1 = x[0];
        char temp2 = x[1];
        char x2 = x[3];
        
        int * addr = hexiCon(Locctr, 5);

        if(strcmp(labOpt, "        ") != 0){
          HaValue = hash(labOpt);
          p->value = Locctr;
          strcpy(p->name, labOpt);
          insert(HaValue, p);
        }

      
        if(strcmp(mneu, "BASE   ") == 0){
        
      }
        else if(strcmp(mneu, "END    ") == 0){
        
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
        Scnt = atoi(&x2);
        Locctr = Locctr + Scnt; 
      }
      }
    }
  } while(strcmp(mneu, "END    ") != 0);
  
  fclose(fp);
  ////////////////////////////////////////Pass 1/////////////////////////////////////////
  FILE *lst;
  FILE *Obj;
  FILE *fp2;

  int position, Line = 0;

  char * pgmlst = argv[1];
  char temp[80] = {'\0'};
  char tempOBJ[80] = {'\0'};
  strcpy(temp, pgmlst);
  strcpy(tempOBJ, pgmlst);
  char * lstP = "lst";
  char * objP = "obj";

  for(int o = 0; o < strlen(pgmlst); o++){
    position = o + 1;
    if(pgmlst[o] == '.'){
      break;
    }
  }
  
  insert_substring(temp, lstP, position);
  insert_substring(tempOBJ, objP, position);
  
  lst = fopen (temp, "w");
  Obj = fopen (tempOBJ, "w");
  int tag = 0;
  int tag2 = 1;
  int tag3 = 1;
  int tag4;
  int tag5 = 1;

  ////////////////////////////////////File making/////////////////////////////////////////

  fp2 = fopen(argv[1], "r");
  if (NULL == fp2) {
        printf("file can't be opened \n");
    } 

  do{
    char sourceLine[81];
    Line ++;

    fgets(sourceLine, 81, fp2);
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
        int * tempX = hexiCon(Locctr, 5);
      
        fprintf(lst, "***********************************************\n");
        fprintf(lst, "Liam Rigney n01450656: SIC/XE assembler\n");
        fprintf(lst, "version date 12/1/2022\n***********************************************\n");
        fprintf(lst, "ASSEMBLER REPORT\n----------------\n     Loc   Object Code       Source Code\n");
        fprintf(lst, "     ---   -----------       -----------\n");
        
        int * addr = hexiCon(Locctr, 5);
        fprintf(lst, "%03d- ", Line);
        filePrintHex(addr, 5, lst);
        fprintf(fp," ");
        fprintf(lst, "                  ");
        
        fprintf(lst, "%s%s%s%s%s%s%s%s%s\n",labOpt, blank, plusOpt, mneu, blank2, symbol, operand, blank3, com);        
      }
      else{        
        
        char * x  = SICOPS(plusOpt, mneu);
        char temp1 = x[0];
        char temp2 = x[1];
        char x2 = x[3];

        
        int * addr = hexiCon(Locctr, 5);
        fprintf(lst, "%03d- ", Line);
        filePrintHex(addr, 5, lst);
        fprintf(fp," ");
        //////////////////////////////////////////////////////////////
        
      tag = 1;
      tag5 = 1;
      
        if(strcmp(mneu, "BASE   ") == 0){
          tag4 = 0;
          
          
          fprintf(lst, "                  ");
      }
        else if(strcmp(mneu, "END    ") == 0){
          tag4 = 1;
          fprintf(lst, "                  ");
      }
        else if(strcmp(mneu, "RESW   ") == 0){
          
          fprintf(lst, "FFFFFF            ");
          
        Scnt = atoi(operand);

        if(strcmp(labOpt, "        ") != 0 && tag4 != 3){
          filePrintHex(hexiCon(Locctr, 6), 6, Obj);
          fprintf(Obj,"\n");
          fprintf(Obj, "000000\n!\n");
          
        }
        else{
          if(strcmp(labOpt, "        ") == 0 && tag4 != 7){
            fprintf(Obj,"!\n");
          }
          //fprintf(Obj,"!\n");
        }
          
          
        tag4 = 2;
        Locctr = Locctr + (Scnt * 3); 
      }
        else if(strcmp(mneu, "WORD   ") == 0){
          
          //HOLD ON
          int value = atoi(operand);
          filePrintHex(hexiCon(value, 6), 6, lst);
          fprintf(fp,"            ");

          if (tag4 != 3) {
            filePrintHex(hexiCon(Locctr, 6), 6, Obj);
            fprintf(Obj,"\n");
            fprintf(Obj, "000000\n");
          }
          
        filePrintHex(hexiCon(value, 6), 6, Obj);
        fprintf(Obj,"\n");
        
        tag4 = 3;
        Scnt = 1;
        tag5 = 0;
        Locctr = Locctr + (Scnt * 3); 
      }
        else if(strcmp(mneu, "RESB   ") == 0){
          tag4 = 5;
          //HOLD ON
        Scnt = atoi(operand);
        Locctr = Locctr + (Scnt * 3); 
      }
        else if(strcmp(mneu, "BYTE   ") == 0){
          tag4 = 6;
          //HOLD ON
        Scnt = 1;
        Locctr = Locctr + (Scnt * 3); 
      }
        else{                                       //NIXPBE calc
        int * OPCode = OPCon(hexDigit(temp1), hexDigit(temp2));
        
        Scnt = atoi(&x2);

        //fprintf(Obj, "!\n");
        if(tag == 1 && tag4 != 7){
          if(tag3 == 1){
            filePrintHex(hexiCon(Locctr, 6), 6, Obj);
            fprintf(Obj,"\n");
            fprintf(Obj, "000000\n");
            tag2 = 1;
            tag3 = 0;
          }
          else{
            tag3 = 1;
          }
        }
          tag4 = 7;
        
        NIXPBE(lst, Obj, OPCode, Scnt, plusOpt[0], symbol[0], Locctr, operand);
        fprintf(Obj, "\n");
        
        Locctr = Locctr + Scnt; 
          tag = 0;
      }
      
      fprintf(lst, "%s%s%s%s%s%s%s%s%s\n",labOpt, blank, plusOpt, mneu, blank2, symbol, operand, blank3, com);
          
      if(tag == 1 && tag5 == 1){
          if (tag2 == 1){
            if (tag3 == 1){
              fprintf(Obj, "!\n");
              tag2 = 0;
              tag3 = 1;
            }
          }
        }

      }
    }
   else{ //Comment
     fprintf(lst, "%03d- ", Line);
     fprintf(lst, "%s\n", sourceLine);
   }

  } while(strcmp(mneu, "END    ") != 0);  
  
  fclose(fp2);

  
  
  
  return 0;
}

void insert_substring(char *a, char *b, int position){
   int length;
   
   length = strlen(a);
   
   char * f = substring(a, 1, position - 1 );      
   char * e = substring(a, position, length-position+1);

   strcpy(a, "");
   strcat(a, f);
   free(f);
   strcat(a, b);
   strcat(a, e);
   free(e);
}

char * substring(char *string, int position, int length){
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
   
   if( pointer == NULL )
       exit(EXIT_FAILURE);
 
   for( c = 0 ; c < length ; c++ )
      *(pointer+c) = *((string+position-1)+c);      
       
   *(pointer+c) = '\0';
 
   return pointer;
}
