/**
 * @file    timx_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for General-Purpose Timers (TIM2-TIM5) of STM32F401 CCU.
 * @version 1.0.0
 * @date    2026-11-08
 *
 * @note    This file provides a strict compile-time type-safe interface
 *          for hardware registers manipulation without runtime overhead.
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_TIMx_TYPES_H
#define PLAY32_TIMx_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup PLAY32_TIMx General-Purpose Timers (TIM2-TIM5)
 * @brief Hardware register map, base addresses, bit masks, and type-safe enumerations for TIM2-TIM5.
 * @{
 */

/**
 * @defgroup PLAY32_TIMx_Memory_Map Peripheral Base Addresses and Instances
 * @brief APB1 base addresses, address offsets, and peripheral pointer declarations for TIM2-TIM5.
 * @{
 */

/**
 * @brief  Base address of the APB1 peripheral bus (0x40000000).
 * @note   TIM2, TIM3, TIM4, and TIM5 are all mapped sequentially starting at the base
 *         of the APB1 peripheral memory region in STM32F401.
 */
#define PLAY32_TIMx_PERIPHERAL    (1UL << 30)

/**
 * @brief  Memory block size allocated per timer instance (0x0400 bytes / 1 KB).
 * @note   Used as the address stride between consecutive APB1 timer peripheral boundaries.
 */
#define PLAY32_TIMx_SIZE          (0x0400U)

/**
 * @brief  APB1 memory slot index for TIM2 (offset 0x0000).
 * @see    PLAY32_TIM2_BASE
 */
#define PLAY32_TIM2_BASE_POS      (0U)

/**
 * @brief  APB1 memory slot index for TIM3 (offset 0x0400).
 * @see    PLAY32_TIM3_BASE
 */
#define PLAY32_TIM3_BASE_POS      (1U)

/**
 * @brief  APB1 memory slot index for TIM4 (offset 0x0800).
 * @see    PLAY32_TIM4_BASE
 */
#define PLAY32_TIM4_BASE_POS      (2U)

/**
 * @brief  APB1 memory slot index for TIM5 (offset 0x0C00).
 * @see    PLAY32_TIM5_BASE
 */
#define PLAY32_TIM5_BASE_POS      (3U)

/**
 * @brief  TIM2 peripheral base address (0x40000000).
 * @note   Computed from @ref PLAY32_TIMx_PERIPHERAL and @ref PLAY32_TIM2_BASE_POS.
 * @see    PLAY32_TIM2
 */
#define PLAY32_TIM2_BASE          (PLAY32_TIMx_PERIPHERAL + (PLAY32_TIM2_BASE_POS * PLAY32_TIMx_SIZE))

/**
 * @brief  TIM3 peripheral base address (0x40000400).
 * @note   Computed from @ref PLAY32_TIMx_PERIPHERAL and @ref PLAY32_TIM3_BASE_POS.
 * @see    PLAY32_TIM3
 */
#define PLAY32_TIM3_BASE          (PLAY32_TIMx_PERIPHERAL + (PLAY32_TIM3_BASE_POS * PLAY32_TIMx_SIZE))

/**
 * @brief  TIM4 peripheral base address (0x40000800).
 * @note   Computed from @ref PLAY32_TIMx_PERIPHERAL and @ref PLAY32_TIM4_BASE_POS.
 * @see    PLAY32_TIM4
 */
#define PLAY32_TIM4_BASE          (PLAY32_TIMx_PERIPHERAL + (PLAY32_TIM4_BASE_POS * PLAY32_TIMx_SIZE))

/**
 * @brief  TIM5 peripheral base address (0x40000C00).
 * @note   Computed from @ref PLAY32_TIMx_PERIPHERAL and @ref PLAY32_TIM5_BASE_POS.
 * @see    PLAY32_TIM5
 */
#define PLAY32_TIM5_BASE          (PLAY32_TIMx_PERIPHERAL + (PLAY32_TIM5_BASE_POS * PLAY32_TIMx_SIZE))

/**
 * @brief  General-Purpose Timer (TIM2-TIM5) hardware register map structure.
 * @note   Matches the memory-mapped register layout in STM32F401 RM0368 (Section 13.4).
 * @warning TIM2 and TIM5 feature 32-bit CNT, ARR, and CCR1-CCR4 registers, whereas
 *          TIM3 and TIM4 are 16-bit timers (upper 16 bits are reserved and read as 0).
 * @see    PLAY32_TIM2
 * @see    PLAY32_TIM3
 * @see    PLAY32_TIM4
 * @see    PLAY32_TIM5
 */
typedef struct {
    volatile uint32_t CR1;                      /**< Offset: 0x00 - TIM control register 1. */
    volatile uint32_t CR2;                      /**< Offset: 0x04 - TIM control register 2. */
    volatile uint32_t SMCR;                     /**< Offset: 0x08 - TIM slave mode control register. */
    volatile uint32_t DIER;                     /**< Offset: 0x0C - TIM DMA/interrupt enable register. */
    volatile uint32_t SR;                       /**< Offset: 0x10 - TIM status register. */
    volatile uint32_t EGR;                      /**< Offset: 0x14 - TIM event generation register. */
    volatile uint32_t CCMR1;                    /**< Offset: 0x18 - TIM capture/compare mode register 1. */
    volatile uint32_t CCMR2;                    /**< Offset: 0x1C - TIM capture/compare mode register 2. */
    volatile uint32_t CCER;                     /**< Offset: 0x20 - TIM capture/compare enable register. */
    volatile uint32_t CNT;                      /**< Offset: 0x24 - TIM counter register (32-bit on TIM2/TIM5, 16-bit on TIM3/TIM4). */
    volatile uint32_t PSC;                      /**< Offset: 0x28 - TIM prescaler register (16-bit). */
    volatile uint32_t ARR;                      /**< Offset: 0x2C - TIM auto-reload register (32-bit on TIM2/TIM5, 16-bit on TIM3/TIM4). */
    uint32_t          PLAY32_TIMx_RESERVED_0;   /**< Offset: 0x30 - Reserved (do not access). */
    volatile uint32_t CCR1;                     /**< Offset: 0x34 - TIM capture/compare register 1. */
    volatile uint32_t CCR2;                     /**< Offset: 0x38 - TIM capture/compare register 2. */
    volatile uint32_t CCR3;                     /**< Offset: 0x3C - TIM capture/compare register 3. */
    volatile uint32_t CCR4;                     /**< Offset: 0x40 - TIM capture/compare register 4. */
    uint32_t          PLAY32_TIMx_RESERVED_1;   /**< Offset: 0x44 - Reserved (do not access). */
    volatile uint32_t DCR;                      /**< Offset: 0x48 - TIM DMA control register. */
    volatile uint32_t DMAR;                     /**< Offset: 0x4C - TIM DMA address for full transfer register. */
    volatile uint32_t OR;                       /**< Offset: 0x50 - TIM option register (available on TIM2 and TIM5 only). */
} PLAY32_TIMx_TypeDef;

/**
 * @brief  TIM2 peripheral register map pointer (32-bit general-purpose timer).
 * @note   Mapped to @ref PLAY32_TIM2_BASE (0x40000000) on the APB1 bus.
 * @see    PLAY32_TIMx_TypeDef
 */
#define PLAY32_TIM2 ((PLAY32_TIMx_TypeDef *)PLAY32_TIM2_BASE)

/**
 * @brief  TIM3 peripheral register map pointer (16-bit general-purpose timer).
 * @note   Mapped to @ref PLAY32_TIM3_BASE (0x40000400) on the APB1 bus.
 * @see    PLAY32_TIMx_TypeDef
 */
#define PLAY32_TIM3 ((PLAY32_TIMx_TypeDef *)PLAY32_TIM3_BASE)

/**
 * @brief  TIM4 peripheral register map pointer (16-bit general-purpose timer).
 * @note   Mapped to @ref PLAY32_TIM4_BASE (0x40000800) on the APB1 bus.
 * @see    PLAY32_TIMx_TypeDef
 */
#define PLAY32_TIM4 ((PLAY32_TIMx_TypeDef *)PLAY32_TIM4_BASE)

/**
 * @brief  TIM5 peripheral register map pointer (32-bit general-purpose timer).
 * @note   Mapped to @ref PLAY32_TIM5_BASE (0x40000C00) on the APB1 bus.
 * @see    PLAY32_TIMx_TypeDef
 */
#define PLAY32_TIM5 ((PLAY32_TIMx_TypeDef *)PLAY32_TIM5_BASE)

/** @} */ /* End of PLAY32_TIMx_Memory_Map */

/**
 * @defgroup PLAY32_TIMx_Common_Types Common Timer Enumerations
 * @brief Reusable active-high, active-low, and status flag enumerations across TIMx registers.
 * @{
 */
#pragma region TIMx_COMMON_ENUM

/**
 * @brief  Standard active-high enable/disable switch state enumeration.
 * @note   Generic 1-bit Read/Write control type used for standard timer enable bits
 *         (such as CEN, OPM, ARPE, and CCxE) where 1 enables the feature.
 * @see    PLAY32_TIMx_InvertedSwitch
 */
typedef enum {
    PLAY32_TIMx_SWITCH_DISABLED = 0U, /**< Feature or channel is disabled (0). */
    PLAY32_TIMx_SWITCH_ENABLED  = 1U  /**< Feature or channel is enabled (1). */
} PLAY32_TIMx_Switch;

/**
 * @brief  Active-low (inverted) enable/disable switch state enumeration.
 * @note   Generic 1-bit Read/Write control type used for disable-polarity bits
 *         (such as UDIS in TIMx_CR1) where 0 enables the feature and 1 disables it.
 * @warning Observe inverted logic: writing @ref PLAY32_TIMx_SWITCH_INVERTED_ENABLED writes 0U.
 * @see    PLAY32_TIMx_Switch
 */
typedef enum {
    PLAY32_TIMx_SWITCH_INVERTED_ENABLED  = 0U, /**< Feature is enabled (bit cleared to 0). */
    PLAY32_TIMx_SWITCH_INVERTED_DISABLED = 1U  /**< Feature is disabled (bit set to 1). */
} PLAY32_TIMx_InvertedSwitch;

/**
 * @brief  Timer hardware event and interrupt flag state enumeration.
 * @note   Generic 1-bit status type used in TIMx_SR to report update, capture/compare,
 *         trigger, and overcapture events.
 * @warning Most flags in TIMx_SR are cleared by software writing 0 (rc_w0); writing 1 has no effect.
 * @see    PLAY32_TIMx_Switch
 */
typedef enum {
    PLAY32_TIMx_FLAG_NOT_SET = 0UL, /**< Event flag is cleared (no event occurred). */
    PLAY32_TIMx_FLAG_SET     = 1UL  /**< Event flag is set (hardware event occurred). */
} PLAY32_TIMx_Flag;

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_Common_Types */
/**
 * @defgroup PLAY32_TIMx_CR1_Types TIM Control Register 1 (TIMx_CR1)
 * @brief Bit positions, masks, and field types for TIMx_CR1 (offset 0x00).
 * @{
 */
#pragma region TIMx_CR1_REGISTER

#pragma region TIMx_CR1_REGISTER_POSITION
#define PLAY32_TIMx_CR1_CEN_POS     (0U) /**< Bit 0: Counter enable position. */
#define PLAY32_TIMx_CR1_UDIS_POS    (1U) /**< Bit 1: Update disable position. */
#define PLAY32_TIMx_CR1_URS_POS     (2U) /**< Bit 2: Update request source position. */
#define PLAY32_TIMx_CR1_OPM_POS     (3U) /**< Bit 3: One-pulse mode position. */
#define PLAY32_TIMx_CR1_DIR_POS     (4U) /**< Bit 4: Direction position. */
#define PLAY32_TIMx_CR1_CMS_POS     (5U) /**< Bits [6:5]: Center-aligned mode selection position. */
#define PLAY32_TIMx_CR1_ARPE_POS    (7U) /**< Bit 7: Auto-reload preload enable position. */
#define PLAY32_TIMx_CR1_CKD_POS     (8U) /**< Bits [9:8]: Clock division position. */
#pragma endregion

#pragma region TIMx_CR1_REGISTER_MASK
#define PLAY32_TIMx_CR1_CEN_MSK     (1UL << PLAY32_TIMx_CR1_CEN_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_TIMx_CR1_UDIS_MSK    (1UL << PLAY32_TIMx_CR1_UDIS_POS) /**< Bit 1 mask (0x00000002). */
#define PLAY32_TIMx_CR1_URS_MSK     (1UL << PLAY32_TIMx_CR1_URS_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_TIMx_CR1_OPM_MSK     (1UL << PLAY32_TIMx_CR1_OPM_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_TIMx_CR1_DIR_MSK     (1UL << PLAY32_TIMx_CR1_DIR_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_TIMx_CR1_CMS_MSK     (3UL << PLAY32_TIMx_CR1_CMS_POS)  /**< Bits [6:5] mask (0x00000060). */
#define PLAY32_TIMx_CR1_ARPE_MSK    (1UL << PLAY32_TIMx_CR1_ARPE_POS) /**< Bit 7 mask (0x00000080). */
#define PLAY32_TIMx_CR1_CKD_MSK     (3UL << PLAY32_TIMx_CR1_CKD_POS)  /**< Bits [9:8] mask (0x00000300). */
#pragma endregion

#pragma region TIMx_CR1_REGISTER_ENUM

/**
 * @brief  Counter enable (CEN) state type.
 * @note   Read/Write control bit (bit 0 of TIMx_CR1, CEN) used to start or stop the timer counter.
 * @warning External clock, gated mode, and encoder mode can work only after the CEN bit
 *          has been previously set by software.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CR1_CounterEnable;

/**
 * @brief  Update disable (UDIS) state type.
 * @note   Read/Write inverted control bit (bit 1 of TIMx_CR1, UDIS) used to enable or disable
 *         Update event (UEV) generation and shadow register transfers.
 * @warning When disabled (1), shadow registers (ARR, PSC, CCRx) keep their values and no UEV
 *          is generated on counter overflow/underflow or UG bit setting.
 * @see    PLAY32_TIMx_InvertedSwitch
 */
typedef PLAY32_TIMx_InvertedSwitch PLAY32_TIMx_CR1_UpdateDisable;

/**
 * @brief  Update request source (URS) selection enumeration.
 * @note   Read/Write control bit (bit 2 of TIMx_CR1, URS) used to select the event sources
 *         that can generate an update interrupt or DMA request (if enabled).
 * @see    PLAY32_TIMx_CR1_UpdateDisable
 */
typedef enum {
    PLAY32_TIMx_CR1_UPDATE_REQUEST_SOURCE_ANY                = 0U, /**< Counter overflow/underflow, setting UG bit, or update through slave mode controller. */
    PLAY32_TIMx_CR1_UPDATE_REQUEST_SOURCE_OVERFLOW_UNDERFLOW = 1U  /**< Only counter overflow/underflow generates an update interrupt or DMA request. */
} PLAY32_TIMx_CR1_UpdateRequestSource;

/**
 * @brief  One-pulse mode (OPM) state type.
 * @note   Read/Write control bit (bit 3 of TIMx_CR1, OPM) used to make the counter stop
 *         automatically at the next update event (clearing the CEN bit).
 * @see    PLAY32_TIMx_Switch
 * @see    PLAY32_TIMx_CR1_CounterEnable
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CR1_OnePulseMode;

/**
 * @brief  Counter counting direction (DIR) enumeration.
 * @note   Read/Write control bit (bit 4 of TIMx_CR1, DIR) used to select upcounting or downcounting.
 * @warning This bit is read-only when the timer is configured in Center-aligned mode or Encoder mode.
 * @see    PLAY32_TIMx_CR1_CenterAlignedModeSelection
 */
typedef enum {
    PLAY32_TIMx_CR1_DIRECTION_UPCOUNTER   = 0U, /**< Counter counts up from 0 to ARR. */
    PLAY32_TIMx_CR1_DIRECTION_DOWNCOUNTER = 1U  /**< Counter counts down from ARR to 0. */
} PLAY32_TIMx_CR1_Direction;

/**
 * @brief  Center-aligned mode selection (CMS) enumeration.
 * @note   Read/Write 2-bit field (bits 6:5 of TIMx_CR1, CMS[1:0]) used to select edge-aligned
 *         mode or one of three center-aligned (up/down) PWM counting modes.
 * @warning It is not allowed to switch from edge-aligned mode to center-aligned mode while
 *          the counter is enabled (CEN = 1).
 * @see    PLAY32_TIMx_CR1_Direction
 */
