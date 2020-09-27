/***************************************************************
 * Galaxy_Core.h
 *
 * Copyright (C) 2020 Francois Alex Hao <he.hao@faurecia.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 or version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
***************************************************************/
#ifndef _GALAXY_CORE_H_
#define _GALAXY_CORE_H_

#include <unistd.h>
#include "Galaxy_Ulitity.h"
#include "Galaxy_Err.h"


class Core_Process
{
public:
    void Algorithm_Input(unsigned int speed);
	void Cruis_Level_Set(Cruis_Speed_Level level);
	Sys_Err_Type Algorithm_Init(uint_16 range);
	void Algorithm_Reset(void);
	static DWORD CALLBACK SpeedThread(LPVOID);

private:
	uint_32 Anti_Shock_Process(uint_32 des,uint_16 range);
	Sys_Err_Type Interpolation_Algorithm(uint_32 des);
	void Destination_Index_Set(uint_32 DI);
	Sys_Err_Type Core_Timer_Init(void);
	Sys_Err_Type Long_Term_Core_Process(Cruis_Speed_Level level,uint_32 des);
	Sys_Err_Type Timer_Stop();
	Sys_Err_Type Timer_Stop_Event_Poll(uint_32 period);
	Sys_Err_Type Core_Algorithm(uint_32 des);
	Sys_Err_Type Core_Buffer_Process(uint_32 des);
	void Core_Reset(void);
	void Set_Output(int spd);
	void Core_Buffer_Init(void);
	void Feed_Core_Buffer(Cruis_Speed_Level level);

private:
    uint_32 Index;
	Cruis_Speed_Level Cruis_level;
	uint_32 Directior;
	uint_16 Anti_Range;
	Speed_Parameter Parameter;
	bool timer_state = false;
	Needle_Status Output_Flag = Needle_Stop;
	bool Timer_Stop_Flag = true;
	Needle_Direction Needle_Move_Direction = Freeze;
	uint_16 Regulus = 0;
	double g_Sirius[600] = {0};
    double g_Core_Buffer[300] = {0};

public:
	Core_Process();
	~Core_Process() {}
};
#endif
