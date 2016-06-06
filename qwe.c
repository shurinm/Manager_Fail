#include<curses.h>
#include<signal.h>
#include<stdlib.h>
#include<termios.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>   

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
	

void get_dir (char *dname, WINDOW *mywin)                            //vivod dirrectorii
{
	DIR *dir;
	struct dirent *entry;
	dir = opendir (dname);

	if (!dir)
	{
		endwin();
		perror ("diropen");
        	exit(1);
	}

	for (int i = 0; (entry = readdir(dir)) !=NULL; i++)
		mvwprintw (mywin, i, 0, "%s", entry->d_name);

	wrefresh(mywin);
	closedir(dir);
} 

void kursor ()

{
	
        
int main (int argc, char ** argv)

{
	WINDOW * win_l;
	WINDOW * win_bl;                            
	WINDOW * win_r;
	WINDOW * win_br;

	initscr ();                           //инициализация структуры данных
	cbreak();                             
	curs_set (0);                         //отключение курсора мыши
	refresh ();                           //обновить экран
	//Left window
	win_bl = create_box(22, 57, 2, 4);
	win_l = create_win(20, 55, 3, 5);
	get_dir(".", win_l);
	win_br = create_box(22, 57, 2, 59);
	win_r = create_win(20, 55, 3, 60);                              // vizov okno_2
	get_dir(".", win_r);


	getch ();
	endwin ();
	exit (EXIT_SUCCESS);
}        

