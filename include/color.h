#ifndef COLOR
#define COLOR

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#ifdef USE_COLOR
#define THEME ANSI_COLOR_RESET
#define EPOCHC ANSI_COLOR_GREEN
#define VARIABLE ANSI_COLOR_BLUE
#define INPUT ANSI_COLOR_CYAN
#define PERCEPTRONC ANSI_COLOR_MAGENTA
#define GREEN ANSI_COLOR_GREEN
#define RED ANSI_COLOR_RED
#define YELLOW ANSI_COLOR_YELLOW
#define BLUE ANSI_COLOR_BLUE
#define CLOSEC ANSI_COLOR_YELLOW
#define FARC RED
#else
#define THEME
#define EPOCHC
#define VARIABLE
#define INPUT
#define PERCEPTRONC
#define GREEN
#define RED
#define BLUE
#define YELLOW
#define CLOSEC
#define FARC
#endif

#endif
