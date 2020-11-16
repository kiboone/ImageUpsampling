# ImageUpsampling
Program to upsample gray-scale image using Nearest Neighbor algorithm

**Input** - Text file with 256 * 256 comma separated RGB values  
**Output** - Text file with 512 * 512 comma separated RGB values

## Makefile
`make` Compiles Upsampling program into executable  
`make test` Produces output of GoogleTest run    
`make coverage` Produces gcovr code coverage output  
`make metric` Compiles program to compute L1 Metric

`make clean` Cleans files created by `make`  
`make cleanmet` Cleans files created by `make metric`  
`make cleantest` Cleans files created by `make test`  
`make cleancov` Cleans files created by `make coverage`  

## Execution
`main inputfile.txt outputfile.txt` to run Upsampling program  
