//
//  user_interface.h
//  emc_smc
//
//  Created by fukai on 2018/10.
//  Copyright © 2018年 赛博智能车实验室. All rights reserved.
//

#ifndef user_interface_h
#define user_interface_h



//菜单显示状态
typedef enum
{
    INFO_WAITING = 0,
    INFO_SUCCESS,
    INFO_NEXT,
		INFO_WRONG,
}MenuStatusNode;

//行显示状态
typedef enum
{
    LINE1 = 0,
    LINE2,
    LINE3,
    LINE4,
    LINE5,
    LINE6,
    LINE7,
    LINE8,
}LineStatusNode;

//显示界面配置结构体
//定义显示的菜单，行数
typedef struct
{
    MenuStatusNode MenuStatus;
    LineStatusNode LineStatus;
}InterfaceCfgNode;

extern InterfaceCfgNode InterfaceCfg;
extern int duty;
void UserInterfaceOled(void);//用户界面(OLED)


#endif


