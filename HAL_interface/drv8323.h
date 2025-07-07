/*
 * drv832xx.h
 *
 *  Created on: Jan 22, 2024
 *      Author: segev.gofin
 *      based on:
 *      	SPI_API.h by	MDBU Software Team
 * 		@brief       SPI API header file to define functions used for SPI Module.
 * 		@note        Copyright (c) 2016 Texas Instruments Incorporated.
 *              	 All rights reserved.
 */

#ifndef INC_DRV832XX_H_
#define INC_DRV832XX_H_

#include "stm32h7xx_hal.h"
#include <stdbool.h>

#define nSCS_PULLED_LOW_FOR_TRANSMIT
#define ADDRESS_OFFSET_TO_RIGHT_4_BIT 11

/*************************************************************
* DRV832XX Analog Subsystem SPI REGISTER ADDRESS
*************************************************************/
/* Analog Subsystem Instructions */
#define SPI_REG_FAULT_STAT      (0x00 << ADDRESS_OFFSET_TO_RIGHT_4_BIT)         /* Fault Status Register */
#define SPI_REG_FAULT_STAT2        (0x01 << ADDRESS_OFFSET_TO_RIGHT_4_BIT)         /* VGS Status Register */
#define SPI_REG_DRV_CTRL        (0x02 << ADDRESS_OFFSET_TO_RIGHT_4_BIT)         /* Driver Control Register */
#define SPI_REG_GATE_DRV_HS     (0x03 << ADDRESS_OFFSET_TO_RIGHT_4_BIT)         /* Gate Drive HS Register */
#define SPI_REG_GATE_DRV_LS     (0x04 << ADDRESS_OFFSET_TO_RIGHT_4_BIT)         /* Gate Drive LS Register */
#define SPI_REG_OCP_CTRL        (0x05 << ADDRESS_OFFSET_TO_RIGHT_4_BIT)         /* OCP Control Register */
#define SPI_REG_CSA_CTRL        (0x06 << ADDRESS_OFFSET_TO_RIGHT_4_BIT)         /* CSA Control Register */

/* Analog Subsystem Instructions - Bit Definitions */

/* SPI_REG_00 : Fault Status Register 1, Register access type: Read only */
#define FAULT_MASK          (0x0400)         /* Logic OR of FAULT status registers. Mirrors nFAULT pin. */
#define VDS_OCP_MASK        (0x0200)         /* Indicates VDS monitor overcurrent fault condition */
#define GDF_MASK            (0x0100)         /* Indicates gate drive fault condition */
#define UVLO_MASK           (0x0080)         /* Indicates undervoltage lockout fault condition */
#define OTSD_MASK           (0x0040)         /* Indicates overtemperature shutdown */
#define VDS_HA_MASK         (0x0020)         /* IndicatesVDS overcurrent fault on theA high-side MOSFET */
#define VDS_LA_MASK         (0x0010)         /* IndicatesVDS overcurrent fault on theA low-side MOSFET */
#define VDS_HB_MASK         (0x0008)         /* IndicatesVDS overcurrent fault on theB high-side MOSFET */
#define VDS_LB_MASK         (0x0004)         /* IndicatesVDS overcurrent fault on theB low-side MOSFET */
#define VDS_HC_MASK         (0x0002)         /* IndicatesVDS overcurrent fault on theC high-side MOSFET */
#define VDS_LC_MASK         (0x0001)         /* IndicatesVDS overcurrent fault on theC low-side MOSFET */