typedef enum {
    PLAY32_TIMx_CR1_CENTER_ALIGNED_MODE_EDGE_ALIGNED = 0U, /**< Edge-aligned mode; counter counts up or down depending on DIR bit. */
    PLAY32_TIMx_CR1_CENTER_ALIGNED_MODE_1            = 1U, /**< Center-aligned mode 1; output compare interrupt flags set only when counting down. */
    PLAY32_TIMx_CR1_CENTER_ALIGNED_MODE_2            = 2U, /**< Center-aligned mode 2; output compare interrupt flags set only when counting up. */
    PLAY32_TIMx_CR1_CENTER_ALIGNED_MODE_3            = 3U  /**< Center-aligned mode 3; output compare interrupt flags set both when counting up and down. */
} PLAY32_TIMx_CR1_CenterAlignedModeSelection;

/**
 * @brief  Auto-reload preload enable (ARPE) state type.
 * @note   Read/Write control bit (bit 7 of TIMx_CR1, ARPE) used to buffer TIMx_ARR via its
 *         preload register so updates take effect only at the next Update event (UEV).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CR1_AutoReloadPreloadEnable;

/**
 * @brief  Clock division ratio (CKD) enumeration.
 * @note   Read/Write 2-bit field (bits 9:8 of TIMx_CR1, CKD[1:0]) indicating the division ratio
 *         between the timer clock (CK_INT) frequency and the dead-time / digital filter sampling clock (t_DTS).
 * @warning Value @ref PLAY32_TIMx_CR1_CLOCK_DIVISION_RESERVED (3U) is reserved by hardware and must not be used.
 */
typedef enum {
    PLAY32_TIMx_CR1_CLOCK_DIVISION_DEFAULT  = 0U, /**< t_DTS = t_CK_INT (1x clock). */
    PLAY32_TIMx_CR1_CLOCK_DIVISION_2        = 1U, /**< t_DTS = 2 * t_CK_INT. */
    PLAY32_TIMx_CR1_CLOCK_DIVISION_4        = 2U, /**< t_DTS = 4 * t_CK_INT. */
    PLAY32_TIMx_CR1_CLOCK_DIVISION_RESERVED = 3U  /**< Reserved (do not write). */
} PLAY32_TIMx_CR1_ClockDivision;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CR1_Types */
/**
 * @defgroup PLAY32_TIMx_CR2_Types TIM Control Register 2 (TIMx_CR2)
 * @brief Bit positions, masks, and field types for TIMx_CR2 (offset 0x04).
 * @{
 */
#pragma region TIMx_CR2_REGISTER

#pragma region TIMx_CR2_REGISTER_POSITION
#define PLAY32_TIMx_CR2_CCDS_POS    (3U) /**< Bit 3: Capture/compare DMA selection position. */
#define PLAY32_TIMx_CR2_MMS_POS     (4U) /**< Bits [6:4]: Master mode selection position. */
#define PLAY32_TIMx_CR2_TI1S_POS    (7U) /**< Bit 7: TI1 selection position. */
#pragma endregion

#pragma region TIMx_CR2_REGISTER_MASK
#define PLAY32_TIMx_CR2_CCDS_MSK    (1UL << PLAY32_TIMx_CR2_CCDS_POS) /**< Bit 3 mask (0x00000008). */
#define PLAY32_TIMx_CR2_MMS_MSK     (7UL << PLAY32_TIMx_CR2_MMS_POS)  /**< Bits [6:4] mask (0x00000070). */
#define PLAY32_TIMx_CR2_TI1S_MSK    (1UL << PLAY32_TIMx_CR2_TI1S_POS) /**< Bit 7 mask (0x00000080). */
#pragma endregion

#pragma region TIMx_CR2_REGISTER_ENUM

/**
 * @brief  Capture/compare DMA selection (CCDS) enumeration.
 * @note   Read/Write control bit (bit 3 of TIMx_CR2, CCDS) determining whether capture/compare
 *         DMA requests are sent on CCx events or on Update events.
 */
typedef enum {
    PLAY32_TIM_CR2_CAPTURE_COMPARE_DMA_SELECTION_REQ_ON_CCX_EVENT = 0U, /**< CCx DMA request sent when CCx event occurs. */
    PLAY32_TIM_CR2_CAPTURE_COMPARE_DMA_SELECTION_REQ_ON_UPDATE    = 1U  /**< CCx DMA requests sent when Update event occurs. */
} PLAY32_TIMx_CR2_CaptureCompareDMASelection;

/**
 * @brief  Master mode selection (MMS) enumeration.
 * @note   Read/Write 3-bit field (bits 6:4 of TIMx_CR2, MMS[2:0]) used to select the internal
 *         signal sent in master mode to slave timers for synchronization (TRGO).
 * @warning The clock of the slave timer or ADC must be enabled prior to receiving events
 *          from the master timer via TRGO.
 */
typedef enum {
    PLAY32_TIM_CR2_MASTER_MODE_SELECTION_RESET          = 0U, /**< UG bit from TIMx_EGR is used as trigger output (TRGO). */
    PLAY32_TIM_CR2_MASTER_MODE_SELECTION_ENABLE         = 1U, /**< Counter enable signal (CNT_EN) is used as trigger output (TRGO). */
    PLAY32_TIM_CR2_MASTER_MODE_SELECTION_UPDATE         = 2U, /**< Update event is selected as trigger output (TRGO). */
    PLAY32_TIM_CR2_MASTER_MODE_SELECTION_COMPARE_PULSE  = 3U, /**< Trigger output sends a positive pulse when CC1IF flag is set. */
    PLAY32_TIM_CR2_MASTER_MODE_SELECTION_COMPARE_OC1REF = 4U, /**< OC1REF signal is used as trigger output (TRGO). */
    PLAY32_TIM_CR2_MASTER_MODE_SELECTION_COMPARE_OC2REF = 5U, /**< OC2REF signal is used as trigger output (TRGO). */
    PLAY32_TIM_CR2_MASTER_MODE_SELECTION_COMPARE_OC3REF = 6U, /**< OC3REF signal is used as trigger output (TRGO). */
    PLAY32_TIM_CR2_MASTER_MODE_SELECTION_COMPARE_OC4REF = 7U  /**< OC4REF signal is used as trigger output (TRGO). */
} PLAY32_TIMx_CR2_MasterModeSelection;

/**
 * @brief  TI1 input selection (TI1S) enumeration.
 * @note   Read/Write control bit (bit 7 of TIMx_CR2, TI1S) selecting whether the TIMx_CH1 pin
 *         alone or the XOR combination of CH1, CH2, and CH3 pins drives the TI1 input (for Hall sensors).
 */
typedef enum {
    PLAY32_TIM_CR2_T1_SELECTION_CH1         = 0U, /**< TIMx_CH1 pin is connected to TI1 input. */
    PLAY32_TIM_CR2_T1_SELECTION_CH1_CH2_CH3 = 1U  /**< TIMx_CH1, CH2, and CH3 pins are XOR-connected to TI1 input. */
} PLAY32_TIMx_CR2_T1Selection;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CR2_Types */
/**
 * @defgroup PLAY32_TIMx_SMCR_Types TIM Slave Mode Control Register (TIMx_SMCR)
 * @brief Bit positions, masks, and field types for TIMx_SMCR (offset 0x08).
 * @{
 */
#pragma region TIMx_SMCR_REGISTER

#pragma region TIMx_SMCR_REGISTER_POSITION
#define PLAY32_TIMx_SMCR_SMS_POS     (0U)  /**< Bits [2:0]: Slave mode selection position. */
#define PLAY32_TIMx_SMCR_TS_POS      (4U)  /**< Bits [6:4]: Trigger selection position. */
#define PLAY32_TIMx_SMCR_MSM_POS     (7U)  /**< Bit 7: Master/slave mode position. */
#define PLAY32_TIMx_SMCR_ETF_POS     (8U)  /**< Bits [11:8]: External trigger filter position. */
#define PLAY32_TIMx_SMCR_ETPS_POS    (12U) /**< Bits [13:12]: External trigger prescaler position. */
#define PLAY32_TIMx_SMCR_ECE_POS     (14U) /**< Bit 14: External clock enable position. */
#define PLAY32_TIMx_SMCR_ETP_POS     (15U) /**< Bit 15: External trigger polarity position. */
#pragma endregion

#pragma region TIMx_SMCR_REGISTER_MASK
#define PLAY32_TIMx_SMCR_SMS_MSK     (7UL << PLAY32_TIMx_SMCR_SMS_POS)   /**< Bits [2:0] mask (0x00000007). */
#define PLAY32_TIMx_SMCR_TS_MSK      (7UL << PLAY32_TIMx_SMCR_TS_POS)    /**< Bits [6:4] mask (0x00000070). */
#define PLAY32_TIMx_SMCR_MSM_MSK     (1UL << PLAY32_TIMx_SMCR_MSM_POS)   /**< Bit 7 mask (0x00000080). */
#define PLAY32_TIMx_SMCR_ETF_MSK     (15UL << PLAY32_TIMx_SMCR_ETF_POS)  /**< Bits [11:8] mask (0x00000F00). */
#define PLAY32_TIMx_SMCR_ETPS_MSK    (3UL << PLAY32_TIMx_SMCR_ETPS_POS)  /**< Bits [13:12] mask (0x00003000). */
#define PLAY32_TIMx_SMCR_ECE_MSK     (1UL << PLAY32_TIMx_SMCR_ECE_POS)   /**< Bit 14 mask (0x00004000). */
#define PLAY32_TIMx_SMCR_ETP_MSK     (1UL << PLAY32_TIMx_SMCR_ETP_POS)   /**< Bit 15 mask (0x00008000). */
#pragma endregion

#pragma region TIMx_SMCR_REGISTER_ENUM

/**
 * @brief  Slave mode selection (SMS) enumeration.
 * @note   Read/Write 3-bit field (bits 2:0 of TIMx_SMCR, SMS[2:0]) used to select how external
 *         or internal trigger inputs control the timer counter (encoder, reset, gated, trigger, or external clock).
 * @warning In Encoder modes (1, 2, or 3), the DIR bit in TIMx_CR1 becomes read-only and is
 *          automatically updated by hardware according to the quadrature input sequence.
 */
typedef enum {
    PLAY32_TIMx_SMCR_SLAVE_MODE_SELECTION_DISABLED       = 0U, /**< Slave mode disabled; prescaler clocked directly by internal clock (CK_INT) if CEN = 1. */
    PLAY32_TIMx_SMCR_SLAVE_MODE_SELECTION_MODE_1         = 1U, /**< Encoder mode 1; counter counts up/down on TI2FP1 edge depending on TI1FP2 level. */
    PLAY32_TIMx_SMCR_SLAVE_MODE_SELECTION_MODE_2         = 2U, /**< Encoder mode 2; counter counts up/down on TI1FP2 edge depending on TI2FP1 level. */
    PLAY32_TIMx_SMCR_SLAVE_MODE_SELECTION_MODE_3         = 3U, /**< Encoder mode 3; counter counts up/down on both TI1FP1 and TI2FP2 edges. */
    PLAY32_TIMx_SMCR_SLAVE_MODE_SELECTION_RESET_MODE     = 4U, /**< Reset mode; rising edge of selected trigger input (TRGI) reinitializes counter and generates update. */
    PLAY32_TIMx_SMCR_SLAVE_MODE_SELECTION_GATED_MODE     = 5U, /**< Gated mode; counter clock is enabled when trigger input (TRGI) is high and stops when low. */
    PLAY32_TIMx_SMCR_SLAVE_MODE_SELECTION_TRIGGER_MODE   = 6U, /**< Trigger mode; counter starts (CEN set by hardware) at a rising edge of trigger TRGI. */
    PLAY32_TIMx_SMCR_SLAVE_MODE_SELECTION_EXT_CLOCK_MODE = 7U  /**< External clock mode 1; rising edges of selected trigger (TRGI) clock the counter. */
} PLAY32_TIMx_SMCR_SlaveModeSelection;

/**
 * @brief  Trigger selection (TS) enumeration.
 * @note   Read/Write 3-bit field (bits 6:4 of TIMx_SMCR, TS[2:0]) used to select the trigger
 *         input (TRGI) used to synchronize the counter.
 * @warning These bits must be changed only when they are not used (e.g., when SMS = 000) to avoid
 *          false edge detections at the transition. Internal trigger ITR0-ITR3 routing depends on the timer instance.
 */
typedef enum {
    PLAY32_TIMx_SMCR_TRIGGER_SELECTION_INTERNAL_TRIGGER_0     = 0U, /**< Internal trigger 0 (ITR0). */
    PLAY32_TIMx_SMCR_TRIGGER_SELECTION_INTERNAL_TRIGGER_1     = 1U, /**< Internal trigger 1 (ITR1). */
    PLAY32_TIMx_SMCR_TRIGGER_SELECTION_INTERNAL_TRIGGER_2     = 2U, /**< Internal trigger 2 (ITR2). */
    PLAY32_TIMx_SMCR_TRIGGER_SELECTION_INTERNAL_TRIGGER_3     = 3U, /**< Internal trigger 3 (ITR3). */
    PLAY32_TIMx_SMCR_TRIGGER_SELECTION_TI1_EDGE_DETECTOR      = 4U, /**< TI1 edge detector (TI1F_ED). */
    PLAY32_TIMx_SMCR_TRIGGER_SELECTION_FILTERED_TIMER_INPUT_1 = 5U, /**< Filtered timer input 1 (TI1FP1). */
    PLAY32_TIMx_SMCR_TRIGGER_SELECTION_FILTERED_TIMER_INPUT_2 = 6U, /**< Filtered timer input 2 (TI2FP2). */
    PLAY32_TIMx_SMCR_TRIGGER_SELECTION_EXTERNAL_TRIGGER_INPUT = 7U  /**< External trigger input (ETRF). */
} PLAY32_TIMx_SMCR_TriggerSelection;

/**
 * @brief  Master/slave mode (MSM) enumeration.
 * @note   Read/Write control bit (bit 7 of TIMx_SMCR, MSM) used to delay the effect of an event
 *         on the trigger input (TRGI) to allow perfect synchronization between the current timer
 *         and its slaves through TRGO.
 * @warning Useful when synchronizing several timers on a single external event; introduces a
 *          slight latency on TRGI processing.
 */
typedef enum {
    PLAY32_TIMx_SMCR_MASTER_SLAVE_MODE_NO_ACTION    = 0U, /**< No action (normal trigger propagation). */
    PLAY32_TIMx_SMCR_MASTER_SLAVE_MODE_SYNC_ENABLED = 1U  /**< The effect of an event on TRGI is delayed to synchronize with slave timers via TRGO. */
} PLAY32_TIMx_SMCR_MasterSlaveMode;

/**
 * @brief  External trigger filter (ETF) enumeration.
 * @note   Read/Write 4-bit field (bits 11:8 of TIMx_SMCR, ETF[3:0]) defining the sampling frequency
 *         and the number of consecutive identical samples (N) required to validate a transition on ETRP.
 * @see    PLAY32_TIMx_CR1_ClockDivision
 */
typedef enum {
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_NO_FILTER      = 0U,  /**< No filter, sampling is done at f_DTS. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_CK_INT_N_2   = 1U,  /**< f_SAMPLING = f_CK_INT, N = 2 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_CK_INT_N_4   = 2U,  /**< f_SAMPLING = f_CK_INT, N = 4 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_CK_INT_N_8   = 3U,  /**< f_SAMPLING = f_CK_INT, N = 8 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_2_N_6    = 4U,  /**< f_SAMPLING = f_DTS / 2, N = 6 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_2_N_8    = 5U,  /**< f_SAMPLING = f_DTS / 2, N = 8 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_4_N_6    = 6U,  /**< f_SAMPLING = f_DTS / 4, N = 6 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_4_N_8    = 7U,  /**< f_SAMPLING = f_DTS / 4, N = 8 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_8_N_6    = 8U,  /**< f_SAMPLING = f_DTS / 8, N = 6 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_8_N_8    = 9U,  /**< f_SAMPLING = f_DTS / 8, N = 8 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_16_N_5   = 10U, /**< f_SAMPLING = f_DTS / 16, N = 5 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_16_N_6   = 11U, /**< f_SAMPLING = f_DTS / 16, N = 6 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_16_N_8   = 12U, /**< f_SAMPLING = f_DTS / 16, N = 8 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_32_N_5   = 13U, /**< f_SAMPLING = f_DTS / 32, N = 5 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_32_N_6   = 14U, /**< f_SAMPLING = f_DTS / 32, N = 6 events. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_FILTER_F_DTS_32_N_8   = 15U  /**< f_SAMPLING = f_DTS / 32, N = 8 events. */
} PLAY32_TIMx_SMCR_ExtTriggerFilter;

