/**
 * @file    rcc.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for Reset and Clock Control (RCC) of STM32F401 CCU.
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

/**
 * @addtogroup PLAY32_RCC
 * @{
 */

/**
 * @defgroup PLAY32_RCC_Driver RCC Register Accessor Generator API
 * @brief X-Macro descriptor table and compile-time inline register accessor functions.
 * @{
 */

/**
 * @brief  Master X-Macro descriptor table for RCC registers on STM32F401.
 * @details Maps each clock control, reset, enable, or status field to its hardware register,
 *          bitfield mnemonic, strict typedef from @ref rcc_types.h, and hardware access mode
 *          using the signature: `X(func_suffix, reg_name, bit_name, type_suffix, access_mode)`.
 *
 * @param  X  Generator macro invoked once per register field entry.
 *
 * @warning Ensure Doxygen is configured with `MACRO_EXPANSION = YES` if you want
 *          expanded inline functions to appear in the generated API documentation.
 * @see    PLAY32_RCC_TypeDef
 * @see    PLAY32_RCC
 */
#define RCC_REGISTERS_TABLE(X) \
/************************************************* RCC CR REGISTER ************************************************************/\
X(high_speed_internal_clock_enable,                CR,           HSION,         HighSpeedInternalClockEnable,          SET_RMW )\
X(high_speed_internal_clock_ready,                 CR,           HSIRDY,        HighSpeedInternalClockReady,           RO      )\
X(high_speed_internal_clock_trim,                  CR,           HSITRIM,       HighSpeedInternalClockTrim,            SET_RMW )\
X(high_speed_internal_clock_calibration,           CR,           HSICAL,        HighSpeedInternalClockCalibration,     RO      )\
X(high_speed_external_clock_enable,                CR,           HSEON,         HighSpeedExternalClockEnable,          SET_RMW )\
X(high_speed_external_clock_ready,                 CR,           HSERDY,        HighSpeedExternalClockReady,           RO      )\
X(high_speed_external_clock_bypass,                CR,           HSEBYP,        HighSpeedExternalClockBypass,          SET_RMW )\
X(clock_security_system_enable,                    CR,           CSSON,         ClockSecuritySystemEnable,             SET_RMW )\
X(phase_locked_loop_enable,                        CR,           PLLON,         PhaseLockedLoopEnable,                 SET_RMW )\
X(phase_locked_loop_ready,                         CR,           PLLRDY,        PhaseLockedLoopReady,                  RO      )\
X(phase_locked_loop_i2s_enable,                    CR,           PLLI2SON,      PhaseLockedLoopI2SEnable,              SET_RMW )\
X(phase_locked_loop_i2s_ready,                     CR,           PLLI2SRDY,     PhaseLockedLoopI2SReady,               RO      )\
\
/************************************************* RCC PLLCFGR REGISTER *******************************************************/\
X(phase_locked_loop_main_divider,                  PLLCFGR,      PLLM,          PhaseLockedLoopMainDivider,            SET_RMW )\
X(phase_locked_loop_number_multiplicator,          PLLCFGR,      PLLN,          PhaseLockedLoopNumberMultiplicator,    SET_RMW )\
X(phase_locked_loop_main_system_divider,           PLLCFGR,      PLLP,          PhaseLockedLoopMainSystemDivider,      SET_RMW )\
X(phase_locked_loop_clock_source,                  PLLCFGR,      PLLSRC,        PhaseLockedLoopClockSource,            SET_RMW )\
X(phase_locked_loop_main_q_divider,                PLLCFGR,      PLLQ,          PhaseLockedLoopMainQDivider,           SET_RMW )\
\
/************************************************* RCC CFGR REGISTER **********************************************************/\
X(system_clock_switch,                             CFGR,         SW,            SystemClockSwitch,                     SET_RMW )\
X(system_clock_switch_status,                      CFGR,         SWS,           SystemClockSwitchStatus,               RO      )\
X(ahb_prescaler,                                   CFGR,         HPRE,          AHBPrescaler,                          SET_RMW )\
X(apb1_prescaler,                                  CFGR,         PPRE1,         APB1Prescaler,                         SET_RMW )\
X(apb2_prescaler,                                  CFGR,         PPRE2,         APB2Prescaler,                         SET_RMW )\
X(rtc_prescaler,                                   CFGR,         RTCPRE,        RTCPrescaler,                          SET_RMW )\
X(mco1_source,                                     CFGR,         MCO1,          MCO1Source,                            SET_RMW )\
X(i2s_source,                                      CFGR,         I2SSRC,        I2SSource,                             SET_RMW )\
X(mco1_prescaler,                                  CFGR,         MCO1PRE,       MCO1Prescaler,                         SET_RMW )\
X(mco2_prescaler,                                  CFGR,         MCO2PRE,       MCO2Prescaler,                         SET_RMW )\
X(mco2_source,                                     CFGR,         MCO2,          MCO2Source,                            SET_RMW )\
\
/************************************************* RCC CIR REGISTER ***********************************************************/\
X(low_speed_internal_ready_interrupt_flag,         CIR,          LSIRDYF,       LowSpeedInternalReadyInterruptFlag,    RO      )\
X(low_speed_external_ready_interrupt_flag,         CIR,          LSERDYF,       LowSpeedExternalReadyInterruptFlag,    RO      )\
X(high_speed_internal_ready_interrupt_flag,        CIR,          HSIRDYF,       HighSpeedInternalReadyInterruptFlag,   RO      )\
X(high_speed_external_ready_interrupt_flag,        CIR,          HSERDYF,       HighSpeedExternalReadyInterruptFlag,   RO      )\
X(phase_locked_loop_ready_interrupt_flag,          CIR,          PLLRDYF,       PhaseLockedLoopReadyInterruptFlag,     RO      )\
X(phase_locked_loop_i2s_ready_interrupt_flag,      CIR,          PLLI2SRDYF,    PhaseLockedLoopI2SReadyInterruptFlag,  RO      )\
X(clock_security_system_interrupt_flag,            CIR,          CSSF,          ClockSecuritySystemInterruptFlag,      RO      )\
X(low_speed_internal_ready_interrupt_enable,       CIR,          LSIRDYIE,      LowSpeedInternalReadyInterruptEnable,  SET_RMW )\
X(low_speed_external_ready_interrupt_enable,       CIR,          LSERDYIE,      LowSpeedExternalReadyInterruptEnable,  SET_RMW )\
X(high_speed_internal_ready_interrupt_enable,      CIR,          HSIRDYIE,      HighSpeedInternalReadyInterruptEnable, SET_RMW )\
X(high_speed_external_ready_interrupt_enable,      CIR,          HSERDYIE,      HighSpeedExternalReadyInterruptEnable, SET_RMW )\
X(phase_locked_loop_ready_interrupt_enable,        CIR,          PLLRDYIE,      PhaseLockedLoopReadyInterruptEnable,   SET_RMW )\
X(phase_locked_loop_i2s_ready_interrupt_enable,    CIR,          PLLI2SRDYIE,   PhaseLockedLoopI2SReadyInterruptEnable,SET_RMW )\
X(low_speed_internal_ready_interrupt_clear,        CIR,          LSIRDYC,       LowSpeedInternalReadyInterruptClear,   SET_WO  )\
X(low_speed_external_ready_interrupt_clear,        CIR,          LSERDYC,       LowSpeedExternalReadyInterruptClear,   SET_WO  )\
X(high_speed_internal_ready_interrupt_clear,       CIR,          HSIRDYC,       HighSpeedInternalReadyInterruptClear,  SET_WO  )\
X(high_speed_external_ready_interrupt_clear,       CIR,          HSERDYC,       HighSpeedExternalReadyInterruptClear,  SET_WO  )\
X(phase_locked_loop_ready_interrupt_clear,         CIR,          PLLRDYC,       PhaseLockedLoopReadyInterruptClear,    SET_WO  )\
X(phase_locked_loop_i2s_ready_interrupt_clear,     CIR,          PLLI2SRDYC,    PhaseLockedLoopI2SReadyInterruptClear, SET_WO  )\
X(clock_security_system_interrupt_clear,           CIR,          CSSC,          ClockSecuritySystemInterruptClear,     SET_WO  )\
\
/************************************************* RCC AHB1RSTR REGISTER ******************************************************/\
X(gpio_a_reset,                                    AHB1RSTR,     GPIOARST,      GPIOAReset,                            SET_RMW )\
X(gpio_b_reset,                                    AHB1RSTR,     GPIOBRST,      GPIOBReset,                            SET_RMW )\
X(gpio_c_reset,                                    AHB1RSTR,     GPIOCRST,      GPIOCReset,                            SET_RMW )\
X(gpio_d_reset,                                    AHB1RSTR,     GPIODRST,      GPIODReset,                            SET_RMW )\
X(gpio_e_reset,                                    AHB1RSTR,     GPIOERST,      GPIOEReset,                            SET_RMW )\
X(gpio_h_reset,                                    AHB1RSTR,     GPIOHRST,      GPIOHReset,                            SET_RMW )\
X(crc_reset,                                       AHB1RSTR,     CRCRST,        CRCReset,                              SET_RMW )\
X(dma_1_reset,                                     AHB1RSTR,     DMA1RST,       DMA1Reset,                             SET_RMW )\
X(dma_2_reset,                                     AHB1RSTR,     DMA2RST,       DMA2Reset,                             SET_RMW )\
\
/************************************************* RCC AHB2RSTR REGISTER ******************************************************/\
X(usb_otg_fs_reset,                                AHB2RSTR,     OTGFSRST,      OTGFSReset,                            SET_RMW )\
\
/************************************************* RCC APB1RSTR REGISTER ******************************************************/\
X(timer_2_reset,                                   APB1RSTR,     TIM2RST,       TIM2Reset,                             SET_RMW )\
X(timer_3_reset,                                   APB1RSTR,     TIM3RST,       TIM3Reset,                             SET_RMW )\
X(timer_4_reset,                                   APB1RSTR,     TIM4RST,       TIM4Reset,                             SET_RMW )\
X(timer_5_reset,                                   APB1RSTR,     TIM5RST,       TIM5Reset,                             SET_RMW )\
X(window_watchdog_reset,                           APB1RSTR,     WWDGRST,       WWDGReset,                             SET_RMW )\
X(spi_2_reset,                                     APB1RSTR,     SPI2RST,       SPI2Reset,                             SET_RMW )\
X(spi_3_reset,                                     APB1RSTR,     SPI3RST,       SPI3Reset,                             SET_RMW )\
X(usart_2_reset,                                   APB1RSTR,     USART2RST,     USART2Reset,                           SET_RMW )\
X(i2c_1_reset,                                     APB1RSTR,     I2C1RST,       I2C1Reset,                             SET_RMW )\
X(i2c_2_reset,                                     APB1RSTR,     I2C2RST,       I2C2Reset,                             SET_RMW )\
X(i2c_3_reset,                                     APB1RSTR,     I2C3RST,       I2C3Reset,                             SET_RMW )\
X(power_reset,                                     APB1RSTR,     PWRRST,        PWRReset,                              SET_RMW )\
\
/************************************************* RCC APB2RSTR REGISTER ******************************************************/\
X(timer_1_reset,                                   APB2RSTR,     TIM1RST,       TIM1Reset,                             SET_RMW )\
X(usart_1_reset,                                   APB2RSTR,     USART1RST,     USART1Reset,                           SET_RMW )\
X(usart_6_reset,                                   APB2RSTR,     USART6RST,     USART6Reset,                           SET_RMW )\
X(analog_digital_converter_1_reset,                APB2RSTR,     ADC1RST,       ADC1Reset,                             SET_RMW )\
X(secure_digital_input_output_reset,               APB2RSTR,     SDIORST,       SDIOReset,                             SET_RMW )\
X(spi_1_reset,                                     APB2RSTR,     SPI1RST,       SPI1Reset,                             SET_RMW )\
X(spi_4_reset,                                     APB2RSTR,     SPI4RST,       SPI4Reset,                             SET_RMW )\
X(system_config_reset,                             APB2RSTR,     SYSCFGRST,     SYSCFGReset,                           SET_RMW )\
X(timer_9_reset,                                   APB2RSTR,     TIM9RST,       TIM9Reset,                             SET_RMW )\
X(timer_10_reset,                                  APB2RSTR,     TIM10RST,      TIM10Reset,                            SET_RMW )\
X(timer_11_reset,                                  APB2RSTR,     TIM11RST,      TIM11Reset,                            SET_RMW )\
\
/************************************************* RCC AHB1ENR REGISTER *******************************************************/\
X(gpio_a_enable,                                   AHB1ENR,      GPIOAEN,       GPIOAEnable,                           SET_RMW )\
X(gpio_b_enable,                                   AHB1ENR,      GPIOBEN,       GPIOBEnable,                           SET_RMW )\
X(gpio_c_enable,                                   AHB1ENR,      GPIOCEN,       GPIOCEnable,                           SET_RMW )\
X(gpio_d_enable,                                   AHB1ENR,      GPIODEN,       GPIODEnable,                           SET_RMW )\
X(gpio_e_enable,                                   AHB1ENR,      GPIOEEN,       GPIOEEnable,                           SET_RMW )\
X(gpio_h_enable,                                   AHB1ENR,      GPIOHEN,       GPIOHEnable,                           SET_RMW )\
X(cyclic_redundancy_check_enable,                  AHB1ENR,      CRCEN,         CyclicRedundancyCheckEnable,           SET_RMW )\
X(direct_memory_access_1_enable,                   AHB1ENR,      DMA1EN,        DirectMemoryAccess1Enable,             SET_RMW )\
X(direct_memory_access_2_enable,                   AHB1ENR,      DMA2EN,        DirectMemoryAccess2Enable,             SET_RMW )\
\
/************************************************* RCC AHB2ENR REGISTER *******************************************************/\
X(usb_one_the_go_full_speed_enable,                AHB2ENR,      OTGFSEN,       USBOneTheGoFullSpeedEnable,            SET_RMW )\
\
/************************************************* RCC APB1ENR REGISTER *******************************************************/\
X(timer_2_enable,                                  APB1ENR,      TIM2EN,        Timer2Enable,                          SET_RMW )\
X(timer_3_enable,                                  APB1ENR,      TIM3EN,        Timer3Enable,                          SET_RMW )\
X(timer_4_enable,                                  APB1ENR,      TIM4EN,        Timer4Enable,                          SET_RMW )\
X(timer_5_enable,                                  APB1ENR,      TIM5EN,        Timer5Enable,                          SET_RMW )\
X(window_watchdog_enable,                          APB1ENR,      WWDGEN,        WindowWatchdogEnable,                  SET_RMW )\
X(spi_2_enable,                                    APB1ENR,      SPI2EN,        SPI2Enable,                            SET_RMW )\
X(spi_3_enable,                                    APB1ENR,      SPI3EN,        SPI3Enable,                            SET_RMW )\
X(usart_2_enable,                                  APB1ENR,      USART2EN,      USART2Enable,                          SET_RMW )\
X(i2c_1_enable,                                    APB1ENR,      I2C1EN,        I2C1Enable,                            SET_RMW )\
X(i2c_2_enable,                                    APB1ENR,      I2C2EN,        I2C2Enable,                            SET_RMW )\
X(i2c_3_enable,                                    APB1ENR,      I2C3EN,        I2C3Enable,                            SET_RMW )\
X(power_enable,                                    APB1ENR,      PWREN,         PowerEnable,                           SET_RMW )\
\
/************************************************* RCC APB2ENR REGISTER *******************************************************/\
X(timer_1_enable,                                  APB2ENR,      TIM1EN,        Timer1Enable,                          SET_RMW )\
X(usart_1_enable,                                  APB2ENR,      USART1EN,      USART1Enable,                          SET_RMW )\
X(usart_6_enable,                                  APB2ENR,      USART6EN,      USART6Enable,                          SET_RMW )\
X(analog_digital_converter_1_enable,               APB2ENR,      ADC1EN,        AnalogDigitalConverter1Enable,         SET_RMW )\
X(secure_digital_input_output_enable,              APB2ENR,      SDIOEN,        SecureDigitalInputOutputEnable,        SET_RMW )\
X(spi_1_enable,                                    APB2ENR,      SPI1EN,        SPI1Enable,                            SET_RMW )\
X(spi_4_enable,                                    APB2ENR,      SPI4EN,        SPI4Enable,                            SET_RMW )\
X(system_config_enable,                            APB2ENR,      SYSCFGEN,      SystemConfigEnable,                    SET_RMW )\
X(timer_9_enable,                                  APB2ENR,      TIM9EN,        Timer9Enable,                          SET_RMW )\
X(timer_10_enable,                                 APB2ENR,      TIM10EN,       Timer10Enable,                         SET_RMW )\
X(timer_11_enable,                                 APB2ENR,      TIM11EN,       Timer11Enable,                         SET_RMW )\
\
/************************************************* RCC AHB1LPENR REGISTER *****************************************************/\
X(gpio_a_low_power_enable,                         AHB1LPENR,    GPIOALPEN,     GPIOALowPowerEnable,                   SET_RMW )\
X(gpio_b_low_power_enable,                         AHB1LPENR,    GPIOBLPEN,     GPIOBLowPowerEnable,                   SET_RMW )\
X(gpio_c_low_power_enable,                         AHB1LPENR,    GPIOCLPEN,     GPIOCLowPowerEnable,                   SET_RMW )\
X(gpio_d_low_power_enable,                         AHB1LPENR,    GPIODLPEN,     GPIODLowPowerEnable,                   SET_RMW )\
X(gpio_e_low_power_enable,                         AHB1LPENR,    GPIOELPEN,     GPIOELowPowerEnable,                   SET_RMW )\
X(gpio_h_low_power_enable,                         AHB1LPENR,    GPIOHLPEN,     GPIOHLowPowerEnable,                   SET_RMW )\
X(cyclic_redundancy_check_low_power_enable,        AHB1LPENR,    CRCLPEN,       CyclicRedundancyCheckLowPowerEnable,   SET_RMW )\
X(direct_memory_access_1_low_power_enable,         AHB1LPENR,    DMA1LPEN,      DirectMemoryAccess1LowPowerEnable,     SET_RMW )\
X(direct_memory_access_2_low_power_enable,         AHB1LPENR,    DMA2LPEN,      DirectMemoryAccess2LowPowerEnable,     SET_RMW )\
\
/************************************************* RCC AHB2LPENR REGISTER *****************************************************/\
X(usb_one_the_go_full_speed_low_power_enable,      AHB2LPENR,    OTGFSLPEN,     USBOneTheGoFullSpeedLowPowerEnable,    SET_RMW )\
\
/************************************************* RCC APB1LPENR REGISTER *****************************************************/\
X(timer_2_low_power_enable,                        APB1LPENR,    TIM2LPEN,      Timer2LowPowerEnable,                  SET_RMW )\
X(timer_3_low_power_enable,                        APB1LPENR,    TIM3LPEN,      Timer3LowPowerEnable,                  SET_RMW )\
X(timer_4_low_power_enable,                        APB1LPENR,    TIM4LPEN,      Timer4LowPowerEnable,                  SET_RMW )\
X(timer_5_low_power_enable,                        APB1LPENR,    TIM5LPEN,      Timer5LowPowerEnable,                  SET_RMW )\
X(window_watchdog_low_power_enable,                APB1LPENR,    WWDGLPEN,      WindowWatchdogLowPowerEnable,          SET_RMW )\
X(spi_2_low_power_enable,                          APB1LPENR,    SPI2LPEN,      SPI2LowPowerEnable,                    SET_RMW )\
X(spi_3_low_power_enable,                          APB1LPENR,    SPI3LPEN,      SPI3LowPowerEnable,                    SET_RMW )\
X(usart_2_low_power_enable,                        APB1LPENR,    USART2LPEN,    USART2LowPowerEnable,                  SET_RMW )\
X(i2c_1_low_power_enable,                          APB1LPENR,    I2C1LPEN,      I2C1LowPowerEnable,                    SET_RMW )\
X(i2c_2_low_power_enable,                          APB1LPENR,    I2C2LPEN,      I2C2LowPowerEnable,                    SET_RMW )\
X(i2c_3_low_power_enable,                          APB1LPENR,    I2C3LPEN,      I2C3LowPowerEnable,                    SET_RMW )\
X(power_low_power_enable,                          APB1LPENR,    PWRLPEN,       PowerLowPowerEnable,                   SET_RMW )\
\
/************************************************* RCC APB2LPENR REGISTER *****************************************************/\
X(timer_1_low_power_enable,                        APB2LPENR,    TIM1LPEN,      Timer1LowPowerEnable,                  SET_RMW )\
X(usart_1_low_power_enable,                        APB2LPENR,    USART1LPEN,    USART1LowPowerEnable,                  SET_RMW )\
X(usart_6_low_power_enable,                        APB2LPENR,    USART6LPEN,    USART6LowPowerEnable,                  SET_RMW )\
X(analog_digital_converter_1_low_power_enable,     APB2LPENR,    ADC1LPEN,      AnalogDigitalConverter1LowPowerEnable, SET_RMW )\
X(secure_digital_input_output_low_power_enable,    APB2LPENR,    SDIOLPEN,      SecureDigitalInputOutputLowPowerEnable,SET_RMW )\
X(spi_1_low_power_enable,                          APB2LPENR,    SPI1LPEN,      SPI1LowPowerEnable,                    SET_RMW )\
X(spi_4_low_power_enable,                          APB2LPENR,    SPI4LPEN,      SPI4LowPowerEnable,                    SET_RMW )\
X(system_config_low_power_enable,                  APB2LPENR,    SYSCFGLPEN,    SystemConfigLowPowerEnable,            SET_RMW )\
X(timer_9_low_power_enable,                        APB2LPENR,    TIM9LPEN,      Timer9LowPowerEnable,                  SET_RMW )\
X(timer_10_low_power_enable,                       APB2LPENR,    TIM10LPEN,     Timer10LowPowerEnable,                 SET_RMW )\
X(timer_11_low_power_enable,                       APB2LPENR,    TIM11LPEN,     Timer11LowPowerEnable,                 SET_RMW )\
\
/************************************************* RCC BDCR REGISTER **********************************************************/\
X(external_low_speed_oscillator_enable,            BDCR,         LSEON,         ExternalLowSpeedOscillatorEnable,      SET_RMW )\
X(external_low_speed_oscillator_ready,             BDCR,         LSERDY,        ExternalLowSpeedOscillatorReady,       RO      )\
X(external_low_speed_oscillator_bypass,            BDCR,         LSEBYP,        ExternalLowSpeedOscillatorBypass,      SET_RMW )\
X(real_time_clock_source_selection,                BDCR,         RTCSEL,        RealTimeClockSourceSelection,          SET_RMW )\
X(real_time_clock_enable,                          BDCR,         RTCEN,         RealTimeClockEnable,                   SET_RMW )\
X(backup_domain_software_reset,                    BDCR,         BDRST,         BackupDomainSoftwareReset,             SET_RMW )\
\
/************************************************* RCC CSR REGISTER ***********************************************************/\
X(internal_low_speed_oscillator_enable,            CSR,          LSION,         InternalLowSpeedOscillatorEnable,      SET_RMW )\
X(internal_low_speed_oscillator_ready,             CSR,          LSIRDY,        InternalLowSpeedOscillatorReady,       RO      )\
X(remove_reset_flag,                               CSR,          RMVF,          RemoveResetFlag,                       SET_RMW )\
X(bor_reset_flag,                                  CSR,          BORRSTF,       BORResetFlag,                          RO      )\
X(pin_reset_flag,                                  CSR,          PINRSTF,       PINResetFlag,                          RO      )\
X(por_pdr_reset_flag,                              CSR,          PORRSTF,       PORPDRResetFlag,                       RO      )\
X(software_reset_flag,                             CSR,          SFTRSTF,       SoftwareResetFlag,                     RO      )\
X(independent_watchdog_reset_flag,                 CSR,          IWDGRSTF,      IndependentWatchdogResetFlag,          RO      )\
X(window_watchdog_reset_flag,                      CSR,          WWDGRSTF,      WindowWatchdogResetFlag,               RO      )\
X(low_power_reset_flag,                            CSR,          LPWRRSTF,      LowPowerResetFlag,                     RO      )\
\
/************************************************* RCC SSCGR REGISTER *********************************************************/\
X(modulation_period,                               SSCGR,        MODPER,        ModulationPeriod,                      SET_RMW )\
X(incrementation_step,                             SSCGR,        INCSTEP,       IncrementationStep,                    SET_RMW )\
X(spread_select,                                   SSCGR,        SPREADSEL,     SpreadSelect,                          SET_RMW )\
X(spread_spectrum_modulation_enable,               SSCGR,        SSCGEN,        SpreadSpectrumModulationEnable,        SET_RMW )\
\
/************************************************* RCC PLLI2SCFGR REGISTER ****************************************************/\
X(phase_locked_loop_i2s_multiplication,            PLLI2SCFGR,   PLLI2SN,       PhaseLockedLoopI2SMultiplication,      SET_RMW )\
X(phase_locked_loop_i2s_division,                  PLLI2SCFGR,   PLLI2SR,       PhaseLockedLoopI2SDivision,            SET_RMW )\
\
/************************************************* RCC DCKCFGR REGISTER *******************************************************/\
X(timers_prescaler,                                DCKCFGR,      TIMPRE,        TimersPrescaler,                       SET_RMW )