/* SPI_REG_01 : Fault Status Register 2, VGS STATUS 2, Register access type: Read only */
#define SA_OC_MASK          (0x0400)         /* Indicatesovercurrent on phase A sense amplifier (DRV8323xS) */
#define SB_OC_MASK          (0x0200)         /* Indicatesovercurrent on phase B sense amplifier (DRV8323xS) */
#define SC_OC_MASK          (0x0100)         /* Indicatesovercurrent on phase C sense amplifier (DRV8323xS) */
#define OTW_MASK            (0x0080)         /* Indicates overtemperature warning */
#define CPUV_MASK           (0x0040)         /* Indicatescharge pump undervoltage fault condition */
#define VGS_HA_MASK         (0x0020)         /* Indicatesgate drive fault on the A high-side MOSFET */
#define VGS_LA_MASK         (0x0010)         /* Indicatesgate drive fault on the A low-side MOSFET */
#define VGS_HB_MASK         (0x0008)         /* Indicatesgate drive fault on the B high-side MOSFET */
#define VGS_LB_MASK         (0x0004)         /* Indicatesgate drive fault on the B low-side MOSFET */
#define VGS_HC_MASK         (0x0002)         /* Indicatesgate drive fault on the C high-side MOSFET */
#define VGS_LC_MASK         (0x0001)         /* Indicatesgate drive fault on the C low-side MOSFET */

/* SPI_REG_02 : DRIVER CONTROL - Control Registers
 * The control registers are used to configure the device.
 * The control registers are read and write capable */
#define RSVD_MASK           (0x0400)         /* Reserved */
#define DIS_CPUV_MASK       (0x0200)         /* 0b = Charge pump UVLO fault is enabled, 1b = Charge pump UVLO fault is disabled */
#define DIS_GDF_MASK        (0x0100)         /* 0b = Gate driv e fault is enabled, 1b = Gate drive fault isdisabled */
#define OTW_REP_MASK        (0x0080)         /* 0b = OTW is not reported on nFAULT or the FAULT bit, 1b = OTWis reported on nFAULT and the FAULT bit */
#define PWM_MODE_MASK       (0x0020)         /* 00b = 6x PWM Mode, 01b = 3x PWM mode, 10b = 1x PWM mode, 11b = Independent PWM mode */
#define PWM_COM_MASK		(0x0010)         /* 0b = 1x PWM mode uses synchronous rectification, 1b = 1x PWM mode uses asynchronous rectification (diode freewheeling) */
#define PWM_DIR_MASK        (0x0008)         /* In 1x PWM mode this bit isORed with the INHC (DIR) input */
#define COAST_MASK          (0x0004)         /* Write a 1 to this bit to put all MOSFETsin the Hi-Z state */
#define BRAKE_MASK          (0x0002)         /* Write a 1 to this bit to turn on all three low-side MOSFETs in 1x PWM mode, This bit isORed with the INL (BRAKE) input */
#define CLR_FLT_MASK        (0x0001)         /* Write a 1 to this bit to clear latched fault bits, This bit automatically resets after being written. */

/* SPI_REG_03 : Gate Drive HS Register, Register access type: Read/Write */
/* Write 110b to lockthe settings by ignoring further register writes
 * except to these bits and address 0x02 bits0-2.
 * Writing any sequence other than 110b has no effect when unlocked.
 * Write 011b to this register to unlock all registers.
 * Writing any sequence other than 011b has no effect when locked.*/


/*******  Bit definitions for Gate Drive HS register  ********/
#define GATE_DRV_HS_LOCK_Pos           (8U)
#define GATE_DRV_HS_UN_LOCK_Msk           (0x3U << GATE_DRV_HS_LOCK_Pos)
#define GATE_DRV_HS_LOCK               GATE_DRV_HS_LOCK_Msk
#define GATE_DRV_HS_LOCK_0             (0x1U << GATE_DRV_HS_LOCK_Pos)
#define GATE_DRV_HS_LOCK_1             (0x2U << GATE_DRV_HS_LOCK_Pos)
#define GATE_DRV_HS_LOCK_2             (0x4U << GATE_DRV_HS_LOCK_Pos)

