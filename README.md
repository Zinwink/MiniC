# MiniC

## build environment
Windows WSL2 Ubuntu22.04
clang version 14.0.0

## How to build
- Generate build information in the build folder  
```bash
cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Release
# use this command int the folder where CMakeList.txt is located 
```

- build project
```bash
cmake --build build/
```

## Usage
- Generate AST image
```bash
./minic -S -a -o imgPath/fileName.png sourcePath/sourceCode.c   
```
- Generate LLVMIR
```bash
./minic -S -I -o imgPath/fileName.ll sourcePath/sourceCode.c  
```
- Generate control flow graph
```bash
./minic -c functionName [-o fileName.png] sourcePath/sourceCode.c
```
- Generate Arm32
```bash
./minic -S [-o Path/fileName.s] sourcePath/sourceCode.c
```




