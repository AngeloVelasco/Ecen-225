/*
This is the driver file for the image library. All function definitions live in here
*/

#include <stdlib.h>
#include <string.h>

#include "image.h"

// --------------------------------------------------------------------------
// Image loading/saving functions
// --------------------------------------------------------------------------

uint8_t load_img(char *filepath, Bitmap *bmp) {
    // Opens file if it exists
    if (!(bmp->img = fopen(filepath, "r"))) {
        return LOAD_ERROR;
    }

    // Read in the bitmap file header
    fread(bmp->file_header, sizeof(uint8_t), BMP_FILE_HEADER_SIZE, bmp->img);

    // Get filesize
    bmp->file_size = (bmp->file_header[5] << 8 * 3) | (bmp->file_header[4] << 8 * 2) |
                     (bmp->file_header[3] << 8 * 1) | (bmp->file_header[2]);

    // Get start location of pixel data
    bmp->pxl_data_offset = (bmp->file_header[13] << 8 * 3) | (bmp->file_header[12] << 8 * 2) |
                           (bmp->file_header[11] << 8 * 1) | (bmp->file_header[10]);

    // Get DIB header data
    uint8_t dib_header_size = bmp->pxl_data_offset - BMP_FILE_HEADER_SIZE;
    bmp->dib_header = (uint8_t *)malloc((dib_header_size) * sizeof(uint8_t));
    fread(bmp->dib_header, sizeof(uint8_t), dib_header_size, bmp->img);

    // Get image width
    bmp->img_width = (bmp->dib_header[7] << 8 * 3) | (bmp->dib_header[6] << 8 * 2) |
                     (bmp->dib_header[5] << 8 * 1) | (bmp->dib_header[4]);

    // Get image height
    bmp->img_height = (bmp->dib_header[11] << 8 * 3) | (bmp->dib_header[10] << 8 * 2) |
                      (bmp->dib_header[9] << 8 * 1) | (bmp->dib_header[8]);

    // Get image data
    bmp->pxl_data_size = bmp->img_width * bmp->img_height * 3;
    bmp->pxl_data = (uint8_t *)malloc(sizeof(uint8_t) * bmp->pxl_data_size);
    fread(bmp->pxl_data, sizeof(uint8_t), bmp->pxl_data_size, bmp->img);

    // Create copy of image data for reset
    bmp->pxl_data_cpy = (uint8_t *)malloc(sizeof(uint8_t) * bmp->pxl_data_size);
    bmp->pxl_data_cpy = memcpy(bmp->pxl_data_cpy, bmp->pxl_data, bmp->pxl_data_size);

    // Close the file
    fclose(bmp->img);

    return LOAD_SUCCESS;
}

void reset_pixel_data(Bitmap *bmp) {
    memcpy(bmp->pxl_data, bmp->pxl_data_cpy, bmp->pxl_data_size);
}

uint8_t save_img(char *imgname, Bitmap *bmp) {
    FILE *save_img;
    if (!(save_img = fopen(imgname, "w"))) {
        fprintf(stderr, "Could not save the file with that name. Change the name and try again.\n");
        return SAVE_ERROR;
    }

    // Write BMP header
    fwrite(bmp->file_header, sizeof(uint8_t), BMP_FILE_HEADER_SIZE, save_img);

    // Write DIB header
    fwrite(bmp->dib_header, sizeof(uint8_t), bmp->pxl_data_offset - BMP_FILE_HEADER_SIZE, save_img);

    // Write pixel data
    fwrite(bmp->pxl_data, sizeof(uint8_t), bmp->pxl_data_size, save_img);

    // Close the file
    fclose(save_img);
    return SAVE_SUCCESS;
}

void close_img(Bitmap *bmp) {
    free(bmp->dib_header);
    free(bmp->pxl_data);
    free(bmp->pxl_data_cpy);
}

// --------------------------------------------------------------------------
// Image manipulation functions
// --------------------------------------------------------------------------