#define GATE_DRV_HS_IDRIVEP_HS_Pos     (4U)
#define GATE_DRV_HS_IDRIVEP_HS_Msk     (0xFU << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS         GATE_DRV_HS_IDRIVEP_HS_Msk
#define GATE_DRV_HS_IDRIVEP_HS_0       (0x1U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_1       (0x2U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_2       (0x4U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_3       (0x8U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_10mA    (0x0U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_30mA    (0x1U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_60mA    (0x2U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_80mA    (0x3U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_120mA   (0x4U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_140mA   (0x5U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_170mA   (0x6U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_190mA   (0x7U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_260mA   (0x8U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_330mA   (0x9U << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_370mA   (0xAU << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_440mA   (0xBU << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_570mA   (0xCU << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_680mA   (0xDU << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_820mA   (0xEU << GATE_DRV_HS_IDRIVEP_HS_Pos)
#define GATE_DRV_HS_IDRIVEP_HS_1000mA  (0xFU << GATE_DRV_HS_IDRIVEP_HS_Pos)

#define GATE_DRV_HS_IDRIVEN_HS_Pos     (0U)
#define GATE_DRV_HS_IDRIVEN_HS_Msk     (0xFU << GATE_DRV_HS_IDRIVEN_HS_Pos)
#define GATE_DRV_HS_IDRIVEN_HS         GATE_DRV_HS_IDRIVEN_HS_Msk
#define GATE_DRV_HS_IDRIVEN_HS_0       0x1U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_1       0x2U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_2       0x4U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_3       0x8U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_20mA    0x0U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_60mA    0x1U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_120mA   0x2U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_160mA   0x3U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_240mA   0x4U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_280mA   0x5U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_340mA   0x6U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_380mA   0x7U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_520mA   0x8U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_660mA   0x9U << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_740mA   0xAU << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_880mA   0xBU << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_1140mA  0xCU << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_1360mA  0xDU << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_1640mA  0xEU << GATE_DRV_HS_IDRIVEN_HS_Pos
#define GATE_DRV_HS_IDRIVEN_HS_2000mA  0xFU << GATE_DRV_HS_IDRIVEN_HS_Pos


/*******  Bit definitions for Gate Drive LS register  ********/
#define GATE_DRV_LS_CBC_Pos            (10U)
#define GATE_DRV_LS_CBC_Msk            (0x7U << GATE_DRV_LS_LOCK_Pos)
#define GATE_DRV_LS_CBC                GATE_DRV_LS_LOCK_Msk
#define GATE_DRV_LS_TDRIVE_Pos         (8U)
#define GATE_DRV_LS_TDRIVE_Msk         (0x7U << GATE_DRV_LS_LOCK_Pos)
#define GATE_DRV_LS_TDRIVE             GATE_DRV_LS_LOCK_Msk
#define GATE_DRV_LS_TDRIVE_0           (0x1U << GATE_DRV_LS_TDRIVE_Pos)
#define GATE_DRV_LS_TDRIVE_1           (0x2U << GATE_DRV_LS_TDRIVE_Pos)
#define GATE_DRV_LS_TDRIVE_500ns       (0x0U << GATE_DRV_LS_TDRIVE_Pos)
#define GATE_DRV_LS_TDRIVE_1000ns      (0x1U << GATE_DRV_LS_TDRIVE_Pos)
#define GATE_DRV_LS_TDRIVE_2000ns      (0x2U << GATE_DRV_LS_TDRIVE_Pos)
#define GATE_DRV_LS_TDRIVE_4000ns      (0x3U << GATE_DRV_LS_TDRIVE_Pos)

