#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib/buttons.h"
#include "lib/colors.h"
#include "lib/device.h"
#include "lib/display.h"
#include "lib/fonts/fonts.h"
#include "lib/log.h"

#define VIEWER_FOLDER "viewer/"
#define MAX_ENTRIES 8
#define MAX_TEXT_SIZE 400
#define MAX_FILE_NAME 100

// Colors — Feel free to change these to fit your preference
#define BACKGROUND_COLOR WHITE
#define FONT_COLOR BLACK
#define SELECTED_BG_COLOR BYU_BLUE
#define SELECTED_FONT_COLOR BYU_LIGHT_SAND

#define NUM_ENTRIES 5
#define MAX_ENTRY_LENGTH 20

char entries[NUM_ENTRIES][MAX_ENTRY_LENGTH] = {"Clear", "Hello", "Chars", "Stars", "Flag"};

// Makes sure to deinitialize everything before program close
void intHandler(int dummy) {
    log_info("Exiting...");

    // Resets the Screen
    display_clear(BLACK);
    display_draw_string(5, 5, "Goodbye!", &Font16, BLACK, WHITE);

    // Releases control of the display
    display_exit();
    exit(0);
}

// clearScreen
//
//
// Clears the screen to white.
void clearScreen() {
    display_clear(WHITE);
}

// drawHelloWorld
//
// Draws "Hello World!" on the display 10 times
// Make each line a different color
void drawHelloWorld() {
    // TODO: Put your code here
    u_int16_t coordinateStartY = 8;

    display_draw_string(0,coordinateStartY ,"Hello World",&Font8,WHITE,BLACK);
    display_draw_string(0,coordinateStartY + 8 ,"Hello World",&Font8,WHITE,BISQUE1);
    display_draw_string(0,coordinateStartY + 16 ,"Hello World",&Font8,WHITE,RED);
    display_draw_string(0,coordinateStartY + 24 ,"Hello World",&Font8,WHITE,YELLOW1);
    display_draw_string(0,coordinateStartY + 32 ,"Hello World",&Font8,WHITE,AZURE1);
    display_draw_string(0,coordinateStartY + 40,"Hello World",&Font8,WHITE,BROWN1);
    display_draw_string(0,coordinateStartY + 48 ,"Hello World",&Font8,WHITE,CORAL1);
    display_draw_string(0,coordinateStartY + 56 ,"Hello World",&Font8,WHITE,DARK_MAGENTA);
    display_draw_string(0,coordinateStartY + 64 ,"Hello World",&Font8,WHITE,DARK_KHAKI);
    display_draw_string(0,coordinateStartY + 72 ,"Hello World",&Font8,WHITE,FIREBRICK1);
    display_draw_string(0,coordinateStartY + 80 ,"Hello World",&Font8,WHITE,PINK);

}

// drawChars
//
// Draw chars of different values, sizes, colors, and locations onto the screen
void drawChars() {
    // TODO: Put your code here
    u_int16_t xStart = ((float)rand()/RAND_MAX)* DISPLAY_WIDTH;
    u_int16_t ystart = ((float)rand()/RAND_MAX)* DISPLAY_HEIGHT;

    display_draw_char(xStart,ystart,'s',&Font8,WHITE,BLACK);
    xStart = ((float)rand()/RAND_MAX)* DISPLAY_WIDTH;
    ystart = ((float)rand()/RAND_MAX)* DISPLAY_HEIGHT;
    display_draw_char(xStart,ystart,'A',&Font12,WHITE,RED);
    xStart = ((float)rand()/RAND_MAX)* DISPLAY_WIDTH;
    ystart = ((float)rand()/RAND_MAX)* DISPLAY_HEIGHT;
    display_draw_char(xStart,ystart, '@',&Font20,WHITE,CORAL4);
    xStart = ((float)rand()/RAND_MAX)* DISPLAY_WIDTH;
    ystart = ((float)rand()/RAND_MAX)* DISPLAY_HEIGHT;
    display_draw_char(xStart,ystart,'&',&Font16,WHITE,STEEL_BLUE);
    xStart = ((float)rand()/RAND_MAX)* DISPLAY_WIDTH;
    ystart = ((float)rand()/RAND_MAX)* DISPLAY_HEIGHT;
    display_draw_char(xStart,ystart,'#',&Font24,WHITE,PLUM);
    xStart = ((float)rand()/RAND_MAX)* DISPLAY_WIDTH;
    ystart = ((float)rand()/RAND_MAX)* DISPLAY_HEIGHT;
}

// drawStars
//
// Draw at least 20 stars on the screen
// TIP: Make a function that uses display_draw_# functions to make the shape of the star,
// Then call that function at multiple locations
void drawStars() {
    // TODO: Put your code here
     u_int16_t xStart = ((float)rand()/RAND_MAX)* DISPLAY_WIDTH;
    u_int16_t ystart = ((float)rand()/RAND_MAX)* DISPLAY_HEIGHT;

    for(int i = 0; i < 20; i++){
        display_draw_char(xStart,ystart,'*',&Font12,WHITE,BLACK);
        xStart = ((float)rand()/RAND_MAX)* DISPLAY_WIDTH;
        ystart = ((float)rand()/RAND_MAX)* DISPLAY_HEIGHT;
    }

}

// drawFlag
//
// Use at least 5 other display_draw functions to make any flag you want.
// It must have at least 3 colors, and use 3 unique display_draw functions
void drawFlag() {
    // TODO: Put your code here
    //y stars by 4
    //x stars by 4 
    float stripe = ((float)DISPLAY_HEIGHT/13);
    for(int i = 0; i < 13; i+=stripe){
        if(i%2 == 0){
            display_draw_rectangle(0,i,DISPLAY_WIDTH, i + stripe,RED,true,1);
        }
    }
    display_draw_rectangle(0,0,(u_int16_t)(DISPLAY_WIDTH * .28), (u_int16_t)(DISPLAY_HEIGHT * .20),BLUE,true,1);
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 6; j++){
            display_draw_char(4*i,j*4,'*',&Font8,BLUE,WHITE);
        }
    }
    
}

// draw_menu
//
// Draw the menu of the screen. It uses the entries array to create the menu, with the num_entries
// specifying how many entries are in the entries array. The selected parameter is the item in the
// menu that is selected and should be highlighted. Use BACKGROUND_COLOR, FONT_COLOR,
// SELECTED_BG_COLOR, and SELECTED_FONT_COLOR to help specify the colors of the background, font,
// select bar color, and selected text color.
void drawMenu(char entries[][MAX_ENTRY_LENGTH], int num_entries, int selected) {
    // TODO: Put your code here
}

int main(void) {
    display_init();
    buttons_init();
    signal(SIGINT, intHandler);

    log_info("Starting...");

    

    while (true) {
        delay_ms(200);

        if (button_up() == 0) {
            clearScreen();
            

            while (button_up() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(1);
            }
        }
        if (button_right() == 0) {
            drawHelloWorld();
            

            while (button_right() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(1);
            }
        }
        if(button_down() == 0){
            drawChars();

            while(button_down() ==0){
                delay_ms(1);
            }
        }
        if(button_left() == 0){
            drawStars();

            while(button_left() ==0){
                delay_ms(1);
            }
        }
        if(button_center() == 0){
            drawFlag();

            while(button_center() ==0){
                delay_ms(1);
            }
        }
    }
    return 0;
}
