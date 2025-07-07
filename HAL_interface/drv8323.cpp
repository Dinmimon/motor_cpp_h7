/*
 * drv8323.c
 *
 *  Created on: 18 Oct 2021
 *      Author: sergey.michelson
 */

/* module includes ********************************************************** */
#include "stdint.h"
#include "stdbool.h"
#include "drv8323.h"
/* constant definitions ***************************************************** */
drv8323_TypeDef_t drv[ALL_DRV8323] = {0};
/* local variables ********************************************************** */

/* inline functions ********************************************************* */

/* local functions ********************************************************** */

/* global functions ********************************************************** */

/**
 * @brief Write to a DRV8323 register
 * 
 * @param drv Pointer to the DRV8323 device structure
 * @param reg Register address
 * @param data Data to write
 * @return HAL status
 */
HAL_StatusTypeDef drv8323_write_reg(drv8323_TypeDef_t *drv, uint16_t reg, uint16_t data)
{
    HAL_StatusTypeDef hal_status = HAL_OK;

    
    uint16_t tx_reg = 0;
    
    // Set the register address and data
    tx_reg |= (reg & 0x7800);
    tx_reg |= data;

    uint16_t pBuf;
    
    // Pull CS pin low to start communication
    HAL_GPIO_WritePin(drv->CSport, drv->CSpin, GPIO_PIN_RESET);
    
    // Transmit the register address and data
    hal_status = HAL_SPI_TransmitReceive(drv->spi, (uint8_t *)&tx_reg, (uint8_t *)&pBuf, 1, HAL_MAX_DELAY);
    
    // Pull CS pin high to end communication
    HAL_GPIO_WritePin(drv->CSport, drv->CSpin, GPIO_PIN_SET);
    
    return hal_status;
}

/**
 * @brief Read from a DRV8323 register
 * 
 * @param drv Pointer to the DRV8323 device structure
 * @param reg Register address
 * @param pBuf Pointer to buffer to store read data
 * @return HAL status
 */
HAL_StatusTypeDef drv8323_read_reg(drv8323_TypeDef_t *drv, uint16_t reg, uint16_t *pBuf)
{
    // Pull CS pin low to start communication
    HAL_GPIO_WritePin(drv->CSport, drv->CSpin, GPIO_PIN_SET);
    
    HAL_StatusTypeDef hal_status;
    uint16_t tx_reg = 0;
    
    // Set the read command bit (bit 15) and the register address
    tx_reg |= (0x8000);
    tx_reg |= (reg & 0x7800);

    // Transmit the register address and receive the data
    hal_status = HAL_SPI_TransmitReceive(drv->spi, (uint8_t *)&tx_reg, (uint8_t *)pBuf, 1, HAL_MAX_DELAY);
    
    // Pull CS pin high to end communication
    HAL_GPIO_WritePin(drv->CSport, drv->CSpin, GPIO_PIN_SET);

    return hal_status;
}

/**
 * @brief Update DRV8323 registers
 * 
 * @param drv Pointer to the DRV8323 device structure
 * @return HAL status
 */
HAL_StatusTypeDef drv8323_update(drv8323_TypeDef_tp drv)
{

	HAL_StatusTypeDef hal_status = HAL_OK;

	hal_status = drv8323_read_reg(drv, SPI_REG_FAULT_STAT, &(drv->fault_status_1));

	hal_status = drv8323_read_reg(drv, SPI_REG_FAULT_STAT2, &(drv->fault_status_2));

	hal_status = drv8323_read_reg(drv, SPI_REG_GATE_DRV_LS, &(drv->gate_drive_LS));

	hal_status = drv8323_read_reg(drv, SPI_REG_OCP_CTRL, &(drv->OCP_control));

	hal_status = drv8323_read_reg(drv, SPI_REG_CSA_CTRL, &(drv->CSA_control));

	return hal_status;
}

/**
 * @brief Initialize DRV8323 registers
 * 
 * @param drv Pointer to the DRV8323 device structure
 * @return HAL status
 */
HAL_StatusTypeDef drv8323_init_registers(drv8323_TypeDef_t *drv)
{
	HAL_StatusTypeDef ret_val = HAL_OK;
	drv8323_TypeDef_t tmpDrv = {0};
	ret_val = drv8323_update(drv);

	if (ret_val != HAL_OK)
	{

		return HAL_ERROR;
	}
	if (drv->gate_drive_HS == UINT16_MAX)
	{
		return HAL_ERROR;
	}
	// Update driver_control with combined masks
	drv->driver_control |= (int16_t)(PWM_MODE_MASK | OTW_REP_MASK);

	// Update gate_drive_HS with combined masks
	drv->gate_drive_HS |= (int16_t)(GATE_DRV_HS_IDRIVEP_HS_1000mA | GATE_DRV_HS_IDRIVEN_HS_2000mA | GATE_DRV_HS_UN_LOCK_Msk);
#ifdef SIBONI
	// Update CSA_control with combined operations
	drv->CSA_control = (int16_t)(drv->CSA_control & ~((3 << CSA_CTRL_CSA_GAIN_Pos) | 3)) |
					   (CSA_CTRL_CSA_GAIN_10VV | CSA_CTRL_SEN_LVL_0_25V);

	// Update OCP_control with combined operations
	drv->OCP_control = (int16_t)(drv->OCP_control & ~0xF) | (OCP_CTRL_VDS_LVL_0_2V);

#endif

	ret_val = drv8323_write_reg(drv, SPI_REG_OCP_CTRL, drv->OCP_control);
	ret_val = drv8323_write_reg(drv, SPI_REG_CSA_CTRL, drv->CSA_control);
	ret_val = drv8323_write_reg(drv, SPI_REG_GATE_DRV_HS, drv->gate_drive_HS);
	ret_val = drv8323_write_reg(drv, SPI_REG_DRV_CTRL, drv->driver_control);

	tmpDrv = *drv;
	ret_val = drv8323_update(drv);
	if ((tmpDrv.driver_control != drv->driver_control) && (tmpDrv.gate_drive_HS != drv->gate_drive_HS) && (tmpDrv.CSA_control != drv->CSA_control) && (tmpDrv.OCP_control != drv->OCP_control))
	{
		return HAL_ERROR;
	}
	else
	{
		return HAL_OK;
	}
}

/**
 * @brief Initialize a DRV8323 device
 * 
 * @param drv_num DRV8323 device number
 * @param spi Pointer to the SPI handle
 * @param CSport GPIO port for chip select
 * @param CSPin GPIO pin for chip select
 */
void drv8323_Init(drv8323_et drv_num, SPI_HandleTypeDef *spi, GPIO_TypeDef *CSport, uint16_t CSPin)
{
	drv[drv_num].spi = spi;
	drv[drv_num].CSpin = CSPin;
	drv[drv_num].CSport = CSport;
	HAL_GPIO_WritePin(drv[drv_num].CSport, drv[drv_num].CSpin, GPIO_PIN_SET);
}

/**
 * @brief Initialize all DRV8323 registers
 */
void drv8323_registers_init(void)
{
	for (int i = 0; i < ALL_DRV8323; i++)
	{
		if (drv8323_init_registers(&drv[i]) != HAL_OK)
		{
//			system_fault_set_fault(drv8323_fault);
		}
	}
}

/**
 * @brief Clear faults in all DRV8323 devices
 * 
 * @return true if successful, false otherwise
 */
bool clear_fault_drv8323(void)
{
	for (int i = 0; i < ALL_DRV8323; i++)
	{
		if (drv8323_init_registers(&drv[i]) != HAL_OK)
		{
			return false;
		}
	}
	return true;
}