#define GATE_DRV_LS_IDRIVEP_LS_Pos     (4U)
#define GATE_DRV_LS_IDRIVEP_LS_Msk     (0xF << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS         GATE_DRV_LS_IDRIVEP_LS_Msk
#define GATE_DRV_LS_IDRIVEP_LS_0       (0x1U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_1       (0x2U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_2       (0x4U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_3       (0x8U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_10mA    (0x0U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_30mA    (0x1U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_60mA    (0x2U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_80mA    (0x3U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_120mA   (0x4U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_140mA   (0x5U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_170mA   (0x6U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_190mA   (0x7U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_260mA   (0x8U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_330mA   (0x9U << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_370mA   (0xAU << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_440mA   (0xBU << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_570mA   (0xCU << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_680mA   (0xDU << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_820mA   (0xEU << GATE_DRV_LS_IDRIVEP_LS_Pos)
#define GATE_DRV_LS_IDRIVEP_LS_1000mA  (0xFU << GATE_DRV_LS_IDRIVEP_LS_Pos)

#define GATE_DRV_LS_IDRIVEN_LS_Pos     (0U)
#define GATE_DRV_LS_IDRIVEN_LS_Msk     (0xFU << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS         GATE_DRV_LS_IDRIVEN_LS_Msk
#define GATE_DRV_LS_IDRIVEN_LS_0       (0x1U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_1       (0x2U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_2       (0x4U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_3       (0x8U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_20mA    (0x0U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_60mA    (0x1U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_120mA   (0x2U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_160mA   (0x3U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_240mA   (0x4U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_280mA   (0x5U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_340mA   (0x6U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_380mA   (0x7U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_520mA   (0x8U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_660mA   (0x9U << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_740mA   (0xAU << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_880mA   (0xBU << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_1140mA  (0xCU << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_1360mA  (0xDU << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_1640mA  (0xEU << GATE_DRV_LS_IDRIVEN_LS_Pos)
#define GATE_DRV_LS_IDRIVEN_LS_2000mA  (0xFU << GATE_DRV_LS_IDRIVEN_LS_Pos)

/*******  Bit definitions for OCP Control register  **********/

#define OCP_CTRL_TRETRY_Pos         (10U)
#define OCP_CTRL_TRETRY_Msk         (0x1U << OCP_CTRL_TRETRY_Pos)
#define OCP_CTRL_TRETRY             OCP_CTRL_TRETRY_Msk

#define OCP_CTRL_DEAD_TIME_Pos      (8U)
#define OCP_CTRL_DEAD_TIME_Msk      (0x3U << OCP_CTRL_DEAD_TIME_Pos)
#define OCP_CTRL_DEAD_TIME          OCP_CTRL_DEAD_TIME_Msk
#define OCP_CTRL_DEAD_TIME_0        (0x1U << OCP_CTRL_DEAD_TIME_Pos)
#define OCP_CTRL_DEAD_TIME_1        (0x2U << OCP_CTRL_DEAD_TIME_Pos)
#define OCP_CTRL_DEAD_TIME_50ns     (0x0U << OCP_CTRL_DEAD_TIME_Pos)
#define OCP_CTRL_DEAD_TIME_100ns    (0x1U << OCP_CTRL_DEAD_TIME_Pos)
#define OCP_CTRL_DEAD_TIME_200ns    (0x2U << OCP_CTRL_DEAD_TIME_Pos)
#define OCP_CTRL_DEAD_TIME_400ns    (0x3U << OCP_CTRL_DEAD_TIME_Pos)

#define OCP_CTRL_OCP_MODE_Pos       (6U)
#define OCP_CTRL_OCP_MODE_Msk       (0x3U << OCP_CTRL_OCP_MODE_Pos)
#define OCP_CTRL_OCP_MODE           OCP_CTRL_OCP_MODE_Msk
#define OCP_CTRL_OCP_MODE_0         (0x1U << OCP_CTRL_OCP_MODE_Pos)
#define OCP_CTRL_OCP_MODE_1         (0x2U << OCP_CTRL_OCP_MODE_Pos)
#define OCP_CTRL_OCP_MODE_LATCH     (0x0U << OCP_CTRL_OCP_MODE_Pos)
#define OCP_CTRL_OCP_MODE_RETRY     (0x1U << OCP_CTRL_OCP_MODE_Pos)
#define OCP_CTRL_OCP_MODE_REPORT    (0x2U << OCP_CTRL_OCP_MODE_Pos)
#define OCP_CTRL_OCP_MODE_NO_ACT    (0x3U << OCP_CTRL_OCP_MODE_Pos)

