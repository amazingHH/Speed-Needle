/***************************************************************
 * Galaxy_Core.cpp
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
#include "Galaxy_Core.h"

using namespace std;

static Speed_Parameter CFG_Table[BUFFER_MAX_SIZE] = {
{2,10,120},
{6,8,180},
{10,6,220},
{14,4,300},
{18,3,350},
{27,2,450},
};

Core_Process::Core_Process()
{}

void Core_Process::Feed_Core_Buffer(Cruis_Speed_Level level)
{
    int i = 0;
    for(i = 0; i < 260; i++)
    {
#ifdef CURL_TYPE_1
        // if (i < 180)
            Core_Process::g_Sirius[i] = sqrt(((double)(i + 1)) / CFG_Table[level].m_Gradient) * 10;
            // Core_Process::g_Sirius[i] = ((double)(i + 1)) / CFG_Table[level].m_Gradient * 10;
        // else
            // Core_Process::g_Sirius[i] = i;
        /*if (i < 60)
            Core_Process::g_Sirius[i] = 20;
        else if ((i >= 60) && (i < 100))
            Core_Process::g_Sirius[i] = 45;
        else if ((i >= 100) && (i < 150))
            Core_Process::g_Sirius[i] = 70;
        else if ((i >= 150) && (i < 210))
            Core_Process::g_Sirius[i] = 110;
        else if ((i >= 210) && (i < 260))
            Core_Process::g_Sirius[i] = 200;
        else
        {
        }*/

#endif // CURL_TYPE_1
#ifdef CURL_TYPE_2
        Core_Process::g_Sirius[i] = ((double)(i + 1) * (double)(i + 1)) * ((double)(1) / (double)(CFG_Table[level].m_Insert_Num));
#endif // CURL_TYPE_2
        // CLUSTER_FULL_LOGI("g_Sirius[%d] = %f \n",i,(g_Sirius[i] * 3));
    }
}

void Core_Process::Core_Buffer_Init(void)
{
    int_16 bf_sz = 0;
	for (bf_sz = 0; bf_sz < BUFFER_MAX_SIZE; bf_sz ++)
    {
        Core_Process::g_Sirius[bf_sz] = 0;
    }
}

void Core_Process::Core_Reset(void)
{
    Core_Process::Needle_Move_Direction = Freeze;
    Core_Process::Output_Flag = Needle_Stop;
    Core_Process::Timer_Stop_Flag = true;
    Core_Process::timer_state = false;
    Core_Process::Index = 0;
    Core_Process::Cruis_level = SNAIL;
    Core_Process::Anti_Range = 1;
}

void Core_Process::Algorithm_Reset(void)
{
    Core_Process::Destination_Index_Set(0);
    Core_Process::Core_Reset();
}

void Core_Process::Cruis_Level_Set(Cruis_Speed_Level level)
{
    Core_Process::Cruis_level = level;
}

Sys_Err_Type Core_Process::Algorithm_Init(uint_16 range)
{
    Sys_Err_Type ret = NO_ERR;
	Core_Process::Cruis_Level_Set(SNAIL);
    ret = Core_Process::Core_Timer_Init();
    Core_Process::Anti_Range = range;
    Core_Process::Index = 0;
    return ret;
}

void Core_Process::Set_Output(int spd)
{
    printf("SPD is %d \n", spd);
}

