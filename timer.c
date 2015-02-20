#include "timer.h"

static ArmTimer_t* arm_timer = (ArmTimer_t*)ARM_TIMER_BASE;

ArmTimer_t*
get_arm_timer(void)
{
    return arm_timer;
}

