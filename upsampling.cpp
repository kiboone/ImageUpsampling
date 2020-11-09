#include <iostream>
#include <vector>
#include <utility> 
#include <math.h> 
#include <algorithm> 
#include <stdlib.h>
#include <fstream>

using namespace std;

int* nearestNeighbor(int, int, int[]);
int* bilinear(int, int, int*);

int main(int argc, char ** argv){
    int pix;
    char comma;
    // int pixels[array_size][array_size];

    int array_size = 4;
    int pixels[array_size * array_size];

    if (argc != 3) {    
        cout << "Usage: main input.txt output.txt\n";
        return 0;
    }

    ifstream infile;
    ofstream outfile;

    char * infilestr  = argv[1];
    char * outfilestr = argv[2];

    infile.open(infilestr);
    outfile.open(outfilestr);
    if (!infile) {
        cout << infilestr << " could not be opened\n";
        exit(0);	
    }

    // Input RBG values from input file
    for(int i = 0; i < array_size * array_size; i++){
        infile >> pix;
        if(infile.peek() == ',') {
            infile >> comma;
        }
        pixels[i] = pix;
    }

    int new_size = array_size * 2;
    int nn_pixels[new_size][new_size];


    /* Image Upsampling Function Calls */
    int* nn_pixels_1d = nearestNeighbor(array_size, new_size, pixels);
    // int* nn_pixels_1d = bilinear(array_size, new_size, pixels);
    

    // Convert to 2D array
    int idx = 0;
    for(int i = 0; i < new_size; i++){
        for(int j = 0; j < new_size; j++){
            nn_pixels[i][j] = nn_pixels_1d[idx];
            idx++;
        }
    }

    idx = 0;
    for(int i = 0; i < new_size; i++){
        for(int j = 0; j < new_size; j++){
            outfile << nn_pixels[i][j] << ",";
        }
        outfile << endl;
    }


    infile.close();
    outfile.close();
    return 0;
}


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
    int A, B, C, D, x, y, index, gray;
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
