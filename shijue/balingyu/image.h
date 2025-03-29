#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// 数据类型声明
typedef signed char int8;
typedef signed short int int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
#define u8 uint8

// 定义常量
#define ROWS 60
#define COLS 94

#define image_h ROWS
#define image_w COLS

#define white_pixel 255
#define black_pixel 0

#define bin_jump_num 1       // 跳过的点数
#define border_max COLS-2    // 边界最大值
#define border_min 1         // 边界最小值

// 颜色定义
#define uesr_RED     0XF800  // 红色
#define uesr_GREEN   0X07E0  // 绿色
#define uesr_BLUE    0X001F  // 蓝色

// 函数声明
uint8 get_start_point(uint8 start_row, u8 data[ROWS][COLS]);
int my_abs(int value);
int16 limit_a_b(int16 x, int a, int b);
int16 limit1(int16 x, int16 y);
float Slope_Calculate(uint8 begin, uint8 end, uint8 *border);
void calculate_s_i(uint8 start, uint8 end, uint8 *border, float *slope_rate, float *intercept);
void search_l_r(uint16 break_flag, u8 data[ROWS][COLS], uint16 *l_stastic, uint16 *r_stastic, 
               uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y, uint8 *hightest);
void get_left(uint16 total_L);
void get_right(uint16 total_R);
void cross_fill(u8 data[ROWS][COLS], uint8 *l_border, uint8 *r_border, uint16 total_num_l, uint16 total_num_r,
               uint16 *dir_l, uint16 *dir_r, uint16(*points_l)[2], uint16(*points_r)[2]);

// 外部变量声明
extern uint8 start_point_l[2];
extern uint8 start_point_r[2];
extern uint16 points_l[300][2];
extern uint16 points_r[300][2];
extern uint16 dir_l[300];
extern uint16 dir_r[300];
extern uint16 data_stastics_l;
extern uint16 data_stastics_r;
extern uint8 l_border[ROWS];
extern uint8 r_border[ROWS];
extern uint8 center_line[ROWS];

// 新增结构体封装边界点
typedef struct {
    uint8 x;
    uint8 y;
} BoundaryPoint;

// 修改函数声明为可重入版本
uint8 find_boundary_points(uint8 start_row, const u8 data[ROWS][COLS], 
                         BoundaryPoint* left, BoundaryPoint* right);
#endif
