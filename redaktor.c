#include<curses.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>

WINDOW *okno_vin (int sy, int sx, int py, int px)	//задание окна
{
	WINDOW *nwin;
	nwin = newwin(sy, sx, py, px);
	box(nwin, 0, 0);
	wrefresh(nwin);
	return nwin;
}




int main (int argc, char **argv)

{
	WINDOW *okno;

	initscr();	//инициализация структуры данных
	cbreak();
	curs_set (0);	//отключить курсор мыши
	noecho();
	start_color();	// цвет 
	init_pair (1, COLOR_CYAN, COLOR_BLUE);	//цвет фона + окна
	refresh();	//обновить экран


	okno = okno_vin(30, 60, 5, 60);


	getch();
	endwin();
	exit (EXIT_SUCCESS);

}