/**
 * @brief  External trigger prescaler (ETPS) selection enumeration.
 * @note   Read/Write 2-bit field (bits 13:12 of TIMx_SMCR, ETPS[1:0]) used to divide the frequency
 *         of the external trigger signal (ETRP).
 * @warning The frequency of ETRP must not exceed 1/4 of CK_INT frequency.
 */
typedef enum {
    PLAY32_TIMx_SMCR_EXT_TRIGGER_PRESCALER_SELECTION_OFF          = 0U, /**< Prescaler OFF (no division). */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_PRESCALER_SELECTION_DIVIDED_BY_2 = 1U, /**< ETRP frequency divided by 2. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_PRESCALER_SELECTION_DIVIDED_BY_4 = 2U, /**< ETRP frequency divided by 4. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_PRESCALER_SELECTION_DIVIDED_BY_8 = 3U  /**< ETRP frequency divided by 8. */
} PLAY32_TIMx_SMCR_ExtTriggerPrescalerSelection;

/**
 * @brief  External clock enable (ECE) state type.
 * @note   Read/Write control bit (bit 14 of TIMx_SMCR, ECE) used to enable External clock mode 2,
 *         where the counter is clocked by any active edge on the ETRF signal.
 * @warning Setting ECE has the same effect as selecting external clock mode 1 with TRGI connected
 *          to ETRF (SMS = 111 and TS = 111). Do not enable ECE simultaneously with Encoder modes.
 * @see    PLAY32_TIMx_Switch
 * @see    PLAY32_TIMx_SMCR_SlaveModeSelection
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_SMCR_ExtClockEnable;

/**
 * @brief  External trigger polarity (ETP) enumeration.
 * @note   Read/Write control bit (bit 15 of TIMx_SMCR, ETP) used to select whether the external
 *         trigger input (ETR) is active high/rising-edge or inverted (active low/falling-edge).
 */
typedef enum {
    PLAY32_TIMx_SMCR_EXT_TRIGGER_POLARITY_NON_INVERTED = 0U, /**< ETR is non-inverted, active at high level or rising edge. */
    PLAY32_TIMx_SMCR_EXT_TRIGGER_POLARITY_INVERTED     = 1U  /**< ETR is inverted, active at low level or falling edge. */
} PLAY32_TIMx_SMCR_ExtTriggerPolarity;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_SMCR_Types */

/**
 * @defgroup PLAY32_TIMx_DIER_Types TIM DMA/Interrupt Enable Register (TIMx_DIER)
 * @brief Bit positions, masks, and field types for TIMx_DIER (offset 0x0C).
 * @{
 */
#pragma region TIMx_DIER_REGISTER

#pragma region TIMx_DIER_REGISTER_POSITION
#define PLAY32_TIMx_DIER_UIE_POS      (0U)  /**< Bit 0: Update interrupt enable position. */
#define PLAY32_TIMx_DIER_CC1IE_POS    (1U)  /**< Bit 1: Capture/Compare 1 interrupt enable position. */
#define PLAY32_TIMx_DIER_CC2IE_POS    (2U)  /**< Bit 2: Capture/Compare 2 interrupt enable position. */
#define PLAY32_TIMx_DIER_CC3IE_POS    (3U)  /**< Bit 3: Capture/Compare 3 interrupt enable position. */
#define PLAY32_TIMx_DIER_CC4IE_POS    (4U)  /**< Bit 4: Capture/Compare 4 interrupt enable position. */
#define PLAY32_TIMx_DIER_TIE_POS      (6U)  /**< Bit 6: Trigger interrupt enable position. */
#define PLAY32_TIMx_DIER_UDE_POS      (8U)  /**< Bit 8: Update DMA request enable position. */
#define PLAY32_TIMx_DIER_CC1DE_POS    (9U)  /**< Bit 9: Capture/Compare 1 DMA request enable position. */
#define PLAY32_TIMx_DIER_CC2DE_POS    (10U) /**< Bit 10: Capture/Compare 2 DMA request enable position. */
#define PLAY32_TIMx_DIER_CC3DE_POS    (11U) /**< Bit 11: Capture/Compare 3 DMA request enable position. */
#define PLAY32_TIMx_DIER_CC4DE_POS    (12U) /**< Bit 12: Capture/Compare 4 DMA request enable position. */
#define PLAY32_TIMx_DIER_TDE_POS      (14U) /**< Bit 14: Trigger DMA request enable position. */
#pragma endregion

#pragma region TIMx_DIER_REGISTER_MASK
#define PLAY32_TIMx_DIER_UIE_MSK      (1UL << PLAY32_TIMx_DIER_UIE_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_TIMx_DIER_CC1IE_MSK    (1UL << PLAY32_TIMx_DIER_CC1IE_POS) /**< Bit 1 mask (0x00000002). */
#define PLAY32_TIMx_DIER_CC2IE_MSK    (1UL << PLAY32_TIMx_DIER_CC2IE_POS) /**< Bit 2 mask (0x00000004). */
#define PLAY32_TIMx_DIER_CC3IE_MSK    (1UL << PLAY32_TIMx_DIER_CC3IE_POS) /**< Bit 3 mask (0x00000008). */
#define PLAY32_TIMx_DIER_CC4IE_MSK    (1UL << PLAY32_TIMx_DIER_CC4IE_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_TIMx_DIER_TIE_MSK      (1UL << PLAY32_TIMx_DIER_TIE_POS)   /**< Bit 6 mask (0x00000040). */
#define PLAY32_TIMx_DIER_UDE_MSK      (1UL << PLAY32_TIMx_DIER_UDE_POS)   /**< Bit 8 mask (0x00000100). */
#define PLAY32_TIMx_DIER_CC1DE_MSK    (1UL << PLAY32_TIMx_DIER_CC1DE_POS) /**< Bit 9 mask (0x00000200). */
#define PLAY32_TIMx_DIER_CC2DE_MSK    (1UL << PLAY32_TIMx_DIER_CC2DE_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_TIMx_DIER_CC3DE_MSK    (1UL << PLAY32_TIMx_DIER_CC3DE_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_TIMx_DIER_CC4DE_MSK    (1UL << PLAY32_TIMx_DIER_CC4DE_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_TIMx_DIER_TDE_MSK      (1UL << PLAY32_TIMx_DIER_TDE_POS)   /**< Bit 14 mask (0x00004000). */
#pragma endregion

#pragma region TIMx_DIER_REGISTER_ENUM

/**
 * @brief  Update interrupt enable (UIE) state type.
 * @note   Read/Write control bit (bit 0 of TIMx_DIER, UIE) used to enable or disable
 *         the interrupt generated on an Update event (UIF flag in TIMx_SR).
 * @warning Ensure the corresponding TIMx IRQ line is enabled in the NVIC and clear
 *          UIF inside the ISR to prevent continuous interrupt re-entry.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_UpdateInterruptEnable;

/**
 * @brief  Capture/Compare 1 interrupt enable (CC1IE) state type.
 * @note   Read/Write control bit (bit 1 of TIMx_DIER, CC1IE) used to enable or disable
 *         the interrupt generated on a Channel 1 capture or compare event (CC1IF flag).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_CaptureCompare1InterruptEnable;

/**
 * @brief  Capture/Compare 2 interrupt enable (CC2IE) state type.
 * @note   Read/Write control bit (bit 2 of TIMx_DIER, CC2IE) used to enable or disable
 *         the interrupt generated on a Channel 2 capture or compare event (CC2IF flag).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_CaptureCompare2InterruptEnable;

/**
 * @brief  Capture/Compare 3 interrupt enable (CC3IE) state type.
 * @note   Read/Write control bit (bit 3 of TIMx_DIER, CC3IE) used to enable or disable
 *         the interrupt generated on a Channel 3 capture or compare event (CC3IF flag).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_CaptureCompare3InterruptEnable;

/**
 * @brief  Capture/Compare 4 interrupt enable (CC4IE) state type.
 * @note   Read/Write control bit (bit 4 of TIMx_DIER, CC4IE) used to enable or disable
 *         the interrupt generated on a Channel 4 capture or compare event (CC4IF flag).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_CaptureCompare4InterruptEnable;

/**
 * @brief  Trigger interrupt enable (TIE) state type.
 * @note   Read/Write control bit (bit 6 of TIMx_DIER, TIE) used to enable or disable
 *         the interrupt generated on a trigger event (TIF flag in TIMx_SR).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_TriggerInterruptEnable;

/**
 * @brief  Update DMA request enable (UDE) state type.
 * @note   Read/Write control bit (bit 8 of TIMx_DIER, UDE) used to enable or disable
 *         the DMA request generated on an Update event.
 * @warning Configure and enable the corresponding DMA stream before setting UDE to avoid
 *          missed DMA transfers.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_UpdateDMAEnable;

/**
 * @brief  Capture/Compare 1 DMA request enable (CC1DE) state type.
 * @note   Read/Write control bit (bit 9 of TIMx_DIER, CC1DE) used to enable or disable
 *         the DMA request generated on a Channel 1 capture or compare event.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_CaptureCompare1DMAEnable;

/**
 * @brief  Capture/Compare 2 DMA request enable (CC2DE) state type.
 * @note   Read/Write control bit (bit 10 of TIMx_DIER, CC2DE) used to enable or disable
 *         the DMA request generated on a Channel 2 capture or compare event.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_CaptureCompare2DMAEnable;

/**
 * @brief  Capture/Compare 3 DMA request enable (CC3DE) state type.
 * @note   Read/Write control bit (bit 11 of TIMx_DIER, CC3DE) used to enable or disable
 *         the DMA request generated on a Channel 3 capture or compare event.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_CaptureCompare3DMAEnable;

/**
 * @brief  Capture/Compare 4 DMA request enable (CC4DE) state type.
 * @note   Read/Write control bit (bit 12 of TIMx_DIER, CC4DE) used to enable or disable
 *         the DMA request generated on a Channel 4 capture or compare event.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_CaptureCompare4DMAEnable;

/**
 * @brief  Trigger DMA request enable (TDE) state type.
 * @note   Read/Write control bit (bit 14 of TIMx_DIER, TDE) used to enable or disable
 *         the DMA request generated on a trigger event.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_DIER_TriggerDMAEnable;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_DIER_Types */

/**
 * @defgroup PLAY32_TIMx_SR_Types TIM Status Register (TIMx_SR)
 * @brief Bit positions, masks, and status flag types for TIMx_SR (offset 0x10).
 * @{
 */
#pragma region TIMx_SR_REGISTER

#pragma region TIMx_SR_REGISTER_POSITION
#define PLAY32_TIMx_SR_UIF_POS   (0U)  /**< Bit 0: Update interrupt flag position. */
#define PLAY32_TIMx_SR_CC1IF_POS (1U)  /**< Bit 1: Capture/Compare 1 interrupt flag position. */
#define PLAY32_TIMx_SR_CC2IF_POS (2U)  /**< Bit 2: Capture/Compare 2 interrupt flag position. */
#define PLAY32_TIMx_SR_CC3IF_POS (3U)  /**< Bit 3: Capture/Compare 3 interrupt flag position. */
#define PLAY32_TIMx_SR_CC4IF_POS (4U)  /**< Bit 4: Capture/Compare 4 interrupt flag position. */
#define PLAY32_TIMx_SR_COMIF_POS (5U)  /**< Bit 5: COM interrupt flag position (reserved on TIM2-TIM5). */
#define PLAY32_TIMx_SR_TIF_POS   (6U)  /**< Bit 6: Trigger interrupt flag position. */
#define PLAY32_TIMx_SR_BIF_POS   (7U)  /**< Bit 7: Break interrupt flag position (reserved on TIM2-TIM5). */
#define PLAY32_TIMx_SR_CC1OF_POS (9U)  /**< Bit 9: Capture/Compare 1 overcapture flag position. */
#define PLAY32_TIMx_SR_CC2OF_POS (10U) /**< Bit 10: Capture/Compare 2 overcapture flag position. */
#define PLAY32_TIMx_SR_CC3OF_POS (11U) /**< Bit 11: Capture/Compare 3 overcapture flag position. */
#define PLAY32_TIMx_SR_CC4OF_POS (12U) /**< Bit 12: Capture/Compare 4 overcapture flag position. */
#pragma endregion

#pragma region TIMx_SR_REGISTER_MASK
#define PLAY32_TIMx_SR_UIF_MSK      (1UL << PLAY32_TIMx_SR_UIF_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_TIMx_SR_CC1IF_MSK    (1UL << PLAY32_TIMx_SR_CC1IF_POS) /**< Bit 1 mask (0x00000002). */
#define PLAY32_TIMx_SR_CC2IF_MSK    (1UL << PLAY32_TIMx_SR_CC2IF_POS) /**< Bit 2 mask (0x00000004). */
#define PLAY32_TIMx_SR_CC3IF_MSK    (1UL << PLAY32_TIMx_SR_CC3IF_POS) /**< Bit 3 mask (0x00000008). */
#define PLAY32_TIMx_SR_CC4IF_MSK    (1UL << PLAY32_TIMx_SR_CC4IF_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_TIMx_SR_COMIF_MSK    (1UL << PLAY32_TIMx_SR_COMIF_POS) /**< Bit 5 mask (0x00000020). */
#define PLAY32_TIMx_SR_TIF_MSK      (1UL << PLAY32_TIMx_SR_TIF_POS)   /**< Bit 6 mask (0x00000040). */
#define PLAY32_TIMx_SR_BIF_MSK      (1UL << PLAY32_TIMx_SR_BIF_POS)   /**< Bit 7 mask (0x00000080). */
#define PLAY32_TIMx_SR_CC1OF_MSK    (1UL << PLAY32_TIMx_SR_CC1OF_POS) /**< Bit 9 mask (0x00000200). */
#define PLAY32_TIMx_SR_CC2OF_MSK    (1UL << PLAY32_TIMx_SR_CC2OF_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_TIMx_SR_CC3OF_MSK    (1UL << PLAY32_TIMx_SR_CC3OF_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_TIMx_SR_CC4OF_MSK    (1UL << PLAY32_TIMx_SR_CC4OF_POS) /**< Bit 12 mask (0x00001000). */
#pragma endregion

#pragma region TIMx_SR_REGISTER_ENUM

