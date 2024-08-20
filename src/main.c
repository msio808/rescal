#include "../include/src.h"
#include "../include/helpers.h"


int main() {
    setup_signal_handler();

    res_t *resistor = calloc(2, sizeof(res_t));
    if (NULL == resistor) {
        fprintf(stderr, "[!] Error: Failed to allocate memory to 'resistor' struct!...\n");
        return EXIT_FAILURE;
    }

    const int num = get_band_number();

    short check = VALUE_ERROR;
    do {
        print_table();
        int mul = num > 4 ? 100 : 10;

        memset(resistor, 0, sizeof(res_t));

        resistor->bands.band_1 = decode_band(input("\n \t [?] Color of 1st band : "));
        if (resistor->bands.band_1 == (colors_t)INVALID_BAND_COLOR) continue;
        resistor->bands.band_1 *= mul;
        mul /= 10;

        resistor->bands.band_2 = decode_band(input(" \t [?] Color of 2nd band : "));
        if (resistor->bands.band_2 == (colors_t)INVALID_BAND_COLOR) continue;
        resistor->bands.band_2 *= mul;
        mul /= 10;

        if (num > MIN_BAND_COUNT) {
            resistor->bands.band_3 = decode_band(input(" \t [?] Color of 3rd band : "));
            if (resistor->bands.band_3 == (colors_t)INVALID_BAND_COLOR) continue;
            resistor->bands.band_3 *= mul;
        }

        resistor->multiplier = decode_multiplier(input("\n \t [?] Color of multiplier : "));
        if (resistor->multiplier == (double)INVALID_BAND_COLOR || resistor->multiplier == (double)VALUE_ERROR) continue;

        resistor->tolerance  = decode_tolerance(input(" \t [?] Color of tolerance : "));
        if (resistor->tolerance == (double)INVALID_BAND_COLOR) continue;

        if (num == MAX_BAND_COUNT) {
            resistor->ppm = decode_ppm(input(" \t [?] Color of TCR/PPM : "));
            if (resistor->ppm == (double)INVALID_BAND_COLOR) continue;
        }

        double value = resistor->bands.band_1 + resistor->bands.band_2 + resistor->bands.band_3;
        value *= resistor->multiplier;

        resistor->resistor_value = format_with_suffix(value, resistor->tolerance);

        cprintf(BOLD, NULL, "\n \t [$] RESISTOR VALUE : %s", resistor->resistor_value);
        if (num == 6) {
            cprintf(BOLD, NULL, " %iPPM/°C", resistor->ppm);
        }

        check = VALUE_SUCCESS;
    } while (check == VALUE_ERROR);

    free(resistor->resistor_value);
    free(resistor);

    print("\n\n");
    return EXIT_SUCCESS;
}


/**
 * @brief Function to get the total number of bands on a resistor
 *
 * @return The number of bands on the resistor
 */
int get_band_number(void) {
    int num;
    do {
        print_table();
        cprintf(BOLD, NULL, "\n \t \t <== RESISTOR COLOR CODE INTERPRETER ==>"
                    "\n\t [#] Resistor must have atleast 4 bands and atmost 6 bands!..."
                    "\n\t [#] NOTE: TCR = Temperature Coefficient Resistance (ppm/°C)!..."
                    "\n\t [+] Enter the number of bands : ");
        char *s = input(NULL);
        num = atoi(s);
        free(s);
    } while (num < MIN_BAND_COUNT || num > MAX_BAND_COUNT);
    return num;
}


/**
 * @brief Function to decode the BAND color of a given resistor
 *
 * @param bandColor Ths color of the band on the resistor
 * @return the BAND value of the color
 */
int decode_band(char *bandColor) {
    if (bandColor == NULL) {
        printf("\n\t [!] ERROR : Failed to read band color!...");
        cgetch();
        return INVALID_BAND_COLOR;
    }

    for (size_t i = 0; i < BAND_MAP_SIZE; ++i) {
        if (strcasecmp(bandColor, (band_map + i)->name) == 0) {
            free(bandColor);
            return *(band + (band_map + i)->color);
        }
    }
    free(bandColor);

    printf("\n\t [!] Please enter a valid band color!...");
    cgetch();
    return INVALID_BAND_COLOR;
}


/**
 * @brief Function to decode the PPM color of a given resistor
 *
 * @param bandColor Ths color of the band on the resistor
 * @return the PPM value of the color
 */
int decode_ppm(char *bandColor) {
    if (bandColor == NULL) {
        printf("\n\t [!] ERROR : Failed to read PPM color!...");
        cgetch();
        return INVALID_BAND_COLOR;
    }

    for (size_t i = 0; i < PPM_MAP_SIZE; ++i) {
        if (strcasecmp(bandColor, (ppm_map + i)->name) == 0) {
            free(bandColor);
            return *(ppm + (ppm_map + i)->color);
        }
    }
    free(bandColor);

    printf("\n\t [!] Please enter a valid PPM color!...");
    cgetch();
    return INVALID_BAND_COLOR;
}


/**
 * @brief Function to decode the TOLERANCE color of a given resistor
 *
 * @param bandColor Ths color of the band on the resistor
 * @return the TOLERANCE value of the color
 */
double decode_tolerance(char *bandColor) {
    if (bandColor == NULL) {
        printf("\n\t [!] ERROR : Failed to read TOLERANCE color!...");
        cgetch();
        return INVALID_BAND_COLOR;
    }

    for (size_t i = 0; i < TOLERANCE_MAP_SIZE; ++i) {
        if (strcasecmp(bandColor, (tolerance_map + i)->name) == 0) {
            free(bandColor);
            return *(tolerance + (tolerance_map + i)->color);
        }
    }
    free(bandColor);

    printf("\n\t [!] Please enter a valid TOLERANCE color!...");
    cgetch();
    return INVALID_BAND_COLOR;
}


/**
 * @brief Function to decode the MULTIPLIER color of a given resistor
 *
 * @param bandColor Ths color of the band on the resistor
 * @return the MULTIPLIER value of the color
 */
double decode_multiplier(char *bandColor) {
    if (bandColor == NULL) {
        printf("\n\t [!] ERROR : Failed to read MULTIPLIER color!...");
        cgetch();
        return INVALID_BAND_COLOR;
    }

    for (size_t i = 0; i < MULTIPLIER_MAP_SIZE; ++i) {
        if (strcasecmp(bandColor, (multiplier_map + i)->name) == 0) {
            free(bandColor);
            return *(multiplier + (multiplier_map + i)->color);
        }
    }
    free(bandColor);

    printf("\n\t [!] Please enter a valid MULTIPLIER color!...");
    cgetch();
    return INVALID_BAND_COLOR;
}
