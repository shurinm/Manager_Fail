#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>

		WINDOW *okno_vin (int sy, int sx, int py, int px)
	{
		WINDOW *nwin;
		nwin = newwin(sy, sx, py, px);
		box(nwin, 0, 0);
		wrefresh(nwin);
		return nwin;
	}

void file_read( char *fname)
{
	FILE *fd;
	char ch;

	fd = fopen(fname, "r");
	if(!fd)
	{
		printf("Error open %s", fname);
		exit(1);
	}
	while ((ch = getc(fd)) != EOF)
		addch(ch);
	refresh();
}	

void mv_curs(int line, int col)
{
	move(line, col);
	refresh();
}
	
int main()
{
	int col = 0;
	int line = 0;
	int key = 0;
	WINDOW *win;
	WINDOW *win_active;
	
	win = initscr();
	noecho();
	keypad(stdscr, TRUE);	
	file_read("texteditor.c");
	move(0,0);
	refresh();
	win_active = okno_vin(30, 60, 5, 60);
	while((key = getch()) != 27)
	{	switch(key)
		{
			case KEY_UP:
				if(line > 0)
					mv_curs(--line, col);
			break;
			case KEY_DOWN:
				if(line < LINES)
					mv_curs(++line, col); 	
			break;
			case KEY_LEFT:
				if(col > 0)
					mv_curs(line, --col);
			break;
			case KEY_RIGHT:
				if(col < COLS)
					mv_curs(line, ++col);
			break;
			case KEY_BACKSPACE:
					delch();
			break;
			default:
				insch(key);
				if(col < COLS)
					col++;
				else
				{
					line++;
					col = 0;
				}
				mv_curs(line, col);
			break;
		}
		refresh();
	}

	endwin();
	return 0;
}