DWORD WINAPI Core_Process::SpeedThread(LPVOID p)
{
    printf("1111__ %s \n",__func__);
    static int i = 0;
    DWORD dwLast;
    DWORD dwCurrent;
    static uint_32 timer_cnt = 0;
    Core_Process * pm = reinterpret_cast<Core_Process *> (p);
    while(1)
    {
        if (pm->Output_Flag == Needle_Start) {
            pm->timer_state = true;
            pm->Timer_Stop_Flag = true;
            if (i == 0)
                dwLast = GetTickCount();
            Sleep(100);
            timer_cnt++;
            // printf("%d \n", timer_cnt);
            if ((timer_cnt * 10) >= (pm->g_Core_Buffer[i] * 3))
            {
                timer_cnt = 0;
                i++;
                if (pm->Needle_Move_Direction == Clockwise)
                    pm->Index ++;
                else if (pm->Needle_Move_Direction == Anti_Clockwise)
                    pm->Index --;
                pm->Set_Output(pm->Index);
                if (i >= pm->Regulus)
                {
                    i = 0;
                    pm->Output_Flag = Needle_Stop;
                    dwCurrent = GetTickCount();
                    printf("Time Spend is %d \n",(dwCurrent-dwLast));
                }
                else {
                    // printf("%d \n", Speed_Index);
                }
            }
        }
        else {
            if (pm->timer_state == true)
            {
               pm->Timer_Stop_Flag = false;
               pm->timer_state = false;
               printf("timer was stopped \n");
            }
            i = 0;
            timer_cnt = 0;
            Sleep(10000);
        }
    }
}

Sys_Err_Type Core_Process::Core_Timer_Init(void)
{
    HANDLE Thread_Handle;
    Sys_Err_Type ret = NO_ERR;
	Core_Process::Core_Buffer_Init();
	Core_Process::Feed_Core_Buffer(Cruis_level);
    Thread_Handle = CreateThread(NULL, 0, &Core_Process::SpeedThread,this,0,NULL);
    if (Thread_Handle == 0)
    {
        printf("Create Thread Error \n");
        ret = FATAL_ERR;
    }
    return ret;
}

uint_32 Core_Process::Anti_Shock_Process(uint_32 des, uint_16 range)
{
    uint_32 processed_des;
    static uint_32 previous_des = 0;
    // processed_des = des;
    if (((previous_des < des) && ((des - previous_des) < range)) ||
        ((previous_des > des) && ((previous_des - des) < range)))
    {
        processed_des = previous_des;
    } else {
        previous_des = des;
        processed_des = previous_des;
    }
    return processed_des;
}

Sys_Err_Type Core_Process::Timer_Stop_Event_Poll(uint_32 period)
{
    static uint_32 cnt = 0;
    while (1)
    {
        if (Core_Process::Timer_Stop_Flag == false)
            return NO_ERR;
        else
        {
            Sleep(5000);
            cnt ++;
            if ((cnt * 5) >= period)
            {
                printf ("FATAL error :: Timer close timeout! /n");
                cnt = 0;
                return FATAL_ERR;
            }
        }
    }
    return CRITICAL_ERR;
}

Sys_Err_Type Core_Process::Timer_Stop()
{
    Sys_Err_Type ret = NO_ERR;
    Core_Process::Output_Flag = Needle_Stop;
    ret = Core_Process::Timer_Stop_Event_Poll(10000);
    printf("ret = %d \n", ret);
    return ret;
}

