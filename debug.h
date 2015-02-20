#pragma once


#include "rpi_gpio.h"


#define _DEBUG




extern void _flash_brk(void);




#ifdef _DEBUG
#   define DEBUG_FLASH_BRK() _flash_brk()
#else
#   define DEBUG_FLASH_BRK()
#endif