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
X(usb_one_the_go_full_speed_enable,    AHB2ENR,    OTGFSEN,    USBOneTheGoFullSpeedEnable    )\
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
/*********************** RCC APB2ENR REGISTER ***************************************/\
X(timer_1_enable,            APB2ENR, TIM1EN,Timer1Enable)\
X(usart_1_enable,            APB2ENR, USART1EN,USART1Enable)\
X(usart_6_enable,            APB2ENR, USART6EN, USART6Enable)\
X(analog_digital_converter_1_enable, APB2ENR, ADC1EN, AnalogDigitalConverter1Enable)\
X(secure_digital_input_output_enable, APB2ENR, SDIOEN, SecureDigitalInputOutputEnable)\
X(spi_1_enable,                         APB2ENR, SPI1EN, SPI1Enable)\
X(spi_4_enable,                     APB2ENR, SPI4EN, SPI4Enable)\
X(system_config_enable,          APB2ENR, SYSCFGEN, SystemConfigEnable)\
X(timer_9_enable,       APB2ENR, TIM9EN, Timer9Enable)\
X(timer_10_enable,           APB2ENR, TIM10EN,Timer10Enable)\
X(timer_11_enable,              APB2ENR, TIM11EN,Timer11Enable)\
\
/*********************************** RCC AHB1LPENR REGISTER **********************************/\
X(gpio_a_low_power_enable,                     AHB1LPENR,    GPIOALPEN,    GPIOALowPowerEnable                    )\
X(gpio_b_low_power_enable,                     AHB1LPENR,    GPIOBLPEN,    GPIOBLowPowerEnable                    )\
X(gpio_c_low_power_enable,                     AHB1LPENR,    GPIOCLPEN,    GPIOCLowPowerEnable                    )\
X(gpio_d_low_power_enable,                     AHB1LPENR,    GPIODLPEN,    GPIODLowPowerEnable                    )\
X(gpio_e_low_power_enable,                     AHB1LPENR,    GPIOELPEN,    GPIOELowPowerEnable                    )\
X(gpio_h_low_power_enable,                     AHB1LPENR,    GPIOHLPEN,    GPIOHLowPowerEnable                    )\
X(cyclic_redundancy_check_low_power_enable,    AHB1LPENR,    CRCLPEN,      CyclicRedundancyCheckLowPowerEnable    )\
X(direct_memory_access_1_low_power_enable,     AHB1LPENR,    DMA1LPEN,     DirectMemoryAccess1LowPowerEnable      )\
X(direct_memory_access_2_low_power_enable,     AHB1LPENR,    DMA2LPEN,     DirectMemoryAccess1LowPowerEnable      )\
\
/************************************* RCC AHB2LPENR REGISTER *******************************/\
X(usb_one_the_go_full_speed_low_power_enable,    AHB2LPENR,    OTGFSLPEN,    USBOneTheGoFullSpeedLowPowerEnable    )\
\
/*************************** RCC APB1LPENR REGISTER ****************************/\
X(timer_2_low_power_enable,            APB1LPENR,    TIM2LPEN,      Timer2LowPowerEnable            )\
X(timer_3_low_power_enable,            APB1LPENR,    TIM3LPEN,      Timer3LowPowerEnable            )\
X(timer_4_low_power_enable,            APB1LPENR,    TIM4LPEN,      Timer4LowPowerEnable            )\
X(timer_5_low_power_enable,            APB1LPENR,    TIM5LPEN,      Timer5LowPowerEnable            )\
X(window_watchdog_low_power_enable,    APB1LPENR,    WWDGLPEN,      WindowWatchdogLowPowerEnable    )\
X(spi_2_low_power_enable,              APB1LPENR,    SPI2LPEN,      SPI2LowPowerEnable              )\
X(spi_3_low_power_enable,              APB1LPENR,    SPI3LPEN,      SPI3LowPowerEnable              )\
X(usart_2_low_power_enable,            APB1LPENR,    USART2LPEN,    USART2LowPowerEnable            )\
X(i2c_1_low_power_enable,              APB1LPENR,    I2C1LPEN,      I2C1LowPowerEnable              )\
X(i2c_2_low_power_enable,              APB1LPENR,    I2C2LPEN,      I2C2LowPowerEnable              )\
X(i2c_3_low_power_enable,              APB1LPENR,    I2C3LPEN,      I2C3LowPowerEnable              )\
X(power_low_power_enable,              APB1LPENR,    PWRLPEN,       PowerLowPowerEnable             )\
\
/*********************** RCC APB2LPENR REGISTER ***************************************/\
X(timer_1_low_power_enable,                        APB2LPENR,    TIM1LPEN,      Timer1LowPowerEnable)\
X(usart_1_low_power_enable,                        APB2LPENR,    USART1LPEN,    USART1LowPowerEnable)\
X(usart_6_low_power_enable,                        APB2LPENR,    USART6LPEN,    USART6LowPowerEnable)\
X(analog_digital_converter_1_low_power_enable,     APB2LPENR,    ADC1LPEN,      AnalogDigitalConverter1LowPowerEnable)\
X(secure_digital_input_output_low_power_enable,    APB2LPENR,    SDIOLPEN,      SecureDigitalInputOutputLowPowerEnable)\
X(spi_1_low_power_enable,                          APB2LPENR,    SPI1LPEN,      SPI1LowPowerEnable)\
X(spi_4_low_power_enable,                          APB2LPENR,    SPI4LPEN,      SPI4LowPowerEnable)\
X(system_config_low_power_enable,                  APB2LPENR,    SYSCFGLPEN,    SystemConfigLowPowerEnable)\
X(timer_9_low_power_enable,                        APB2LPENR,    TIM9LPEN,      Timer9LowPowerEnable)\
X(timer_10_low_power_enable,                       APB2LPENR,    TIM10LPEN,     Timer10LowPowerEnable)\
X(timer_11_low_power_enable,                       APB2LPENR,    TIM11LPEN,     Timer11LowPowerEnable)\
\
/*********************** RCC BDCR REGISTER ***************************************/\
X(external_low_speed_oscillator_enable, BDCR, LSEON, ExternalLowSpeedOscillatorEnable)\
X(external_low_speed_oscillator_ready, BDCR, LSERDY, ExternalLowSpeedOscillatorReady)\
X(external_low_speed_oscillator_bypass, BDCR, LSEBYP, ExternalLowSpeedOscillatorBypass)\
X(real_time_clock_source_selection, BDCR, RTCSEL, RealTimeClockSourceSelection)\
X(real_time_clock_enable, BDCR, RTCEN, RealTimeClockEnable)\
X(backup_domain_software_reset, BDCR, BDRST, BackupDomainSoftwareReset)\
\
/*********************** RCC CSR REGISTER ***************************************/\
X(internal_low_speed_oscillator_enable, CSR, LSION, InternalLowSpeedOscillatorEnable)\
X(internal_low_speed_oscillator_ready, CSR, LSIRDY, InternalLowSpeedOscillatorEnable)\
X(remove_reset_flag, CSR, RMVF, RemoveResetFlag)\
X(bor_reset_flag, CSR, BORRSTF , BORResetFlag)\
X(pin_reset_flag, CSR, PINRSTF, PINResetFlag)\
X(por_pdr_resetflag, CSR, PORRSTF, PORPDRResetFlag)\
X(software_reset_flag, CSR, SFTRSTF, SoftwareResetFlag)\
X(independent_watchdog_reset_flag, CSR, IWDGRSTF, IndependentWatchdogResetFlag)\
X(window_watchdog_reset_flag, CSR, WWDGRSTF, WindowWatchdogResetFlag)\
X(low_power_reset_flag, CSR, LPWRRSTF, LowPowerResetFlag)\
\
/*********************** RCC SSCGR REGISTER ***************************************/\
X(ModulationPeriod, SSCGR, MODPER, ModulationPeriod)\
X(IncrementationStep, SSCGR, INCSTEP, IncrementationStep)\
X(SpreadSelect, SSCGR, SPREADSEL, SpreadSelect)\
X(SpreadSpectrumModulationEnable, SSCGR, SSCGEN, SpreadSpectrumModulationEnable)\
\
/*********************** RCC PLLI2SCFGR REGISTER ***************************************/\
X(phase_locked_loop_i2s_multiplication, PLLI2SCFGR, PLLI2SN, PhaseLockedLoopI2SMultiplication)\
X(phase_locked_loop_i2s_division, PLLI2SCFGR, PLLI2SR, PhaseLockedLoopI2SDivision)\
\
/*********************** RCC DCKCFGR REGISTER ***************************************/\
X(Timers_Prescalers_Selection, DCKCFGR, TIMPRE,  TimersPrescalersSelection)\

