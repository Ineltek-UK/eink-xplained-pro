/**
 * \file
 * 
 * \brief Eink Display Driver Component
 * 
 * Eink Software Library
 * Microchip ASF3 Variant - release 1.1 - August 2018
 * 
 * \author George Sephton
 * 
 * \copyright Copyright (c) 2018 Ineltek Ltd. All rights reserved.
 * 
 * \page eink_xplained_license License
 *
 * \brief Software License and Disclaimer
 *
 * \section software_license Software License
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a copy of the GNU General Public License, see
 * see <https://www.gnu.org/licenses/>
 *
 * \subsection software_license_logo Logo Use
 *
 * Use of the Ineltek logo, packaged with this software library, is not subject
 * to the above GPL software license and is property of Ineltek GmbH and it subsidiaries.
 * It may not be used for commercial use and may not be used to endorse or promote products
 * without specific prior written permission.
 *
 * \subsection software_license_conditions Conditions
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    software license, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    software license, this list of conditions and the following disclaimer
 *    in the documentation and/or other materials provided with the distribution.
 *
 * 3. The names, trademarks or logos of Eink, Ineltek or Microchip, and any combination
 *    thereof, may not be used to endorse or promote products derived from this
 *    software without specific prior written permission. They are also subject to their
 *    own copyrights and trademarks that may not be expressed here.
 *
 * \section disclaimer Disclaimer
 *
 * THIS SOFTWARE IS PROVIDED BY INELTEK "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL INELTEK BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef EINK_DRIVER_H_
#define EINK_DRIVER_H_

#include <compiler.h>
#include <ioport.h>
#include <delay.h>

// Controller and Eink configuration file
#include <conf_eink.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Eink X Coordinate typdef.
 */
typedef uint16_t eink_x_coordinate;
/**
 *  \brief Eink Y Coordinate typdef.
 */
typedef uint16_t eink_y_coordinate;
/**
 *  \brief Eink Partial Window X Coordinate typdef.
 */
typedef uint16_t eink_pw_x_coordinate;
/**
 *  \brief Eink Partial Window Y Coordinate typdef.
 */
typedef uint16_t eink_pw_y_coordinate;
/**
 *  \brief Eink Coordinate typdef.
 */
typedef uint16_t eink_coordinate;

/**
 * \brief Temperature Sensor Selector enum.
 *
 * - Internal (Default)
 * - External
 */
enum temperature_sensor {
    INTERNAL_TEMPERATURE_SENSOR,
    EXTERNAL_TEMPERATURE_SENSOR
};

/**
 * \brief Display Rotation enum.
 *
 * Automatically deals with Scan and Gate direction to ensure correct rotation.
 * 
 * \note 0 degrees of rotation  for the ED029TC1 has the display horizontal,
 * with the FPC on the right of the display.
 */
enum eink_display_rotation {
    ROTATE_0,
    ROTATE_90,
    ROTATE_180,
    ROTATE_270
};

/**
 * \brief Initializes the Eink hardware interface.
 *
 * \note Initializes the display controller hardware interface, regardless
 * of driver IC, interface or display. Takes defintions from conf_eink.h.
 */
static void eink_interface_init(void)
{
    /* Set up the Eink interface outputs */
    ioport_set_pin_dir(EINK_BS, IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(EINK_CSB, IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(EINK_DC, IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(EINK_RST, IOPORT_DIR_OUTPUT);
    
    ioport_set_pin_dir(EINK_SPI_SDA, IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(EINK_SPI_SCL, IOPORT_DIR_OUTPUT);
    
    /* Set up the Eink initial outputs */
    ioport_set_pin_level(EINK_BS, 0); /* Set BS LOW for 4 wire SPI interface */
    ioport_set_pin_level(EINK_CSB, 1); /* Set CSB HIGH to disable communication to connected display */
    ioport_set_pin_level(EINK_DC, 1); /* Set DC HIGH by default */
    ioport_set_pin_level(EINK_RST, 1); /* Set RST HIGH since reset is active low */
    
    ioport_set_pin_level(EINK_SPI_SDA, 0); /* Set SDA LOW for initial state */
    ioport_set_pin_level(EINK_SPI_SCL, 0); /* Set SCL LOW for initial state */

    /* Set up the BUSY input */
    ioport_set_pin_dir(EINK_BUSY, IOPORT_DIR_INPUT);
    ioport_set_pin_mode(EINK_BUSY, IOPORT_MODE_PULLUP);
}

/** \name Eink display driver data transfer functions.
 * @{
 */
void eink_write_data(
        uint8_t command,
        uint8_t *data,
        uint16_t data_bytes);
        
void eink_read_data(
        uint8_t command,
        uint8_t *data);
        
void eink_send_raw_byte(
        uint8_t send_byte);
/** @} */

void eink_set_bit(
        uint8_t *byte,
        uint8_t bit_number,
        bool bit_value);

#ifdef __cplusplus
}
#endif

#endif /* EINK_DRIVER_H_ */