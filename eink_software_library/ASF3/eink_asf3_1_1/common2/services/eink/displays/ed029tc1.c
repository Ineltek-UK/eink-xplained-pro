/**
 * \file
 * 
 * \brief ED029TC1 Eink Display Service
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
#include <common2/services/eink/displays/ed029tc1.h>

/**
 * \brief ED029TC1 GFX Library Configuration.
 * Used to load the GFX config structure with ED029TC1 information and map
 * the display specific functions.
 */
const struct eink_gfx_config eink_gfx_ed029tc1_config = { GFX_ED029TC1, GFX_ED029TC1_MAX_WIDTH, GFX_ED029TC1_MAX_HEIGHT, ed029tc1_dtm1_display_buffer, ed029tc1_dtm2_display_buffer, eink_ed029tc1_refresh_display_buffer, eink_ed029tc1_put_display_buffer, eink_ed029tc1_set_pixel, eink_ed029tc1_graphics_load_mono_image };
    
/**
 * \brief Initialize UC8151 controller and Eink display.
 * It will also write the display buffers to all zeros.
 *
 * \note This function will clear the contents of the display if clear_display is set to true
 *
 * \param *config The configuration to write to the display driver.
 * \param clear_display If enabled, the display with be cleared.
 */
void eink_ed029tc1_init(struct uc8151_config *const config, bool clear_display)
{
    /* Sanity check arguments */
    Assert(config);
    
    uint16_t buffer_index;

    /* Initialize the low-level display controller. */
    uc8151_init();

    /* Configure the UC8151 controller. */
    uc8151_set_config(config);
    
    /* Set Partial Window settings */
    uc8151_global_instance.partial_window_en = PARTIAL_WINDOW_DISABLED;
    uc8151_global_instance.partial_window_width = 0;
    uc8151_global_instance.partial_window_height = 0;
    
    /* Set the GFX Library Configuration to ED029TC1 */
    ptr_eink_gfx_config = (struct eink_gfx_config*) &eink_gfx_ed029tc1_config;

    /* Set both display buffers to all WHITE. */
    for (buffer_index = 0; buffer_index < GFX_ED029TC1_DISPLAY_BUFFER_SIZE; buffer_index++) {
        ptr_eink_gfx_config->display_buffer_1_ptr[buffer_index] = 0xFF;
        ptr_eink_gfx_config->display_buffer_1_ptr[buffer_index] = 0xFF;
    }
    
    /* Send both display buffers to the display if requested. */
    if(clear_display) eink_ed029tc1_put_display_buffer(true);
}

/**
 * \brief Sends the two display buffers to the Display and can be 
 * refreshed if requested.
 * 
 * When using the UC8151 in black/white mode, DTM1 is used as the OLD display
 * buffer and DTM2 is used as the NEW display buffer.
 * 
 * The controller looks at each pixels current state and the new 
 * state and selects a waveform based on this. In this mode, there are 4
 * waveforms to choose from:
 * - Black to White
 * - White to White
 * - White to Black
 * - Black to Black
 * 
 * When using the UC8151 in black/white/red mode, DTM1 is used as the B/W display
 * buffer and DTM2 is used as the Red display buffer. The controller doesn't take
 * the previous pixel state into account in this mode.
 *
 * \param refresh_display Refresh the display after uploading the display buffers.
 */
void eink_ed029tc1_put_display_buffer(bool refresh_display)
{
    uint16_t i;
    
    /* Enable power to the display */
    eink_write_data(UC8151_PON, 0, 0);
        
    /* Update the DTM1 register with the previous display buffer */
    eink_write_data(UC8151_DTM1, ptr_eink_gfx_config->display_buffer_1_ptr, GFX_ED029TC1_DISPLAY_BUFFER_SIZE);
    eink_write_data(UC8151_DSP, 0, 0);
    uc8151_wait_for_busy();
    
    /* Update the DTM2 register with the display buffer */
    eink_write_data(UC8151_DTM2, ptr_eink_gfx_config->display_buffer_2_ptr, GFX_ED029TC1_DISPLAY_BUFFER_SIZE);
    eink_write_data(UC8151_DSP, 0, 0);
    uc8151_wait_for_busy();
    
    if(refresh_display) {
        /* Send the Refresh Display command */
        eink_write_data(UC8151_DRF, 0, 0);
        uc8151_wait_for_busy();
    }
    
    /* Disable power to the display */
    eink_write_data(UC8151_POF, 0, 0);
    uc8151_wait_for_busy();
    
    if (uc8151_global_instance.panel_settings.display_colours == B_W_PIXELS) {
    
        /* Copy the current display buffer into the previous display buffer */
        for (i=0;i<GFX_ED029TC1_DISPLAY_BUFFER_SIZE;i++) {
            ptr_eink_gfx_config->display_buffer_1_ptr[i] = ptr_eink_gfx_config->display_buffer_2_ptr[i];
        }
    }
}

