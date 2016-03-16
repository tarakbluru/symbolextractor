/*
********************************************************************************
The MIT License (MIT)

Copyright (c) 2016 Tarakeshwar NC 

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*******************************************************************************
*/

/*
*******************************************************************************
sym_extractor.c - Extracts a particular symbol from the set of GFDL provided 
data. 
Assumption:  RAR files are already converted into .csv files.
*******************************************************************************
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define INPUT_FILES     "inputfiles.txt"
#define SYMBOL          "symbol.txt"
#define INPUT_FOLDER    "inputfolder.txt"
#define BUF_SIZE        (1024u)

int main ( void )
{
    char folder [BUF_SIZE];
    char tmpname [BUF_SIZE];
    char filelist[BUF_SIZE];
    char outfile [BUF_SIZE];
    char symname [BUF_SIZE];
    char data    [BUF_SIZE];
    int retval = 0;
    int header;
    
    FILE* finputfiles = NULL; 
    FILE* fsymbolfile = NULL;
    FILE* ffolderfile = NULL;
    FILE* fout = NULL;
    
        /*Open the input files */
    finputfiles = fopen (INPUT_FILES, "r");
    if(finputfiles == NULL) {
        printf ("Not able to open %s ", INPUT_FILES);
	retval = -1;
        goto BAIL_OUT;
    }
        fsymbolfile = fopen (SYMBOL, "r");
    if(fsymbolfile  == NULL) {
        printf ("Not able to open %s ", SYMBOL);
	retval = -2;
        goto BAIL_OUT;
    }
    ffolderfile = fopen (INPUT_FOLDER, "r");
    if (ffolderfile == NULL) {
        printf ("Not able to open %s ", INPUT_FOLDER);
        retval = -3;
	goto BAIL_OUT;
    }

    /*Initialize the buffers */
    memset(folder,0x0,sizeof(folder));
    memset(tmpname, 0x0, sizeof(tmpname));
    memset(filelist,0x0, sizeof(filelist));
    memset(outfile, 0x0, sizeof(outfile));
    memset(symname, 0x0, sizeof(symname));
    memset(data, 0x0, sizeof(data));
    
    if ( fscanf(ffolderfile,"%s",folder) != EOF ) {
        strcat(folder,"\\");
    }
    fclose(ffolderfile); ffolderfile = NULL;
    /*
     *   for all symbols
     *       open the outputfile
     *       Add the header
     *       go thru each of input file
     *       if the line contains symbol then write the line
    */
    while (!feof(fsymbolfile)) {
        if (fscanf(fsymbolfile, "%s", symname) != EOF ){
            strcpy (outfile, symname);
            strcat (outfile, ".csv");
            strcat (symname, ",");  // Add comma to search pattern NIFTY-I, this
                                    // avoids NIFTY-II and NIFTY-III
            fout = fopen (outfile,"w");
            printf("Extracting symbol :: %s into %s \n", symname, outfile);
            if (fout == NULL) {
                printf("Not able to open %s \n", outfile);
		retval = -4;
                goto BAIL_OUT;
            }
            header = 0;
            while (!feof(finputfiles)){
                if (fscanf(finputfiles, "%s", filelist) != EOF) {
                    FILE* fin;
                    strcpy (tmpname, folder);
                    strcat (tmpname, filelist);
                    fin = fopen(tmpname, "r");
                    printf ("Opening the file %s \n", tmpname);
                    if (fin == NULL) {
                        printf("Not able to open %s \n", tmpname);
			retval = -5;
                        goto BAIL_OUT;
                    }
                    while (!feof(fin)) {
                        fgets(data, BUF_SIZE, fin);
                        if (header == 0) {
                            fwrite(data, strlen(data), 1, fout);
                            header = 1;
                        }
                        if (strstr (data, symname) == data) {
                            fwrite(data, strlen(data), 1, fout);
                        }
                    }
                    fclose(fin);
                }
            }
            fclose (fout);
            rewind(finputfiles);
        }
    }

BAIL_OUT:
    if(finputfiles != NULL) {
        fclose (finputfiles);
    }
    if(fsymbolfile  != NULL) {
        fclose (fsymbolfile);
    }
    if (ffolderfile != NULL) {
        fclose (ffolderfile);
    }

    return retval;
}/*main*/
