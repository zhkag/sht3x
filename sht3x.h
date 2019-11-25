#ifndef __SHT3X_H__
#define __SHT3X_H__

#include <rthw.h>
#include <rtthread.h>

#include <rthw.h>
#include <rtdevice.h>

#define SHT3X_REPETABILITY_LOW 0
#define SHT3X_REPETABILITY_MEDIUM 1
#define SHT3X_REPETABILITY_HIGH 2

/* sht3x commands define */
// read serial number:
#define CMD_READ_SERIALNBR  0x3780     
// read status register:
#define CMD_READ_STATUS     0xF32D     
// clear status register:
#define CMD_CLEAR_STATUS    0x3041  
// enabled heater:
#define CMD_HEATER_ENABLE   0x306D   
// disable heater  
#define CMD_HEATER_DISABLE  0x3066      
// soft reset
#define CMD_SOFT_RESET      0x30A2      
// accelerated response time
#define CMD_ART             0x2B32
// break, stop periodic data acquisition mode
#define CMD_BREAK           0x3093

// measurement: polling, high repeatability
#define CMD_MEAS_POLLING_H 0x2400  
// measurement: polling, medium repeatability
#define CMD_MEAS_POLLING_M 0x240B  
// measurement: polling, low repeatability
#define CMD_MEAS_POLLING_L 0x2416 

#define SHT3X_ADDR_PD 0x44 // addr pin pulled down: 0x44
#define SHT3X_ADDR_PU 0x45 // addr pin pulled down: 0x45

typedef union sht3x_status_word
{
    rt_uint16_t status_word;
    struct status_bits
    {
        // rt_uint16_t alert_pending: 1 ;
        // rt_uint16_t reserved_0 : 1 ;
        // rt_uint16_t heater : 1 ;
        // rt_uint16_t reserved_1 : 1 ;
        // rt_uint16_t RH_tracking_alert : 1 ;
        // rt_uint16_t T_tracking_alert : 1 ;
        // rt_uint16_t reserved_2 : 5 ;
        // rt_uint16_t reset_detected : 1 ;
        // rt_uint16_t reserved_3 : 2 ;
        // rt_uint16_t command_ok : 1 ;
        // rt_uint16_t checksum_ok : 1 ;
        rt_uint16_t checksum_ok : 1 ;
        rt_uint16_t command_ok : 1 ;
        rt_uint16_t reserved_3 : 2 ;
        rt_uint16_t reset_detected : 1 ;
        rt_uint16_t reserved_2 : 5 ;
        rt_uint16_t T_tracking_alert : 1 ;
        rt_uint16_t RH_tracking_alert : 1 ;
        rt_uint16_t reserved_1 : 1 ;
        rt_uint16_t heater : 1 ;
        rt_uint16_t reserved_0 : 1 ;
        rt_uint16_t alert_pending: 1 ;
    } bits;
}sht3x_status;


struct sht3x_device
{
    struct rt_i2c_bus_device *i2c;
    rt_uint8_t sht3x_addr ;
    rt_mutex_t lock;
    float temperature ;
    float humidity ;
    /* the command for data readout: change it as you need */ 
    rt_uint16_t cmd_readout;
    sht3x_status status ;
};
typedef struct sht3x_device *sht3x_device_t;

/**
 * This function resets all parameter with default
 *
 * @param dev the pointer of device driver structure
 *
 * @return the softreset status,RT_EOK reprensents setting successfully.
 */
rt_err_t sht3x_softreset(sht3x_device_t dev);

/**
 * This function initializes sht3x registered device driver
 *
 * @param dev the name of sht3x device
 *
 * @return the sht3x device.
 */
sht3x_device_t sht3x_init(const char *i2c_bus_name, rt_uint8_t sht3x_addr);

/**
 * This function releases memory and deletes mutex lock
 *
 * @param dev the pointer of device driver structure
 */
void sht3x_deinit(sht3x_device_t dev);

/**
 * This function reads temperature and humidity by sht3x sensor measurement using single shot mode
 *
 * @param dev the pointer of device driver structure
 *
 * @return the relative temperature converted to float data.
 */
rt_err_t sht3x_read_singleshot(sht3x_device_t dev);


#endif /* _SHT30_H__ */