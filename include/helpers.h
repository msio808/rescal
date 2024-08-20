#ifndef HELPERS_H
#define HELPERS_H
#pragma once

#include <math.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <execinfo.h>

#define ERROR_LOGPATH "../logs/errorlogs.log"

typedef enum FLAGS {
    //? For styling/formatting output texts on the terminal
    DIM          =  0x00000002,
    BOLD         =  0x00000001,
    INVERT       =  0x00000007,
    ITALIC       =  0x00000003,
    UNDERLINED   =  0x00000004,
    RESET_ATTR   =  0x00000000,

    //?
    VALUE_ERROR     = -0x00000001,
    VALUE_SUCCESS   =  0x00000000,

    BUFSIZE             =  0x00000040,
    MIN_BAND_COUNT      =  0x00000004,
    MAX_BAND_COUNT      =  0x00000006,
    INVALID_BAND_COLOR  = -0x00000009
} flags_t;


/**
 * @brief Flags for styling/coloring functions, & functions to convert from RGB values to 256 bit mode
**/
typedef enum COLOR_MODES {
    RGB_MAX     = 0x000000FF,  //? Maximum RGB value
    BIT_MODE    = 0x00000002,  //? 24 bit mode
    FOREGROUND  = 0x00000026,  //? Foreground Mode
    BACKGROUND  = 0x00000030,  //? Background Mode
} cmodes_t;


/**
 * @brief Struct for holding rgb color values
**/
typedef struct RGB_COLORS {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB_t;


/**
 * @brief Struct for holding rgb color set of the 'RGB_t' struct for styling text on the terminal
**/
typedef struct RGB_COLORSET {
    RGB_t foreground;
    RGB_t background;
} RGBset_t;


void print_table(void);
void set_console_text_attr(int);
void set_console_color_attr(RGBset_t);

void clr_scr(void);
void set_fg_color(RGB_t);
void set_bg_color(RGB_t);
void set_console_text_attr(int);
void set_console_color_attr(RGBset_t);

void signal_handler(int);
void setup_signal_handler(void);

void print(const char *,...) __attribute__((format(printf, 1, 2)));
void cprintf(int, const RGBset_t *, const char *,...) __attribute__((format(printf, 3, 4)));


#endif //HELPERS_H