#define OCP_CTRL_OCP_DEG_Pos        (4U)
#define OCP_CTRL_OCP_DEG_Msk        (0x3U << OCP_CTRL_OCP_DEG_Pos)
#define OCP_CTRL_OCP_DEG            OCP_CTRL_OCP_DEG_Msk
#define OCP_CTRL_OCP_DEG_0          (0x1U << OCP_CTRL_OCP_DEG_Pos)
#define OCP_CTRL_OCP_DEG_1          (0x2U << OCP_CTRL_OCP_DEG_Pos)
#define OCP_CTRL_OCP_DEG_2us        (0x0U << OCP_CTRL_OCP_DEG_Pos)
#define OCP_CTRL_OCP_DEG_4us        (0x1U << OCP_CTRL_OCP_DEG_Pos)
#define OCP_CTRL_OCP_DEG_6us        (0x2U << OCP_CTRL_OCP_DEG_Pos)
#define OCP_CTRL_OCP_DEG_8us        (0x3U << OCP_CTRL_OCP_DEG_Pos)

#define OCP_CTRL_VDS_LVL_Pos        (0U)
#define OCP_CTRL_VDS_LVL_Msk        (0xFU << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL            OCP_CTRL_VDS_LVL_Msk
#define OCP_CTRL_VDS_LVL_0          (0x1U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_1          (0x2U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_2          (0x4U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_3          (0x8U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_06V      (0x0U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_07V      (0x1U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_08V      (0x2U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_09V      (0x3U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_1V      (0x4U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_2V      (0x5U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_3V      (0x6U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_4V      (0x7U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_5V      (0x8U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_6V      (0x9U << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_7V      (0xAU << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_8V      (0xBU << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_0_9V      (0xCU << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_1_0V      (0xDU << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_1_5V      (0xEU << OCP_CTRL_VDS_LVL_Pos)
#define OCP_CTRL_VDS_LVL_2_0V      (0xFU << OCP_CTRL_VDS_LVL_Pos)

/*******  Bit definitions for CSA Control register  **********/
#define CSA_CTRL_CSA_FET_Pos        (10U)
#define CSA_CTRL_CSA_FET_Msk        (0x1U << CSA_CTRL_CSA_FET_Pos)
#define CSA_CTRL_CSA_FET            CSA_CTRL_CSA_FET_Msk

#define CSA_CTRL_VREF_DIV_Pos       (9U)
#define CSA_CTRL_VREF_DIV_Msk       (0x1U << CSA_CTRL_VREF_DIV_Pos)
#define CSA_CTRL_VREF_DIV           CSA_CTRL_VREF_DIV_Msk

#define CSA_CTRL_LS_REF_Pos         (8U)
#define CSA_CTRL_LS_REF_Msk         (0x1U << CSA_CTRL_LS_REF_Pos)
#define CSA_CTRL_LS_REF             CSA_CTRL_LS_REF_Msk

#define CSA_CTRL_CSA_GAIN_Pos       (6U)
#define CSA_CTRL_CSA_GAIN_Msk       (0x3U << CSA_CTRL_CSA_GAIN_Pos)
#define CSA_CTRL_CSA_GAIN           CSA_CTRL_CSA_GAIN_Msk
#define CSA_CTRL_CSA_GAIN_0         (0x1U << CSA_CTRL_CSA_GAIN_Pos)
#define CSA_CTRL_CSA_GAIN_1         (0x2U << CSA_CTRL_CSA_GAIN_Pos)
#define CSA_CTRL_CSA_GAIN_5VV       (0x0U << CSA_CTRL_CSA_GAIN_Pos)
#define CSA_CTRL_CSA_GAIN_10VV      (0x1U << CSA_CTRL_CSA_GAIN_Pos)
#define CSA_CTRL_CSA_GAIN_20VV      (0x2U << CSA_CTRL_CSA_GAIN_Pos)
#define CSA_CTRL_CSA_GAIN_40VV      (0x3U << CSA_CTRL_CSA_GAIN_Pos)

