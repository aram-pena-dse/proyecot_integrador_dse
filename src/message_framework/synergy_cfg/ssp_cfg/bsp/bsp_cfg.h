/* generated configuration header file - do not edit */
#ifndef BSP_CFG_H_
#define BSP_CFG_H_
#include "bsp_clock_cfg.h"
#include "bsp_mcu_family_cfg.h"
#include "bsp_board_cfg.h"
#define SYNERGY_NOT_DEFINED 0
#if (SYNERGY_NOT_DEFINED) == (4)
#define BSP_CFG_RTOS (0)
#else
#define BSP_CFG_RTOS (1)
#endif
#undef SYNERGY_NOT_DEFINED
#define BSP_CFG_MCU_VCC_MV (3300)
#define BSP_CFG_STACK_MAIN_BYTES (0x1000)
#define BSP_CFG_STACK_PROCESS_BYTES (0)
#define BSP_CFG_HEAP_BYTES (0x1000)
#define BSP_CFG_PARAM_CHECKING_ENABLE (1)
#define BSP_CFG_ASSERT (0)
#define BSP_CFG_ERROR_LOG (0)
#define BSP_CFG_ID_CODE_LONG_1 (0xFFFFFFFF)
#define BSP_CFG_ID_CODE_LONG_2 (0xFFFFFFFF)
#define BSP_CFG_ID_CODE_LONG_3 (0xFFFFFFFF)
#define BSP_CFG_ID_CODE_LONG_4 (0xFFFFFFFF)
#endif /* BSP_CFG_H_ */
