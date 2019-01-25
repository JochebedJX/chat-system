#include<iostream>
#include<vector>
#include<signal.h>
#include<pthread.h>
#include"udp_client.h"

using namespace std;

volatile int is_quit =0;

typedef struct{
  udp_client *clientp;
  window *winp;
  string nick_name;
  string school;
}client_info_t;

client_info_t cw;
vector<string> friends;

static void del_user(string &del)
{
  vector<string>::iterator it=friends.begin();
  for(;it!=friends.end();it++)
  {
    if(*it==del)
    {
      friends.erase(it);
    }
  }
}
static void add_user(string &fri)
{
  vector<string>::iterator it=friends.begin();
  for(;it!=friends.end();it++)
  {
    if(*it==fri)
    {
      return;
    }
  }
  friends.push_back(fri);
}

void usage(string proc)
{
  cout<<proc<<"server_ip server_port"<<" port"<<endl;
}

void *run_header(void *arg)
{
  client_info_t *cwp=(client_info_t*)arg;
  window *w=cwp->winp;
  w->draw_header();
  string title = "Little Cute Girl Chatting Room";
  int i=1;
  int y,x;
  while(1)
  {
    int dir;
    w->draw_header();
    getmaxyx(w->get_header(),y,x);
    w->put_str_to_win(w->get_header(),y/2,i,title);
    if(i>=x-title.size()-2)
    {
      dir=1;
    }
    if(i<=2)
    {
      dir=0;
    }
    if(dir==0)
    {
      i++;
    }else{
      i--;
    }
    usleep(300000);
  }
  return NULL;
}

void *run_output(void* arg)
{
  client_info_t *cwp=(client_info_t*)arg;
  window *w=cwp->winp;
  udp_client* cp=cwp->clientp;
  w->draw_output();
  w->draw_flist();
  int i=1;
  int y,x;
  string out_string;
  string show_string;
  data d;
  while(1)
  {
    int dir=0;
    cp->recv_data(out_string);
    d.unserialize(out_string);
    show_string=d.nick_name;
    show_string+="~";
    show_string+=d.school;

    if(d.type=="quit")
    {
      del_user(show_string);
    }
    else{
      add_user(show_string);
      show_string+="# ";
      show_string+=d.message;

      if(i>y-2)
      {
        i=1;
        w->draw_output();
      }
      getmaxyx(w->get_output(),y,x);
      w->put_str_to_win(w->get_output(),i++,2,show_string);
    }
    //flist
    w->draw_flist();
    int j=0;
    for(;j<friends.size();j++)
    {
      w->put_str_to_win(w->get_flist(),j+1,2,friends[j]);

    }
  }
}
void *run_input(void* arg)
{
  client_info_t *cwp=(client_info_t*)arg;
  window *w=cwp->winp;
  udp_client* cp=cwp->clientp;
  w->draw_input();

  string tips = "Please Enter# ";
  string str;
  data d;
  string out_string;
  while(1)
  {
    w->put_str_to_win(w->get_input(),1,2,tips);
    w->get_str_from_win(w->get_input(),str);

    d.nick_name=cwp->nick_name;
    d.school=cwp->school;
    d.message=str;
    d.type="None";
    d.serialize(out_string);
    cp->send_data(out_string);

    w->draw_input();
  }
}
void send_quit(int sig)
{
  data d;
  d.nick_name=cw.nick_name;
  d.school=cw.school;
  d.message="None";
  d.type="quit";
  string out_string;
  d.serialize(out_string);
  cw.clientp->send_data(out_string);
  is_quit=1;
}
int main(int argc,char * argv[])
{
  if(argc !=3)
  {
    usage(argv[0]);
    return 1;
  }

  signal(SIGINT,send_quit);

  cout<<"Please Enter your nick_name: ";
  cin>>cw.nick_name;
  cout<<"Please Enter your school: ";
  cin>>cw.school;

  udp_client cli(argv[1],atoi(argv[2]));
  cli.init_client();
  window w;

  cw.clientp =&cli;
  cw.winp=&w;

  pthread_t header,output_flist,input;
  pthread_create(&header,NULL,run_header,(void* )&cw);
  pthread_create(&output_flist,NULL,run_output,(void* )&cw);
  pthread_create(&input,NULL,run_input,(void* )&cw);

  //pthread_join(header,NULL);
  //pthread_join(output_flist,NULL);
  //pthread_join(input,NULL);
  while(!is_quit)
  {
    sleep(1);
  }

  return 0;
}