#define CSA_CTRL_DIS_EN_Pos         (5U)
#define CSA_CTRL_DIS_EN_Msk         (0x1U << CSA_CTRL_DIS_EN_Pos)
#define CSA_CTRL_DIS_EN             CSA_CTRL_DIS_EN_Msk

#define CSA_CTRL_CSA_CAL_A_Pos      (4U)
#define CSA_CTRL_CSA_CAL_A_Msk      (0x1U << CSA_CTRL_CSA_CAL_A_Pos)
#define CSA_CTRL_CSA_CAL_A          CSA_CTRL_CSA_CAL_A_Msk
#define CSA_CTRL_CSA_CAL_B_Pos      (3U)
#define CSA_CTRL_CSA_CAL_B_Msk      (0x1U << CSA_CTRL_CSA_CAL_B_Pos)
#define CSA_CTRL_CSA_CAL_B          CSA_CTRL_CSA_CAL_B_Msk
#define CSA_CTRL_CSA_CAL_C_Pos      (2U)
#define CSA_CTRL_CSA_CAL_C_Msk      (0x1U << CSA_CTRL_CSA_CAL_C_Pos)
#define CSA_CTRL_CSA_CAL_C          CSA_CTRL_CSA_CAL_C_Msk

#define CSA_CTRL_SEN_LVL_Pos        (0U)
#define CSA_CTRL_SEN_LVL_Msk        (0x3U << CSA_CTRL_SEN_LVL_Pos)
#define CSA_CTRL_SEN_LVL            CSA_CTRL_SEN_LVL_Msk
#define CSA_CTRL_SEN_LVL_0          (0x1U << CSA_CTRL_SEN_LVL_Pos)
#define CSA_CTRL_SEN_LVL_1          (0x2U << CSA_CTRL_SEN_LVL_Pos)
#define CSA_CTRL_SEN_LVL_0_25V      (0x0U << CSA_CTRL_SEN_LVL_Pos)
#define CSA_CTRL_SEN_LVL_0_50V      (0x1U << CSA_CTRL_SEN_LVL_Pos)
#define CSA_CTRL_SEN_LVL_0_75V      (0x2U << CSA_CTRL_SEN_LVL_Pos)
#define CSA_CTRL_SEN_LVL_1_00V      (0x3U << CSA_CTRL_SEN_LVL_Pos)





typedef enum
{
    STATUS_NONE = 0,
	STATUS_INIT,
	STATUS_ERROR,
	STATUS_NON_SPI
}drv_status_TypeDef;

typedef struct drv8323_TypeDef_s
{
    uint16_t fault_status_1;
    uint16_t fault_status_2;
    uint16_t driver_control;
    uint16_t gate_drive_HS;
    uint16_t gate_drive_LS;
    uint16_t OCP_control;
    uint16_t CSA_control;
	GPIO_TypeDef *CSport;
	uint16_t CSpin;
	SPI_HandleTypeDef *spi;
	drv_status_TypeDef device_status;
} drv8323_TypeDef_t,*drv8323_TypeDef_tp;

typedef enum drv8323_e
{
	DRV8323_1 = 0,
	DRV8323_2,
	ALL_DRV8323,
}drv8323_et, *drv8323_etp;


/**************  function prototypes  *****************/
void drv8323_Init(drv8323_et drv_num, SPI_HandleTypeDef *spi,GPIO_TypeDef *CSport , uint16_t CSPin);
void drv8323_registers_init(void);

#endif /* INC_DRV832XX_H_ */
