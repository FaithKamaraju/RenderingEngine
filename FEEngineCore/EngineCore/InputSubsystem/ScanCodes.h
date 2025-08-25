#pragma once


typedef enum FE_Scancode
{
    FE_SCANCODE_UNKNOWN = 0,

    FE_SCANCODE_A = 4,
    FE_SCANCODE_B = 5,
    FE_SCANCODE_C = 6,
    FE_SCANCODE_D = 7,
    FE_SCANCODE_E = 8,
    FE_SCANCODE_F = 9,
    FE_SCANCODE_G = 10,
    FE_SCANCODE_H = 11,
    FE_SCANCODE_I = 12,
    FE_SCANCODE_J = 13,
    FE_SCANCODE_K = 14,
    FE_SCANCODE_L = 15,
    FE_SCANCODE_M = 16,
    FE_SCANCODE_N = 17,
    FE_SCANCODE_O = 18,
    FE_SCANCODE_P = 19,
    FE_SCANCODE_Q = 20,
    FE_SCANCODE_R = 21,
    FE_SCANCODE_S = 22,
    FE_SCANCODE_T = 23,
    FE_SCANCODE_U = 24,
    FE_SCANCODE_V = 25,
    FE_SCANCODE_W = 26,
    FE_SCANCODE_X = 27,
    FE_SCANCODE_Y = 28,
    FE_SCANCODE_Z = 29,
    FE_SCANCODE_1 = 30,
    FE_SCANCODE_2 = 31,
    FE_SCANCODE_3 = 32,
    FE_SCANCODE_4 = 33,
    FE_SCANCODE_5 = 34,
    FE_SCANCODE_6 = 35,
    FE_SCANCODE_7 = 36,
    FE_SCANCODE_8 = 37,
    FE_SCANCODE_9 = 38,
    FE_SCANCODE_0 = 39,
    FE_SCANCODE_RETURN = 40,
    FE_SCANCODE_ESCAPE = 41,
    FE_SCANCODE_BACKSPACE = 42,
    FE_SCANCODE_TAB = 43,
    FE_SCANCODE_SPACE = 44,
    FE_SCANCODE_MINUS = 45,
    FE_SCANCODE_EQUALS = 46,
    FE_SCANCODE_LEFTBRACKET = 47,
    FE_SCANCODE_RIGHTBRACKET = 48,
    FE_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    FE_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate SDL_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    FE_SCANCODE_SEMICOLON = 51,
    FE_SCANCODE_APOSTROPHE = 52,
    FE_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    FE_SCANCODE_COMMA = 54,
    FE_SCANCODE_PERIOD = 55,
    FE_SCANCODE_SLASH = 56,
    FE_SCANCODE_CAPSLOCK = 57,
    FE_SCANCODE_F1 = 58,
    FE_SCANCODE_F2 = 59,
    FE_SCANCODE_F3 = 60,
    FE_SCANCODE_F4 = 61,
    FE_SCANCODE_F5 = 62,
    FE_SCANCODE_F6 = 63,
    FE_SCANCODE_F7 = 64,
    FE_SCANCODE_F8 = 65,
    FE_SCANCODE_F9 = 66,
    FE_SCANCODE_F10 = 67,
    FE_SCANCODE_F11 = 68,
    FE_SCANCODE_F12 = 69,
    FE_SCANCODE_PRINTSCREEN = 70,
    FE_SCANCODE_SCROLLLOCK = 71,
    FE_SCANCODE_PAUSE = 72,
    FE_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but does send code 73, not 117) */
    FE_SCANCODE_HOME = 74,
    FE_SCANCODE_PAGEUP = 75,
    FE_SCANCODE_DELETE = 76,
    FE_SCANCODE_END = 77,
    FE_SCANCODE_PAGEDOWN = 78,
    FE_SCANCODE_RIGHT = 79,
    FE_SCANCODE_LEFT = 80,
    FE_SCANCODE_DOWN = 81,
    FE_SCANCODE_UP = 82,
    FE_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards */
    FE_SCANCODE_KP_DIVIDE = 84,
    FE_SCANCODE_KP_MULTIPLY = 85,
    FE_SCANCODE_KP_MINUS = 86,
    FE_SCANCODE_KP_PLUS = 87,
    FE_SCANCODE_KP_ENTER = 88,
    FE_SCANCODE_KP_1 = 89,
    FE_SCANCODE_KP_2 = 90,
    FE_SCANCODE_KP_3 = 91,
    FE_SCANCODE_KP_4 = 92,
    FE_SCANCODE_KP_5 = 93,
    FE_SCANCODE_KP_6 = 94,
    FE_SCANCODE_KP_7 = 95,
    FE_SCANCODE_KP_8 = 96,
    FE_SCANCODE_KP_9 = 97,
    FE_SCANCODE_KP_0 = 98,
    FE_SCANCODE_KP_PERIOD = 99,
    FE_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Z.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    FE_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
    FE_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    FE_SCANCODE_KP_EQUALS = 103,
    FE_SCANCODE_F13 = 104,
    FE_SCANCODE_F14 = 105,
    FE_SCANCODE_F15 = 106,
    FE_SCANCODE_F16 = 107,
    FE_SCANCODE_F17 = 108,
    FE_SCANCODE_F18 = 109,
    FE_SCANCODE_F19 = 110,
    FE_SCANCODE_F20 = 111,
    FE_SCANCODE_F21 = 112,
    FE_SCANCODE_F22 = 113,
    FE_SCANCODE_F23 = 114,
    FE_SCANCODE_F24 = 115,
    FE_SCANCODE_EXECUTE = 116,
    FE_SCANCODE_HELP = 117,    /**< AL Integrated Help Center */
    FE_SCANCODE_MENU = 118,    /**< Menu (show menu) */
    FE_SCANCODE_SELECT = 119,
    FE_SCANCODE_STOP = 120,    /**< AC Stop */
    FE_SCANCODE_AGAIN = 121,   /**< AC Redo/Repeat */
    FE_SCANCODE_UNDO = 122,    /**< AC Undo */
    FE_SCANCODE_CUT = 123,     /**< AC Cut */
    FE_SCANCODE_COPY = 124,    /**< AC Copy */
    FE_SCANCODE_PASTE = 125,   /**< AC Paste */
    FE_SCANCODE_FIND = 126,    /**< AC Find */
    FE_SCANCODE_MUTE = 127,
    FE_SCANCODE_VOLUMEUP = 128,
    FE_SCANCODE_VOLUMEDOWN = 129,
    /* not sure whether there's a reason to enable these */
    /*     SDL_SCANCODE_LOCKINGCAPSLOCK = 130,  */
    /*     SDL_SCANCODE_LOCKINGNUMLOCK = 131, */
    /*     SDL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    FE_SCANCODE_KP_COMMA = 133,
    FE_SCANCODE_KP_EQUALSAS400 = 134,
    FE_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see footnotes in USB doc */
    FE_SCANCODE_INTERNATIONAL2 = 136,
    FE_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
    FE_SCANCODE_INTERNATIONAL4 = 138,
    FE_SCANCODE_INTERNATIONAL5 = 139,
    FE_SCANCODE_INTERNATIONAL6 = 140,
    FE_SCANCODE_INTERNATIONAL7 = 141,
    FE_SCANCODE_INTERNATIONAL8 = 142,
    FE_SCANCODE_INTERNATIONAL9 = 143,
    FE_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
    FE_SCANCODE_LANG2 = 145, /**< Hanja conversion */
    FE_SCANCODE_LANG3 = 146, /**< Katakana */
    FE_SCANCODE_LANG4 = 147, /**< Hiragana */
    FE_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    FE_SCANCODE_LANG6 = 149, /**< reserved */
    FE_SCANCODE_LANG7 = 150, /**< reserved */
    FE_SCANCODE_LANG8 = 151, /**< reserved */
    FE_SCANCODE_LANG9 = 152, /**< reserved */
    FE_SCANCODE_ALTERASE = 153,    /**< Erase-Eaze */
    FE_SCANCODE_SYSREQ = 154,
    FE_SCANCODE_CANCEL = 155,      /**< AC Cancel */
    FE_SCANCODE_CLEAR = 156,
    FE_SCANCODE_PRIOR = 157,
    FE_SCANCODE_RETURN2 = 158,
    FE_SCANCODE_SEPARATOR = 159,
    FE_SCANCODE_OUT = 160,
    FE_SCANCODE_OPER = 161,
    FE_SCANCODE_CLEARAGAIN = 162,
    FE_SCANCODE_CRSEL = 163,
    FE_SCANCODE_EXSEL = 164,
    FE_SCANCODE_KP_00 = 176,
    FE_SCANCODE_KP_000 = 177,
    FE_SCANCODE_THOUSANDSSEPARATOR = 178,
    FE_SCANCODE_DECIMALSEPARATOR = 179,
    FE_SCANCODE_CURRENCYUNIT = 180,
    FE_SCANCODE_CURRENCYSUBUNIT = 181,
    FE_SCANCODE_KP_LEFTPAREN = 182,
    FE_SCANCODE_KP_RIGHTPAREN = 183,
    FE_SCANCODE_KP_LEFTBRACE = 184,
    FE_SCANCODE_KP_RIGHTBRACE = 185,
    FE_SCANCODE_KP_TAB = 186,
    FE_SCANCODE_KP_BACKSPACE = 187,
    FE_SCANCODE_KP_A = 188,
    FE_SCANCODE_KP_B = 189,
    FE_SCANCODE_KP_C = 190,
    FE_SCANCODE_KP_D = 191,
    FE_SCANCODE_KP_E = 192,
    FE_SCANCODE_KP_F = 193,
    FE_SCANCODE_KP_XOR = 194,
    FE_SCANCODE_KP_POWER = 195,
    FE_SCANCODE_KP_PERCENT = 196,
    FE_SCANCODE_KP_LESS = 197,
    FE_SCANCODE_KP_GREATER = 198,
    FE_SCANCODE_KP_AMPERSAND = 199,
    FE_SCANCODE_KP_DBLAMPERSAND = 200,
    FE_SCANCODE_KP_VERTICALBAR = 201,
    FE_SCANCODE_KP_DBLVERTICALBAR = 202,
    FE_SCANCODE_KP_COLON = 203,
    FE_SCANCODE_KP_HASH = 204,
    FE_SCANCODE_KP_SPACE = 205,
    FE_SCANCODE_KP_AT = 206,
    FE_SCANCODE_KP_EXCLAM = 207,
    FE_SCANCODE_KP_MEMSTORE = 208,
    FE_SCANCODE_KP_MEMRECALL = 209,
    FE_SCANCODE_KP_MEMCLEAR = 210,
    FE_SCANCODE_KP_MEMADD = 211,
    FE_SCANCODE_KP_MEMSUBTRACT = 212,
    FE_SCANCODE_KP_MEMMULTIPLY = 213,
    FE_SCANCODE_KP_MEMDIVIDE = 214,
    FE_SCANCODE_KP_PLUSMINUS = 215,
    FE_SCANCODE_KP_CLEAR = 216,
    FE_SCANCODE_KP_CLEARENTRY = 217,
    FE_SCANCODE_KP_BINARY = 218,
    FE_SCANCODE_KP_OCTAL = 219,
    FE_SCANCODE_KP_DECIMAL = 220,
    FE_SCANCODE_KP_HEXADECIMAL = 221,
    FE_SCANCODE_LCTRL = 224,
    FE_SCANCODE_LSHIFT = 225,
    FE_SCANCODE_LALT = 226, /**< alt, option */
    FE_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    FE_SCANCODE_RCTRL = 228,
    FE_SCANCODE_RSHIFT = 229,
    FE_SCANCODE_RALT = 230, /**< alt gr, option */
    FE_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */
    FE_SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special SDL_KMOD_MODE for it I'm adding it here
                                 */

                                 /* @} *//* Usage page 0x07 */

                                 /**
                                  *  \name Usage page 0x0C
                                  *
                                  *  These values are mapped from usage page 0x0C (USB consumer page).
                                  *
                                  *  There are way more keys in the spec than we can represent in the
                                  *  current scancode range, so pick the ones that commonly come up in
                                  *  real world usage.
                                  */
                                  /* @{ */

    FE_SCANCODE_SLEEP = 258,                   /**< Sleep */
    FE_SCANCODE_WAKE = 259,                    /**< Wake */
    FE_SCANCODE_CHANNEL_INCREMENT = 260,       /**< Channel Increment */
    FE_SCANCODE_CHANNEL_DECREMENT = 261,       /**< Channel Decrement */
    FE_SCANCODE_MEDIA_PLAY = 262,          /**< Play */
    FE_SCANCODE_MEDIA_PAUSE = 263,         /**< Pause */
    FE_SCANCODE_MEDIA_RECORD = 264,        /**< Record */
    FE_SCANCODE_MEDIA_FAST_FORWARD = 265,  /**< Fast Forward */
    FE_SCANCODE_MEDIA_REWIND = 266,        /**< Rewind */
    FE_SCANCODE_MEDIA_NEXT_TRACK = 267,    /**< Next Track */
    FE_SCANCODE_MEDIA_PREVIOUS_TRACK = 268, /**< Previous Track */
    FE_SCANCODE_MEDIA_STOP = 269,          /**< Stop */
    FE_SCANCODE_MEDIA_EJECT = 270,         /**< Eject */
    FE_SCANCODE_MEDIA_PLAY_PAUSE = 271,    /**< Play / Pause */
    FE_SCANCODE_MEDIA_SELECT = 272,        /* Media Select */
    FE_SCANCODE_AC_NEW = 273,              /**< AC New */
    FE_SCANCODE_AC_OPEN = 274,             /**< AC Open */
    FE_SCANCODE_AC_CLOSE = 275,            /**< AC Close */
    FE_SCANCODE_AC_EXIT = 276,             /**< AC Exit */
    FE_SCANCODE_AC_SAVE = 277,             /**< AC Save */
    FE_SCANCODE_AC_PRINT = 278,            /**< AC Print */
    FE_SCANCODE_AC_PROPERTIES = 279,       /**< AC Properties */
    FE_SCANCODE_AC_SEARCH = 280,           /**< AC Search */
    FE_SCANCODE_AC_HOME = 281,             /**< AC Home */
    FE_SCANCODE_AC_BACK = 282,             /**< AC Back */
    FE_SCANCODE_AC_FORWARD = 283,          /**< AC Forward */
    FE_SCANCODE_AC_STOP = 284,             /**< AC Stop */
    FE_SCANCODE_AC_REFRESH = 285,          /**< AC Refresh */
    FE_SCANCODE_AC_BOOKMARKS = 286,        /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */


    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
     /* @{ */

    FE_SCANCODE_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    FE_SCANCODE_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    FE_SCANCODE_CALL = 289, /**< Used for accepting phone calls. */
    FE_SCANCODE_ENDCALL = 290, /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */

    FE_SCANCODE_RESERVED = 400,    /**< 400-500 reserved for dynamic keycodes */
    FE_SCANCODE_COUNT = 512 /**< not a key, just marks the number of scancodes for array bounds */

} FE_Scancode;