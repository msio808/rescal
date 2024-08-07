#include "src.h"

int main() {
    int num = get_band_number();

    res_t *resistor = (res_t *)calloc(sizeof(res_t), 2);
    if (NULL == resistor) {
        fprintf(stderr, "[!] Error: Failed to allocate memory to 'resistor' struct!...\n");
        return EXIT_FAILURE;
    }

    int mul = (num > 4 ? 100 : 10);

    resistor->bands.band_1 = decode_band(
            get_band_color("\n\t[?] Color of 1st band : "));
    resistor->bands.band_1 *= mul;
    mul /= 10;

    resistor->bands.band_2 = decode_band(
            get_band_color("\t[?] Color of 2nd band : "));
    resistor->bands.band_2 *= mul;
    mul /= 10;

    if (num > 4) {
        resistor->bands.band_3 = decode_band(
                get_band_color("\t[?] Color of 3rd band : "));
        resistor->bands.band_3 *= mul;
        mul /=10;
    }

    resistor->multiplier = get_multiplier_value(
            decode_multiplier(input("\n\t[?] Color of multiplier : ")));
    
    resistor->tolerance  = get_tolerance_value(
            decode_tolerance(input("\t[?] Color of tolerance : ")));

    if (num == 6)
        resistor->ppm = get_ppm_value(decode_ppm(input("\t[?] Color of TCR : ")));

    double value = (resistor->bands.band_1 + resistor->bands.band_2 + resistor->bands.band_3);
    value *= resistor->multiplier;

    resistor->resistor_value = format_with_suffix(value, resistor->tolerance);

    printf("\n\t[$] RESISTOR VALUE : %s", resistor->resistor_value);
    if (num == 6)
        printf(" %iPPM/°C", resistor->ppm);
    printf("\n\n");

    free(resistor->resistor_value);
    free(resistor);

    return EXIT_SUCCESS;
}

int get_ppm_value(colors_t color) {
    return *(ppm + color);
}
double get_tolerance_value(colors_t color) {
    return *(tolerance + color);
}
double get_multiplier_value(colors_t color) {
    return *(multipliers + color);
}

int get_band_number(void) {
    int num;
    do {
        clr_scr();
        char *s = input("\t\t <== RESISTOR COLOR CODE INTERPRETER ==>\n"
                    "\t[#] Resistor must have atleast 4 bands and atmost 6 bands!...\n"
                    "\t[#] NOTE: TCR = Temperature Coefficient Resistance (ppm/°C)!...\n"
                    "\t[+] Enter the number of bands : ");
        num = atoi(s);
        free(s);
    } while (num < MIN_BAND_COUNT || num > MAX_BAND_COUNT);
    return num;
}

char *get_band_color(const char *prompt) {
    int flag = -1;
    char *color;
    do {
        color = input(prompt);
        for (size_t i = 0; i < MULTIPLIER_MAP_SIZE; ++i) {
            if (strcasecmp(color, (multiplier_map + i)->name) == 0) {
                flag = 0;
                break;
            }
        }
        if (-1 == flag) {
            fprintf(stderr, "\t[!] Error: Enter a valid color!...\n");
            free(color);
            cgetch();
        }
        
    } while (flag == -1);
    return color;
}

int decode_ppm(char *color) {
    for (size_t i = 0; i < PPM_MAP_SIZE; ++i) {
        if (strcasecmp(color, (ppm_map + i)->name) == 0) {
            int val = (ppm_map + i)->color;
            free(color);
            return val;
        }
    }
    free(color);
    return -1;  //* Color not found
}

int decode_band(char *color) {
    for (size_t i = 0; i < BAND_MAP_SIZE; ++i) {
        if (strcasecmp(color, (band_map + i)->name) == 0) {
            int val = (band_map + i)->color;
            free(color);
            return val;
        }
    }
    free(color);
    return -1;  //* Color not found
}

double decode_tolerance(char *color) {
    for (size_t i = 0; i < TOLERANCE_MAP_SIZE; ++i) {
        if (strcasecmp(color, (tolerance_map + i)->name) == 0) {
            double val = (tolerance_map + i)->color;
            free(color);
            return val;
        }
    }
    free(color);
    return NO_BAND;  //* Color not found
}

double decode_multiplier(char *color) {
    for (size_t i = 0; i < MULTIPLIER_MAP_SIZE; ++i) {
        if (strcasecmp(color, (multiplier_map + i)->name) == 0) {
            free(color);
            return (multiplier_map + i)->color;
        }
    }
    free(color);
    return -1.0;  //* Color not found
}

char *input(const char *prompt) {
    if (prompt) {
        fputs(prompt, stdout);
        fflush(stdout);
    }

    char *array = (char *) calloc(BUFSIZE, sizeof(char));
    if (NULL == array) {
        fprintf(stderr, "Error: Memory allocation to 'array' failed!...");
        return NULL;
    }
    
    memset(array, 0, BUFSIZE * sizeof(char));
    if (NULL != fgets(array, BUFSIZE, stdin)) {
        size_t len = strlen(array);
        if ((len > 1) && *(array + (len - 1)) == '\n') {
            *(array + (len - 1)) = '\0'; //* Remove trailing newline character, if present
            len -= 1;
        }
        else {
            free(array);
            return NULL;
        }
    }
    return array; //* Return dynamically allocated string
}

// TODO : Function to convert number to a formatted string with suffix
char *format_with_suffix(double num, double tol) {
    size_t SIZE = BUFSIZE / 2;
    //* Allocate memory the resulting string
    char *result = (char *)calloc(SIZE, sizeof(char));
    if (NULL == result) {
        fprintf(stderr, "Error: Memory Allocation Failed!...\n");
        return NULL;
    }

    if (num >= GIGA)
        snprintf(result, SIZE, "%.2fGΩhms ±%.2f%%", num / GIGA, tol);
    else if (num >= MEGA)
        snprintf(result, SIZE, "%.2fMΩhms ±%.2f%%", num / MEGA, tol);
    else if (num >= KILO)
        
        snprintf(result, SIZE, "%.2fKΩhms ±%.2f%%", num / KILO, tol);
    else
        snprintf(result, SIZE, "%.2fΩhms ±%.2f%%", num, tol);

    return result;
}


void clr_scr(void) {
    printf("\033c");
}

/* 
    TODO : getch function for unix system.
?   Gets a character from the user without echoing to the terminal.
*/
int cgetch(void) {
    struct termios old_tio, new_tio;
    int c;

    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return c;
}