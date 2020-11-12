/*
    Driver file for upsampling
*/

#include <iostream>
#include <vector>
#include <utility> 
#include <math.h> 
#include <algorithm> 
#include <stdlib.h>
#include <fstream>
#include "functions.cpp"

using namespace std;

int* nearestNeighbor(int, int, int[]);
int* bilinear(int, int, int*);

int main(int argc, char ** argv){
    int pix;
    char comma;
    // int pixels[array_size][array_size];

    int array_size = 256;
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

    // Export to file
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
