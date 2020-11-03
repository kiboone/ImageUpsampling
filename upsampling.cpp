#include <iostream>
#include <vector>
#include <utility> 
#include <math.h> 
#include <algorithm> 
#include <stdlib.h>
#include <fstream>

using namespace std;

int* nearestNeighbor(int, int, int[], int);

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
        infile >> comma;
        pixels[i] = pix;
    }
    cout << "check1\n";

    // Nearest Neighbor
    int new_size = array_size * 2;
    int* nn_pixels_1d = nearestNeighbor(array_size, new_size, pixels, 2);
    // for (int i = 0;i < new_size* new_size; i++){
    //     cout << nn_pixels_1d[i] << " ";
    // }
    int nn_pixels[new_size][new_size];
    int idx = 0;
    for(int i = 0; i < array_size; i++){
        for(int j = 0; j < array_size; j++){
            nn_pixels[i][j] = nn_pixels_1d[idx];
            idx++;
        }
    }

    for(int i = 0; i < array_size; i++){
        for(int j = 0; j < array_size; j++){
            cout << nn_pixels[i][j] << " ";
        }
        cout << endl;
    }
    // Print pixels to output file
    for(int i = 0; i < array_size; i++){
        for(int j = 0; j < array_size; j++){
            outfile << nn_pixels[i][j] << " ";
        }
        outfile << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}


int* nearestNeighbor(int array_size, int new_size, int* pixels, int ratio) {
    cout << "check2\n";

    // int temp[new_size * new_size];
    // double ratio = 2 ;
    // double px, py; 
    // for (int i = 0; i < new_size; i++) {
    //     for (int j = 0; j < new_size; j++) {
    //         cout << "woo\n";
    //         px = floor(j * ratio) ;
    //         py = floor(i * ratio) ;
    //         temp[(i * new_size) + j] = pixels[(int)((py * array_size) + px)] ;
    //     }
    // }
    // pixels = temp;

    int temp[new_size * new_size] ;
    
    double x_ratio = array_size/(double)new_size ;
    double y_ratio = array_size/(double)new_size ;
    double px, py ; 
    for (int i=0;i<new_size;i++) {
        for (int j=0;j<new_size;j++) {
            px = floor(j*x_ratio) ;
            py = floor(i*y_ratio) ;
            temp[(i*new_size)+j] = pixels[(int)((py*array_size)+px)] ;
        }
    }
    pixels = temp;
    cout << "check3\n";
    return pixels ;
}