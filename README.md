# symbolextractor

Extracts symbols from the set of Data files

Build:
gcc -o symextract.exe sym_extractor.c

To Run:

1. run the command 
   sym datafolder
      
   eg.- sym f:\Tarak\Market\gfdl\ieod

  This step creates 2 files:    
   inputfolder.txt - has path to the data files folder
   inputfiles.txt - has list of files
2. update - inputfiles.txt - to select the files.
3. symbol.txt - has symbols that needs to be extracted
4. run the command 
   symextract.exe - 
This step creates the extracted symbol file.
