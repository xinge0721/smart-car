#include "image.h"
#include "data_reader.h"

#define bin_jump_num	1//跳过的点数
#define border_max	COLS-2 //边界最大值
#define border_min	1	//边界最小值	

/*
函数名称：void get_start_point(uint8 start_row)
功能说明：寻找两个边界的边界点作为八邻域循环的起始点
参数说明：输入任意行数
函数返回：无
修改时间：2022年9月8日
备    注：
example：  get_start_point(image_h-2)
 */
// 移除全局变量start_point_l/start_point_r

uint8 find_boundary_points(uint8 start_row, const u8 data[ROWS][COLS],
                         BoundaryPoint* left, BoundaryPoint* right) 
{
    // 修改实现逻辑使用指针参数
    uint8 l_found = 0, r_found = 0;
    
    // 保留原有搜索逻辑，但修改为：
    if (data[start_row][i] == 0 && data[start_row][i - 1] == 255) {
        left->x = i;
        left->y = start_row;
        l_found = 1;
        break;
    }

    // 右边同理...
}
