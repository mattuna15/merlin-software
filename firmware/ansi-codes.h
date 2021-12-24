#ifndef _HEADER_ANSI
#define _HEADER_ANSI

#define _EXPAND_TO_STR(a)			#a
#define _EXPAND(a)					_EXPAND_TO_STR(a)

#define COLOR_DEFAULT_FG			C_LIGHTGREY
#define COLOR_DEFAULT_BG			C_DARKGREY
#define COLOR_RESET_FG				"\e[" _EXPAND(C_LIGHTGREY) "m"
#define COLOR_RESET_BG				"\e[" _EXPAND(C_DARKGREY) "m"

#define COLOR_FG(fg, txt)			"\e[" _EXPAND_TO_STR(fg) "m" txt COLOR_RESET_FG
#define COLOR_BG(bg, txt)			"\e[" _EXPAND(bg##_BG) "m" txt COLOR_RESET_BG
#define SET_COLOR_FG(fg)			"\e[" _EXPAND_TO_STR(fg) "m"
#define SET_COLOR_BG(bg)			"\e[" _EXPAND(bg##_BG)  "m"
#define COLOR_BG_FG(bg, fg, txt)	"\e[" _EXPAND(bg##_BG)  "m" "\e[" _EXPAND_TO_STR(fg) "m" txt COLOR_RESET_FG COLOR_RESET_BG
#define COLOR_FG_BG(fg, bg, txt)	"\e[" _EXPAND(bg##_BG)  "m" "\e[" _EXPAND_TO_STR(fg) "m" txt COLOR_RESET_FG COLOR_RESET_BG

#define C_BLACK			30
#define C_RED			31
#define C_GREEN			32
#define C_YELLOW		33
#define C_BLUE			34
#define C_MAGENTA		35
#define C_CYAN			36
#define C_LIGHTGREY		37
#define C_DARKGREY		90
#define C_LIGHTRED		91
#define C_LIGHTGREEN	92
#define C_LIGHTYELLOW	93
#define C_LIGHTBLUE		94
#define C_LIGHTPINK		95
#define C_LIGHTCYAN		96
#define C_WHITE			97

#define C_BLACK_BG			40
#define C_RED_BG			41
#define C_GREEN_BG			42
#define C_YELLOW_BG			43
#define C_BLUE_BG			44
#define C_MAGENTA_BG		45
#define C_CYAN_BG			46
#define C_LIGHTGREY_BG		47
#define C_DARKGREY_BG		100
#define C_LIGHTRED_BG		101
#define C_LIGHTGREEN_BG		102
#define C_LIGHTYELLOW_BG	103
#define C_LIGHTBLUE_BG		104
#define C_LIGHTPINK_BG		105
#define C_LIGHTCYAN_BG		106
#define C_WHITE_BG			107

//---------------------------------------------------
#endif