#include "../../include/src.h"
#include "../../include/helpers.h"


/**
 * @brief Function to read input from user
 *
 * @param prompt Prompt to display on the terminal
 *
 * @returns A dynamically allocated string
 */
char *input(const char *prompt) {
    if (prompt) {
        fputs(prompt, stdout);
        fflush(stdout);
    }

    char *array = calloc(BUFSIZE, sizeof(char));
    if (NULL == array) {
        fprintf(stderr, "Error: Memory allocation to 'array' failed!...");
        return NULL;
    }

    memset(array, 0, BUFSIZE * sizeof(char));
    if (NULL != fgets(array, BUFSIZE, stdin)) {
        const size_t len = strlen(array);
        if (len > 1 && *(array + (len - 1)) == '\n') {
            *(array + (len - 1)) = '\0';
        }
        else {
            free(array);
            return NULL;
        }
    }
    return array;
}


/**
 * @brief Function to convert number to a formatted string with suffix
 *
 * @param num The number to be converted
 * @param tol The tolerance value
 *
 * @return A dynamically allocated string.
 */
char *format_with_suffix(const double num, const double tol) {
    const size_t SIZE = BUFSIZE / 2;
    char *result = calloc(SIZE, sizeof(char));
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



/**
 * @brief This is a custom printf function, prints bold, colored text to the terminal
 *
 * @param textStyle Style of the text to be printed
 * @param rgbColor Foreground & Background color of the text
 * @param fmt A pointer to the formated string to print to the user
 * @param ... Additional arguments
 */
void cprintf(const int textStyle, const RGBset_t *rgbColor, const char *fmt,...) {
    if (rgbColor != NULL) {
        set_console_color_attr(*rgbColor);
    }
    set_console_text_attr(textStyle);

    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);

    set_console_text_attr(RESET_ATTR);
    fflush(stdout);
}


/**
 * @brief This is a custom printf function
 *
 * @param fmt A pointer to the formated string to print to the user
 * @param ... Additional arguments
 */
void print(const char *fmt,...) {
    va_list args;

    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);

    fflush(stdout);
}


/**
 * @author Gavin A. S. Cheng
 * @see https://ascheng.medium.com/linux-getch-for-unix-c2c829721a30
 *
 * @brief This function is a custom getch function for linux
 *        The function is cited from a blog post on medium.com
 *        check the link above for reference.
 *
 * @returns the character that was read by the function
 */
int cgetch(void) {
    struct termios old_tio, new_tio;

    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    const int c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return c;
}