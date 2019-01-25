#include<iostream>
#include"udp_server.h"

using namespace std;

void usage(string proc)
{
  cout<<"Usage: "<<proc<<" port"<<endl;
}
void *recv_message(void *arg)
{
  udp_server* sp=(udp_server*)arg;
  string message;
  while(1){
    sp->recv_data(message);
    cout<<"debug:"<<message<<endl;
  }
}
void *send_message(void* arg)
{
  udp_server *sp=(udp_server*)arg;
  while(1){
    sp->broadcast();
  }
}
int main(int argc,char * argv[])
{
  if(argc !=2)
  {
    usage(argv[0]);
    return 1;
  }

  udp_server ser(atoi(argv[1]));
  ser.init_server();
  pthread_t r,s;
  pthread_create(&r,NULL,recv_message,(void* )&ser);
  pthread_create(&s,NULL,send_message,(void* )&ser);

  pthread_join(r,NULL);
  pthread_join(s,NULL);

  return 0;
}