/**
 * \brief Set a specified pixel in the display buffer based an x and a y coordinate.
 *
 * \param x_set X coordinate of the pixel to set.
 * \param y_set Y coordinate of the pixel to set.
 * \param pixel_colour Color to set the pixel to.
 */
void eink_ed029tc1_set_pixel(eink_x_coordinate x_set, eink_y_coordinate y_set, enum eink_pixel_colour pixel_colour)
{
    /* Sanity check arguments */
    Assert(x_set);
    Assert(y_set);
    Assert(pixel_colour);
    
    eink_y_coordinate y1_set, x1_set, byte_set;
    uint8_t bit_set, pixel_set_1 = 1, pixel_set_2 = 1;
    
    /* Ignore any pixels being set outside of the display window */
    if ( (x_set >= 0) && (x_set < uc8151_global_instance.display_width) && (y_set >= 0) && (y_set < uc8151_global_instance.display_height) ) {
        
        if ( (uc8151_global_instance.panel_settings.display_rotation == ROTATE_90) || (uc8151_global_instance.panel_settings.display_rotation == ROTATE_270) ) {
            /* Calculate which byte the pixel in question is contained in */
            x1_set = 15 - ((x_set - (x_set % 8)) / 8);
            byte_set = (((y_set + 1) * 16) - 1 - x1_set);
            /* Calculate which bit in that byte the pixel in question is */
            bit_set = 7 - (x_set % 8);
        } else {
            /* Calculate which byte the pixel in question is contained in */
            y1_set = ((y_set - (y_set % 8)) / 8);
            byte_set = (((x_set + 1) * 16) - 1 - y1_set);
            /* Calculate which bit in that byte the pixel in question is */
            bit_set = (y_set % 8);
        }
        /**
         * When using the UC8151 in black/white mode, DTM1 is used as the OLD display
         * buffer and DTM2 is used as the NEW display buffer.
         *
         * The controller looks at each pixels current state and the new
         * state and selects a waveform based on this. In this mode, there are 4
         * waveforms to choose from:
         * - Black to White
         * - White to White
         * - White to Black
         * - Black to Black
         *
         * When using the UC8151 in black/white/red mode, DTM1 is used as the B/W display
         * buffer and DTM2 is used as the Red display buffer. The controller doesn't take
         * the previous pixel state into account in this mode.
         */
        if (uc8151_global_instance.panel_settings.display_colours == B_W_PIXELS) {
        
            /*
            *           DTM2
            * BLACK:     0      (BLACK BORDER)
            * WHITE:     1      (BLACK BORDER)
            */
            if (pixel_colour == PIXEL_BLACK) pixel_set_2 = 0;
            else if (pixel_colour == PIXEL_WHITE) pixel_set_2 = 1;
            /* Ignore RED pixels if not supported */
        
            /* Set the NEW display buffer */
            eink_set_bit(&ptr_eink_gfx_config->display_buffer_2_ptr[byte_set], bit_set, pixel_set_2);
        
        } else {
        
            /*
            *           DTM1     DTM2
            * BLACK:     0        1      (WHITE BORDER)
            * WHITE:     1        1      (WHITE BORDER)
            * RED:       1        0      (WHITE BORDER)
            * RED:       0        0      (WHITE BORDER)
            */
            if (pixel_colour == PIXEL_BLACK) {
                pixel_set_1 = 0;
                pixel_set_2 = 1;
            } else if(pixel_colour == PIXEL_WHITE) {
                pixel_set_1 = 1;
                pixel_set_2 = 1;
            } else if(pixel_colour == PIXEL_RED) {
                pixel_set_1 = 0;
                pixel_set_2 = 0;    
            }
        
            /* Set the B/W and RED display buffers */
            eink_set_bit(&ptr_eink_gfx_config->display_buffer_1_ptr[byte_set], bit_set, pixel_set_1);
            eink_set_bit(&ptr_eink_gfx_config->display_buffer_2_ptr[byte_set], bit_set, pixel_set_2);    
        }
    }
}

