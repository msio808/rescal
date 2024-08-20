#include "../../include/src.h"
#include "../../include/helpers.h"

/**
 * @brief Uses escape sequence '\033c', to reset the terminal to its initial state (ie: clear the terminal).
**/
void clr_scr(void) {
    print("\033c");
}


/**
 * @brief Sets the terminal foreground color to given rgb values
 *
 * @param color rgb color code of the foreground
 */
void set_fg_color(const RGB_t color) {
    print("\033[%i;%i;%hhu;%hhu;%hhum", FOREGROUND, BIT_MODE, color.red, color.green, color.blue);
}


/**
 * @brief Sets the terminal background color to given rgb values
 *
 * @param color rgb color code of the background
 */
void set_bg_color(const RGB_t color) {
    print("\033[%i;%i;%hhu;%hhu;%hhum", BACKGROUND, BIT_MODE, color.red, color.green, color.blue);
}


/**
 * @brief Sets the styles for the text on the terminal
 *
 * @param textStyle text mode/style
 */
void set_console_text_attr(const int textStyle) {
    switch (textStyle) {
        case DIM :
            print("\033[%im\033[%im", BOLD, DIM);
        break;

        case BOLD:
            print("\033[%im", BOLD);
        break;

        case INVERT :
            print("\033[%im\033[%im", BOLD, INVERT);
        break;
        case UNDERLINED :
            print("\033[%im\033[%im", BOLD, UNDERLINED);
            break;

        default :
            print("\033[%im", textStyle);
        break;
    }
}


/**
 * @brief Sets the terminal foreground & background color to the given set of RGB values
 *
 * @param colors : rgb color set of the foreground and background
 */
void set_console_color_attr(const RGBset_t colors) {
    set_fg_color(colors.foreground);
    set_bg_color(colors.background);
}


/**
 * @brief Prints the resistor color code table on the screen
 */
void print_table(void) {
    const RGBset_t colorSet[] = {
        {
            .foreground = {255, 255, 255},// White text
            .background = {0, 0, 0},      // Black cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {150, 75, 0}    // Brown cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {255, 0, 0}     // Red cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {255, 165, 0}   // Orange cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {255, 255, 0}   // Yellow cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {0, 255, 0}     // Green cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {0, 0, 255}     // Blue cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {128, 0, 128}   // Violet cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {128, 128, 128} // Grey cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {255, 255, 255} // White cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {255, 215, 0}   // Gold cell
        },
        {
            .foreground = {0, 0, 0},      // Black text
            .background = {192, 192, 192} // Silver cell
        }
    };

    clr_scr();
    cprintf(UNDERLINED, &colorSet[BLACK], "\n\t\t\t\t RESISTOR COLOR BAND TABLE \n\n");
    cprintf(BOLD, &colorSet[WHITE],  "\t COLORS ┃ 1st BAND  ┃ 2nd BAND  ┃ 3rd BAND  ┃ Multipier ┃ Tolerance ┃     TCR     \n");

    cprintf(BOLD, &colorSet[BLACK],  "\t BLACK        0           0           0         ×1Ω                   250 PPM/°C  \n");
    cprintf(BOLD, &colorSet[BROWN],  "\t BROWN  ┃     1     ┃     1     ┃     1     ┃   ×10Ω    ┃  ±1%%      ┃ 100 PPM/°C  \n");
    cprintf(BOLD, &colorSet[RED],    "\t  RED   ┃     2     ┃     2     ┃     2     ┃   ×100Ω   ┃  ±2%%      ┃  50 PPM/°C  \n");
    cprintf(BOLD, &colorSet[ORANGE], "\t ORANGE ┃     3     ┃     3     ┃     3     ┃   ×1KΩ    ┃  ±3%%      ┃  15 PPM/°C  \n");
    cprintf(BOLD, &colorSet[YELLOW], "\t YELLOW ┃     4     ┃     4     ┃     4     ┃   ×10KΩ   ┃  ±4%%      ┃  25 PPM/°C  \n");
    cprintf(BOLD, &colorSet[GREEN],  "\t GREEN  ┃     5     ┃     5     ┃     5     ┃   ×100KΩ  ┃  ±0.5%%    ┃  20 PPM/°C  \n");
    cprintf(BOLD, &colorSet[BLUE],   "\t  BLUE  ┃     6     ┃     6     ┃     6     ┃   ×1MΩ    ┃  ±0.25%%   ┃  10 PPM/°C  \n");
    cprintf(BOLD, &colorSet[VIOLET], "\t VIOLET ┃     7     ┃     7     ┃     7     ┃   ×10MΩ   ┃  ±0.1%%    ┃   5 PPM/°C  \n");
    cprintf(BOLD, &colorSet[GREY],   "\t  GREY  ┃     8     ┃     8     ┃     8     ┃   ×100MΩ  ┃  ±0.05%%   ┃   1 PPM/°C  \n");
    cprintf(BOLD, &colorSet[WHITE],  "\t WHITE  ┃     9     ┃     9     ┃     9     ┃   ×1GΩ    ┃           ┃             \n");
    cprintf(BOLD, &colorSet[GOLD],   "\t  GOLD  ┃           ┃           ┃           ┃   ×0.1Ω   ┃  ±5%%      ┃             \n");
    cprintf(BOLD, &colorSet[SILVER], "\t SILVER ┃           ┃           ┃           ┃   ×0.01Ω  ┃  ±10%%     ┃             \n");
}


/**
 * @brief Handles the SIGSEGV/SIGINT signal (caused by pressing CTRL+C).
 *        Resets terminal attributes to default when SIGINT/SIGSEGV is received.
 * @param signal signal captured
 */
void signal_handler(const int signal) {
    if (signal == SIGINT) {
        clr_scr();
        print("\n\t [!] ERROR : Program Abruptly terminated.\n\n");
        exit(EXIT_FAILURE);
    }

    if (signal == SIGSEGV) {
        clr_scr();
        void *array[BUFSIZE];
        const size_t size = backtrace(array, BUFSIZE);

        print("\n\t SIGNAL %i (Segmentation fault) received.", signal);
        print("\n\t SEE the logfile at [%s] for more details.\n\n", ERROR_LOGPATH);

        const int fd = open(ERROR_LOGPATH, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == VALUE_ERROR) {
            print("\n\t Error opening log file\n\n");
            exit(EXIT_FAILURE);
        }

        dprintf(fd, "Error : signal %d (Segmentation fault) received.\n\n", signal);
        backtrace_symbols_fd(array, size, fd);
        close(fd);
        exit(EXIT_FAILURE);
    }
}


/**
 * @brief Set's up and calls the 'signal_handler' function which listens for 'SIGINT/SIGSEGV'
 */
void setup_signal_handler(void) {
    if (signal(SIGINT, signal_handler) == SIG_ERR || signal(SIGSEGV, signal_handler) == SIG_ERR) {
        print("\n\t Error setting up signal handler\n\n");
        exit(EXIT_FAILURE);
    }
}
