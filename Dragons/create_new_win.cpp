#include <ncurses.h>

WINDOW* create_newwin(int height, int width, int starty, int startx)
{
    WINDOW* local_win = NULL;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);
    return local_win;
}

void move_win(WINDOW* local_win, int y, int x)
{
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // clear border for old win
    wrefresh(local_win);

    mvwin(local_win, y, x);
    box(local_win, 0, 0); // reset border
    wrefresh(local_win);
}

int main()
{
    WINDOW* my_win = NULL;
    int startx = 0, starty = 0, width = 10, height = 3;
    int ch = 0;
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;
    printw("Press F1 to exit");
    refresh();
    my_win = create_newwin(height, width, starty, startx);

    while ((ch = getch()) != KEY_F(1)) {
        switch(ch) {
            case KEY_LEFT:
                move_win(my_win, starty, --startx);
                break;
            case KEY_RIGHT:
                move_win(my_win, starty, ++startx);
                break;
            case KEY_UP:
                move_win(my_win, --starty, startx);
                break;
            case KEY_DOWN:
                move_win(my_win, ++starty, startx);
                break;
        }
    }

    if (my_win) {
        delwin(my_win);
    }
    endwin();
    return 0;
}