/*----------------------------------------------------------------------------
 * Writer Generators (Dispatched by 5th column: SET_RMW, SET_WO, RO)
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a read-modify-write `static inline` setter for multi-field RCC registers.
 * @param  short_name  Snake-case function suffix (e.g., `gpio_b_enable`).
 * @param  _reg        Target register member in @ref PLAY32_RCC_TypeDef (e.g., `AHB1ENR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `GPIOBEN`).
 * @param  _type       Type suffix matching `PLAY32_RCC_<_reg>_<_type>` (e.g., `GPIOBEnable`).
 */
#define GEN_SET_RMW(short_name, _reg, _sub_reg, _type)                                          \
    /**                                                                                         \
     * @brief  Sets the @c _sub_reg field (@c short_name) in @c RCC_##_reg.                     \
     * @param[in] value  Typed value to write (@see PLAY32_RCC_##_reg##_##_type).               \
     */                                                                                         \
    static inline void play32_rcc_set_##short_name(                                             \
        const PLAY32_RCC_##_reg##_##_type value                                                 \
    ) {                                                                                         \
        PLAY32_RCC->_reg = (PLAY32_RCC->_reg & ~(PLAY32_RCC_##_reg##_##_sub_reg##_MSK))         \
            | (((uint32_t)value << (PLAY32_RCC_##_reg##_##_sub_reg##_POS))                      \
            & (PLAY32_RCC_##_reg##_##_sub_reg##_MSK));                                          \
    }

/**
 * @brief  Generates a single-write `static inline` setter for write-only self-clearing RCC bits.
 * @details Compiles to a single `STR` instruction without read-modify-write overhead
 *          (used for `RCC_CIR` `*C` interrupt clear flags).
 * @param  short_name  Snake-case function suffix (e.g., `high_speed_external_ready_interrupt_clear`).
 * @param  _reg        Target register member in @ref PLAY32_RCC_TypeDef (`CIR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_MSK` macro (e.g., `HSERDYC`).
 * @param  _type       Type suffix matching `PLAY32_RCC_<_reg>_<_type>`.
 */
#define GEN_SET_WO(short_name, _reg, _sub_reg, _type)                                           \
    /**                                                                                         \
     * @brief  Triggers @c short_name (@c _sub_reg) in write-only @c RCC_##_reg.                \
     * @param[in] value  Control switch state (@see PLAY32_RCC_##_reg##_##_type).               \
     */                                                                                         \
    static inline void play32_rcc_set_##short_name(                                             \
        const PLAY32_RCC_##_reg##_##_type value                                                 \
    ) {                                                                                         \
        if (value == PLAY32_RCC_SWITCH_ENABLED) {                                               \
            PLAY32_RCC->_reg = PLAY32_RCC_##_reg##_##_sub_reg##_MSK;                            \
        }                                                                                       \
    }

/** @brief Read-only field guard: emits no setter function. */
#define GEN_RO(short_name, _reg, _sub_reg, _type) /* Read-only: no setter emitted */

/** @brief Dispatches writer generation based on the table's access-mode column. */
#define DISPATCH_WRITER(short_name, _reg, _sub_reg, _type, mode)                                \
    GEN_##mode(short_name, _reg, _sub_reg, _type)

/*----------------------------------------------------------------------------
 * Reader Generators (Skips write-only clear bits automatically)
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a `static inline` getter for a readable RCC register field.
 * @param  short_name  Snake-case function suffix (e.g., `system_clock_switch_status`).
 * @param  _reg        Target register member in @ref PLAY32_RCC_TypeDef (e.g., `CFGR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `SWS`).
 * @param  _type       Type suffix matching `PLAY32_RCC_<_reg>_<_type>` (e.g., `SystemClockSwitchStatus`).
 */
#define GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)                                       \
    /**                                                                                         \
     * @brief  Gets the current @c _sub_reg field (@c short_name) from @c RCC_##_reg.           \
     * @return Current field value cast to @ref PLAY32_RCC_##_reg##_##_type.                    \
     */                                                                                         \
    static inline PLAY32_RCC_##_reg##_##_type play32_rcc_get_##short_name(void) {               \
        return (PLAY32_RCC_##_reg##_##_type)                                                    \
            ((PLAY32_RCC->_reg & (PLAY32_RCC_##_reg##_##_sub_reg##_MSK))                        \
            >> (PLAY32_RCC_##_reg##_##_sub_reg##_POS));                                         \
    }

#define GET_SET_RMW(short_name, _reg, _sub_reg, _type) GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_RO(short_name, _reg, _sub_reg, _type)      GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_SET_WO(short_name, _reg, _sub_reg, _type)  /* Write-only clear bit: no getter emitted */

/** @brief Dispatches reader generation based on the table's access-mode column. */
#define DISPATCH_READER(short_name, _reg, _sub_reg, _type, mode)                                \
    GET_##mode(short_name, _reg, _sub_reg, _type)

/* Instantiate all RCC setter and getter inline functions */
RCC_REGISTERS_TABLE(DISPATCH_WRITER)
RCC_REGISTERS_TABLE(DISPATCH_READER)

#undef GEN_SET_RMW
#undef GEN_SET_WO
#undef GEN_RO
#undef DISPATCH_WRITER
#undef GEN_GET_COMMON
#undef GET_SET_RMW
#undef GET_RO
#undef GET_SET_WO
#undef DISPATCH_READER

/** @} */ /* End of PLAY32_RCC_Driver */
/** @} */ /* End of PLAY32_RCC */

#endif /* PLAY32_RCC_H */
