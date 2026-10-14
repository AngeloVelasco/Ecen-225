#include <stdio.h>
#include <stdint.h>
#include <stdc-predef.h>

unsigned int convertme = 3735928559;
char name[] = "Angelo Velasco";
int age = 25;



//method for part 2
void inttochar(uint8_t numberConversion){
    printf("The character equivalent to %d is %c \n", numberConversion, numberConversion);
}

//method for part 4
void massprint(uint16_t convertme){
    float divideme = convertme/2;
    int score =80;
    int favoriteNumber = 67;
    printf("The character equivalent to %d is %c\n ", convertme,convertme);
    printf("Did you know that %d divided by 2 is %f\n", convertme,divideme);
    printf("In hexadecimal, %d is %x\n", convertme,convertme);
    printf("My grade in Physics121 is %d%%\n",score);
    printf("My favorite number is %i\n", favoriteNumber);
}

//method for part 5
void mathew_11_29(float load){
    printf("Come unto me all ye that labour and are heavy laden %f\n", load);
    printf("Take my yoke upon you, learn of me and I shall give you rest. %d\n",(int)load);
}
int main(){
//this is part 1 
    printf("Hex equivalent of %i is %x\n",convertme, convertme);
//this is part 2 (Method in line 12)
    inttochar(97);
    inttochar(65);
    inttochar(70);
//this is part 3
    printf("Hello, my name is %s, and I am %d years old, did you know that 1 divided by 2 is %f\n",name,age,.5);
//this is part 4 (Method in line 17)
    massprint(80);
//this is part 5 (Method in line 29)
    mathew_11_29(696.96969);

}

