#include "data_reader.h"
#include "image.h"


// 获取当前工作目录
char* getCurrentDirectory() {
    char* currentPath = (char*)malloc(PATH_MAX);
    if (currentPath == NULL) {
        return NULL;
    }
    
    if (GetCurrentDir(currentPath, PATH_MAX) == NULL) {
        free(currentPath);
        return NULL;
    }
    
    return currentPath;
}

// 读取文件数据到二维数组
int readDataFromFile(const char* filename,u8 data[ROWS][COLS]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        printf("请确保文件存在且路径正确\n");
        return 0;
    }
    
    printf("正在读取文件: %s\n", filename);
    
    // 读取文件中的数据到二维数组
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (fscanf(file, "%d", &data[i][j]) != 1) {
                printf("读取数据出错，行 %d, 列 %d\n", i+1, j+1);
                fclose(file);
                return 0;
            }
        }
    }
    
    fclose(file);
    return 1;
}

// 打印二维数组
void printData(u8 data[ROWS][COLS]) {
    // 清除控制台
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    printf("数据内容 (%d 行 x %d 列):\n", ROWS, COLS);
    
    // 打印数组
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if(data[i][j] == 0){
                // 黑底白字显示0
                printf("\033[40;37m 0 \033[0m");
            }
            else if(data[i][j] == '@'){
                // 红底白字显示边界点
                printf("\033[41;37m @ \033[0m");
            }
            else{
                // 白底黑字显示#代表255
                printf("\033[47;30m # \033[0m");
            }
        }
        printf("\n");
    }
}

// 打印数组中的某一行
void printRow(uint8 row, u8 data[ROWS][COLS]) {
    // 检查行号是否有效
    if (row >= ROWS) {
        printf("错误：行号 %d 超出范围（0-%d）\n", row, ROWS - 1);
        return;
    }
    
    printf("第 %d 行数据: ", row);
    
    // 打印该行的所有数据
    for (int j = 0; j < COLS; j++) {
        if(data[row][j] == 0){
            // 黑底白字显示0
            printf("\033[40;37m 0 \033[0m");
        }
        else if(data[row][j] == '@'){
            // 红底白字显示边界点
            printf("\033[41;37m @ \033[0m");
        }
        else{
            // 白底黑字显示#代表255
            printf("\033[47;30m # \033[0m");
        }
    }
    printf("\n");
}

int main() {
    // 使用绝对路径
    // 全局二维数组
    u8 data[ROWS][COLS];
    const char* filename = "G:/bianchen/xiangmu/smart car/shijue/balingyu/data.txt";
        if (readDataFromFile(filename,data)) {
            printf("文件读取成功!\n");
            
            printRow(ROWS-1, data);

            get_start_point(ROWS-1,data);
            
            // 打印查找边界后的最后一行数据
            printRow(ROWS-1, data);
            
            printData(data);

        } else {
            printf("文件读取失败!\n");
        }

    // 修改调用方式
    BoundaryPoint left = {0}, right = {0};
    if(find_boundary_points(ROWS-1, data, &left, &right)) {
        printf("找到边界点：左(%d,%d) 右(%d,%d)\n", 
              left.x, left.y, right.x, right.y);
    }
    
    return 0;
}