/**
 * @brief  Update interrupt flag (UIF) state type.
 * @note   Read/Clear-by-0 status bit (bit 0 of TIMx_SR, UIF) set by hardware on an Update event
 *         (counter overflow/underflow, UG bit assertion, or update via slave mode controller).
 * @warning Cleared by software writing @ref PLAY32_TIMx_FLAG_NOT_SET (0). Writing 1 has no effect.
 * @see    PLAY32_TIMx_Flag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_UpdateInterruptFlag;

/**
 * @brief  Capture/Compare 1 interrupt flag (CC1IF) state type.
 * @note   Read/Clear-by-0 status bit (bit 1 of TIMx_SR, CC1IF) set when the counter value
 *         matches CCR1 (output mode) or when a capture event occurs on IC1 (input mode).
 * @warning In input capture mode, CC1IF is cleared automatically by reading TIMx_CCR1 or by
 *          writing @ref PLAY32_TIMx_FLAG_NOT_SET (0). In output mode, it must be cleared by software.
 * @see    PLAY32_TIMx_Flag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_CaptureCompare1InterruptFlag;

/**
 * @brief  Capture/Compare 2 interrupt flag (CC2IF) state type.
 * @note   Read/Clear-by-0 status bit (bit 2 of TIMx_SR, CC2IF) set when the counter value
 *         matches CCR2 (output mode) or when a capture event occurs on IC2 (input mode).
 * @warning In input capture mode, CC2IF is cleared automatically by reading TIMx_CCR2 or by
 *          writing @ref PLAY32_TIMx_FLAG_NOT_SET (0). In output mode, it must be cleared by software.
 * @see    PLAY32_TIMx_Flag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_CaptureCompare2InterruptFlag;

/**
 * @brief  Capture/Compare 3 interrupt flag (CC3IF) state type.
 * @note   Read/Clear-by-0 status bit (bit 3 of TIMx_SR, CC3IF) set when the counter value
 *         matches CCR3 (output mode) or when a capture event occurs on IC3 (input mode).
 * @warning In input capture mode, CC3IF is cleared automatically by reading TIMx_CCR3 or by
 *          writing @ref PLAY32_TIMx_FLAG_NOT_SET (0). In output mode, it must be cleared by software.
 * @see    PLAY32_TIMx_Flag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_CaptureCompare3InterruptFlag;

/**
 * @brief  Capture/Compare 4 interrupt flag (CC4IF) state type.
 * @note   Read/Clear-by-0 status bit (bit 4 of TIMx_SR, CC4IF) set when the counter value
 *         matches CCR4 (output mode) or when a capture event occurs on IC4 (input mode).
 * @warning In input capture mode, CC4IF is cleared automatically by reading TIMx_CCR4 or by
 *          writing @ref PLAY32_TIMx_FLAG_NOT_SET (0). In output mode, it must be cleared by software.
 * @see    PLAY32_TIMx_Flag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_CaptureCompare4InterruptFlag;

/**
 * @brief  Commutation interrupt flag (COMIF) state type.
 * @note   Status bit (bit 5 of TIMx_SR, COMIF) used on advanced-control timers when capture/compare
 *         control bits are updated.
 * @warning Reserved on general-purpose timers TIM2-TIM5 (always reads 0; keep at reset value).
 * @see    PLAY32_TIMx_Flag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_COMInterruptFlag;

/**
 * @brief  Trigger interrupt flag (TIF) state type.
 * @note   Read/Clear-by-0 status bit (bit 6 of TIMx_SR, TIF) set by hardware on a trigger event
 *         (active edge detected on TRGI input, or any edge in gated mode).
 * @warning Cleared by software writing @ref PLAY32_TIMx_FLAG_NOT_SET (0).
 * @see    PLAY32_TIMx_Flag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_TriggerInterruptFlag;

/**
 * @brief  Break interrupt flag (BIF) state type.
 * @note   Status bit (bit 7 of TIMx_SR, BIF) used on advanced-control timers when an active
 *         level is detected on the break input.
 * @warning Reserved on general-purpose timers TIM2-TIM5 (always reads 0; keep at reset value).
 * @see    PLAY32_TIMx_Flag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_BreakInterruptFlag;

/**
 * @brief  Capture/Compare 1 overcapture flag (CC1OF) state type.
 * @note   Read/Clear-by-0 status bit (bit 9 of TIMx_SR, CC1OF) set by hardware only when the
 *         corresponding channel is configured in input capture mode and a new capture occurs
 *         while CC1IF is already set.
 * @warning Cleared by software writing @ref PLAY32_TIMx_FLAG_NOT_SET (0).
 * @see    PLAY32_TIMx_Flag
 * @see    PLAY32_TIMx_SR_CaptureCompare1InterruptFlag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_CaptureCompare1OvercaptureFlag;

/**
 * @brief  Capture/Compare 2 overcapture flag (CC2OF) state type.
 * @note   Read/Clear-by-0 status bit (bit 10 of TIMx_SR, CC2OF) set by hardware only when the
 *         corresponding channel is configured in input capture mode and a new capture occurs
 *         while CC2IF is already set.
 * @warning Cleared by software writing @ref PLAY32_TIMx_FLAG_NOT_SET (0).
 * @see    PLAY32_TIMx_Flag
 * @see    PLAY32_TIMx_SR_CaptureCompare2InterruptFlag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_CaptureCompare2OvercaptureFlag;

/**
 * @brief  Capture/Compare 3 overcapture flag (CC3OF) state type.
 * @note   Read/Clear-by-0 status bit (bit 11 of TIMx_SR, CC3OF) set by hardware only when the
 *         corresponding channel is configured in input capture mode and a new capture occurs
 *         while CC3IF is already set.
 * @warning Cleared by software writing @ref PLAY32_TIMx_FLAG_NOT_SET (0).
 * @see    PLAY32_TIMx_Flag
 * @see    PLAY32_TIMx_SR_CaptureCompare3InterruptFlag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_CaptureCompare3OvercaptureFlag;

/**
 * @brief  Capture/Compare 4 overcapture flag (CC4OF) state type.
 * @note   Read/Clear-by-0 status bit (bit 12 of TIMx_SR, CC4OF) set by hardware only when the
 *         corresponding channel is configured in input capture mode and a new capture occurs
 *         while CC4IF is already set.
 * @warning Cleared by software writing @ref PLAY32_TIMx_FLAG_NOT_SET (0).
 * @see    PLAY32_TIMx_Flag
 * @see    PLAY32_TIMx_SR_CaptureCompare4InterruptFlag
 */
typedef PLAY32_TIMx_Flag PLAY32_TIMx_SR_CaptureCompare4OvercaptureFlag;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_SR_Types */

/**
 * @defgroup PLAY32_TIMx_EGR_Types TIM Event Generation Register (TIMx_EGR)
 * @brief Bit positions, masks, and event trigger types for TIMx_EGR (offset 0x14).
 * @{
 */
#pragma region TIMx_EGR_REGISTER

#pragma region TIMx_EGR_REGISTER_POSITION
#define PLAY32_TIMx_EGR_UG_POS      (0U) /**< Bit 0: Update generation position. */
#define PLAY32_TIMx_EGR_CC1G_POS    (1U) /**< Bit 1: Capture/Compare 1 generation position. */
#define PLAY32_TIMx_EGR_CC2G_POS    (2U) /**< Bit 2: Capture/Compare 2 generation position. */
#define PLAY32_TIMx_EGR_CC3G_POS    (3U) /**< Bit 3: Capture/Compare 3 generation position. */
#define PLAY32_TIMx_EGR_CC4G_POS    (4U) /**< Bit 4: Capture/Compare 4 generation position. */
#define PLAY32_TIMx_EGR_TG_POS      (6U) /**< Bit 6: Trigger generation position. */
#pragma endregion

#pragma region TIMx_EGR_REGISTER_MASK
#define PLAY32_TIMx_EGR_UG_MSK      (1UL << PLAY32_TIMx_EGR_UG_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_TIMx_EGR_CC1G_MSK    (1UL << PLAY32_TIMx_EGR_CC1G_POS) /**< Bit 1 mask (0x00000002). */
#define PLAY32_TIMx_EGR_CC2G_MSK    (1UL << PLAY32_TIMx_EGR_CC2G_POS) /**< Bit 2 mask (0x00000004). */
#define PLAY32_TIMx_EGR_CC3G_MSK    (1UL << PLAY32_TIMx_EGR_CC3G_POS) /**< Bit 3 mask (0x00000008). */
#define PLAY32_TIMx_EGR_CC4G_MSK    (1UL << PLAY32_TIMx_EGR_CC4G_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_TIMx_EGR_TG_MSK      (1UL << PLAY32_TIMx_EGR_TG_POS)   /**< Bit 6 mask (0x00000040). */
#pragma endregion

#pragma region TIMx_EGR_REGISTER_ENUM

/**
 * @brief  Update generation (UG) control type.
 * @note   Write-only self-clearing bit (bit 0 of TIMx_EGR, UG) set by software to reinitialize
 *         the counter and generate an update of the shadow registers (ARR, PSC, CCRx).
 * @warning Cleared automatically by hardware; reading this bit always returns 0.
 *          Also sets the UIF flag in TIMx_SR (and triggers an interrupt/DMA request if UDIS = 0 and URS = 0).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_EGR_UpdateGeneration;

/**
 * @brief  Capture/Compare 1 generation (CC1G) control type.
 * @note   Write-only self-clearing bit (bit 1 of TIMx_EGR, CC1G) set by software to trigger
 *         a Capture/Compare 1 event (sets CC1IF flag, and captures CNT into CCR1 if configured as input).
 * @warning Cleared automatically by hardware; reading this bit always returns 0.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_EGR_CaptureCompare1Generation;

/**
 * @brief  Capture/Compare 2 generation (CC2G) control type.
 * @note   Write-only self-clearing bit (bit 2 of TIMx_EGR, CC2G) set by software to trigger
 *         a Capture/Compare 2 event (sets CC2IF flag, and captures CNT into CCR2 if configured as input).
 * @warning Cleared automatically by hardware; reading this bit always returns 0.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_EGR_CaptureCompare2Generation;

/**
 * @brief  Capture/Compare 3 generation (CC3G) control type.
 * @note   Write-only self-clearing bit (bit 3 of TIMx_EGR, CC3G) set by software to trigger
 *         a Capture/Compare 3 event (sets CC3IF flag, and captures CNT into CCR3 if configured as input).
 * @warning Cleared automatically by hardware; reading this bit always returns 0.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_EGR_CaptureCompare3Generation;

/**
 * @brief  Capture/Compare 4 generation (CC4G) control type.
 * @note   Write-only self-clearing bit (bit 4 of TIMx_EGR, CC4G) set by software to trigger
 *         a Capture/Compare 4 event (sets CC4IF flag, and captures CNT into CCR4 if configured as input).
 * @warning Cleared automatically by hardware; reading this bit always returns 0.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_EGR_CaptureCompare4Generation;

/**
 * @brief  Trigger generation (TG) control type.
 * @note   Write-only self-clearing bit (bit 6 of TIMx_EGR, TG) set by software to generate
 *         a trigger event (sets TIF flag in TIMx_SR and generates an interrupt/DMA request if enabled).
 * @warning Cleared automatically by hardware; reading this bit always returns 0.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_EGR_TriggerGeneration;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_EGR_Types */

/**
 * @defgroup PLAY32_TIMx_CCMR1_Types TIM Capture/Compare Mode Register 1 (TIMx_CCMR1)
 * @brief Bit positions, masks, and field types for TIMx_CCMR1 (offset 0x18).
 * @{
 */
#pragma region TIMx_CCMR1_REGISTER

#pragma region TIMx_CCMR1_REGISTER_POSITION
/* Common channel direction selection */
#define PLAY32_TIMx_CCMR1_CC1S_POS      (0U)  /**< Bits [1:0]: Capture/Compare 1 selection position. */
#define PLAY32_TIMx_CCMR1_CC2S_POS      (8U)  /**< Bits [9:8]: Capture/Compare 2 selection position. */

/* Output compare mode */
#define PLAY32_TIMx_CCMR1_OC1FE_POS     (2U)  /**< Bit 2: Output compare 1 fast enable position. */
#define PLAY32_TIMx_CCMR1_OC1PE_POS     (3U)  /**< Bit 3: Output compare 1 preload enable position. */
#define PLAY32_TIMx_CCMR1_OC1M_POS      (4U)  /**< Bits [6:4]: Output compare 1 mode position. */
#define PLAY32_TIMx_CCMR1_OC1CE_POS     (7U)  /**< Bit 7: Output compare 1 clear enable position. */
#define PLAY32_TIMx_CCMR1_OC2FE_POS     (10U) /**< Bit 10: Output compare 2 fast enable position. */
#define PLAY32_TIMx_CCMR1_OC2PE_POS     (11U) /**< Bit 11: Output compare 2 preload enable position. */
#define PLAY32_TIMx_CCMR1_OC2M_POS      (12U) /**< Bits [14:12]: Output compare 2 mode position. */
#define PLAY32_TIMx_CCMR1_OC2CE_POS     (15U) /**< Bit 15: Output compare 2 clear enable position. */

/* Input capture mode */
#define PLAY32_TIMx_CCMR1_IC1PSC_POS    (2U)  /**< Bits [3:2]: Input capture 1 prescaler position. */
#define PLAY32_TIMx_CCMR1_IC1F_POS      (4U)  /**< Bits [7:4]: Input capture 1 filter position. */
#define PLAY32_TIMx_CCMR1_IC2PSC_POS    (10U) /**< Bits [11:10]: Input capture 2 prescaler position. */
#define PLAY32_TIMx_CCMR1_IC2F_POS      (12U) /**< Bits [15:12]: Input capture 2 filter position. */
#pragma endregion

#pragma region TIMx_CCMR1_REGISTER_MASK
#define PLAY32_TIMx_CCMR1_CC1S_MSK      (3UL << PLAY32_TIMx_CCMR1_CC1S_POS)   /**< Bits [1:0] mask (0x00000003). */
#define PLAY32_TIMx_CCMR1_OC1FE_MSK     (1UL << PLAY32_TIMx_CCMR1_OC1FE_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_TIMx_CCMR1_OC1PE_MSK     (1UL << PLAY32_TIMx_CCMR1_OC1PE_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_TIMx_CCMR1_OC1M_MSK      (7UL << PLAY32_TIMx_CCMR1_OC1M_POS)   /**< Bits [6:4] mask (0x00000070). */
#define PLAY32_TIMx_CCMR1_OC1CE_MSK     (1UL << PLAY32_TIMx_CCMR1_OC1CE_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_TIMx_CCMR1_CC2S_MSK      (3UL << PLAY32_TIMx_CCMR1_CC2S_POS)   /**< Bits [9:8] mask (0x00000300). */
#define PLAY32_TIMx_CCMR1_OC2FE_MSK     (1UL << PLAY32_TIMx_CCMR1_OC2FE_POS)  /**< Bit 10 mask (0x00000400). */
#define PLAY32_TIMx_CCMR1_OC2PE_MSK     (1UL << PLAY32_TIMx_CCMR1_OC2PE_POS)  /**< Bit 11 mask (0x00000800). */
#define PLAY32_TIMx_CCMR1_OC2M_MSK      (7UL << PLAY32_TIMx_CCMR1_OC2M_POS)   /**< Bits [14:12] mask (0x00007000). */
#define PLAY32_TIMx_CCMR1_OC2CE_MSK     (1UL << PLAY32_TIMx_CCMR1_OC2CE_POS)  /**< Bit 15 mask (0x00008000). */
#define PLAY32_TIMx_CCMR1_IC1PSC_MSK    (3UL << PLAY32_TIMx_CCMR1_IC1PSC_POS) /**< Bits [3:2] mask (0x0000000C). */
#define PLAY32_TIMx_CCMR1_IC1F_MSK      (15UL << PLAY32_TIMx_CCMR1_IC1F_POS)  /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_TIMx_CCMR1_IC2PSC_MSK    (3UL << PLAY32_TIMx_CCMR1_IC2PSC_POS) /**< Bits [11:10] mask (0x00000C00). */
#define PLAY32_TIMx_CCMR1_IC2F_MSK      (15UL << PLAY32_TIMx_CCMR1_IC2F_POS)  /**< Bits [15:12] mask (0x0000F000). */
#pragma endregion
#pragma region TIMx_CCMR1_REGISTER_ENUM
/**
 * @brief  Capture/Compare 1 selection (CC1S) enumeration.
 * @note   Read/Write 2-bit field (bits 1:0 of TIMx_CCMR1, CC1S[1:0]) defining the direction
 *         of Channel 1 (output or input) and selecting the input mapping source.
 * @warning CC1S bits are writable only when the channel is disabled (CC1E = 0 in TIMx_CCER).
 */
typedef enum {
    PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_1_SELECTION_CC1_AS_OUTPUT             = 0U, /**< CC1 channel is configured as output. */
    PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_1_SELECTION_CC1_AS_INPUT_IC1_STRAIGHT = 1U, /**< CC1 channel is configured as input, IC1 is mapped on TI1. */
    PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_1_SELECTION_CC1_AS_INPUT_IC1_CROSS    = 2U, /**< CC1 channel is configured as input, IC1 is mapped on TI2. */
    PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_1_SELECTION_CC1_AS_INPUT_IC1_TRC      = 3U  /**< CC1 channel is configured as input, IC1 is mapped on TRC (requires internal trigger selected via TS). */
} PLAY32_TIMx_CCMR1_CaptureCompare1Selection;

/**
 * @brief  Output Compare 1 fast enable (OC1FE) state type.
 * @note   Read/Write control bit (bit 2 of TIMx_CCMR1, OC1FE) used to accelerate the effect
 *         of an event on the trigger input on the CC1 output (reduces latency to 3 clock cycles).
 * @warning Effective only when Channel 1 is configured in PWM1 or PWM2 mode.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR1_OutputCompare1FastEnable;

/**
 * @brief  Output Compare 1 preload enable (OC1PE) state type.
 * @note   Read/Write control bit (bit 3 of TIMx_CCMR1, OC1PE) used to enable the preload register
 *         on TIMx_CCR1 so written values are transferred to the active register only on an Update event.
 * @warning Preload registers must be enabled in PWM mode if CCR1 is updated dynamically during operation,
 *          and are not usable in One-Pulse Mode (OPM = 1).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR1_OutputCompare1PreloadEnable;

/**
 * @brief  Output Compare 1 mode (OC1M) enumeration.
 * @note   Read/Write 3-bit field (bits 6:4 of TIMx_CCMR1, OC1M[2:0]) defining the behavior
 *         of the output reference signal OC1REF.
 * @warning In PWM mode 1 or 2, the OCREF level changes only when the result of the comparison
 *          changes or when the output compare mode switches from frozen to PWM mode.
 */
