/***************************************************************
 * Galaxy_Ulitity.h
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
#ifndef _GALAXY_ULITITY_H_
#define _GALAXY_ULITITY_H_

#ifdef __WIN32__
#include <process.h>
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


/***************************************************************
                    MACROS DECLARE
***************************************************************/
#define LOG_ENABLE 1
#define LOG_DISABLE 2

#define BUFFER_MAX_SIZE 600

#define ANTI_SHOCK_RANGE 5

#define ANTI_SHOCK_TACHO_RANGE 50

#define PROCESS_TYPE_THRESHOLD 9

#define SPEED_MULTIPE 1

#define SHORT_TERM_PERIOD 100

#define SPEED_SCORP 1

/***************************************************************
                    ENUM DECLARE
***************************************************************/
typedef unsigned char uint_8;
typedef char int_8;
typedef unsigned short int uint_16;
typedef short int int_16;
typedef unsigned int uint_32;
typedef int int_32;
typedef double int_64;

typedef enum {
SNAIL = 0,
TORTOISE,
RABBIT,
HORSE,
JAGUAR,
ULTIMATE,
LEVEL_MAX,
}Cruis_Speed_Level;

typedef enum {
SPEED = 0,
TACHO,
TYPE_MAX,
}Process_Type;

typedef enum {
Freeze = 0,
Clockwise,
Anti_Clockwise,
Direction_Max,
}Needle_Direction;

typedef enum {
Needle_Start = 0,
Needle_Stop,
Needle_Max,
}Needle_Status;

typedef enum {
Short_Term = 0,
Long_Term,
Max_Term,
}Term_Type;

typedef struct {
uint_8 m_Gradient;
uint_8 m_Time;
uint_32 m_Insert_Num;
}Speed_Parameter;



/***************************************************************
                    STRUCT DECLARE
***************************************************************/

/***************************************************************
                    FUNCTION DECLARE
***************************************************************/

#endif
