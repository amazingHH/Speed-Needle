/***************************************************************
 * Galaxy_Err.h
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
#ifndef _GALAXY_ERR_H_
#define _GALAXY_ERR_H_

typedef enum {
	NO_ERR = 0,
	NORMAL_ERR,
	CRITICAL_ERR,
	FATAL_ERR,
	ERR_MAX,
	}Sys_Err_Type;

#endif