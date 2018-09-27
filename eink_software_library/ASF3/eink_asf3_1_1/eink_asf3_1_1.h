/**
 * \file
 * 
 * \brief Eink Software Library
 *        Microchip ASF3 Variant - release 1.1 - August 2018
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

/** \mainpage
 * \section intro Introduction
 * This is Ineltek's Eink Software Library (version 1.1) for use with Microchip SAM MCUs and ASF3.
 *
 * It is designed to work with the following displays and driver ICs:
 * - <strong>ED029TC1</strong> : UC8151
 * - <em><strong>HINK-E0154A05</strong> : SSD1608 (not yet implemented)</em>
 * - <em><strong>ED057TC2</strong> : UC8159 (not yet implemented)</em>
 * 
 * It also includes several open source fonts in varying sizes and weights.
 * \note The library only allows a single display to be connected to the MCU.
 * 
 * \section setup_steps Setup Steps
 * 
 * \subsection setup_prerequisites Prerequisites
 * 
 * In order to use the Eink ASF3 Software Library, several ASF services must be added from the ASF
 * wizard. These are:
 * - Delay routines (service)
 * - IOPORT - General purpose I/O service (service)
 * 
 * \note Note that this library is not compatible with Atmel START - for this you must use the
 * Eink ASF4 Software Library.
 *
 * Next, the library must be added to the compiler include paths:<br>
 * See Project Properties > Toolchain > ARM/GNU C Compiler > Directories:
 * - <BASE_DIR>/eink_asf3_1_1
 * - <BASE_DIR>/eink_asf3_1_1/fonts
 *
 * Finally the following line must be added directly below the ASF include statement:
 * \code
 * #include <asf.h>
 * #include <eink_asf3_1_1.h>
 * \endcode
 * 
 * \subsection setup_initialization Initialization Code
 *
 * We now need to add the initialization code to our main.c file to get the example up and running.
 * 
 * First the conf_eink_example.h must be copied from the eink_asf3_1_1 directory
 * into your src/config directory and renamed to conf_eink.h
 *
 * Next, the definition:
 * \code
 * #define eink_project_excluded
 * \endcode
 * must be add above the ASF include if the Eink library is not included in the Solution Explorer:
 * \code
 * #define eink_project_excluded
 * #include <asf.h>
 * #include <eink_asf3_1_1.h>
 * \endcode
 *
 * To initialize the display, we have to first select which display we are using as the Eink Software
 * Library supports multiple Eink displays.
 *
 * \subsubsection setup_initialization_ed029tc1 ED029TC1 Initialization
 * To initialize the Eink library for use with the ED029TC1 (UC8151), the eink_ed029tc1_init() function
 * must be called. \ref uc8151_config must be used as the configuration struct. Note that
 * uc8151_get_config_defaults() should be called before making any required changes and passing them to
 * the initialization function.
 *
 * Example Code:
 *
 * \code
 * struct uc8151_config eink_conf;
 *
 * uc8151_get_config_defaults(&eink_conf);
 * eink_conf.temperature_sensor_settings.sensor_select = EXTERNAL_TEMPERATURE_SENSOR;
 * eink_conf.panel_settings.display_colours = B_W_PIXELS;
 * eink_conf.panel_settings.display_rotation = ROTATE_180;
 * eink_ed029tc1_init(&eink_conf, false);
 * \endcode
 *
 * \subsubsection setup_initialization_hink_e0154a05 HINK-E0154A05 Initialization
 * \note Note yet implemented
 *
 * \subsubsection setup_initialization_ED057TC2 ED057TC2 Initialization
 * \note Note yet implemented
 *
 * \section gfx_library GFX Library
 * 
 * Once initialized, the library stores a buffer in RAM in order keep track of the canvas - initially
 * it is all white. There are several primitive function that allow for some data to be written to the canvas:
 * - gfx_eink_graphics_fill_screen()
 * - gfx_eink_load_mono_image()
 * - gfx_eink_graphics_draw_line()
 * - gfx_eink_graphics_draw_rect()
 * - gfx_eink_text_write_string()
 * - gfx_eink_set_pixel()
 * 
 * The canvas buffer can be uploaded to the display controller with the use of gfx_eink_put_display_buffer()
 *
 * If you decide to load the buffer but refresh the display later on, this can be achieved using the 
 * gfx_eink_refresh_display_buffer()
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 7.0 and requires ASF version
 * 3 (originally compiled using ASF version 3.42.0). Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.ineltek.com">Ineltek</A>.\n
 */
#ifndef EINK_ASF3_H_INCLUDED
#define EINK_ASF3_H_INCLUDED

#ifdef eink_project_excluded
    #include <common2/components/eink_drivers/eink_driver.c>

    #include <common2/components/eink_drivers/uc8151/uc8151.c>
    #include <common2/services/eink/displays/ed029tc1.c>
    #include <common2/components/eink_drivers/ssd1608/ssd1608.c>
    #include <common2/services/eink/displays/hink_e0154a05.c>

    #include <common2/services/eink/eink_gfx/eink_gfx.h>
    #include <common2/services/eink/eink_gfx/eink_gfx_graphics.c>
    #include <common2/services/eink/eink_gfx/eink_gfx_text.c>
#else
    #include <common2/components/eink_drivers/eink_driver.h>

    #include <common2/components/eink_drivers/uc8151/uc8151.h>
    #include <common2/services/eink/displays/ed029tc1.h>
    #include <common2/components/eink_drivers/ssd1608/ssd1608.h>
    #include <common2/services/eink/displays/hink_e0154a05.h>

    #include <common2/services/eink/eink_gfx/eink_gfx.h>
    #include <common2/services/eink/eink_gfx/eink_gfx_graphics.h>
    #include <common2/services/eink/eink_gfx/eink_gfx_text.h>
#endif

#endif /* EINK_ASF3_H_INCLUDED */