//
//  user_interface.c
//  emc_smc
//
//  Created by fukai on 2018/10.
//  Copyright © 2018年 赛博智能车实验室. All rights reserved.
//

#include "headfile.h"
int duty=5000;

//结构体初始化
InterfaceCfgNode InterfaceCfg =
{
  .MenuStatus = INFO_WAITING,
  .LineStatus = LINE1,
};

//OLED界面显示
void OledDisplay(void)
{
  switch(InterfaceCfg.MenuStatus)
  {
  case INFO_WAITING:
		oled_p8x16str(30,3,"Waiting..");
		oled_p6x8str(14,5,"                            ");
		oled_p6x8str(15,6,"                           ");
    break;
    
    
  case INFO_SUCCESS:
		oled_p8x16str(30,3,"Success!!");
	oled_p6x8str(14,5,"id:");
	oled_p6x8str(15,6,"tempera:");
		oled_p6x8str(31,5,data_stream);
		oled_p6x8str(65,6,data_stream2);
		break;
	
	case INFO_NEXT:
		oled_fill(0);
		break;
	
	case INFO_WRONG:
		oled_p8x16str(30,3,"Warning!!");
	oled_p6x8str(14,5,"id:");
	oled_p6x8str(15,6,"tempera:");
		oled_p6x8str(31,5,data_stream);
		oled_p6x8str(65,6,data_stream2);
		break;
  }
}


//用户界面(OLED)
void UserInterfaceOled(void)
{
  //FunctionSelection();//功能选择
  //DebugParameter();//参数调节 
  OledDisplay();//OLED屏幕显示
}








