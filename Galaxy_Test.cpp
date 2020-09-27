/***************************************************************
 * Galaxy_Test.cpp
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
#include "Galaxy_Test.h"

Sys_Err_Type Initial (Core_Process * p, uint_16 range)
{
    Sys_Err_Type ret = NO_ERR;
    ret = p->Algorithm_Init(range);
    if (ret != NO_ERR)
    {
        printf("init error \n");
    }
    return ret;
}

void operate(Core_Process * p, uint_32 des)
{
    p->Algorithm_Input(des);
}

int main(void)
{
    Sys_Err_Type ret = NO_ERR;
    uint_32 testid = 0;
    uint_32 testid2 = 0;
	Core_Process * Speed_process = new Core_Process();
	Core_Process * Tacho_process = new Core_Process();
	ret = Initial(Speed_process, 1);
	ret = Initial(Tacho_process, 10);
	if (ret != NO_ERR)
    {
        return 0;
    }
	while(1)
	{
        Sleep(50);
        scanf("%d", &testid);
        Speed_process->Algorithm_Input(testid);
        // Tacho_process->Algorithm_Input(testid2);

	}
	delete Speed_process;
	delete Tacho_process;

	return ret;
}

