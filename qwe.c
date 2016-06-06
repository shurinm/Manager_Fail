#include<curses.h>
#include<signal.h>
#include<stdlib.h>
#include<termios.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>   
#include <string.h>

WINDOW *create_box (int sy, int sx, int py, int px)                             //VIVOD OKNA
{
	WINDOW *nwin;
	nwin = newwin (sy, sx, py, px);
	refresh();
	box(nwin, 0, 0);
	wrefresh(nwin);
	return nwin;           
}
WINDOW *create_win (int sy, int sx, int py, int px)
{
	WINDOW *nwin;
	nwin = newwin (sy, sx, py, px);
	wrefresh(nwin);
	return nwin;
}	
	

int get_dir (char *dname, WINDOW *mywin, char data[128][128])                            //vivod dirrectorii
{
	int i;
	DIR *dir;
	struct dirent *entry;
	dir = opendir (dname);

	if (!dir)
	{
		endwin();
		perror ("diropen");
        	exit(1);
	}

	for (i = 0; (entry = readdir(dir)) !=NULL; i++)
	{
		mvwprintw (mywin, i, 0, "%s", entry->d_name);
		strcpy(data[i], entry->d_name);
	}

	wattron(mywin, COLOR_PAIR(1));
	mvwprintw(mywin, 0, 0, data[0]);
	wattroff(mywin, COLOR_PAIR(1));


	wrefresh(mywin);
	closedir(dir);
	return i;
} 

void ref_data(char data[128][128], unsigned count, unsigned select, WINDOW *win)
{
	for(int i = 0; i< count; i++)
		mvwprintw(win, i, 0, data[i]);

	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, select, 0, data[select]);
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
}	
        
int main (int argc, char ** argv)

{
	WINDOW * win_l;
	WINDOW * win_bl;                            
	WINDOW * win_r;
	WINDOW * win_br;
	char data[128][128];	
	unsigned count_l = 0;

	initscr ();                           //инициализация структуры данных
	cbreak();                             
	curs_set (0);                         //отключение курсора мыши
	noecho();
	keypad(stdscr, TRUE);		//ON special key
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLUE);
	refresh ();                           //обновить экран
		
//Left window
	win_bl = create_box(22, 57, 2, 4);
	win_l = create_win(20, 55, 3, 5);
	win_br = create_box(22, 57, 2, 59);
	win_r = create_win(20, 55, 3, 60);
                              // vizov okno_2
	count_l = get_dir(".", win_l, data);

	//NAVIGATOR
	int key = 0;
	unsigned pline = 0;		//Индекс с которого начинается вывод
	unsigned  cline = 0;		//Текущая строка в окне(которая выбрана)
	while((key = getch()) != 27)
	{
		switch(key)
		{
			case KEY_DOWN:
				if(cline < count_l - 1)
					cline++;
				ref_data(data, count_l, cline, win_l);
			break;
			case KEY_UP:
				if(cline > 0)	
					cline--;
				ref_data(data, count_l, cline, win_l);
			break;
			}

	}

	getch ();
	endwin ();
	exit (EXIT_SUCCESS);
}        