Sys_Err_Type Core_Process::Core_Buffer_Process(uint_32 des)
{
    Sys_Err_Type ret = NO_ERR;
	int i = 0;
    static uint_32 Last_Speed = 0;
    if (Core_Process::Index > 0)
        Last_Speed = Core_Process::Index * SPEED_MULTIPE;
    printf("Last_Speed = %d \n", Last_Speed);
    printf("Index = %d \n", Index);
	if (Last_Speed < des)
	{
		Core_Process::Needle_Move_Direction = Clockwise;
		Core_Process::Regulus = ((des - Last_Speed) / SPEED_MULTIPE);
		printf("Core_Process::Regulus < = %d, des is %d, Last Speed is %d\n", Core_Process::Regulus, des, Last_Speed);
	}
	else if (Last_Speed > des)
	{
		Core_Process::Needle_Move_Direction = Anti_Clockwise;
		Core_Process::Regulus = ((Last_Speed - des) /SPEED_MULTIPE);
		printf("Regulus > = %d \n", Core_Process::Regulus);
	}
	else
	{
		Core_Process::Needle_Move_Direction = Freeze;
		Core_Process::Regulus = 0;
	}
	printf("Needle_Move_Direction = %d \n",Core_Process::Needle_Move_Direction);

	if (Core_Process::Needle_Move_Direction == Clockwise)
	{
        for(i = 0; i< Core_Process::Regulus; i++)
        {
            Core_Process::g_Core_Buffer[i] = Core_Process::g_Sirius[i + (Last_Speed / SPEED_MULTIPE)];
            // printf("Clockwise g_Core_Buffer[%d] = %f \n",i,g_Core_Buffer[i]);
        }
		Core_Process::Output_Flag = Needle_Start;
	} else if (Core_Process::Needle_Move_Direction == Anti_Clockwise) {
        for(i = 0; i< Core_Process::Regulus; i++)
        {
            // g_Core_Buffer[i] = g_Sirius[260 - (Last_Speed / SPEED_MULTIPE) + i];
            Core_Process::g_Core_Buffer[i] = Core_Process::g_Sirius[i];
            // printf("Anti-Clockwise g_Core_Buffer[%d] = %f \n",i,g_Core_Buffer[i]);
        }
		Core_Process::Output_Flag = Needle_Start;
	} else {
	    Core_Process::Output_Flag = Needle_Stop;
	}
    Last_Speed = des;
    return ret;
}

Sys_Err_Type Core_Process::Long_Term_Core_Process(Cruis_Speed_Level level,uint_32 des)
{
    Sys_Err_Type ret = NO_ERR;
    printf ("get into the %s \n", __func__);
    if (Core_Process::timer_state == true)
        ret = Timer_Stop();
    else
        printf ("do not need stop \n", ret);
	if (level < LEVEL_MAX)
        memcpy(&(Core_Process::Parameter),&CFG_Table[level], sizeof(Speed_Parameter));
	else
	{
		ret = FATAL_ERR;
		return ret;
	}
	ret = Core_Process::Core_Buffer_Process(des);
	return ret;
}

Sys_Err_Type Core_Process::Interpolation_Algorithm(uint_32 des)
{
    Sys_Err_Type ret = NO_ERR;
    if (((des > (Core_Process::Index * SPEED_SCORP)) && ((des - (Core_Process::Index * SPEED_SCORP)) >= PROCESS_TYPE_THRESHOLD)) ||
   	((des < (Core_Process::Index *SPEED_SCORP)) && (((Core_Process::Index *SPEED_SCORP) - des) >= PROCESS_TYPE_THRESHOLD)))
   	{
   	    ret = Long_Term_Core_Process(Cruis_level,des);
		if (ret != NO_ERR)
			printf("Long Process Error \n");
        // printf("Get into the %s 1st function \n",__func__);
   	} else {
   	    printf("Get into the %s 3rd function \n",__func__);
		// do nothing
   	}
   	return ret;
}

Sys_Err_Type Core_Process::Core_Algorithm(uint_32 des)
{
    static uint_32 previous_des;
    Sys_Err_Type ret = NO_ERR;
    uint_32 Aris = 0;
    Aris = Core_Process::Anti_Shock_Process(des, Core_Process::Anti_Range);
    if(previous_des == Aris)
    {
       ret = NORMAL_ERR;
       return ret;
    }
    printf("Aris is %d \n", Aris);
    ret = Core_Process::Interpolation_Algorithm(Aris);
    return ret;
}

void Core_Process::Algorithm_Input(unsigned int speed)
{
    Core_Process::Destination_Index_Set(speed);
}

void Core_Process::Destination_Index_Set(uint_32 DI)
{
    Sys_Err_Type ret = NO_ERR;
    Core_Process::Directior = DI;
    ret =  Core_Process::Core_Algorithm(Core_Process::Directior);
    if (ret != NO_ERR)
    {
        printf("Core_Algorithm process error ! \n");
    }
}

