#include <ncurses.h>
void rectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}
int main()
{
 initscr();
 curs_set(0);
 start_color();
 init_pair(1,COLOR_GREEN,COLOR_BLACK);
 init_pair(2,COLOR_YELLOW,COLOR_BLACK);
 init_pair(3,COLOR_RED,COLOR_BLACK);
 noecho(); 
 mvprintw(LINES/2,COLS/2,"PONG\n");

 while(1)
 {
  char ch=getch();
  if (ch=='\n')
  break;
 }
 int x1=5,x2=COLS-5,y1=3,y2=3,w=1,h=5,ballx=COLS/2,bally=LINES/2,xmove=1,ymove=1,winner=0;
 while(!winner)
 {
 clear();
 timeout(50);
 attron(COLOR_PAIR(1));
 rectangle(y1,x1,y1+h,x1+w);
 attroff(COLOR_PAIR(1));
 attron(COLOR_PAIR(3));
 rectangle(y2,x2,y2+h,x2+w);
 attroff(COLOR_PAIR(3));
 attron(COLOR_PAIR(2));
 mvprintw(bally,ballx,"O");
 attron(COLOR_PAIR(2));
 char c=getch();
 switch(c)
 {
  case 'w':
   if(y1>=0)
    y1-=2;
   break;
  case 's':
   if(y1+h<=LINES)
    y1+=2;
   break;
 }
 ballx=ballx+xmove;
 bally=bally+ymove;
 y2=bally-(h/2);
 if(bally>=LINES-2 || bally <=3)
  ymove=-ymove;
 if ((ballx==x1+w+1) && (bally>=y1 && bally<=y1+h))
  xmove=-xmove;
 if ((ballx==x2-1) && (bally>=y2 && bally<=y2+h))
  xmove=-xmove;

 if(ballx<=0)
  winner=2;
 else if(ballx>=COLS)
  winner=1;
 }
 while(1)
 {
  timeout(10000);
  if(winner==1)
  mvprintw(LINES/2,COLS/2,"PLAYER WON!!");
  else
  mvprintw(LINES/2,COLS/2,"COMPUTER WON!!");
  char ch=getch();
  if(ch=='\n')
   break;
 }
 endwin();

 return 0;
}