typedef enum {
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_FROZEN                         = 0U, /**< Frozen; comparison between CNT and CCR1 has no effect on outputs. */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_CHANNEL_1_TO_ACTIVE_ON_MATCH   = 1U, /**< Set channel 1 to active level on match (OC1REF forced high when CNT == CCR1). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_CHANNEL_1_TO_INACTIVE_ON_MATCH = 2U, /**< Set channel 1 to inactive level on match (OC1REF forced low when CNT == CCR1). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_TOGGLE                         = 3U, /**< Toggle; OC1REF toggles when TIMx_CNT == TIMx_CCR1. */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_FORCE_INACTIVE                 = 4U, /**< Force inactive level (OC1REF forced low). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_FORCE_ACTIVE                   = 5U, /**< Force active level (OC1REF forced high). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_PWM_1                          = 6U, /**< PWM mode 1; channel 1 is active as long as CNT < CCR1 (upcounting) or CNT <= CCR1 (downcounting). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_PWM_2                          = 7U  /**< PWM mode 2; channel 1 is inactive as long as CNT < CCR1 (upcounting) or CNT <= CCR1 (downcounting). */
} PLAY32_TIMx_CCMR1_OutputCompare1Mode;

/**
 * @brief  Output Compare 1 clear enable (OC1CE) state type.
 * @note   Read/Write control bit (bit 7 of TIMx_CCMR1, OC1CE) used to clear OC1REF to low
 *         as soon as a high level is detected on the ETRF input.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR1_OutputCompare1ClearEnable;

/**
 * @brief  Capture/Compare 2 selection (CC2S) enumeration.
 * @note   Read/Write 2-bit field (bits 9:8 of TIMx_CCMR1, CC2S[1:0]) defining the direction
 *         of Channel 2 (output or input) and selecting the input mapping source.
 * @warning CC2S bits are writable only when the channel is disabled (CC2E = 0 in TIMx_CCER).
 */
typedef enum {
    PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_2_SELECTION_CC2_AS_OUTPUT             = 0U, /**< CC2 channel is configured as output. */
    PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_2_SELECTION_CC2_AS_INPUT_IC2_STRAIGHT = 1U, /**< CC2 channel is configured as input, IC2 is mapped on TI2. */
    PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_2_SELECTION_CC2_AS_INPUT_IC2_CROSS    = 2U, /**< CC2 channel is configured as input, IC2 is mapped on TI1. */
    PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_2_SELECTION_CC2_AS_INPUT_IC2_TRC      = 3U  /**< CC2 channel is configured as input, IC2 is mapped on TRC (requires internal trigger selected via TS). */
} PLAY32_TIMx_CCMR1_CaptureCompare2Selection;

/**
 * @brief  Output Compare 2 fast enable (OC2FE) state type.
 * @note   Read/Write control bit (bit 10 of TIMx_CCMR1, OC2FE) used to accelerate the effect
 *         of an event on the trigger input on the CC2 output.
 * @warning Effective only when Channel 2 is configured in PWM1 or PWM2 mode.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR1_OutputCompare2FastEnable;

/**
 * @brief  Output Compare 2 preload enable (OC2PE) state type.
 * @note   Read/Write control bit (bit 11 of TIMx_CCMR1, OC2PE) used to enable the preload register
 *         on TIMx_CCR2 so written values are transferred to the active register only on an Update event.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR1_OutputCompare2PreloadEnable;

/**
 * @brief  Output Compare 2 mode (OC2M) enumeration.
 * @note   Read/Write 3-bit field (bits 14:12 of TIMx_CCMR1, OC2M[2:0]) defining the behavior
 *         of the output reference signal OC2REF.
 */
typedef enum {
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_2_MODE_FROZEN                         = 0U, /**< Frozen; comparison between CNT and CCR2 has no effect on outputs. */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_2_MODE_CHANNEL_2_TO_ACTIVE_ON_MATCH   = 1U, /**< Set channel 2 to active level on match (OC2REF forced high when CNT == CCR2). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_2_MODE_CHANNEL_2_TO_INACTIVE_ON_MATCH = 2U, /**< Set channel 2 to inactive level on match (OC2REF forced low when CNT == CCR2). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_2_MODE_TOGGLE                         = 3U, /**< Toggle; OC2REF toggles when TIMx_CNT == TIMx_CCR2. */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_2_MODE_FORCE_INACTIVE                 = 4U, /**< Force inactive level (OC2REF forced low). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_2_MODE_FORCE_ACTIVE                   = 5U, /**< Force active level (OC2REF forced high). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_2_MODE_PWM_1                          = 6U, /**< PWM mode 1; channel 2 is active as long as CNT < CCR2 (upcounting) or CNT <= CCR2 (downcounting). */
    PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_2_MODE_PWM_2                          = 7U  /**< PWM mode 2; channel 2 is inactive as long as CNT < CCR2 (upcounting) or CNT <= CCR2 (downcounting). */
} PLAY32_TIMx_CCMR1_OutputCompare2Mode;

/**
 * @brief  Output Compare 2 clear enable (OC2CE) state type.
 * @note   Read/Write control bit (bit 15 of TIMx_CCMR1, OC2CE) used to clear OC2REF to low
 *         as soon as a high level is detected on the ETRF input.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR1_OutputCompare2ClearEnable;

/**
 * @brief  Input Capture 1 prescaler (IC1PSC) enumeration.
 * @note   Read/Write 2-bit field (bits 3:2 of TIMx_CCMR1, IC1PSC[1:0], valid only when CC1S != 00)
 *         defining the ratio of the prescaler acting on capture input IC1.
 * @warning The prescaler is reset as soon as CC1E = 0 in TIMx_CCER.
 */
typedef enum {
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_1_PRESCALER_NO_PRESCALER   = 0U, /**< No prescaler; capture is done each time an edge is detected on the capture input. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_1_PRESCALER_EVERY_2_EVENTS = 1U, /**< Capture is done once every 2 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_1_PRESCALER_EVERY_4_EVENTS = 2U, /**< Capture is done once every 4 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_1_PRESCALER_EVERY_8_EVENTS = 3U  /**< Capture is done once every 8 events. */
} PLAY32_TIMx_CCMR1_InputCapture1Prescaler;

/**
 * @brief  Input Capture 1 filter (IC1F) enumeration.
 * @note   Read/Write 4-bit field (bits 7:4 of TIMx_CCMR1, IC1F[3:0], valid only when CC1S != 00)
 *         defining the sampling frequency and number of consecutive identical samples (N) required
 *         to validate a transition on TI1.
 * @see    PLAY32_TIMx_CR1_ClockDivision
 */
typedef enum {
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_NO_FILTER    = 0U,  /**< No filter, sampling is done at f_DTS. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_CK_INT_N_2 = 1U,  /**< f_SAMPLING = f_CK_INT, N = 2 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_CK_INT_N_4 = 2U,  /**< f_SAMPLING = f_CK_INT, N = 4 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_CK_INT_N_8 = 3U,  /**< f_SAMPLING = f_CK_INT, N = 8 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_2_N_6  = 4U,  /**< f_SAMPLING = f_DTS / 2, N = 6 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_2_N_8  = 5U,  /**< f_SAMPLING = f_DTS / 2, N = 8 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_4_N_6  = 6U,  /**< f_SAMPLING = f_DTS / 4, N = 6 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_4_N_8  = 7U,  /**< f_SAMPLING = f_DTS / 4, N = 8 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_8_N_6  = 8U,  /**< f_SAMPLING = f_DTS / 8, N = 6 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_8_N_8  = 9U,  /**< f_SAMPLING = f_DTS / 8, N = 8 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_16_N_5 = 10U, /**< f_SAMPLING = f_DTS / 16, N = 5 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_16_N_6 = 11U, /**< f_SAMPLING = f_DTS / 16, N = 6 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_16_N_8 = 12U, /**< f_SAMPLING = f_DTS / 16, N = 8 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_32_N_5 = 13U, /**< f_SAMPLING = f_DTS / 32, N = 5 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_32_N_6 = 14U, /**< f_SAMPLING = f_DTS / 32, N = 6 events. */
    PLAY32_TIMX_CCMR1_CAPTURE_1_FILTER_F_DTS_32_N_8 = 15U  /**< f_SAMPLING = f_DTS / 32, N = 8 events. */
} PLAY32_TIMx_CCMR1_InputCapture1Filter;

/**
 * @brief  Input Capture 2 prescaler (IC2PSC) enumeration.
 * @note   Read/Write 2-bit field (bits 11:10 of TIMx_CCMR1, IC2PSC[1:0], valid only when CC2S != 00)
 *         defining the ratio of the prescaler acting on capture input IC2.
 * @warning The prescaler is reset as soon as CC2E = 0 in TIMx_CCER.
 */
typedef enum {
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_PRESCALER_NO_PRESCALER   = 0U, /**< No prescaler; capture is done each time an edge is detected on the capture input. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_PRESCALER_EVERY_2_EVENTS = 1U, /**< Capture is done once every 2 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_PRESCALER_EVERY_4_EVENTS = 2U, /**< Capture is done once every 4 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_PRESCALER_EVERY_8_EVENTS = 3U  /**< Capture is done once every 8 events. */
} PLAY32_TIMx_CCMR1_InputCapture2Prescaler;

/**
 * @brief  Input Capture 2 filter (IC2F) enumeration.
 * @note   Read/Write 4-bit field (bits 15:12 of TIMx_CCMR1, IC2F[3:0], valid only when CC2S != 00)
 *         defining the sampling frequency and number of consecutive identical samples (N) required
 *         to validate a transition on TI2.
 * @see    PLAY32_TIMx_CR1_ClockDivision
 */
typedef enum {
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_NO_FILTER    = 0U,  /**< No filter, sampling is done at f_DTS. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_CK_INT_N_2 = 1U,  /**< f_SAMPLING = f_CK_INT, N = 2 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_CK_INT_N_4 = 2U,  /**< f_SAMPLING = f_CK_INT, N = 4 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_CK_INT_N_8 = 3U,  /**< f_SAMPLING = f_CK_INT, N = 8 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_2_N_6  = 4U,  /**< f_SAMPLING = f_DTS / 2, N = 6 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_2_N_8  = 5U,  /**< f_SAMPLING = f_DTS / 2, N = 8 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_4_N_6  = 6U,  /**< f_SAMPLING = f_DTS / 4, N = 6 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_4_N_8  = 7U,  /**< f_SAMPLING = f_DTS / 4, N = 8 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_8_N_6  = 8U,  /**< f_SAMPLING = f_DTS / 8, N = 6 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_8_N_8  = 9U,  /**< f_SAMPLING = f_DTS / 8, N = 8 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_16_N_5 = 10U, /**< f_SAMPLING = f_DTS / 16, N = 5 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_16_N_6 = 11U, /**< f_SAMPLING = f_DTS / 16, N = 6 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_16_N_8 = 12U, /**< f_SAMPLING = f_DTS / 16, N = 8 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_32_N_5 = 13U, /**< f_SAMPLING = f_DTS / 32, N = 5 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_32_N_6 = 14U, /**< f_SAMPLING = f_DTS / 32, N = 6 events. */
    PLAY32_TIMX_CCMR1_INPUT_CAPTURE_2_FILTER_F_DTS_32_N_8 = 15U  /**< f_SAMPLING = f_DTS / 32, N = 8 events. */
} PLAY32_TIMx_CCMR1_InputCapture2Filter;
#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CCMR1_Types */

/**
 * @defgroup PLAY32_TIMx_CCMR2_Types TIM Capture/Compare Mode Register 2 (TIMx_CCMR2)
 * @brief Bit positions, masks, and field types for TIMx_CCMR2 (offset 0x1C).
 * @{
 */
#pragma region TIMx_CCMR2_REGISTER

#pragma region TIMx_CCMR2_REGISTER_POSITION
/* Common channel direction selection */
#define PLAY32_TIMx_CCMR2_CC3S_POS      (0U)  /**< Bits [1:0]: Capture/Compare 3 selection position. */
#define PLAY32_TIMx_CCMR2_CC4S_POS      (8U)  /**< Bits [9:8]: Capture/Compare 4 selection position. */

/* Output compare mode */
#define PLAY32_TIMx_CCMR2_OC3FE_POS     (2U)  /**< Bit 2: Output compare 3 fast enable position. */
#define PLAY32_TIMx_CCMR2_OC3PE_POS     (3U)  /**< Bit 3: Output compare 3 preload enable position. */
#define PLAY32_TIMx_CCMR2_OC3M_POS      (4U)  /**< Bits [6:4]: Output compare 3 mode position. */
#define PLAY32_TIMx_CCMR2_OC3CE_POS     (7U)  /**< Bit 7: Output compare 3 clear enable position. */
#define PLAY32_TIMx_CCMR2_OC4FE_POS     (10U) /**< Bit 10: Output compare 4 fast enable position. */
#define PLAY32_TIMx_CCMR2_OC4PE_POS     (11U) /**< Bit 11: Output compare 4 preload enable position. */
#define PLAY32_TIMx_CCMR2_OC4M_POS      (12U) /**< Bits [14:12]: Output compare 4 mode position. */
#define PLAY32_TIMx_CCMR2_OC4CE_POS     (15U) /**< Bit 15: Output compare 4 clear enable position. */

/* Input capture mode */
#define PLAY32_TIMx_CCMR2_IC3PSC_POS    (2U)  /**< Bits [3:2]: Input capture 3 prescaler position. */
#define PLAY32_TIMx_CCMR2_IC3F_POS      (4U)  /**< Bits [7:4]: Input capture 3 filter position. */
#define PLAY32_TIMx_CCMR2_IC4PSC_POS    (10U) /**< Bits [11:10]: Input capture 4 prescaler position. */
#define PLAY32_TIMx_CCMR2_IC4F_POS      (12U) /**< Bits [15:12]: Input capture 4 filter position. */
#pragma endregion

#pragma region TIMx_CCMR2_REGISTER_MASK
#define PLAY32_TIMx_CCMR2_CC3S_MSK      (3UL << PLAY32_TIMx_CCMR2_CC3S_POS)   /**< Bits [1:0] mask (0x00000003). */
#define PLAY32_TIMx_CCMR2_OC3FE_MSK     (1UL << PLAY32_TIMx_CCMR2_OC3FE_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_TIMx_CCMR2_OC3PE_MSK     (1UL << PLAY32_TIMx_CCMR2_OC3PE_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_TIMx_CCMR2_OC3M_MSK      (7UL << PLAY32_TIMx_CCMR2_OC3M_POS)   /**< Bits [6:4] mask (0x00000070). */
#define PLAY32_TIMx_CCMR2_OC3CE_MSK     (1UL << PLAY32_TIMx_CCMR2_OC3CE_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_TIMx_CCMR2_CC4S_MSK      (3UL << PLAY32_TIMx_CCMR2_CC4S_POS)   /**< Bits [9:8] mask (0x00000300). */
#define PLAY32_TIMx_CCMR2_OC4FE_MSK     (1UL << PLAY32_TIMx_CCMR2_OC4FE_POS)  /**< Bit 10 mask (0x00000400). */
#define PLAY32_TIMx_CCMR2_OC4PE_MSK     (1UL << PLAY32_TIMx_CCMR2_OC4PE_POS)  /**< Bit 11 mask (0x00000800). */
#define PLAY32_TIMx_CCMR2_OC4M_MSK      (7UL << PLAY32_TIMx_CCMR2_OC4M_POS)   /**< Bits [14:12] mask (0x00007000). */
#define PLAY32_TIMx_CCMR2_OC4CE_MSK     (1UL << PLAY32_TIMx_CCMR2_OC4CE_POS)  /**< Bit 15 mask (0x00008000). */
#define PLAY32_TIMx_CCMR2_IC3PSC_MSK    (3UL << PLAY32_TIMx_CCMR2_IC3PSC_POS) /**< Bits [3:2] mask (0x0000000C). */
#define PLAY32_TIMx_CCMR2_IC3F_MSK      (15UL << PLAY32_TIMx_CCMR2_IC3F_POS)  /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_TIMx_CCMR2_IC4PSC_MSK    (3UL << PLAY32_TIMx_CCMR2_IC4PSC_POS) /**< Bits [11:10] mask (0x00000C00). */
#define PLAY32_TIMx_CCMR2_IC4F_MSK      (15UL << PLAY32_TIMx_CCMR2_IC4F_POS)  /**< Bits [15:12] mask (0x0000F000). */
#pragma endregion
#pragma region TIMx_CCMR2_REGISTER_ENUM

