#ifndef SRC_H
#define SRC_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <termios.h>
#include <strings.h>

// Enum for resistor colors
typedef enum COLORS {
    BLACK, BROWN, RED, ORANGE, YELLOW, GREEN,
    BLUE, VIOLET, GREY, WHITE, GOLD, SILVER
} colors_t;

// Struct to hold resistor band values
typedef struct RESBANDS {
    colors_t band_1;
    colors_t band_2;
    colors_t band_3;
} RB_t;

typedef struct COLORMAP{
    const char* name;
    colors_t color;
} colormap_t;

// Struct to hold resistor information including bands and tolerance
typedef struct RESISTOR {
    RB_t      bands;
    char      *resistor_value;
    int       ppm;
    double    tolerance; // Tolerance band
    double    multiplier;  // Multiplier band
} res_t;


static const int band[] = {
    [BLACK]     = BLACK,
    [BROWN]     = BROWN,
    [RED]       = RED,
    [ORANGE]    = ORANGE,
    [YELLOW]    = YELLOW,
    [GREEN]     = GREEN,
    [BLUE]      = BLUE,
    [VIOLET]    = VIOLET,
    [GREY]      = GREY,
    [WHITE]     = WHITE,
};

static const int ppm[] = {
    [BLACK]     = 250,
    [BROWN]     = 100,  //? 10 PPM/°C
    [RED]       = 50,   //? 100 PPM/°C
    [ORANGE]    = 15,   //? 15 PPM/°C
    [YELLOW]    = 25,   //? 25 PPM/°C
    [GREEN]     = 20,    //? 20 PPM/°C
    [BLUE]      = 10,   //? 10 PPM/°C
    [VIOLET]    = 5,    //? 5 PPM/°C
    [GREY]      = 1,    //? 1 PPM/°C
};

static const double tolerance[] = {
    [BROWN]     = 1E0,    //? +/- 1%
    [RED]       = 2E0,    //? +/- 2%
    [ORANGE]    = 3E0,    //? +/- 3%
    [YELLOW]    = 4E0,    //? +/- 4%
    [GREEN]     = 5E-1,   //? +/- .5%
    [BLUE]      = 25E-2,  //? +/- .25%
    [VIOLET]    = 1E-1,   //? +/- .1%
    [GREY]      = 5E-2,   //? +/- .05%
    [GOLD]      = 5E0,    //? +/- 5%
    [SILVER]    = 1E1,    //? +/- 10%
};

static const double multiplier[] = {
    [BLACK]     = 1E0,  //? 1Ω
    [BROWN]     = 1E1,  //? 10Ω
    [RED]       = 1E2,  //? 100Ω
    [ORANGE]    = 1E3,  //? 1KΩ
    [YELLOW]    = 1E4,  //? 10KΩ
    [GREEN]     = 1E5,  //? 100KΩ
    [BLUE]      = 1E6,  //? 1MΩ
    [VIOLET]    = 1E7,  //? 10MΩ
    [GREY]      = 1E8,  //? 100MΩ
    [WHITE]     = 1E9,  //? 1GΩ
    [GOLD]      = 1E-1, //? 100mΩ
    [SILVER]    = 1E-2  //? 10mΩ
};

static const colormap_t ppm_map[] = {
    {"BLACK", BLACK},
    {"BROWN", BROWN},
    {"RED", RED},
    {"ORANGE", ORANGE},
    {"YELLOW", YELLOW},
    {"GREEN", GREEN},
    {"BLUE", BLUE},
    {"VIOLET", VIOLET},
    {"GRAY", GREY},
    {"GREY", GREY},  //? GREY? Alias for GRAY
};

static const colormap_t band_map[] = {
    {"BLACK", BLACK},
    {"BROWN", BROWN},
    {"RED", RED},
    {"ORANGE", ORANGE},
    {"YELLOW", YELLOW},
    {"GREEN", GREEN},
    {"BLUE", BLUE},
    {"VIOLET", VIOLET},
    {"GRAY", GREY},
    {"GREY", GREY},  //? GREY? Alias for GRAY
    {"WHITE", WHITE},
};

static const colormap_t tolerance_map[] = {
    {"BROWN", BROWN},
    {"RED", RED},
    {"ORANGE", ORANGE},
    {"YELLOW", YELLOW},
    {"GREEN", GREEN},
    {"BLUE", BLUE},
    {"VIOLET", VIOLET},
    {"GRAY", GREY},
    {"GREY", GREY},  //? GREY? Alias for GRAY
    {"GOLD", GOLD},
    {"SILVER", SILVER},
};

static const colormap_t multiplier_map[] = {
    {"BLACK", BLACK},
    {"BROWN", BROWN},
    {"RED", RED},
    {"ORANGE", ORANGE},
    {"YELLOW", YELLOW},
    {"GREEN", GREEN},
    {"BLUE", BLUE},
    {"VIOLET", VIOLET},
    {"GRAY", GREY},
    {"GREY", GREY},  //? GREY? Alias for GRAY
    {"WHITE", WHITE},
    {"GOLD", GOLD},
    {"SILVER", SILVER}
};

#define KILO                    1E3
#define MEGA                    1E6
#define GIGA                    1E9

#define PPM_MAP_SIZE            (sizeof(ppm_map) / sizeof(colormap_t))
#define BAND_MAP_SIZE           (sizeof(band_map) / sizeof(colormap_t))
#define TOLERANCE_MAP_SIZE      (sizeof(tolerance_map) / sizeof(colormap_t))
#define MULTIPLIER_MAP_SIZE     (sizeof(multiplier_map) / sizeof(colormap_t))

char *input(const char *);
char *format_with_suffix(double, double);

int    cgetch(void);
void   clr_scr(void);
int    get_band_number(void);

int    decode_ppm(char *);
int    decode_band(char *);
double decode_tolerance(char *);
double decode_multiplier(char *);

#endif // SRC_H