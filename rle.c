#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1024

int main( int argc, char* argv[] ){

    char* inputFile = argv[1];
    char* outputFile = argv[2];
    int rnl = atoi(argv[3]);
    int mode = atoi(argv[4]);

    if( argc !=5){
        perror("Not enough/too many command arguments: rle <input file> <output file> <compression length> <mode>\n");
        exit(-1);
    }

    int inFD = open( inputFile, O_RDONLY );
    if( inFD == -1 ){
        perror("Could not open input file");
        exit(-1);
    }
    int outFD = open( outputFile, 
            O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR);
    if( outFD == -1 ){
        perror("Could not open output file");
        exit(-1);
    }   
    char bufferK [BUFFERSIZE];
    char bufferNK [BUFFERSIZE];

    int counter = 1;
    if (mode == 0){
        ssize_t r = read(inFD, bufferNK, rnl);
        if( r == -1 ){
            perror("Could not read from input file");
            exit(-1);
        }
        if(r == 0){
            exit(-1);
        }

        while(1){
            ssize_t compressK = read(inFD, bufferK, rnl);  
            if( compressK == -1 ){
                perror("Could not read from input file");
                exit(-1);
            }
            if(compressK == 0){
                break;
            }

            int strCompare = strncmp(bufferK , bufferNK, rnl );
            if (strCompare == 0){  //Pattern Match
                counter++;   
                continue;
            }   
            else { //pattern does not match
                ssize_t Wcounter = write(outFD, &counter, 1);
                if( compressK == -1 ){
                    perror("Could not write to output file");
                    exit(-1);
                }

                ssize_t WbufferNK = write(outFD, bufferNK, rnl);
                if( WbufferNK == -1 ){
                    perror("Could not write to output file");
                    exit(-1);
                }

                counter = 1;
                strncpy(bufferNK, bufferK, rnl);
                continue;
            }

        }
    }
    int decounter = 1;
    while(mode == 1){
        ssize_t decompressK = read(inFD, &decounter, 1);  
        if( decompressK == -1 ){
            perror("Could not read from input file");
            exit(-1);
        }

        if(decompressK ==0){
            break;
        }
        ssize_t decompressNK = read(inFD, bufferNK, rnl);            
        if( decompressNK == -1 ){
            perror("Could not read from input file");
            exit(-1);
        }

        for ( int i= 0; i< decounter; i++){
            ssize_t w =  write(outFD, bufferNK,rnl);
            if( w == -1 ){
                perror("Could not write to output file");
                exit(-1);
            }    
        }

    }

    return 0;
}

