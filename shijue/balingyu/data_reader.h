#ifndef DATA_READER_H
#define DATA_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Windows系统需要的头文件
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// 使用与image.h相同的常量定义
#define ROWS 60
#define COLS 94

// 避免PATH_MAX重复定义
#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

// 使用相同的类型定义
#define uint8 unsigned char
#define u8 uint8

// 函数声明
char* getCurrentDirectory();
int readDataFromFile(const char* filename, u8 data[ROWS][COLS]);
void printData(u8 data[ROWS][COLS]);
void printRow(uint8 row, u8 data[ROWS][COLS]);

#endif

