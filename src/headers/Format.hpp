#ifndef LAB3__COLOR
#define LAB3__COLOR

#include <ostream>
#include <sstream>
#include <cstdarg>
namespace Format {
    enum Code {
        // Formatting
        RESET           = 0,
        BOLD            = 1,
        UNDERLINED      = 4,
        INVERTED        = 7,
        BLINK           = 5,

        // Foreground Colors
        FG_DEFAULT      = 39,
        BLACK           = 30,
        RED             = 31,
        GREEN           = 32,
        YELLOW          = 33,
        BLUE            = 34,
        MAGENTA         = 35,
        CYAN            = 36,
        LIGHT_GRAY      = 37,
        DARK_GRAY       = 90,
        LIGHT_RED       = 91,
        LIGHT_GREEN     = 92,
        LIGHT_YELLOW    = 93,
        LIGHT_BLUE      = 94,
        LIGHT_MAGENTA   = 95,
        LIGHT_CYAN      = 96,
        WHITE           = 97,

        // Background Colors
        BG_DEFAULT         = 49,
        BG_BLACK           = 40,
        BG_RED             = 41,
        BG_GREEN           = 42,
        BG_YELLOW          = 43,
        BG_BLUE            = 44,
        BG_MAGENTA         = 45,
        BG_CYAN            = 46,
        BG_LIGHT_GRAY      = 47,
        BG_DARK_GRAY       = 100,
        BG_LIGHT_RED       = 101,
        BG_LIGHT_GREEN     = 102,
        BG_LIGHT_YELLOW    = 103,
        BG_LIGHT_BLUE      = 104,
        BG_LIGHT_MAGENTA   = 105,
        BG_LIGHT_CYAN      = 106,
        BG_WHITE           = 107,

    };

    std::ostream& operator<<(std::ostream& os, Code code);
}

#endif