#define GENERATE_SET_FUNCTION(short_name, _reg, _sub_reg, _type)                           \
    /** @brief Sets the field short_name in RCC register. */                               \
    static inline void play32_rcc_set_##short_name(                                        \
        const PLAY32_RCC_##_reg##_##_type value                                            \
    ) {                                                                                    \
        PLAY32_RCC->_reg = (PLAY32_RCC->_reg & ~(PLAY32_RCC_##_reg##_##_sub_reg##_MSK))    \
            | (((uint32_t)value << (PLAY32_RCC_##_reg##_##_sub_reg##_POS))                 \
            & (PLAY32_RCC_##_reg##_##_sub_reg##_MSK));                                     \
    }

#define GENERATE_GET_FUNCTION(short_name, _reg, _sub_reg, _type)                 \
    /** @brief Sets the field short_name in RCC register. */                     \
    static inline PLAY32_RCC_##_reg##_##_type play32_rcc_get_##short_name() {    \
        return (PLAY32_RCC_##_reg##_##_type)                                     \
            ((PLAY32_RCC->_reg & (PLAY32_RCC_##_reg##_##_sub_reg##_MSK))         \
            >> (PLAY32_RCC_##_reg##_##_sub_reg##_POS));                          \
    }

RCC_REGISTERS_TABLE(GENERATE_SET_FUNCTION);
RCC_REGISTERS_TABLE(GENERATE_GET_FUNCTION);


#undef GENERATE_SET_FUNCTION
#undef GENERATE_GET_FUNCTION
#endif //PLAY32_RCC_H
