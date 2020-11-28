#include <ncurses.h>
#include "../core/core.h"
#include "controller.h"

static long from, to, size;
static const char *from_str, *to_str;
static int mode, dist;

void controller_initialize(void) {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    core_initialize((long*)&size);
    from = 0;
    core_idx_to_str(from, &from_str);
    to = 1;
    core_idx_to_str(to, &to_str);
    mvprintw(0, 0, "From:%35s", from_str);
    mvprintw(1, 0, "To:%37s", to_str);
    mvprintw(2, 0, "Criterium:%30s", "Cost");
    mode = 0;
    dist = 0;
    move(mode, 39);
}

void controller_finalize(void) {
    core_finalize();
    endwin();
}

char controller_handle(void) {
    int in = getch();
    char out = 1;
    double val;
    unsigned long steps, *path;
    int ret;
    switch (in) {
    case 'Q':
    case 'q':
        out = 0;
        break;
    case KEY_UP:
    case KEY_DOWN:
        mode = !mode;
        move(mode, 39);
        break;
    case KEY_LEFT:
        if (mode) {
            to = (((to - 1) % size) + size) % size;
            core_idx_to_str(to, &to_str);
            mvprintw(1, 0, "To:%37s", to_str);
        } else {
            from = (((from - 1) % size) + size) % size;
            core_idx_to_str(from, &from_str);
            mvprintw(0, 0, "From:%35s", from_str);
        }
        move(mode, 39);
        break;
    case KEY_RIGHT:
        if (mode) {
            to = (((to + 1) % size) + size) % size;
            core_idx_to_str(to, &to_str);
            mvprintw(1, 0, "To:%37s", to_str);
        } else {
            from = (((from + 1) % size) + size) % size;
            core_idx_to_str(from, &from_str);
            mvprintw(0, 0, "From:%35s", from_str);
        }
        move(mode, 39);
        break;
    case 'M':
    case 'm':
        dist = !dist;
        mvprintw(2, 0, "Criterium:%30s", dist ? "Distance" : "Cost");
        move(mode, 39);
        break;
    case ' ':
        ret = core_find_path(from, to, dist, &val, &steps, &path);
        clear();
        mvprintw(0, 0, "From:%35s", from_str);
        mvprintw(1, 0, "To:%37s", to_str);
        mvprintw(2, 0, "Criterium:%30s", dist ? "Distance" : "Cost");
        if (!ret) {
            mvprintw(4, 0, dist ? "Distance:%29.0lfkm" : "Cost:$%34.2lf", val);
            mvprintw(5, 0, "Path:");
            const char *buf;
            for (unsigned long i = 0, *iter = path; i < steps; ++i, ++iter) {
                core_idx_to_str(*iter, &buf);
                mvprintw(6 + i, 0, "%s", buf);
            }
            core_free_path(path);
        } else if (ret == -1) {
            mvprintw(4, 0, "%s", "No path");
        } else {
            mvprintw(4, 0, "%s", "Error");
        }
        move(mode, 39);
    }
    return out;
}
