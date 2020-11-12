/*
    Seperate file for upsampling algorithms for ease of unit testing
        - Nearest Neighbor Upsampling
        - Bilinear Upsampling
*/
#include <math.h> 

int* nearestNeighbor(int array_size, int new_size, int* pixels) {
    int* temp  = new int[new_size * new_size] ;
    double ratio = array_size/(double)new_size ;
    double px, py ; 
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            px = floor(j * ratio) ;
            py = floor(i * ratio) ;
            temp[(i * new_size) + j] = pixels[(int)((py * array_size) + px)] ;
        }
    }
    return temp ;
}


int* bilinear(int array_size, int new_size, int* pixels) {
    int * temp = new int[new_size * new_size];
    int A, B, C, D, x, y, index, pix;
    float x_ratio = ((float)(array_size - 1))/ new_size;
    float y_ratio = ((float)(array_size - 1))/ new_size;
    float x_diff, y_diff, ya, yb;
    int offset = 0 ;
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            x = (int)(x_ratio * j);
            y = (int)(y_ratio * i);
            x_diff = (x_ratio * j) - x;
            y_diff = (y_ratio * i) - y;
            index = y * array_size + x;

            A = pixels[index] & 0xff;
            B = pixels[index+1] & 0xff;
            C = pixels[index + array_size] & 0xff;
            D = pixels[index + array_size + 1] & 0xff;
            
            pix = (int)(
                    A*(1-x_diff)*(1-y_diff) +  B*(x_diff)*(1-y_diff) +
                    C*(y_diff)*(1-x_diff)   +  D*(x_diff*y_diff)
                    );

            temp[offset++] = pix;                                   
        }
    }
    return temp;
}