#include "image.h"

#include <stdio.h>

int main() {
    // Allocate memory for struct
    Bitmap original_image;

    // Load data from an image file into a struct
    if (load_img("./original.bmp", &original_image) == LOAD_ERROR) {
        printf("Unable to load image. Exiting...");
        return 1;
    }

    // Remove only the red color channel from the image
    remove_color_channel(RED_CHANNEL, &original_image);
    // Save the modified image to the file "red_mask.bmp"

    if (save_img("red_mask.bmp", &original_image) == SAVE_ERROR) {
        printf("Unable to save image. Exiting...");
        return 1;
    }
    // Revert the image back to the original
    reset_pixel_data(&original_image);

    remove_color_channel(GREEN_CHANNEL, &original_image);

    if(save_img("green_mask.bmp", &original_image)==SAVE_ERROR){
        printf("Unable to save image. Exiting...");
        return 1;
    }

    reset_pixel_data(&original_image);

    remove_color_channel(BLUE_CHANNEL, &original_image);

    if(save_img("blue_mask.bmp", &original_image)==SAVE_ERROR){
        printf("Unable to save image. Exiting...");
        return 1;
    }

    reset_pixel_data(&original_image);

    grayscale(&original_image);

    if(save_img("grayscale.bmp",&original_image)){
        printf("Unable to save image. Exiting...");
        return 1;
    }

    reset_pixel_data(&original_image);

    or_filter(&original_image);

    if(save_img("or_filter.bmp",&original_image)){
        printf("Unable to save image. Exiting..");
        return 1;
    }

    reset_pixel_data(&original_image);

    // TODO:
    // Run "or filter" function on bitmap image
    // Save the modified image to the file "or_filter.bmp"
    // Revert the image back to the original

    // Clean up the memory
    close_img(&original_image);

    return 0;
}
