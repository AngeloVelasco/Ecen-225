#include "custom_strings.h"

//  ____________ Instructions on this assignment ____________
//
//  You will either need to implement or debug all of the
//  functions in data.c and custom_strings.c.
//
//  As you code, follow the following rules:
//  1.  Unless specified in the function, do not change the
//      data types.
//  2.  If you need to change a data type to a floating-point
//      number, then use `double`, not `float`.  This is for
//      the autograder.
//  3.  You can use printf() statments for debugging data.c and
//      custom_strings.c, but comment them out or remove them
//      before you pass off.
//  4.  If there are any specific rules for the function, follow
//      them.
//
//  Here's a bit of advice:
//  1.  Look up what a bit mask is.
//  2.  Recall what bitwise operations do.
//  3.  Use plenty of printf() statements when you debug.
//  4.  It's better to have code that is broken up and easy
//      to read than code that is compact.
//
//  Good luck!


uint32_t getStringLength(char string[]) {
    // TODO: Implement this function
    int howmany = 0;
    int i;
    for(i =0; string[i] != '\0'; howmany++){
        i++;
    }
    return howmany;
}

void toUpper(char output[], char input[]) {
    // TODO: Implement this function
    int i;
    for( i = 0; input[i] != '\0'; i++){
        if(input[i]>= 97 && input[i] <= 122){
            output[i] = input[i] - 32;
        }else{
            output[i] = input[i];
        }
        output[i+1] = '\0';
    }
}

int32_t findLastChar(char charToFind, char string[]) {
    // TODO: Implement this function
    int i;
    int answer =0 ;

    for(i =0; string[i]!= '\0'; i++){
        if(string[i] == charToFind){
            answer = i;
        }
        }
        if( answer == 0){
            return -1;
        }
    
    return answer ;
}

void getFileExtension(char extension[], char fileName[]) {
    // TODO: Implement this function
    int i;
    int j = 0;
    for(i = 0; fileName[i] != 46 ;i++){
    }
    for(j; fileName[i] != '\0';i++,j++){
        extension[j] = fileName[i+1];
        
    }
    extension[j] = '\0';

}

void combinePath(char path[], char folderName[], char fileName[]) {
    // TODO: Implement this function

    int i = 0;
    for(i; folderName[i] != '\0'; i++){
        path[i] = folderName[i];
    }
    path[i] = '/';
    for(int j =0; fileName[j] != '\0';j++){
        path[i+1] = fileName[j];
        i++;
    }

    path[i+1] = '\0';



    
}
