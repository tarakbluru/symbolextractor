@echo off

REM 
REM The MIT License (MIT)

REM Copyright (c) 2016 Tarakeshwar NC 

REM Permission is hereby granted, free of charge, to any person obtaining a copy of 
REM this software and associated documentation files (the "Software"), to deal in 
REM the Software without restriction, including without limitation the rights to 
REM use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
REM the Software, and to permit persons to whom the Software is furnished to do so, 
REM subject to the following conditions:

REM The above copyright notice and this permission notice shall be included in all 
REM copies or substantial portions of the Software.

REM THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
REM IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
REM FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
REM AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
REM LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
REM OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
REM SOFTWARE.
REM 

REM 
REM sym.bat - Creates a list of inputfiles a text file containing path to the 
REM to the data files. 
REM 

@echo off
dir /D /O:n /B %1\*.* > inputfiles.txt
echo %1 > inputfolder.txt