/**
 * \brief Load a bitmap into the display buffer.
 *
 * This function simply copies an array of data directly into the appropriate display buffers
 * (depending on color). For best results an array of the same size of the display buffers should
 * be used.
 *
 * This can be achieved by using the following definition:
 *
 * \code
 * GFX_ED029TC1_DISPLAY_BUFFER_SIZE
 * \endcode
 * 
 * \note The data bytes in the buffer are translated vertically (non-paged) with byte 0 being 
 * equal to the first 8 pixels in the bottom left corner of the display - bytes should be Big Endian.
 * 
 * \param *img_array Pointer to bitmap array.
 * \param array_size Bitmap array size.
 * \param foreground_colour Color of the foreground - where bit is equal to 1 in the array.
 * \param eink_pixel_colour Color of the background - where bit is equal to 0 in the array.
 *
 * \note The loaded bitmap does not follow the same rotation rules as the rest of the display:
 *       - Screen rotation of 0 degrees and 90 degrees will display the bitmap at 0 degrees
 *       - Screen rotation of 180 degrees and 270 degrees will display the bitmap at 180 degrees
 * \note As a result bitmaps will always be shown horizontally. For vertical bitmaps, the image 
 *       must be rotated prior to creating the bitmap. 
 */
void eink_ed029tc1_graphics_load_mono_image(uint8_t *img_array, uint16_t array_size, enum eink_pixel_colour foreground_colour, enum eink_pixel_colour background_colour)
{
    /* Sanity check arguments */
    Assert(img_array);
    Assert(array_size);
    Assert(foreground_colour);
    Assert(background_colour);

    uint16_t buffer_index;
        
    /* Set background colour. */
    switch (background_colour) {
        case PIXEL_BLACK: gfx_eink_graphics_fill_screen(FILL_BLACK); break;
        case PIXEL_WHITE: gfx_eink_graphics_fill_screen(FILL_WHITE); break;
        case PIXEL_RED:   gfx_eink_graphics_fill_screen(FILL_RED); break;
    }
     
     if(foreground_colour != background_colour) {
        /*
        * When using the UC8151 in black/white mode (ED029TC1), DTM1 is used
        * as the OLD display buffer and DTM2 is used as the current display
        * buffer.
        *
        * When using the UC8151 in black/white/red mode (EL029TR1), DTM1 is
        * used as the B/W display buffer and DTM2 is used as the Red display
        * buffer.
        */
        if (uc8151_global_instance.panel_settings.display_colours == B_W_PIXELS) {
        
            /*
            *           DTM2
            * BLACK:     0      (BLACK BORDER)
            * WHITE:     1      (BLACK BORDER)
            */
        
            /* Set the NEW display buffer */
            for (buffer_index = 0; buffer_index < array_size; buffer_index++) {
                if (foreground_colour == PIXEL_BLACK) {
                    ptr_eink_gfx_config->display_buffer_2_ptr[buffer_index] &= ~(*img_array);
                } else if (foreground_colour == PIXEL_WHITE) {
                    ptr_eink_gfx_config->display_buffer_2_ptr[buffer_index] |= (*img_array);
                }
                
                img_array++;
                /* Ignore RED pixels if not supported */
            }
        
        } else {
        
            /*
            *           DTM1     DTM2
            * BLACK:     0        1      (WHITE BORDER)
            * WHITE:     1        1      (WHITE BORDER)
            * RED:       1        0      (WHITE BORDER)
            * RED:       0        0      (WHITE BORDER)
            */
        
            /* Set the B/W and RED display buffers */
            for (buffer_index = 0; buffer_index < array_size; buffer_index++) {
                if (background_colour == PIXEL_RED) {
                    ptr_eink_gfx_config->display_buffer_1_ptr[buffer_index] = 0x00;
                    ptr_eink_gfx_config->display_buffer_2_ptr[buffer_index] = 0x00;
                } else if (background_colour == PIXEL_BLACK) {
                    ptr_eink_gfx_config->display_buffer_1_ptr[buffer_index] = 0x00;
                    ptr_eink_gfx_config->display_buffer_2_ptr[buffer_index] = 0xFF;
                } else if (background_colour == PIXEL_WHITE) {
                    ptr_eink_gfx_config->display_buffer_1_ptr[buffer_index] = 0xFF;
                    ptr_eink_gfx_config->display_buffer_2_ptr[buffer_index] = 0xFF;
                }
                
                if (foreground_colour == PIXEL_BLACK) {
                    ptr_eink_gfx_config->display_buffer_1_ptr[buffer_index] &= ~(*img_array);
                    ptr_eink_gfx_config->display_buffer_2_ptr[buffer_index] |= (*img_array);
                    
                } else if (foreground_colour == PIXEL_WHITE) {
                    ptr_eink_gfx_config->display_buffer_1_ptr[buffer_index] |= (*img_array);
                    ptr_eink_gfx_config->display_buffer_2_ptr[buffer_index] |= (*img_array);

                } else if (foreground_colour == PIXEL_RED) {
                    ptr_eink_gfx_config->display_buffer_1_ptr[buffer_index] |= (*img_array);
                    ptr_eink_gfx_config->display_buffer_2_ptr[buffer_index] &= ~(*img_array);
                }
                img_array++;
            }
        }
    }
}