#ifndef COLORS_H_
#define COLORS_H_

#define CLS "\033[1;1H\033[J"

#define DEFAULT "\033[0m"
#define BOLD "\033[1m"
#define SEMI_BRIGHT "\033[2m"
#define UNDERSCORE "\033[4m"
#define FLASHING "\033[5m"
#define REVERSE "\033[7m"

#define SET_NORMAL_INTENSITY "\033[22m"
#define CANCEL_UNDERSCORE "\033[24m"
#define CANCEL_FLUSHING "\033[25m"
#define CANCEL_REVERSE "\033[27m"

#define BLACK_FG "\033[30m"
#define RED_FG "\033[31m"
#define GREEN_FG "\033[32m"
#define YELLOW_FG "\033[33m"
#define BLUE_FG "\033[34m"
#define PURPLE_FG "\033[35m"
#define AQUA_FG "\033[36m"
#define GRAY_FG "\033[37m"

#define BLACK_BG "\033[40m"
#define RED_BG "\033[41m"
#define GREEN_BG "\033[42m"
#define YELLOW_BG "\033[43m"
#define BLUE_BG "\033[44m"
#define PURPLE_BG "\033[45m"
#define AQUA_BG "\033[46m"
#define GRAY_BG "\033[47m"

void cls();
void print_red(const char *s);
void print_green(const char *s);
void print_flashing(const char *s);

#endif // COLORS_H_
