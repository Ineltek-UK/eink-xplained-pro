/**
 * \file
 * 
 * \brief Eink Configuration File
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
/**
 * \name Eink SPI Interface defines.
 *
 * \def EINK_BS
 *  Defines the SPI Bus Selection pin.
 *  - LOW : 4-Wire (8-bit data).
 *  - HIGH : 3-Wire (9-bit data).
 * 
 * \note The Eink software library uses the displays in 4-wire mode.
 *
 * \def EINK_BUSY
 *  Defines the Busy pin.
 *  \note - ED029TC1 : When LOW the display driver is busy and shouldn't be interrupted.
 *  \note - HINK-E0154A05/ED057TC2 : When HIGH the display driver is busy and shouldn't be interrupted.
 *
 * \def EINK_CSB
 *  Defines the SPI Chip Select pin.
 *  \note Active LOW.
 *
 * \def EINK_DC
 *  Defines the Data/Command Select pin.
 *  - HIGH : data to be treated as DATA.
 *  - LOW : data to be treated as CMD.
 *
 * \def EINK_RST
 *  Defines the RESET pin.
 *  \note Active LOW.
 *
 * \def EINK_SPI_SDA
 *  Defines the bidirectional SPI DATA pin.
 *
 * \def EINK_SPI_SCL
 *  Defines the SPI CLOCK pin.
*/
#ifndef CONF_UC8151_H_INCLUDED
#define CONF_UC8151_H_INCLUDED

#include <board.h>

#ifdef EXT1_ADC_MODULE
/* Interface configuration for SAM Xplained Pro */
#  define EINK_BS                     EXT1_PIN_5
#  define EINK_BUSY                   EXT1_PIN_6
#  define EINK_CSB                    EXT1_PIN_15
#  define EINK_DC                     EXT1_PIN_3
#  define EINK_RST                    EXT1_PIN_16

#  define EINK_SPI_SDA                EXT1_PIN_17
#  define EINK_SPI_SCL                EXT1_PIN_18
#else
/* SAMV71 Xplained Ultra configuration */
#  define EINK_BS                     EXT1_PIN_5
#  define EINK_BUSY                   EXT1_PIN_6
#  define EINK_CSB                    EXT1_PIN_15
#  define EINK_DC                     EXT1_PIN_3
#  define EINK_RST                    EXT1_PIN_16

#  define EINK_SPI_SDA                EXT1_PIN_17
#  define EINK_SPI_SCL                EXT1_PIN_18
#endif

#endif /* CONF_UC8151_H_INCLUDED */