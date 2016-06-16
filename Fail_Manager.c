#include<curses.h>
#include<signal.h>
#include<stdlib.h>
#include<termios.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include <sys/stat.h>
#include<dirent.h>
#include<stdio.h>   
#include <string.h>
#include<unistd.h>
#include <string.h>

#define LEFT    0
#define RIGHT   1
#define BLEFT   2
#define BRIGHT  3

int get_content (char *dname, char content[512][128])                            //vivod dirrectorii
{
	DIR *dir;
	struct dirent *dinfo;
	unsigned count = 0;
	
	//Открываем директорию
	dir = opendir (dname);
	if (!dir)
		return -1;

	//Считываем содержимое директории
	for (; (dinfo = readdir(dir)) !=NULL; count++)
		strcpy(content[count], dinfo->d_name);
	content[count][0] = '\0';

	closedir(dir);
	return count;
} 

//Функция обновляет все окна
void refresh_manager(WINDOW **win, char content[2][512][128], unsigned active, unsigned print, unsigned select)
{
	unsigned p;

	//Очистка экрана
	for(int i = 0; i < 4; i++)
		wclear(win[i]);
	
	//Вывод рамок
	box(win[BLEFT], 0, 0);
	box(win[BRIGHT],0 ,0);
	//refresh();

	//Вывод содержимого директорий
	for(int i = 0; i < 2; i++)
	{	
		if(i == active)
			p = print;
		else p = 0;
		for(int j = 0; content[i][p][0] != '\0'; p++, j++)
			mvwprintw(win[i], j, 3, content[i][p]);
	}
	mvwprintw(win[active], select, 0, " > ");

	//Обновление окон
	for(int i = 3; i >= 0; i--)
		wrefresh(win[i]);
}

//Функция инициализирует графику и все переменные
void init_manager(WINDOW ***win, char content[2][512][128], unsigned count[2], char patch[2][512], unsigned *active, unsigned *print, unsigned *select)
{
	//Инициализация графики
	initscr();
	cbreak();
	curs_set(0);
	noecho();
	keypad(stdscr, TRUE);
	
	//Выделение памяти
	(*win) = malloc(4 * sizeof(WINDOW *));
	
	//Инициализации переменных
	(*active) = LEFT;
	(*print) = 0;
	(*select) = 0;
	getcwd(patch[LEFT], 512);
	getcwd(patch[RIGHT], 512);
	count[LEFT] = get_content(patch[LEFT], content[LEFT]);
	count[RIGHT] = get_content(patch[RIGHT], content[RIGHT]);
	(*win)[BLEFT] = newwin(LINES, COLS / 2, 0, 0);
	(*win)[BRIGHT] = newwin(LINES, COLS / 2, 0, COLS / 2);
	(*win)[LEFT] = newwin(LINES - 2, (COLS / 2) - 2, 1, 1);
	(*win)[RIGHT] = newwin(LINES - 2, (COLS / 2) - 2, 1, (COLS / 2) + 1);
	
	refresh();
}

void open_dir(char* name, char patch[2][512], char content[512][128], unsigned *count, unsigned active)
{
	struct stat info;
	
	stat(name, &info);
	if(info.st_mode == 16877)
	{
		chdir(name);
		getcwd(patch[active], 512);
		(*count) = get_content(patch[active], content);
	}
}

//Функция отключает графику
void destroy_manager()
{
	endwin();
}

int main ()
{
	WINDOW **win;			//Окна
	char content[2][512][128];	//Содержимое окон
	char patch[2][512];		//Директории в которых мы находимся
	unsigned count[2];
	unsigned active;		//Индекс активного окна
	unsigned print;
	unsigned select;
	int key = 0;

	init_manager(&win, content, count, patch, &active, &print, &select);
	refresh_manager(win, content, active, print, select);
		
	while((key = getch()) != 27)
	{
		switch(key)
		{
			case KEY_DOWN:
				if(print + select >= count[active] - 1)
					continue;
				if(select >= LINES - 3)
					print++;
				else
					select++;
			break;
			case KEY_UP:
				if(print <= 0 && select <= 0)
					continue;
				if(select <= 0)
					print--;
				else
					select--;
			break;
			case KEY_LEFT:
				if(active == LEFT)
					continue;
				active = LEFT;
				print = 0;
				select = 0;
				chdir(patch[active]);
			break;
			case KEY_RIGHT:
				if(active == RIGHT)
					continue;
				active = RIGHT;
				print = 0;
				select = 0;
				chdir(patch[active]);
			break;
			case '\n':
				open_dir(content[active][select + print], patch, content[active], &(count[active]), active);
				print = 0;
				select = 0;
			break;
		}
		refresh_manager(win, content, active, print, select);
	}
	destroy_manager();
}
/*	
	data_current = data_l = malloc(sizeof(char*) * 512);
	data_r = malloc(sizeof(char*) * 512);
	
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
	win_active = win_l = create_win(20, 55, 3, 5);
	win_br = create_box(22, 57, 2, 59);
	win_r = create_win(20, 55, 3, 60);                              // vizov okno_2
	count_active = count_l = get_dir("..", win_l, data_l);
	count_r = get_dir(".", win_r, data_r);

	//NAVIGATOR
	int key = 0;
	unsigned pline = 0;		//Индекс с которого начинается вывод
	unsigned  cline = 0;		//Текущая строка в окне(которая выбрана)

	ref_data(data_l, count_l, 0, win_l);
	ref_data(data_r, count_r, -1, win_r);
	while((key = getch()) != 27)
	{
		switch(key)
		{
			case KEY_DOWN:
				if(cline < count_active - 1)
					cline++;
				ref_data(data_current, count_active, cline, win_active);
			break;
			case KEY_UP:
				if(cline > 0)	
					cline--;
				ref_data(data_current, count_active, cline, win_active);
			break;
			case KEY_LEFT:
				win_active = win_l;
				count_active = count_l;
				cline = 0;
				data_current = data_l;
				ref_data(data_r, count_r, -1, win_r);
				ref_data(data_l, count_l, cline, win_l);
			break;
			case KEY_RIGHT: 
				win_active = win_r;
				count_active = count_r;
				cline = 0;
				data_current = data_r;
				ref_data(data_l, count_l, -1, win_l);
				ref_data(data_r, count_r, cline, win_r);
			break;
			case 	'\n':
				if(win_active == win_l)
				{
					//chdir(data_l[cline]);
					count_l = get_dir(data_l[cline], win_l, data_l);
					count_active = count_l;
					data_current = data_l;
					
				}				
			break;
			case KEY_F(4):
				execl("/home/2016/shurin/File_Manager/texteditor", "texteditor", (char*)0);
				_exit(0);
			break;
		}
	}
				

	getch ();
	endwin ();
	exit (EXIT_SUCCESS);
*/

