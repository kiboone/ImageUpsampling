/*
    Compute L1 Metric between two pixel arrays 
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

    int array_size = 512;
    int og[array_size * array_size];
    int out[array_size * array_size];

    int L1 = 0;

    if (argc != 3) {    
        cout << "Usage: main original.txt output.txt\n";
        return 0;
    }

    // File Input
    ifstream ogfile;
    ifstream outfile;
    char * ogfilestr  = argv[1];
    char * outfilestr = argv[2];
    ogfile.open(ogfilestr);
    outfile.open(outfilestr);
    if (!ogfile) {
        cout << ogfilestr << " could not be opened\n";
        exit(0);	
    }
    if (!outfile) {
        cout << outfilestr << " could not be opened\n";
        exit(0);	
    }

    // Input RBG values from input files
    for(int i = 0; i < array_size * array_size; i++){
        ogfile >> pix;
        if(ogfile.peek() == ',') {
            ogfile >> comma;
        }
        og[i] = pix;
    }
    for(int i = 0; i < array_size * array_size; i++){
        outfile >> pix;
        if(outfile.peek() == ',') {
            outfile >> comma;
        }
        out[i] = pix;
    }


    // Compute L1 Metric
    for(int i = 0; i < array_size * array_size; i++){
        L1 += abs(og[i] - out[i]);
    }

    cout << "L1 Metric: " << L1 << endl;

    ogfile.close();
    outfile.close();
    return 0;
}
