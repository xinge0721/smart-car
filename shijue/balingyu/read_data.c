#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define ROWS 60
#define COLS 94
#define u8 unsigned char

// 定义坐标点结构体
typedef struct 
{
    u8 x;
    u8 y;
} xy_t;

// 定义边缘结构体
typedef struct 
{
    xy_t left;
    xy_t right;   
} edge_t;


bool fopen_data(int data[ROWS][COLS])
{

    FILE *file = fopen("G:\\bianchen\\xiangmu\\smart car\\shijue\\balingyu\\data.txt", "r");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return false;
    }
        
    // 读取数据
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (fscanf(file, "%d", &data[i][j]) != 1) {
                printf("读取文件错误，请检查文件格式！\n");
                fclose(file);
                return false;
            }
        }
    }
    
    // 关闭文件
    fclose(file);
    return true;
}

void print_data(int data[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (data[i][j] == 0) {
                printf("\033[47m  \033[0m");  // 白色底色
            } else if (data[i][j] == 255) {
                printf("\033[40m  \033[0m");  // 黑色底色
            } else if (data[i][j] == 99) {
                printf("\033[41m  \033[0m");  // 红色底色
            }
        }
        printf("\n");  // 每行结束后换行
    }
}   

//查找 row_index 行最左,最右边的白色边缘并记录到edge结构体 
void mark_white_edges(int data[ROWS][COLS], int row_index, edge_t *edge)
{
    assert(data != NULL);
    assert(row_index >= 0 && row_index < ROWS);
    assert(edge != NULL);

    // 查找最左值
    for(int j = COLS / 2; j >= 0; j--)
    {
        if(data[row_index][j] == 0 && data[row_index][j - 1] != 255)
        {
            data[row_index][j] = 99;
            edge->left.x = j;
            edge->left.y = row_index;
            break;
        }
    }

    // 查找最右值
    for(int j = COLS / 2; j < COLS ; j++)
    {
        if(data[row_index][j] == 0 && data[row_index][j + 1] != 255)
        {   
            data[row_index][j] = 99;
            edge->right.x = j;
            edge->right.y = row_index;
            break;
        }
    }   
}

int main() {
    // 声明二维数组
    int data[ROWS][COLS];
    edge_t edge = {0};  // 只使用一个边缘结构体
    
    if (!fopen_data(data)) {
        return 1;
    }

    print_data(data);

    // 对第59行（索引为58）进行边缘标记
    mark_white_edges(data, 59, &edge);

    printf("----------------------------------\n");
    printf("左边缘坐标: (%d, %d)\n", edge.left.x, edge.left.y);
    printf("右边缘坐标: (%d, %d)\n", edge.right.x, edge.right.y);
    printf("----------------------------------\n");

    print_data(data);

    return 0;
} 