/**
 * @brief  Capture/Compare 3 selection (CC3S) enumeration.
 * @note   Read/Write 2-bit field (bits 1:0 of TIMx_CCMR2, CC3S[1:0]) defining the direction
 *         of Channel 3 (output or input) and selecting the input mapping source.
 * @warning CC3S bits are writable only when the channel is disabled (CC3E = 0 in TIMx_CCER).
 */
typedef enum {
    PLAY32_TIMx_CCMR2_CAPTURE_COMPARE_3_SELECTION_CC3_AS_OUTPUT             = 0U, /**< CC3 channel is configured as output. */
    PLAY32_TIMx_CCMR2_CAPTURE_COMPARE_3_SELECTION_CC3_AS_INPUT_IC3_STRAIGHT = 1U, /**< CC3 channel is configured as input, IC3 is mapped on TI3. */
    PLAY32_TIMx_CCMR2_CAPTURE_COMPARE_3_SELECTION_CC3_AS_INPUT_IC3_CROSS    = 2U, /**< CC3 channel is configured as input, IC3 is mapped on TI4. */
    PLAY32_TIMx_CCMR2_CAPTURE_COMPARE_3_SELECTION_CC3_AS_INPUT_IC3_TRC      = 3U  /**< CC3 channel is configured as input, IC3 is mapped on TRC (requires internal trigger selected via TS). */
} PLAY32_TIMx_CCMR2_CaptureCompare3Selection;

/**
 * @brief  Output Compare 3 fast enable (OC3FE) state type.
 * @note   Read/Write control bit (bit 2 of TIMx_CCMR2, OC3FE) used to accelerate the effect
 *         of an event on the trigger input on the CC3 output (reduces latency to 3 clock cycles).
 * @warning Effective only when Channel 3 is configured in PWM1 or PWM2 mode.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR2_OutputCompare3FastEnable;

/**
 * @brief  Output Compare 3 preload enable (OC3PE) state type.
 * @note   Read/Write control bit (bit 3 of TIMx_CCMR2, OC3PE) used to enable the preload register
 *         on TIMx_CCR3 so written values are transferred to the active register only on an Update event.
 * @warning Preload registers must be enabled in PWM mode if CCR3 is updated dynamically during operation,
 *          and are not usable in One-Pulse Mode (OPM = 1).
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR2_OutputCompare3PreloadEnable;

/**
 * @brief  Output Compare 3 mode (OC3M) enumeration.
 * @note   Read/Write 3-bit field (bits 6:4 of TIMx_CCMR2, OC3M[2:0]) defining the behavior
 *         of the output reference signal OC3REF.
 * @warning In PWM mode 1 or 2, the OCREF level changes only when the result of the comparison
 *          changes or when the output compare mode switches from frozen to PWM mode.
 */
typedef enum {
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_3_MODE_FROZEN                         = 0U, /**< Frozen; comparison between CNT and CCR3 has no effect on outputs. */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_3_MODE_CHANNEL_3_TO_ACTIVE_ON_MATCH   = 1U, /**< Set channel 3 to active level on match (OC3REF forced high when CNT == CCR3). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_3_MODE_CHANNEL_3_TO_INACTIVE_ON_MATCH = 2U, /**< Set channel 3 to inactive level on match (OC3REF forced low when CNT == CCR3). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_3_MODE_TOGGLE                         = 3U, /**< Toggle; OC3REF toggles when TIMx_CNT == TIMx_CCR3. */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_3_MODE_FORCE_INACTIVE                 = 4U, /**< Force inactive level (OC3REF forced low). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_3_MODE_FORCE_ACTIVE                   = 5U, /**< Force active level (OC3REF forced high). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_3_MODE_PWM_1                          = 6U, /**< PWM mode 1; channel 3 is active as long as CNT < CCR3 (upcounting) or CNT <= CCR3 (downcounting). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_3_MODE_PWM_2                          = 7U  /**< PWM mode 2; channel 3 is inactive as long as CNT < CCR3 (upcounting) or CNT <= CCR3 (downcounting). */
} PLAY32_TIMx_CCMR2_OutputCompare3Mode;

/**
 * @brief  Output Compare 3 clear enable (OC3CE) state type.
 * @note   Read/Write control bit (bit 7 of TIMx_CCMR2, OC3CE) used to clear OC3REF to low
 *         as soon as a high level is detected on the ETRF input.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR2_OutputCompare3ClearEnable;

/**
 * @brief  Capture/Compare 4 selection (CC4S) enumeration.
 * @note   Read/Write 2-bit field (bits 9:8 of TIMx_CCMR2, CC4S[1:0]) defining the direction
 *         of Channel 4 (output or input) and selecting the input mapping source.
 * @warning CC4S bits are writable only when the channel is disabled (CC4E = 0 in TIMx_CCER).
 */
typedef enum {
    PLAY32_TIMx_CCMR2_CAPTURE_COMPARE_4_SELECTION_CC2_AS_OUTPUT             = 0U, /**< CC4 channel is configured as output. */
    PLAY32_TIMx_CCMR2_CAPTURE_COMPARE_4_SELECTION_CC2_AS_INPUT_IC4_STRAIGHT = 1U, /**< CC4 channel is configured as input, IC4 is mapped on TI4. */
    PLAY32_TIMx_CCMR2_CAPTURE_COMPARE_4_SELECTION_CC2_AS_INPUT_IC4_CROSS    = 2U, /**< CC4 channel is configured as input, IC4 is mapped on TI3. */
    PLAY32_TIMx_CCMR2_CAPTURE_COMPARE_4_SELECTION_CC2_AS_INPUT_IC4_TRC      = 3U  /**< CC4 channel is configured as input, IC4 is mapped on TRC (requires internal trigger selected via TS). */
} PLAY32_TIMx_CCMR2_CaptureCompare4Selection;

/**
 * @brief  Output Compare 4 fast enable (OC4FE) state type.
 * @note   Read/Write control bit (bit 10 of TIMx_CCMR2, OC4FE) used to accelerate the effect
 *         of an event on the trigger input on the CC4 output.
 * @warning Effective only when Channel 4 is configured in PWM1 or PWM2 mode.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR2_OutputCompare4FastEnable;

/**
 * @brief  Output Compare 4 preload enable (OC4PE) state type.
 * @note   Read/Write control bit (bit 11 of TIMx_CCMR2, OC4PE) used to enable the preload register
 *         on TIMx_CCR4 so written values are transferred to the active register only on an Update event.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR2_OutputCompare4PreloadEnable;

/**
 * @brief  Output Compare 4 mode (OC4M) enumeration.
 * @note   Read/Write 3-bit field (bits 14:12 of TIMx_CCMR2, OC4M[2:0]) defining the behavior
 *         of the output reference signal OC4REF.
 */
typedef enum {
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_4_MODE_FROZEN                         = 0U, /**< Frozen; comparison between CNT and CCR4 has no effect on outputs. */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_4_MODE_CHANNEL_4_TO_ACTIVE_ON_MATCH   = 1U, /**< Set channel 4 to active level on match (OC4REF forced high when CNT == CCR4). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_4_MODE_CHANNEL_4_TO_INACTIVE_ON_MATCH = 2U, /**< Set channel 4 to inactive level on match (OC4REF forced low when CNT == CCR4). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_4_MODE_TOGGLE                         = 3U, /**< Toggle; OC4REF toggles when TIMx_CNT == TIMx_CCR4. */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_4_MODE_FORCE_INACTIVE                 = 4U, /**< Force inactive level (OC4REF forced low). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_4_MODE_FORCE_ACTIVE                   = 5U, /**< Force active level (OC4REF forced high). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_4_MODE_PWM_1                          = 6U, /**< PWM mode 1; channel 4 is active as long as CNT < CCR4 (upcounting) or CNT <= CCR4 (downcounting). */
    PLAY32_TIMx_CCMR2_OUTPUT_COMPARE_4_MODE_PWM_2                          = 7U  /**< PWM mode 2; channel 4 is inactive as long as CNT < CCR4 (upcounting) or CNT <= CCR4 (downcounting). */
} PLAY32_TIMx_CCMR2_OutputCompare4Mode;
/**
 * @brief  Output Compare 4 clear enable (OC4CE) state type.
 * @note   Read/Write control bit (bit 15 of TIMx_CCMR2, OC4CE) used to clear OC4REF to low
 *         as soon as a high level is detected on the ETRF input.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCMR2_OutputCompare4ClearEnable;

/**
 * @brief  Input Capture 3 prescaler (IC3PSC) enumeration.
 * @note   Read/Write 2-bit field (bits 3:2 of TIMx_CCMR2, IC3PSC[1:0], valid only when CC3S != 00)
 *         defining the ratio of the prescaler acting on capture input IC3.
 * @warning The prescaler is reset as soon as CC3E = 0 in TIMx_CCER.
 */
typedef enum {
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_PRESCALER_NO_PRESCALER   = 0U, /**< No prescaler; capture is done each time an edge is detected on the capture input. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_PRESCALER_EVERY_2_EVENTS = 1U, /**< Capture is done once every 2 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_PRESCALER_EVERY_4_EVENTS = 2U, /**< Capture is done once every 4 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_PRESCALER_EVERY_8_EVENTS = 3U  /**< Capture is done once every 8 events. */
} PLAY32_TIMx_CCMR2_InputCapture3Prescaler;

/**
 * @brief  Input Capture 3 filter (IC3F) enumeration.
 * @note   Read/Write 4-bit field (bits 7:4 of TIMx_CCMR2, IC3F[3:0], valid only when CC3S != 00)
 *         defining the sampling frequency and number of consecutive identical samples (N) required
 *         to validate a transition on TI3.
 * @see    PLAY32_TIMx_CR1_ClockDivision
 */
typedef enum {
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_NO_FILTER    = 0U,  /**< No filter, sampling is done at f_DTS. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_CK_INT_N_2 = 1U,  /**< f_SAMPLING = f_CK_INT, N = 2 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_CK_INT_N_4 = 2U,  /**< f_SAMPLING = f_CK_INT, N = 4 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_CK_INT_N_8 = 3U,  /**< f_SAMPLING = f_CK_INT, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_2_N_6  = 4U,  /**< f_SAMPLING = f_DTS / 2, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_2_N_8  = 5U,  /**< f_SAMPLING = f_DTS / 2, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_4_N_6  = 6U,  /**< f_SAMPLING = f_DTS / 4, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_4_N_8  = 7U,  /**< f_SAMPLING = f_DTS / 4, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_8_N_6  = 8U,  /**< f_SAMPLING = f_DTS / 8, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_8_N_8  = 9U,  /**< f_SAMPLING = f_DTS / 8, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_16_N_5 = 10U, /**< f_SAMPLING = f_DTS / 16, N = 5 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_16_N_6 = 11U, /**< f_SAMPLING = f_DTS / 16, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_16_N_8 = 12U, /**< f_SAMPLING = f_DTS / 16, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_32_N_5 = 13U, /**< f_SAMPLING = f_DTS / 32, N = 5 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_32_N_6 = 14U, /**< f_SAMPLING = f_DTS / 32, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_3_FILTER_F_DTS_32_N_8 = 15U  /**< f_SAMPLING = f_DTS / 32, N = 8 events. */
} PLAY32_TIMx_CCMR2_InputCapture3Filter;

/**
 * @brief  Input Capture 4 prescaler (IC4PSC) enumeration.
 * @note   Read/Write 2-bit field (bits 11:10 of TIMx_CCMR2, IC4PSC[1:0], valid only when CC4S != 00)
 *         defining the ratio of the prescaler acting on capture input IC4.
 * @warning The prescaler is reset as soon as CC4E = 0 in TIMx_CCER.
 */
typedef enum {
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_PRESCALER_NO_PRESCALER   = 0U, /**< No prescaler; capture is done each time an edge is detected on the capture input. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_PRESCALER_EVERY_2_EVENTS = 1U, /**< Capture is done once every 2 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_PRESCALER_EVERY_4_EVENTS = 2U, /**< Capture is done once every 4 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_PRESCALER_EVERY_8_EVENTS = 3U  /**< Capture is done once every 8 events. */
} PLAY32_TIMx_CCMR2_InputCapture4Prescaler;

/**
 * @brief  Input Capture 4 filter (IC4F) enumeration.
 * @note   Read/Write 4-bit field (bits 15:12 of TIMx_CCMR2, IC4F[3:0], valid only when CC4S != 00)
 *         defining the sampling frequency and number of consecutive identical samples (N) required
 *         to validate a transition on TI4.
 * @see    PLAY32_TIMx_CR1_ClockDivision
 */
typedef enum {
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_NO_FILTER    = 0U,  /**< No filter, sampling is done at f_DTS. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_CK_INT_N_2 = 1U,  /**< f_SAMPLING = f_CK_INT, N = 2 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_CK_INT_N_4 = 2U,  /**< f_SAMPLING = f_CK_INT, N = 4 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_CK_INT_N_8 = 3U,  /**< f_SAMPLING = f_CK_INT, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_2_N_6  = 4U,  /**< f_SAMPLING = f_DTS / 2, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_2_N_8  = 5U,  /**< f_SAMPLING = f_DTS / 2, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_4_N_6  = 6U,  /**< f_SAMPLING = f_DTS / 4, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_4_N_8  = 7U,  /**< f_SAMPLING = f_DTS / 4, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_8_N_6  = 8U,  /**< f_SAMPLING = f_DTS / 8, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_8_N_8  = 9U,  /**< f_SAMPLING = f_DTS / 8, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_16_N_5 = 10U, /**< f_SAMPLING = f_DTS / 16, N = 5 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_16_N_6 = 11U, /**< f_SAMPLING = f_DTS / 16, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_16_N_8 = 12U, /**< f_SAMPLING = f_DTS / 16, N = 8 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_32_N_5 = 13U, /**< f_SAMPLING = f_DTS / 32, N = 5 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_32_N_6 = 14U, /**< f_SAMPLING = f_DTS / 32, N = 6 events. */
    PLAY32_TIMX_CCMR2_INPUT_CAPTURE_4_FILTER_F_DTS_32_N_8 = 15U  /**< f_SAMPLING = f_DTS / 32, N = 8 events. */
} PLAY32_TIMx_CCMR2_InputCapture4Filter;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CCMR2_Types */
/**
 * @defgroup PLAY32_TIMx_CCER_Types TIM Capture/Compare Enable Register (TIMx_CCER)
 * @brief Bit positions, masks, and field types for TIMx_CCER (offset 0x20).
 * @{
 */
#pragma region TIMx_CCER_REGISTER

#pragma region TIMx_CCER_REGISTER_POSITION
#define PLAY32_TIMx_CCER_CC1E_POS     (0U)  /**< Bit 0: Capture/Compare 1 output/capture enable position. */
#define PLAY32_TIMx_CCER_CC1P_POS     (1U)  /**< Bit 1: Capture/Compare 1 output/input polarity position. */
#define PLAY32_TIMx_CCER_CC1NP_POS    (3U)  /**< Bit 3: Capture/Compare 1 complementary/input polarity position. */
#define PLAY32_TIMx_CCER_CC2E_POS     (4U)  /**< Bit 4: Capture/Compare 2 output/capture enable position. */
#define PLAY32_TIMx_CCER_CC2P_POS     (5U)  /**< Bit 5: Capture/Compare 2 output/input polarity position. */
#define PLAY32_TIMx_CCER_CC2NP_POS    (7U)  /**< Bit 7: Capture/Compare 2 complementary/input polarity position. */
#define PLAY32_TIMx_CCER_CC3E_POS     (8U)  /**< Bit 8: Capture/Compare 3 output/capture enable position. */
#define PLAY32_TIMx_CCER_CC3P_POS     (9U)  /**< Bit 9: Capture/Compare 3 output/input polarity position. */
#define PLAY32_TIMx_CCER_CC3NP_POS    (11U) /**< Bit 11: Capture/Compare 3 complementary/input polarity position. */
#define PLAY32_TIMx_CCER_CC4E_POS     (12U) /**< Bit 12: Capture/Compare 4 output/capture enable position. */
#define PLAY32_TIMx_CCER_CC4P_POS     (13U) /**< Bit 13: Capture/Compare 4 output/input polarity position. */
#define PLAY32_TIMx_CCER_CC4NP_POS    (15U) /**< Bit 15: Capture/Compare 4 complementary/input polarity position. */
#pragma endregion

