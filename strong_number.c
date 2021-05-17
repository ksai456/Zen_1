#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define TRUE 1

static int line_number = 1;

int reverse_number(int num){
    int rev = 0, remainder;
    while (num != 0) {
        remainder = num % 10;
        rev = rev * 10 + remainder;
        num /= 10;
    }
    return rev;
}

int check_strong(int num){
    int i,fact,r,sum=0,temp;
    temp=num;
    while(num)
    {
        i=1,fact=1;
        r=num%10;
        while(i<=r)
        {
            fact=fact*i;
            i++;
        }
        sum=sum+fact;
        num=num/10;
    }
    if(sum==temp){
        return 1;
    }
    return 0;
}



int check_digit(char word[]){                      //Function for checking if passed word is integer or not
    char c;
    char words[20];
    //printf("words : %s\n", word);
    strcpy(words, word);
    int i,digit,number=0; 
    for(i=0;i<strlen(words);i++){ 
        c = words[i]; 
        if(c>='0' && c<='9') //to confirm it's a digit 
        { 
            digit = c - '0'; 
            number = number*10 + digit;
        }
    }
    if(number > 0){
        check_strong(number);
        return number;
    }
    return 0;    
}


int split_words(char *arr){             //Funtion for splitting words in a line
    char str1[300];
    char newString[20][300]; 
    int i,j,ctr;
    strcpy(str1, arr);
    j=0; ctr=0;
    for(i=0;i<=(strlen(str1));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(str1[i]==' '||str1[i]=='\0')
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j]=str1[i];
            j++;
        }
    }
    int Etnumber = 0;
    int lineNumber[5]={0};
    int k = 0;
    for(i=0;i < ctr;i++){
        //printf("%s ", newString[i]);
        Etnumber = check_digit(newString[i]);
        if(Etnumber > 0){
            lineNumber[k] = Etnumber;
            k++;
        }
    }
    //printf("\n");
    int sum = 0;
    int count = 0;
    printf("***********************START***************************\n");
    printf("Numbers in line - %d\n", line_number );
    for(int a = 0; a<k; a++){
         printf(" --> %i\n", lineNumber[a]);
         if(check_strong(lineNumber[a])){
              printf(" %d is a Strong number\n", lineNumber[a]);
             sum += lineNumber[a];
             count ++;
         }
    }
    printf("-----------------------------------------------\n");
    printf("Count of Strong Numbers : %d\n", count);
    printf("Sum of Strong Numbers : %d\n", sum);
    printf("-----------------------------------------------\n");
    if(count == 1 || count == 4){                   //if 1 or 4 strong numbers reverse the string
        for(int j = ctr-2; j >= 0; --j){
            printf("%s ", newString[j]);
            printf("");
        }
        printf("\n");
    }
    if(count == 2 || count == 5){                   //if 2 or 5  strong numbers replace strong numbers with sum of strong numbers
        char num[10];
        for(int j = 0; j < ctr; j++){
            if(check_digit(newString[j])){
                snprintf(num, sizeof(num), "%d", sum);
                strncpy(newString[j], num, sizeof(num));
            }
            printf("%s ", newString[j]);
        }
        printf("\n");
    }
    if(count == 3 || count == 7){                   //if 3 or 7 strong numbers revers the words in same place
        char num[5];
        char reverse[20];
        for(int j = 0; j < ctr; j++){
            strncpy(reverse, newString[j], sizeof(reverse));
            for(int r = strlen(newString[j])-1; r >= 0; r--){
                if(reverse[r] != '\n')
                    printf("%c", reverse[r]);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("*************************END***************************\n");
    line_number++;
}



int main(void){
    char *line = NULL;
    size_t len = 0;
    FILE *fptr=NULL; 
    char arr[20][200];
    char target[20][200];
    int n = 0;
    fptr = fopen("file_contents.txt", "r");     //open file in Read mode
    if(!fptr){
        printf("cant open file\n");             //if can't open file print error
        exit(1);
    }
    int i = 0;
    while(getline(&line, &len, fptr) != -1){    //get line by line and copying to array
        strcpy(arr[i], line);
        i++;
    }
    
    for(int j = 0; j<i; j++){                   //splitting words in line
        split_words(arr[j]);
    }
    fclose(fptr);                               //file close
    free(line);                                 //free allocated memory to line
    return 0;
}