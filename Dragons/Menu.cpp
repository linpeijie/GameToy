/*compile and link: gcc <program file> -lmenu -lncurses -lncursesw*/
#include <ncurses.h>
#include <menu.h>
#include <locale.h>
#include <cstring>

const char *choices[] = {
    "New Game",
    "Load Game",
    "Options",
    "About",
    "Exit",
};

int main(int argc,char* argv[])
{
    setlocale(LC_ALL,"");
    ITEM **my_items;
    ITEM *cur_item;
    MENU *my_menu;

    int c, n_choices,i;

    initscr();
    cbreak();  //读取按键功能启动
    noecho();
    keypad(stdscr, TRUE);  //读取功能按键 激活
    
    /*分配内存空间*/
    n_choices = sizeof(choices) / sizeof(choices[0]);  //求菜单项
    my_items = new ITEM *[n_choices + 1];

    for(i = 0; i < n_choices; ++i)
    {
        my_items[i] = new_item(choices[i], "");
    }

    my_items[n_choices] = (ITEM*) NULL;

    my_menu = new_menu((ITEM **)my_items);
    
    /* set menu */
    set_menu_win(my_menu, stdscr);    //设置 menu 的主窗口
    set_menu_sub(my_menu, derwin(stdscr, 5, 10, (LINES - 5) / 2, (COLS - 10) / 2));    //设置 menu 的子窗口，以及子窗口在主窗口的位置
    set_menu_mark(my_menu, "");    // 设置 menu 前面的标记
    /* post menu */
    mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
	mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage (F1 to Exit)");
    post_menu(my_menu);
    refresh();

    /* 主循环体 */
    while ((c = getch()) != KEY_F(1))
    {
        char* cur_item_select = NULL;

        switch (c)
        {
        case KEY_DOWN:
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
        case 10: /* Enter */
		    move(0, 0);    // 移动光标
		    clrtoeol();
            cur_item_select = (char *)item_name(current_item(my_menu));
            mvprintw(0, 0, "Item selected is : %s", cur_item_select);
			pos_menu_cursor(my_menu);
			break;
        }

        /* 场景（窗口）切换, 功能实现 */
        if(cur_item_select and !strcmp(cur_item_select, "New Game"))
        {
            clear();    // 清空屏幕
            move(LINES / 2, COLS / 2);    // 移动光标
		    clrtoeol();
            mvprintw(LINES / 2, COLS / 2, "Test: %s", 
					cur_item_select);
        }else if (cur_item_select and !strcmp(cur_item_select, "Load Game"))
        {
            continue;
        }else if (cur_item_select and !strcmp(cur_item_select, "Options"))
        {
            continue;
        }else if (cur_item_select and !strcmp(cur_item_select, "About"))
        {
            clear();    // 清空屏幕
            move(LINES / 2, COLS / 2);    // 移动光标
		    clrtoeol();
            mvprintw(LINES / 2, COLS / 2, "林培捷");
        }else if(cur_item_select and !strcmp(cur_item_select, "Exit"))
        {
            break;
        }
    }
    
    /*释放内存*/
    unpost_menu(my_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(my_items[i]);
    free_menu(my_menu);
    delete [] my_items;
    endwin();
}