#pragma region TIMx_CCER_REGISTER_MASK
#define PLAY32_TIMx_CCER_CC1E_MSK     (1UL << PLAY32_TIMx_CCER_CC1E_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_TIMx_CCER_CC1P_MSK     (1UL << PLAY32_TIMx_CCER_CC1P_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_TIMx_CCER_CC1NP_MSK    (1UL << PLAY32_TIMx_CCER_CC1NP_POS) /**< Bit 3 mask (0x00000008). */
#define PLAY32_TIMx_CCER_CC2E_MSK     (1UL << PLAY32_TIMx_CCER_CC2E_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_TIMx_CCER_CC2P_MSK     (1UL << PLAY32_TIMx_CCER_CC2P_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_TIMx_CCER_CC2NP_MSK    (1UL << PLAY32_TIMx_CCER_CC2NP_POS) /**< Bit 7 mask (0x00000080). */
#define PLAY32_TIMx_CCER_CC3E_MSK     (1UL << PLAY32_TIMx_CCER_CC3E_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_TIMx_CCER_CC3P_MSK     (1UL << PLAY32_TIMx_CCER_CC3P_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_TIMx_CCER_CC3NP_MSK    (1UL << PLAY32_TIMx_CCER_CC3NP_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_TIMx_CCER_CC4E_MSK     (1UL << PLAY32_TIMx_CCER_CC4E_POS)  /**< Bit 12 mask (0x00001000). */
#define PLAY32_TIMx_CCER_CC4P_MSK     (1UL << PLAY32_TIMx_CCER_CC4P_POS)  /**< Bit 13 mask (0x00002000). */
#define PLAY32_TIMx_CCER_CC4NP_MSK    (1UL << PLAY32_TIMx_CCER_CC4NP_POS) /**< Bit 15 mask (0x00008000). */
#pragma endregion

#pragma region TIMx_CCER_REGISTER_ENUM

/**
 * @brief  Capture/Compare 1 enable (CC1E) state type.
 * @note   Read/Write control bit (bit 0 of TIMx_CCER, CC1E) used to enable Channel 1 output
 *         driving onto the corresponding pin (output mode) or counter capture into CCR1 (input mode).
 * @warning While CC1E = 1, the CC1S direction bits in TIMx_CCMR1 become read-only.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCER_CaptureCompare1Enable;

/**
 * @brief  Capture/Compare 1 polarity (CC1P) enumeration.
 * @note   Read/Write control bit (bit 1 of TIMx_CCER, CC1P) defining output polarity when CC1S = 00,
 *         or working alongside CC1NP to select active trigger/capture edge when CC1S != 00.
 */
typedef enum {
    PLAY32_TIMx_CCER_CAPTURE_COMPARE_1_POLARITY_ACTIVE_HIGH = 0U, /**< Output: OC1 active high. Input (with CC1NP=0): non-inverted / rising edge. */
    PLAY32_TIMx_CCER_CAPTURE_COMPARE_1_POLARITY_ACTIVE_LOW  = 1U  /**< Output: OC1 active low. Input (with CC1NP=0): inverted / falling edge. */
} PLAY32_TIMx_CCER_CaptureCompare1Polarity;

/**
 * @brief  Capture/Compare 1 negative/input polarity (CC1NP) state type.
 * @note   Read/Write control bit (bit 3 of TIMx_CCER, CC1NP) used together with CC1P in input capture
 *         or external trigger mode to select rising, falling, or both-edges sensitivity.
 * @warning When Channel 1 is configured as an output (CC1S = 00), CC1NP must be kept cleared (0)
 *          on general-purpose timers TIM2-TIM5.
 * @see    PLAY32_TIMx_Switch
 * @see    PLAY32_TIMx_CCER_CaptureCompare1Polarity
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCER_CaptureCompare1NegativePolarity;

/**
 * @brief  Capture/Compare 2 enable (CC2E) state type.
 * @note   Read/Write control bit (bit 4 of TIMx_CCER, CC2E) used to enable Channel 2 output
 *         driving onto the corresponding pin (output mode) or counter capture into CCR2 (input mode).
 * @warning While CC2E = 1, the CC2S direction bits in TIMx_CCMR1 become read-only.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCER_CaptureCompare2Enable;

/**
 * @brief  Capture/Compare 2 polarity (CC2P) enumeration.
 * @note   Read/Write control bit (bit 5 of TIMx_CCER, CC2P) defining output polarity when CC2S = 00,
 *         or working alongside CC2NP to select active trigger/capture edge when CC2S != 00.
 */
typedef enum {
    PLAY32_TIMx_CCER_CAPTURE_COMPARE_2_POLARITY_ACTIVE_HIGH = 0U, /**< Output: OC2 active high. Input (with CC2NP=0): non-inverted / rising edge. */
    PLAY32_TIMx_CCER_CAPTURE_COMPARE_2_POLARITY_ACTIVE_LOW  = 1U  /**< Output: OC2 active low. Input (with CC2NP=0): inverted / falling edge. */
} PLAY32_TIMx_CCER_CaptureCompare2Polarity;

/**
 * @brief  Capture/Compare 2 negative/input polarity (CC2NP) state type.
 * @note   Read/Write control bit (bit 7 of TIMx_CCER, CC2NP) used together with CC2P in input capture
 *         or external trigger mode to select rising, falling, or both-edges sensitivity.
 * @warning When Channel 2 is configured as an output (CC2S = 00), CC2NP must be kept cleared (0)
 *          on general-purpose timers TIM2-TIM5.
 * @see    PLAY32_TIMx_Switch
 * @see    PLAY32_TIMx_CCER_CaptureCompare2Polarity
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCER_CaptureCompare2NegativePolarity;

/**
 * @brief  Capture/Compare 3 enable (CC3E) state type.
 * @note   Read/Write control bit (bit 8 of TIMx_CCER, CC3E) used to enable Channel 3 output
 *         driving onto the corresponding pin (output mode) or counter capture into CCR3 (input mode).
 * @warning While CC3E = 1, the CC3S direction bits in TIMx_CCMR2 become read-only.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCER_CaptureCompare3Enable;

/**
 * @brief  Capture/Compare 3 polarity (CC3P) enumeration.
 * @note   Read/Write control bit (bit 9 of TIMx_CCER, CC3P) defining output polarity when CC3S = 00,
 *         or working alongside CC3NP to select active trigger/capture edge when CC3S != 00.
 */
typedef enum {
    PLAY32_TIMx_CCER_CAPTURE_COMPARE_3_POLARITY_ACTIVE_HIGH = 0U, /**< Output: OC3 active high. Input (with CC3NP=0): non-inverted / rising edge. */
    PLAY32_TIMx_CCER_CAPTURE_COMPARE_3_POLARITY_ACTIVE_LOW  = 1U  /**< Output: OC3 active low. Input (with CC3NP=0): inverted / falling edge. */
} PLAY32_TIMx_CCER_CaptureCompare3Polarity;

/**
 * @brief  Capture/Compare 3 negative/input polarity (CC3NP) state type.
 * @note   Read/Write control bit (bit 11 of TIMx_CCER, CC3NP) used together with CC3P in input capture
 *         mode to select rising, falling, or both-edges sensitivity.
 * @warning When Channel 3 is configured as an output (CC3S = 00), CC3NP must be kept cleared (0)
 *          on general-purpose timers TIM2-TIM5.
 * @see    PLAY32_TIMx_Switch
 * @see    PLAY32_TIMx_CCER_CaptureCompare3Polarity
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCER_CaptureCompare3NegativePolarity;

/**
 * @brief  Capture/Compare 4 enable (CC4E) state type.
 * @note   Read/Write control bit (bit 12 of TIMx_CCER, CC4E) used to enable Channel 4 output
 *         driving onto the corresponding pin (output mode) or counter capture into CCR4 (input mode).
 * @warning While CC4E = 1, the CC4S direction bits in TIMx_CCMR2 become read-only.
 * @see    PLAY32_TIMx_Switch
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCER_CaptureCompare4Enable;

/**
 * @brief  Capture/Compare 4 polarity (CC4P) enumeration.
 * @note   Read/Write control bit (bit 13 of TIMx_CCER, CC4P) defining output polarity when CC4S = 00,
 *         or working alongside CC4NP to select active trigger/capture edge when CC4S != 00.
 */
typedef enum {
    PLAY32_TIMx_CCER_CAPTURE_COMPARE_4_POLARITY_ACTIVE_HIGH = 0U, /**< Output: OC4 active high. Input (with CC4NP=0): non-inverted / rising edge. */
    PLAY32_TIMx_CCER_CAPTURE_COMPARE_4_POLARITY_ACTIVE_LOW  = 1U  /**< Output: OC4 active low. Input (with CC4NP=0): inverted / falling edge. */
} PLAY32_TIMx_CCER_CaptureCompare4Polarity;

/**
 * @brief  Capture/Compare 4 negative/input polarity (CC4NP) state type.
 * @note   Read/Write control bit (bit 15 of TIMx_CCER, CC4NP) used together with CC4P in input capture
 *         mode to select rising, falling, or both-edges sensitivity.
 * @warning When Channel 4 is configured as an output (CC4S = 00), CC4NP must be kept cleared (0)
 *          on general-purpose timers TIM2-TIM5.
 * @see    PLAY32_TIMx_Switch
 * @see    PLAY32_TIMx_CCER_CaptureCompare4Polarity
 */
typedef PLAY32_TIMx_Switch PLAY32_TIMx_CCER_CaptureCompare4NegativePolarity;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CCER_Types */


/**
 * @defgroup PLAY32_TIMx_CNT_Types TIM Counter Register (TIMx_CNT)
 * @brief Bit position, mask, and value type for TIMx_CNT (offset 0x24).
 * @{
 */
#pragma region TIMx_CNT_REGISTER

#pragma region TIMx_CNT_REGISTER_POSITION
#define PLAY32_TIMx_CNT_CNT_POS    (0U) /**< Bits [31:0] (TIM2/TIM5) or [15:0] (TIM3/TIM4): Counter value position. */
#pragma endregion

#pragma region TIMx_CNT_REGISTER_MASK
#define PLAY32_TIMx_CNT_CNT_MSK    (0xFFFFFFFFUL << PLAY32_TIMx_CNT_CNT_POS) /**< Counter value mask (0xFFFFFFFF for 32-bit timers, 0x0000FFFF effective on 16-bit timers). */
#pragma endregion

#pragma region TIMx_CNT_REGISTER_VALUE
/**
 * @brief  Timer counter (CNT) value type.
 * @note   Read/Write register value (offset 0x24) holding the current counter value.
 * @warning TIM2 and TIM5 use full 32-bit counters (bits [31:0]), whereas TIM3 and TIM4
 *          are 16-bit timers where bits [31:16] are reserved and must be kept cleared (0).
 */
typedef uint32_t PLAY32_TIMx_CNT_Counter;
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CNT_Types */

/**
 * @defgroup PLAY32_TIMx_PSC_Types TIM Prescaler Register (TIMx_PSC)
 * @brief Bit position, mask, and value type for TIMx_PSC (offset 0x28).
 * @{
 */
#pragma region TIMx_PSC_REGISTER

#pragma region TIMx_PSC_REGISTER_POSITION
#define PLAY32_TIMx_PSC_PSC_POS    (0U) /**< Bits [15:0]: Prescaler value position. */
#pragma endregion

#pragma region TIMx_PSC_REGISTER_MASK
#define PLAY32_TIMx_PSC_PSC_MSK    (0x0000FFFFUL << PLAY32_TIMx_PSC_PSC_POS) /**< Bits [15:0] mask (0x0000FFFF). */
#pragma endregion

#pragma region TIMx_PSC_REGISTER_VALUE
/**
 * @brief  Timer prescaler (PSC) value type.
 * @note   Read/Write 16-bit register value (bits 15:0 of TIMx_PSC, offset 0x28) dividing the
 *         counter clock frequency according to: \f$f_{\text{CK\_CNT}} = \frac{f_{\text{CK\_PSC}}}{\text{PSC}[15:0] + 1}\f$.
 * @warning PSC is buffered via a preload register; newly written values take effect only at the next Update event (UEV).
 *          Bits [31:16] are reserved and must be kept cleared (0).
 */
typedef uint32_t PLAY32_TIMx_PSC_Prescaler;
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_PSC_Types */

/**
 * @defgroup PLAY32_TIMx_ARR_Types TIM Auto-Reload Register (TIMx_ARR)
 * @brief Bit position, mask, and value type for TIMx_ARR (offset 0x2C).
 * @{
 */
#pragma region TIMx_ARR_REGISTER

#pragma region TIMx_ARR_REGISTER_POSITION
#define PLAY32_TIMx_ARR_ARR_POS    (0U) /**< Bits [31:0] (TIM2/TIM5) or [15:0] (TIM3/TIM4): Auto-reload value position. */
#pragma endregion

#pragma region TIMx_ARR_REGISTER_MASK
#define PLAY32_TIMx_ARR_ARR_MSK    (0xFFFFFFFFUL << PLAY32_TIMx_ARR_ARR_POS) /**< Auto-reload value mask (0xFFFFFFFF for 32-bit timers, 0x0000FFFF effective on 16-bit timers). */
#pragma endregion

#pragma region TIMx_ARR_REGISTER_VALUE
/**
 * @brief  Timer auto-reload register (ARR) value type.
 * @note   Read/Write register value (offset 0x2C) defining the period/ceiling value loaded into the
 *         active auto-reload register (immediately if ARPE = 0, or on Update event if ARPE = 1).
 * @warning The counter is blocked while ARR is null (0). TIM3 and TIM4 use only bits [15:0];
 *          bits [31:16] are reserved on 16-bit timers.
 * @see    PLAY32_TIMx_CR1_AutoReloadPreloadEnable
 */
typedef uint32_t PLAY32_TIMx_ARR_AutoReloadRegister;
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_ARR_Types */

/**
 * @defgroup PLAY32_TIMx_CCR1_Types TIM Capture/Compare Register 1 (TIMx_CCR1)
 * @brief Bit position, mask, and value type for TIMx_CCR1 (offset 0x34).
 * @{
 */
#pragma region TIMx_CCR1_REGISTER

#pragma region TIMx_CCR1_REGISTER_POSITION
#define PLAY32_TIMx_CCR1_CCR1_POS    (0U) /**< Bits [31:0] (TIM2/TIM5) or [15:0] (TIM3/TIM4): Capture/Compare 1 value position. */
#pragma endregion

#pragma region TIMx_CCR1_REGISTER_MASK
#define PLAY32_TIMx_CCR1_CCR1_MSK    (0xFFFFFFFFUL << PLAY32_TIMx_CCR1_CCR1_POS) /**< Capture/Compare 1 value mask (0xFFFFFFFF for 32-bit timers, 0x0000FFFF effective on 16-bit timers). */
#pragma endregion

#pragma region TIMx_CCR1_REGISTER_VALUE
/**
 * @brief  Capture/Compare 1 register (CCR1) value type.
 * @note   Register value (offset 0x34) holding the compare threshold in output mode (Read/Write)
 *         or the counter value transferred by the last input capture 1 event in input mode (Read-only).
 * @warning In output mode, CCR1 updates take effect immediately if OC1PE = 0 or at the next Update
 *          event if OC1PE = 1. TIM3 and TIM4 use only bits [15:0]; bits [31:16] are reserved.
 * @see    PLAY32_TIMx_CCMR1_OutputCompare1PreloadEnable
 */
typedef uint32_t PLAY32_TIMx_CCR1_CaptureCompare1Register;
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CCR1_Types */

/**
 * @defgroup PLAY32_TIMx_CCR2_Types TIM Capture/Compare Register 2 (TIMx_CCR2)
 * @brief Bit position, mask, and value type for TIMx_CCR2 (offset 0x38).
 * @{
 */
#pragma region TIMx_CCR2_REGISTER

#pragma region TIMx_CCR2_REGISTER_POSITION
#define PLAY32_TIMx_CCR2_CCR2_POS    (0U) /**< Bits [31:0] (TIM2/TIM5) or [15:0] (TIM3/TIM4): Capture/Compare 2 value position. */
#pragma endregion

