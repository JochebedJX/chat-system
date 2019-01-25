#pragma once
#include<iostream>
#include<ncurses.h>
#include<unistd.h>

using namespace std;

class window {
  public:
    window();
    WINDOW *get_header();
    WINDOW *get_output();
    WINDOW *get_flist();
    WINDOW *get_input();
    
    void put_str_to_win(WINDOW *w,int y,int x,string &message);
    void get_str_from_win(WINDOW *w,string &out_string);

    void draw_header();
    void draw_output();
    void draw_flist();
    void draw_input();
    ~window();

  private:
    WINDOW *header;
    WINDOW *output;
    WINDOW *flist;
    WINDOW *input;

};




