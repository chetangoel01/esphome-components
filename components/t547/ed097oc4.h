#pragma once

#include <driver/gpio.h>


// Data lines
#define D7 GPIO_NUM_7
#define D6 GPIO_NUM_6
#define D5 GPIO_NUM_5
#define D4 GPIO_NUM_4
#define D3 GPIO_NUM_3
#define D2 GPIO_NUM_2
#define D1 GPIO_NUM_1
#define D0 GPIO_NUM_8

// E-paper control lines
#define CKV GPIO_NUM_38
#define STH GPIO_NUM_40
#define CKH GPIO_NUM_41

// If LilyGO docs show CFG on IO21:
#define CFG_DATA GPIO_NUM_21

void epd_base_init(uint32_t epd_row_width);
//void epd_poweron();
//void epd_poweroff();

/**
 * Start a draw cycle.
 */
void epd_start_frame();

/**
 * End a draw cycle.
 */
void epd_end_frame();

/**
 * Waits until all previously submitted data has been written.
 * Then, the following operations are initiated:
 *
 *  - Previously submitted data is latched to the output register.
 *  - The RMT peripheral is set up to pulse the vertical (gate) driver for
 *  `output_time_dus` / 10 microseconds.
 *  - The I2S peripheral starts transmission of the current buffer to
 *  the source driver.
 *  - The line buffers are switched.
 *
 * This sequence of operations allows for pipelining data preparation and
 * transfer, reducing total refresh times.
 */
void IRAM_ATTR epd_output_row(uint32_t output_time_dus);

/** Skip a row without writing to it. */
void IRAM_ATTR epd_skip();

/**
 * Get the currently writable line buffer.
 */
uint8_t IRAM_ATTR *epd_get_current_buffer();

/**
 * Switches front and back line buffer.
 * If the switched-to line buffer is currently in use,
 * this function blocks until transmission is done.
 */
void IRAM_ATTR epd_switch_buffer();