#pragma region TIMx_CCR2_REGISTER_MASK
#define PLAY32_TIMx_CCR2_CCR2_MSK    (0xFFFFFFFFUL << PLAY32_TIMx_CCR2_CCR2_POS) /**< Capture/Compare 2 value mask (0xFFFFFFFF for 32-bit timers, 0x0000FFFF effective on 16-bit timers). */
#pragma endregion

#pragma region TIMx_CCR2_REGISTER_VALUE
/**
 * @brief  Capture/Compare 2 register (CCR2) value type.
 * @note   Register value (offset 0x38) holding the compare threshold in output mode (Read/Write)
 *         or the counter value transferred by the last input capture 2 event in input mode (Read-only).
 * @warning In output mode, CCR2 updates take effect immediately if OC2PE = 0 or at the next Update
 *          event if OC2PE = 1. TIM3 and TIM4 use only bits [15:0]; bits [31:16] are reserved.
 * @see    PLAY32_TIMx_CCMR1_OutputCompare2PreloadEnable
 */
typedef uint32_t PLAY32_TIMx_CCR2_CaptureCompare2Register;
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CCR2_Types */

/**
 * @defgroup PLAY32_TIMx_CCR3_Types TIM Capture/Compare Register 3 (TIMx_CCR3)
 * @brief Bit position, mask, and value type for TIMx_CCR3 (offset 0x3C).
 * @{
 */
#pragma region TIMx_CCR3_REGISTER

#pragma region TIMx_CCR3_REGISTER_POSITION
#define PLAY32_TIMx_CCR3_CCR3_POS    (0U) /**< Bits [31:0] (TIM2/TIM5) or [15:0] (TIM3/TIM4): Capture/Compare 3 value position. */
#pragma endregion

#pragma region TIMx_CCR3_REGISTER_MASK
#define PLAY32_TIMx_CCR3_CCR3_MSK    (0xFFFFFFFFUL << PLAY32_TIMx_CCR3_CCR3_POS) /**< Capture/Compare 3 value mask (0xFFFFFFFF for 32-bit timers, 0x0000FFFF effective on 16-bit timers). */
#pragma endregion

#pragma region TIMx_CCR3_REGISTER_VALUE
/**
 * @brief  Capture/Compare 3 register (CCR3) value type.
 * @note   Register value (offset 0x3C) holding the compare threshold in output mode (Read/Write)
 *         or the counter value transferred by the last input capture 3 event in input mode (Read-only).
 * @warning In output mode, CCR3 updates take effect immediately if OC3PE = 0 or at the next Update
 *          event if OC3PE = 1. TIM3 and TIM4 use only bits [15:0]; bits [31:16] are reserved.
 * @see    PLAY32_TIMx_CCMR2_OutputCompare3PreloadEnable
 */
typedef uint32_t PLAY32_TIMx_CCR3_CaptureCompare3Register;
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CCR3_Types */

/**
 * @defgroup PLAY32_TIMx_CCR4_Types TIM Capture/Compare Register 4 (TIMx_CCR4)
 * @brief Bit position, mask, and value type for TIMx_CCR4 (offset 0x40).
 * @{
 */
#pragma region TIMx_CCR4_REGISTER

#pragma region TIMx_CCR4_REGISTER_POSITION
#define PLAY32_TIMx_CCR4_CCR4_POS    (0U) /**< Bits [31:0] (TIM2/TIM5) or [15:0] (TIM3/TIM4): Capture/Compare 4 value position. */
#pragma endregion

#pragma region TIMx_CCR4_REGISTER_MASK
#define PLAY32_TIMx_CCR4_CCR4_MSK    (0xFFFFFFFFUL << PLAY32_TIMx_CCR4_CCR4_POS) /**< Capture/Compare 4 value mask (0xFFFFFFFF for 32-bit timers, 0x0000FFFF effective on 16-bit timers). */
#pragma endregion

#pragma region TIMx_CCR4_REGISTER_VALUE
/**
 * @brief  Capture/Compare 4 register (CCR4) value type.
 * @note   Register value (offset 0x40) holding the compare threshold in output mode (Read/Write)
 *         or the counter value transferred by the last input capture 4 event in input mode (Read-only).
 * @warning In output mode, CCR4 updates take effect immediately if OC4PE = 0 or at the next Update
 *          event if OC4PE = 1. TIM3 and TIM4 use only bits [15:0]; bits [31:16] are reserved.
 * @see    PLAY32_TIMx_CCMR2_OutputCompare4PreloadEnable
 */
typedef uint32_t PLAY32_TIMx_CCR4_CaptureCompare4Register;
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_CCR4_Types */
/**
 * @defgroup PLAY32_TIMx_DCR_Types TIM DMA Control Register (TIMx_DCR)
 * @brief Bit positions, masks, and field types for TIMx_DCR (offset 0x48).
 * @{
 */
#pragma region TIMx_DCR_REGISTER

#pragma region TIMx_DCR_REGISTER_POSITION
#define PLAY32_TIMx_DCR_DBA_POS    (0U) /**< Bits [4:0]: DMA base address offset position. */
#define PLAY32_TIMx_DCR_DBL_POS    (8U) /**< Bits [12:8]: DMA burst length position. */
#pragma endregion

#pragma region TIMx_DCR_REGISTER_MASK
#define PLAY32_TIMx_DCR_DBA_MSK    (31UL << PLAY32_TIMx_DCR_DBA_POS) /**< Bits [4:0] mask (0x0000001F). */
#define PLAY32_TIMx_DCR_DBL_MSK    (31UL << PLAY32_TIMx_DCR_DBL_POS) /**< Bits [12:8] mask (0x00001F00). */
#pragma endregion

#pragma region TIMx_DCR_REGISTER_ENUM

/**
 * @brief  DMA burst length (DBL) enumeration.
 * @note   Read/Write 5-bit field (bits 12:8 of TIMx_DCR, DBL[4:0]) defining the number of
 *         consecutive 32-bit register transfers performed per DMA request via TIMx_DMAR
 *         (from 1 transfer for DBL = 0 up to 18 transfers for DBL = 17).
 * @warning Values 18 to 31 (0x12 to 0x1F) are reserved by hardware and must not be used.
 * @see    PLAY32_TIMx_DCR_DMABaseAddress
 */
typedef enum {
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_1_TRANSFER   = 0U,  /**< 1 transfer (burst of 1 register). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_2_TRANSFERS  = 1U,  /**< 2 transfers (burst of 2 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_3_TRANSFERS  = 2U,  /**< 3 transfers (burst of 3 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_4_TRANSFERS  = 3U,  /**< 4 transfers (burst of 4 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_5_TRANSFERS  = 4U,  /**< 5 transfers (burst of 5 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_6_TRANSFERS  = 5U,  /**< 6 transfers (burst of 6 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_7_TRANSFERS  = 6U,  /**< 7 transfers (burst of 7 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_8_TRANSFERS  = 7U,  /**< 8 transfers (burst of 8 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_9_TRANSFERS  = 8U,  /**< 9 transfers (burst of 9 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_10_TRANSFERS = 9U,  /**< 10 transfers (burst of 10 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_11_TRANSFERS = 10U, /**< 11 transfers (burst of 11 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_12_TRANSFERS = 11U, /**< 12 transfers (burst of 12 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_13_TRANSFERS = 12U, /**< 13 transfers (burst of 13 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_14_TRANSFERS = 13U, /**< 14 transfers (burst of 14 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_15_TRANSFERS = 14U, /**< 15 transfers (burst of 15 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_16_TRANSFERS = 15U, /**< 16 transfers (burst of 16 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_17_TRANSFERS = 16U, /**< 17 transfers (burst of 17 registers). */
    PLAY32_TIMx_DCR_DMA_BURST_LENGTH_18_TRANSFERS = 17U  /**< 18 transfers (burst of 18 registers). */
} PLAY32_TIMx_DCR_DMABurstLength;

/**
 * @brief  DMA base address (DBA) register offset enumeration.
 * @note   Read/Write 5-bit field (bits 4:0 of TIMx_DCR, DBA[4:0]) defining the starting register
 *         (expressed as a 32-bit word offset from TIMx_CR1) accessed when reading/writing TIMx_DMAR.
 * @warning Reserved offsets (12 and 17) and values above 20 must not be targeted by DMA bursts.
 * @see    PLAY32_TIMx_DCR_DMABurstLength
 */
typedef enum {
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CR1        = 0U,  /**< Offset 0x00: TIMx_CR1. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CR2        = 1U,  /**< Offset 0x04: TIMx_CR2. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CMCR       = 2U,  /**< Offset 0x08: TIMx_SMCR (Slave Mode Control Register). */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_DIER       = 3U,  /**< Offset 0x0C: TIMx_DIER. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_SR         = 4U,  /**< Offset 0x10: TIMx_SR. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_EGR        = 5U,  /**< Offset 0x14: TIMx_EGR. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CCMR1      = 6U,  /**< Offset 0x18: TIMx_CCMR1. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CCMR2      = 7U,  /**< Offset 0x1C: TIMx_CCMR2. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CCER       = 8U,  /**< Offset 0x20: TIMx_CCER. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CNT        = 9U,  /**< Offset 0x24: TIMx_CNT. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_PCS        = 10U, /**< Offset 0x28: TIMx_PSC (Prescaler Register). */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_ARR        = 11U, /**< Offset 0x2C: TIMx_ARR. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_RESERVED_0 = 12U, /**< Offset 0x30: Reserved (do not use). */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CCR1       = 13U, /**< Offset 0x34: TIMx_CCR1. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CCR2       = 14U, /**< Offset 0x38: TIMx_CCR2. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CCR3       = 15U, /**< Offset 0x3C: TIMx_CCR3. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_CCR4       = 16U, /**< Offset 0x40: TIMx_CCR4. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_RESERVED_1 = 17U, /**< Offset 0x44: Reserved (do not use). */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_DCR        = 18U, /**< Offset 0x48: TIMx_DCR. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_DMAR       = 19U, /**< Offset 0x4C: TIMx_DMAR. */
    PLAY32_TIMx_DCR_DMA_BASE_ADDRESS_OR         = 20U  /**< Offset 0x50: TIMx_OR (TIM2/TIM5 only). */
} PLAY32_TIMx_DCR_DMABaseAddress;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_DCR_Types */

/**
 * @defgroup PLAY32_TIMx_DMAR_Types TIM DMA Address for Full Transfer Register (TIMx_DMAR)
 * @brief Bit position, mask, and value type for TIMx_DMAR (offset 0x4C).
 * @{
 */
#pragma region TIMx_DMAR_REGISTER

#pragma region TIMx_DMAR_REGISTER_POSITION
#define PLAY32_TIMx_DMAR_DMAB_POS    (0U) /**< Bits [31:0] (TIM2/TIM5) or [15:0] (TIM3/TIM4): DMA register for burst accesses position. */
#pragma endregion

#pragma region TIMx_DMAR_REGISTER_MASK
#define PLAY32_TIMx_DMAR_DMAB_MSK    (0xFFFFFFFFUL << PLAY32_TIMx_DMAR_DMAB_POS) /**< DMA burst data mask (0xFFFFFFFF for 32-bit timers, 0x0000FFFF effective on 16-bit timers). */
#pragma endregion

#pragma region TIMx_DMAR_REGISTER_VALUE
/**
 * @brief  DMA register for burst accesses (DMAB) value type.
 * @note   Read/Write virtual burst portal register (offset 0x4C, DMAB[15:0] / [31:0]).
 *         Each read or write access to TIMx_DMAR automatically redirects to the register
 *         pointed to by @ref PLAY32_TIMx_DCR_DMABaseAddress plus the current burst transfer index.
 * @warning Configure DBA and DBL in TIMx_DCR and point the DMA peripheral address to TIMx_DMAR
 *          before enabling the DMA request.
 * @see    PLAY32_TIMx_DCR_DMABaseAddress
 * @see    PLAY32_TIMx_DCR_DMABurstLength
 */
typedef uint32_t PLAY32_TIMx_DMAR_DMABurst;
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_TIMx_DMAR_Types */

/**
 * @defgroup PLAY32_TIMx_OR_Types TIM Option Register (TIMx_OR)
 * @brief Bit positions, masks, and remapping enumerations for TIM2_OR and TIM5_OR (offset 0x50).
 * @{
 */
#pragma region TIMx_OR_REGISTER

#pragma region TIMx_OR_REGISTER_POSITION
#define PLAY32_TIMx_OR_TI4_RMP_POS     (6U)  /**< Bits [7:6]: TIM5 Channel 4 input remap position (TIM5_OR only). */
#define PLAY32_TIMx_OR_ITR1_RMP_POS    (10U) /**< Bits [11:10]: TIM2 Internal trigger 1 remap position (TIM2_OR only). */
#pragma endregion

#pragma region TIMx_OR_REGISTER_MASK
#define PLAY32_TIMx_OR_TI4_RMP_MSK     (3UL << PLAY32_TIMx_OR_TI4_RMP_POS)  /**< Bits [7:6] mask (0x000000C0). */
#define PLAY32_TIMx_OR_ITR1_RMP_MSK    (3UL << PLAY32_TIMx_OR_ITR1_RMP_POS) /**< Bits [11:10] mask (0x00000C00). */
#pragma endregion

#pragma region TIMx_OR_REGISTER_ENUM

/**
 * @brief  TIM5 Input 4 remap (TI4_RMP) enumeration.
 * @note   Read/Write 2-bit field (bits 7:6 of TIM5_OR, TI4_RMP[1:0]) used to connect internal
 *         low-frequency clock sources (LSI, LSE, or RTC wakeup) to TIM5 Channel 4 for calibration.
 * @warning Available exclusively on **TIM5** (`TIM5_OR`); reserved on TIM2, TIM3, and TIM4.
 */
typedef enum {
    PLAY32_TIMx_OR_TIMER_INPUT_4_REMAP_TIM5_CH4_TO_GPIO = 0U, /**< TIM5 Channel 4 is connected to the GPIO pin. */
    PLAY32_TIMx_OR_TIMER_INPUT_4_REMAP_LSI_TO_TIM5_CH4  = 1U, /**< LSI internal clock is connected to TIM5_CH4 input for calibration. */
    PLAY32_TIMx_OR_TIMER_INPUT_4_REMAP_LSE_TO_TIM5_CH4  = 2U, /**< LSE internal clock is connected to TIM5_CH4 input for calibration. */
    PLAY32_TIMx_OR_TIMER_INPUT_4_REMAP_RTC_TO_TIM5_CH4  = 3U  /**< RTC wakeup interrupt output is connected to TIM5_CH4 input for calibration. */
} PLAY32_TIMx_OR_TimerInput4Remap;

/**
 * @brief  TIM2 Internal trigger 1 remap (ITR1_RMP) enumeration.
 * @note   Read/Write 2-bit field (bits 11:10 of TIM2_OR, ITR1_RMP[1:0]) used to route
 *         internal synchronization signals to TIM2 ITR1.
 * @warning Available exclusively on **TIM2** (`TIM2_OR`); reserved on TIM3, TIM4, and TIM5.
 *          On STM32F401 (which lacks Ethernet PTP and USB OTG_HS), only
 *          @ref PLAY32_TIMx_OR_INTERNAL_TRIGGER_1_REMAP_OTG_FS_SOF_TO_TIM2_ITR1 is active.
 */
typedef enum {
    PLAY32_TIMx_OR_INTERNAL_TRIGGER_1_REMAP_RESERVED                   = 0U, /**< Reserved (default reset state; do not rely on trigger). */
    PLAY32_TIMx_OR_INTERNAL_TRIGGER_1_REMAP_PTP_TO_TIM2_ITR1           = 1U, /**< Ethernet PTP trigger output connected to TIM2_ITR1 (unavailable on STM32F401). */
    PLAY32_TIMx_OR_INTERNAL_TRIGGER_1_REMAP_OTG_FS_SOF_TO_TIM2_ITR1    = 2U, /**< USB OTG_FS Start-Of-Frame (SOF) connected to TIM2_ITR1. */
    PLAY32_TIMx_OR_INTERNAL_TRIGGER_1_REMAP_OTG_HS_SOF_TO_TO_TIM2_ITR1 = 3U  /**< USB OTG_HS SOF connected to TIM2_ITR1 (unavailable on STM32F401). */
} PLAY32_TIMx_OR_InternalTrigger1Remap;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_TIMx_OR_Types */

/** @} */ /* End of PLAY32_TIMx */

#endif /* PLAY32_TIMx_TYPES_H */
