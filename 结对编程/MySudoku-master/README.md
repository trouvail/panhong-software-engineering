# MySudoku 
数独终局的生成和求解项目
## intro
* BIN目录放置可执行的二进制文件，链接库和生成的数独终局,TEST存放单元测试文件
* 根目录放置代码和头文件
* 运行时请通过命令行运行**bin**目录下的可执行文件，使用 ./sudoku -c N生成终局，./sudoku -s PATH求解数独
## environment
* win10 1903
* C++
* VS2019
## struct
|———README.md  
|———BIN  
|>>>|———sudoku.exe  
|>>>|———sudoku.txt  
|>>>|———sudoku_finality.txt  
|>>>|———ques.txt  
|———TEST  
|>>>|———pch.h  
|>>>|———pch.cpp  
|>>>|———UnitTest.cpp    //测试函数  
|>>>|———pro.txt   //这是格式有问题的数独  
|>>>|———ques.txt    //这是格式正确的数独  
|———main.cpp  
|———head.h  
|———func.cpp  
## tips
1. 生成的数独终局起名为sudoku_finality.txt,解决后的为sudoku.txt原因是个人文档中说的是例如使用sudoku.txt，但解决后的数独要求为sudoku.txt，为了防止重名，故分开。
2. ques.txt中有1000个数独题目。
3. 注意题目的要求，由于个人项目的pdf中要求问题之间空一行，但是示例中没空行，这里我默认使用的是空行的文件。也就是生成的和解决后的文件终局之间空了一行。**若题目文件没有空行将会导致程序错误，请务必注意。**
4. #define _CRT_SECURE_NO_WARNINGS 是为了防止VS2019出现报错，如果不定义可能会导致类似于需要使用fopen_s不能使用fopen的错误。如果出现类似警告可以将编译改成Release
