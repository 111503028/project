#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define RED  "\x1B[31m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
#define RESET  "\x1B[0m"
#define TRUE 1
#define CH '_'
#define MAXCH 51
#define MAXNO 91
#define LEAP_YEAR      (year % 4 == 0 && year % 100!= 0 || year % 400 == 0)
int fm(int , int , int);
int firstday(int , int , int);
void printchar(char c);
int getkey();
void savefile(int ,int ,int);
int monthday[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char *monthname[] = {"January",
		    "February",
		    "March",
		    "April",
	       	    "May",
		    "June",
		    "July",
                    "August",
		    "September",
		    "October",
		    "November",
		    "Decembeer"
		    };
char *monthname1[] = { "JAN",
			"FEB",
			"MAR", 
			"APR",
			"MAY",
			"JUN",
			"JUL",
			"AUG",
			"SEP",
                        "OCT",
			"NOV",
			"DEC",
			};

int main(){
	cbreak();
	noecho();				// no echo //
	int row,col;				/* to store the number of rows and */
	initscr();				/* start the curses mode */
	getmaxyx(stdscr,row,col);		/* get the number of rows and columns */	
	char mesg[]="**********CALENDER***********";	
	int monthday[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	char *monthname[]={"January","February","March","April","May","June","July",
                "August","September","October","November","Decembeer"};
	
	char *monthname1[]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP",
                        "OCT","NOV","DEC"};

	int month, year, i, j, z, keycode, k;
	k = 1;

label: { 
	attron(A_BOLD);
	mvprintw(0, col / 2 - 1, "%s", mesg);
	attroff(A_BOLD);
	}
 	while( TRUE) {
		fflush(stdin);
		mvprintw(1, 0, "enter month in mm-yyyy format\n", row, col);
		scanw("%d-%d", &month, &year);
		if(year < 0){
			printw("invalid input\n");
			//printw("enter month in mm-yyyy format\n");
			continue;
			}
		if(month > 12 || month < 1) {
			printw("invalid input\n");
			row ++;
			col ++;
			continue;
			}
		break;
		}
	while(1) {
		clear();

	/* ======calculate first day of week====*/

		z = firstday( 1,  month, year);
		if(z == 0) {
			 z = 7;
		}
		printw("\n\n\t\t");
		attron(A_BOLD);
		printw("%s-%d\n", monthname[month - 1], year);
		attroff(A_BOLD);

	/*============= checking leap year or not==========*/

		monthday[1] = LEAP_YEAR ? 29 : 28;

	/*=======output==========*/

		attron(A_BOLD);
		printchar(CH);
		printw("\t");
		printw( "SUN");
		printw("	MON	TUE	WED	THU	FRI	SAT");
		printchar(CH);
		attroff(A_BOLD);

	/*=========== setting position======*
		
		for( i = 1; i<=z ; i++){
			printw("\t-");
		}
			//printf("	%d",k);
		j = z;
		k = 0;*/
		j = z;
		//for( i = 1; i < z ; i++){
		while( z != 1) {
			printw("\t-");
			z-- ;
		}
			//printf("	%d",k);
		//j = z;
		k=0;

	/*========printing dates=========*/
		start_color();
		attron(A_BOLD);
		for( i = 1; i <= monthday[month -1]; i++) {
		
			k = j % 7 + 1;

			j++;
			if(k == 2) {
							
				printw("\n\t");
				printw("%2d",i );
				}
			
			else{
				printw("	%2d",i);
				//j++;
				} 
			}
		printchar(CH);
		attroff(A_BOLD);
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		init_pair(2, COLOR_BLUE, COLOR_WHITE);
		attron(COLOR_PAIR(2));
		mvprintw(row - 5, 0, "(*)", row, col);
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		mvprintw(row - 5, 3, " use LEFT RIGHT UP DOWN arrow", row, col);
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		mvprintw(row - 4, 0, "(*)", row, col);
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		mvprintw(row - 4, 3, " press N for next year", row, col);
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		mvprintw(row - 3, 0, "(*)", row, col);
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		mvprintw(row - 3, 3, " press P to save calender", row, col);
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		mvprintw(row - 2, 0, "(*)", row, col);
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		mvprintw(row - 2, 3, " press I for new month and new year", row, col);
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		mvprintw(row - 1, 0, "(*)", row, col);
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		mvprintw(row - 1, 3, " press ESC to exit", row, col);
		attroff(COLOR_PAIR(1));
		keycode = getkey();
	
	/* ===== getting key code ====*/

		if ( keycode == 261) {
			year++;
			
			
		}
		if( keycode == 260 ) {
			year--;
			
		}
		if( keycode == 259) {
			month++;
			if( month > 12) {
				month = 1;
				year++;
			}
			
		}
		if( keycode == 258) {
			month--;
			if( month < 1){
				month = 12;
				year--;
			}

		}
		if(keycode == 25) {
			savefile(month, year, z);
			refresh();
		}
		if( keycode == 105) {
			clear();
			goto label;
		}
	}
	 exit(0);
	 refresh();
	 getch();
	 endwin();
	return 0;
}

int fm( int date, int month, int year) {
	int leap, fmonth;
	if(year % 4 == 0 && year % 100!=0 || year % 400 == 0)
		leap = 1;
	else
		leap = 0;
	fmonth = 3 + ( 2 - leap ) * ((month + 2) / (2 * month)) + ( 5 * month + month / 9) / 2;
	fmonth = fmonth % 7;
	return fmonth;
}

/* ===================first day of month=====================*/

int firstday(int date, int month, int year){
	int firstday, yy, century;
	yy = year % 100;
	century = year / 100 ;
	firstday = 1.25 * yy + fm(date , month, year) + date - 2 * (century % 4);
	firstday = firstday % 7;
	return firstday;
}

/*======================printchar======================*/

void printchar( char c){
	int i;
	printw( "\n\t");
	for( i = 0; i <= MAXCH; i++) {
		printw( "%c",c );
		printw( "%c",c );
	}
	printw("\n");
}

/*=============================getting key code ==============================*/

int getkey(){
	//int key = 0;
	int key;
	keypad(stdscr, TRUE);
	key = getch();
	noecho();
	if(key == 27){
		endwin();
		exit(0);
		return 27; 	 //ESC
	}
	
	if(key == 105)
		return 105;	// next yr next month // 
	if(key == 72)
		return 72;
	if(key == 261)
		return 261; 	// right arrow // 
	if(key == 259)
		return 259; 	// up arrow //
	if(key == 260)
		return 260;  	// left arrow //
	if( key == 258)
		return 258; 	// down arrow //
	else 
 		return 0;
	
} 

/* ============= ==================to save calender file=============== ======*/

void savefile(int M,int y, int z){
	int i , j;
	char filename[12];
	char stryear[5];
	FILE *fp;
	strcpy(filename , monthname1[M - 1]);
	strcat(filename , stryear);
	strcat(filename,".txt");
	fp = fopen(filename,"w");
	if(fp == NULL){
		printf("cannot create file\n");
		//getch();
		exit(1);
	}
	fprintf( fp,MAG "\n\n\t\t%s%d\n\n\t" RESET, monthname[M - 1],y);
	for( i =1 ; i < MAXNO ; i++){
		fprintf(fp,BLU "_" RESET);
	}
	fprintf(fp,"\n");
	for( i =1 ; i <= z ; i++){
		fprintf(fp, "\t_");
	}
	j = z;
	for( i =1 ; i <= monthday[M-1] ; i++){
		if( j++ % 7 == 0){
			fprintf(fp,"\n");
		}
		fprintf( fp, "\t%2d", i);
	}
	fprintf(fp ,"\n\t");
	for( i=1 ; i <= MAXNO ; i++){
		fprintf( fp, CYN "_" RESET);
	}		
	fclose(fp);
}


