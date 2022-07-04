#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readAPTdatafile(const char InputFileName[]){
    // Open the file
    FILE *FileHandle = fopen(InputFileName, "rt");
    
    // If the file does not exist
    if(FileHandle==NULL){
        printf("File %s ot found\n",InputFileName);
        perror("ERROR!");
    }
    
    // count the number of lines in the file == number of atoms
    int numlines = 0;
    for (c = getc(FileHandle); c != EOF; c = getc(FileHandle)){
        if (c == '\n'){
            numlines+=1;
        }
    }
            
    // Seek the end of the file
    fseek(FileHandle, 0L, SEEK_END);
  
    // calculating the size of the file
    size_t filesize = (size_t)ftell(FileHandle);
    
    // gerate the temporary data pointers
    float *X, *Y, *Z, *QbyM ;
    char tmpbuff[filesize];
    
    // Generate the atom data buffers
    
    while(fgets(tmpbuff,filesize,FileHandle)){
        // read a line into many
        sscanf(tmpbuff,"%f %f %f %f",X,Y,Z,QbyM);
        
    }
    
}




int main()
{
	return 0;
}

