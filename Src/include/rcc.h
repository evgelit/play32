/**
 * @file    rcc.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for Reset and clock control (RCC) of STM32F401 CCU.
 * @version 1.0.0
 * @date    2026-11-08
 *
 * @note    Uses advanced Computed Macro Calls for linear register dispatching,
 *          providing zero-cost abstractions and eliminating code duplication.
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_RCC_H
#define PLAY32_RCC_H

#include "rcc_types.h"

#define RCC_REGISTERS_TABLE(X) \
/*************************************** RCC CR REGISTER ***************************************/\
X(high_speed_internal_clock_enable,         CR,     HSION,         HighSpeedInternalClockEnable)\
X(high_speed_internal_clock_ready,          CR,     HSIRDY,        HighSpeedInternalClockReady)\
X(high_speed_internal_clock_trim,           CR,     HSITRIM,       HighSpeedInternalClockTrim)\
X(high_speed_internal_clock_calibration,    CR,     HSICAL,        HighSpeedInternalClockCalibration)\
X(high_speed_external_clock_enable,         CR,     HSEON,         HighSpeedExternalClockEnable)\
X(high_speed_external_clock_ready,          CR,     HSERDY,        HighSpeedExternalClockReady)\
X(high_speed_external_clock_bypass,         CR,     HSEBYP,       HighSpeedExternalClockBypass)\
X(clock_security_system_enable,             CR,     CSSON,        ClockSecuritySystemEnable)\
X(phase_locked_loop_enable,                 CR,     PLLON,        PhaseLockedLoopEnable)\
X(phase_locked_loop_ready,                  CR,     PLLRDY,        PhaseLockedLoopReady)\
X(phase_locked_loop_i2s_enable,             CR,     PLLI2SON,        PhaseLockedLoopI2SEnable)\
X(phase_locked_loop_i2s_ready,              CR,     PLLI2SRDY,        PhaseLockedLoopI2SReady)\
\
/*************************************** RCC PLLCFGR REGISTER ***************************************/\
X(phase_locked_loop_main_divider,          PLLCFGR, PLLM,      PhaseLockedLoopMainDivider)\
X(phase_locked_loop_number_multiplicator,  PLLCFGR, PLLM,      PhaseLockedLoopNumberMultiplicator)\
/** TODO: implement rest of PPLCFGR reg **/\
\
/*************************************** RCC CFGR REGISTER ***************************************/\
/*************************************** RCC CIR REGISTER ***************************************/\
/*************************************** RCC AHB1RSTR REGISTER ***************************************/\
/*************************************** RCC AHB2RSTR REGISTER ***************************************/\
/*************************************** RCC APB1RSTR REGISTER ***************************************/\
/*************************************** RCC APB2RSTR REGISTER ***************************************/\
/*********************************** RCC AHB1ENR REGISTER **********************************/\
X(gpio_a_enable,                     AHB1ENR,    GPIOAEN,    GPIOAEnable                    )\
X(gpio_b_enable,                     AHB1ENR,    GPIOBEN,    GPIOBEnable                    )\
X(gpio_c_enable,                     AHB1ENR,    GPIOCEN,    GPIOCEnable                    )\
X(gpio_d_enable,                     AHB1ENR,    GPIODEN,    GPIODEnable                    )\
X(gpio_e_enable,                     AHB1ENR,    GPIOEEN,    GPIOEEnable                    )\
X(gpio_h_enable,                     AHB1ENR,    GPIOHEN,    GPIOHEnable                    )\
X(cyclic_redundancy_check_enable,    AHB1ENR,    CRCEN,      CyclicRedundancyCheckEnable    )\
X(direct_memory_access_1_enable,     AHB1ENR,    DMA1EN,     DirectMemoryAccess1Enable      )\
X(direct_memory_access_2_enable,     AHB1ENR,    DMA2EN,     DirectMemoryAccess1Enable      )\
\
/************************************* RCC AHB2ENR REGISTER *******************************/\
X(usb_one_the_go_full_speed_enable,    AHB2ENR,    OTGFS,    USBOneTheGoFullSpeedEnable    )\
\
/*************************** RCC APB1ENR REGISTER ****************************/\
X(timer_2_enable,            APB1ENR,    TIM2EN,      Timer2Enable            )\
X(timer_3_enable,            APB1ENR,    TIM3EN,      Timer3Enable            )\
X(timer_4_enable,            APB1ENR,    TIM4EN,      Timer4Enable            )\
X(timer_5_enable,            APB1ENR,    TIM5EN,      Timer5Enable            )\
X(window_watchdog_enable,    APB1ENR,    WWDGEN,      WindowWatchdogEnable    )\
X(spi_2_enable,              APB1ENR,    SPI2EN,      SPI2Enable              )\
X(spi_3_enable,              APB1ENR,    SPI3EN,      SPI3Enable              )\
X(usart_2_enable,            APB1ENR,    USART2EN,    USART2Enable            )\
X(i2c_1_enable,              APB1ENR,    I2C1EN,      I2C1Enable              )\
X(i2c_2_enable,              APB1ENR,    I2C2EN,      I2C2Enable              )\
X(i2c_3_enable,              APB1ENR,    I2C3EN,      I2C3Enable              )\
X(power_enable,              APB1ENR,    PWREN,       PowerEnable             )\
\
/*************************************** RCC APB2ENR REGISTER ***************************************/\

#define GENERATE_SET_FUNCTION(short_name, _reg, _sub_reg, _type)                \
    /** @brief Sets the field short_name in RCC register. */                   \
    static inline void play32_rcc_set_##short_name(  \
        const PLAY32_RCC_##_reg##_##_type value                                \
    ) {                                                                         \
        PLAY32_RCC->_reg = (PLAY32_RCC->_reg & ~(PLAY32_RCC_##_reg##_##_sub_reg##_MSK))    \
            | (((uint32_t)value << (PLAY32_RCC_##_reg##_##_sub_reg##_POS))     \
            & (PLAY32_RCC_##_reg##_##_sub_reg##_MSK));                         \
    }

#define GENERATE_GET_FUNCTION(short_name, _reg, _sub_reg, _type)                \
    /** @brief Sets the field short_name in RCC register. */                   \
    static inline PLAY32_RCC_##_reg##_##_type play32_rcc_get_##short_name() {                                                                         \
        return (PLAY32_RCC_##_reg##_##_type)                                  \
            ((PLAY32_RCC->_reg & (PLAY32_RCC_##_reg##_##_sub_reg##_MSK))             \
            >> (PLAY32_RCC_##_reg##_##_sub_reg##_POS));                        \
    }

RCC_REGISTERS_TABLE(GENERATE_SET_FUNCTION);
RCC_REGISTERS_TABLE(GENERATE_GET_FUNCTION);

#undef GENERATE_SET_FUNCTION
#undef GENERATE_GET_FUNCTION
#endif //PLAY32_RCC_H
