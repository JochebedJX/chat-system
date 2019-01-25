#include"window.h"
#include<iostream>
using namespace std;
#define SIZE 1024
window::window()
{
  initscr();
}
WINDOW *window::get_header()
{
  return header;
}
WINDOW *window::get_output()
{
  return output;
}
WINDOW *window::get_flist()
{
  return flist;
}
WINDOW *window::get_input()
{
  return input;
}
void window::put_str_to_win(WINDOW *w,int y,int x,string &message)
{
  mvwaddstr(w,y,x,message.c_str());
  wrefresh(w);
}
void window::get_str_from_win(WINDOW *w,string &out_string)
{
  char buf[SIZE];
  wgetnstr(w,buf,SIZE);
  out_string=buf;
}

void window::draw_header()
{
  int y=0;
  int x=0;
  int h=LINES/5;
  int w=COLS;
  header=newwin(h,w,y,x);
  box(header,'+','=');
  wrefresh(header);
}
void window::draw_output()
{
  int y=LINES/5;
  int x=0;
  int h=LINES*3/5;
  int w=COLS*3/4;
  output=newwin(h,w,y,x);
  box(output,'+','=');
  wrefresh(output);

}
void window::draw_flist()
{
  int y=LINES/5;
  int x=COLS*3/4;
  int h=LINES*3/5;
  int w=COLS/4;
  flist=newwin(h,w,y,x);
  box(flist,'+','=');
  wrefresh(flist);

}
void window::draw_input()
{
  int y=LINES*4/5;
  int x=0;
  int h=LINES/5;
  int w=COLS;
  input=newwin(h,w,y,x);

  box(input,'+','=');
  wrefresh(input);
}
window::~window()
{
  endwin();
}




//int main()
//{
//  window w;
//  w.draw_header();
//  w.draw_output();
//  w.draw_flist();
//  w.draw_input();
//
//  //header
//  string title = "Little Cute Girl Chatting Room";
//  while(1)
//  {
//    int i=1;
//    int y,x;
//    int dir;
//    w.draw_header();
//    getmaxyx(w.get_header(),y,x);
//    w.put_str_to_win(w.get_header(),y/2,i,title);
//    if(i>=x-title.size()-2)
//    {
//      dir=1;
//    }
//    if(i<=2)
//    {
//      dir=0;
//    }
//    if(dir==0)
//    {
//      i++;
//    }else{
//      i--;
//    }
//    usleep(300000);
//  }
//
//  //output
//  
//
//  return 0;
//}