void remove_color_channel(Color color, Bitmap *bmp) {
    // TODO: Put code here
    if (color == BLUE_CHANNEL){
        for( int y = 0; y < bmp->img_height; y++){
            for(int x = 0; x < bmp->img_width; x++){
                int index = (y * bmp->img_width + x) * 3;
                bmp->pxl_data[index] = 0;
            }
        }
    } 

    if (color == GREEN_CHANNEL){
         for( int y = 0; y < bmp->img_height; y++){
            for(int x = 0; x < bmp->img_width; x++){
                int index = (y * bmp->img_width + x) * 3;
                bmp->pxl_data[index + 1] = 0;
            }
        }
       
    }
    
    if(color == RED_CHANNEL){
         for( int y = 0; y < bmp->img_height; y++){
            for(int x = 0; x < bmp->img_width; x++){
                int index = (y * bmp->img_width + x) * 3;
                bmp->pxl_data[index + 2] = 0;
            }
        }
    }

}

void grayscale(Bitmap *bmp) {
    // TODO: Put code here
    for( int y = 0; y < bmp->img_height; y++){
        for(int x = 0; x < bmp->img_width; x++){
            int index = (y * bmp->img_width + x) * 3;
            float gandalfthegrey = ((bmp->pxl_data[index] * 0.114) +(bmp->pxl_data[index + 1] * 0.587) + (bmp->pxl_data[index + 2] * 0.299));
            bmp->pxl_data[index] = gandalfthegrey;
            bmp->pxl_data[index + 1] = gandalfthegrey;
            bmp->pxl_data[index + 2] = gandalfthegrey;
        }
    }
}

void or_filter(Bitmap *bmp) {
    // TODO: Put code here
    for(int y = 0; y < bmp->img_height; y++){
        for(int x = 0; x < bmp->img_width; x++ ){
            int index = (y * bmp->img_width + x) * 3;
            int indexUnder = ((y+1) * bmp->img_width + x) * 3;
            int indexAbove = ((y-1) * bmp->img_width + x) * 3;

            //top row 
            if( y == 0){
                u_int8_t current = bmp->pxl_data_cpy[index];
                u_int8_t below = bmp->pxl_data_cpy[indexUnder];
                u_int8_t mask = (current | below);

                current = bmp->pxl_data_cpy[index + 1];
                below = bmp->pxl_data_cpy[indexUnder + 1];
                u_int8_t maskGreen = (current | below);

                current = bmp->pxl_data_cpy[index + 2];
                below = bmp->pxl_data_cpy[indexUnder + 2];
                u_int8_t maskRed = (current | below);

                bmp->pxl_data[index] = mask;
                bmp->pxl_data[index + 1] = maskGreen;
                bmp->pxl_data[index + 2] = maskRed;


            }else if(y == bmp->img_height -1 ){
                u_int8_t current = bmp->pxl_data_cpy[index];
                u_int8_t above = bmp->pxl_data_cpy[indexAbove];
                u_int8_t mask = (current | above);

                current = bmp->pxl_data_cpy[index + 1];
                above = bmp->pxl_data_cpy[indexAbove + 1];
                u_int8_t maskGreen = (current | above);

                current = bmp->pxl_data_cpy[index + 2];
                above = bmp->pxl_data_cpy[indexAbove + 2];
                u_int8_t maskRed = (current | above);

                bmp->pxl_data[index] = mask;
                bmp->pxl_data[index + 1] = maskGreen;
                bmp->pxl_data[index + 2] = maskRed;
            }

            // middle row
            else{
                u_int8_t blue = bmp->pxl_data_cpy[index];
                u_int8_t green = bmp->pxl_data_cpy[index + 1];
                u_int8_t red = bmp->pxl_data_cpy[index + 2];
                
                u_int8_t heaven = bmp->pxl_data_cpy[indexAbove];
                u_int8_t landDownUnder = bmp->pxl_data_cpy[indexUnder];
                u_int8_t finalBlue = (blue | heaven | landDownUnder);

                heaven = bmp->pxl_data_cpy[indexAbove + 1 ];
                landDownUnder = bmp->pxl_data_cpy[indexUnder + 1];
                u_int8_t finalGreen = (green | heaven | landDownUnder);

                heaven = bmp->pxl_data_cpy[indexAbove + 2 ];
                landDownUnder = bmp->pxl_data_cpy[indexUnder + 2];
                u_int8_t finalRed = (red | heaven | landDownUnder);

              

            

                bmp->pxl_data[index] = finalBlue;
                bmp->pxl_data[index + 1] = finalGreen;
                bmp->pxl_data[index + 2] = finalRed;
            }

        }
    }
}
