#include<iostream>
#include<map>
#include"data.h"
#include "udp_server.h"

using namespace std;

udp_server::udp_server(int _port)
  :port(_port)
  ,pool(SIZE)
{}
void udp_server::init_server()
{
  sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0)
  {
    cerr<<"socket error"<<endl;
    return ;
  }
  struct sockaddr_in local;
  local.sin_family=AF_INET;
  local.sin_port=htons(port);
  local.sin_addr.s_addr=htonl(INADDR_ANY);
  if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
  {
    cerr<<"bind error"<<endl;
    return ;
  }
}
void udp_server::recv_data(string &out_string)
{
  char buf[SIZE];
  struct sockaddr_in peer;
  socklen_t len =sizeof(peer);
  ssize_t s=recvfrom(sock,buf,SIZE,0,(struct sockaddr*)&peer,&len);
  if(s>0)
  {
    buf[s]=0;
    out_string=buf;
    pool.put_message(out_string);
    data d;
    d.unserialize(out_string);
    if(d.type=="quit")
    {
      map<uint32_t,struct sockaddr_in>::iterator it=online.find(peer.sin_addr.s_addr);
      if(it!=online.end())
      {
        online.erase(it->first);
      }
    }else{
      online.insert(pair<uint32_t,struct sockaddr_in>(peer.sin_addr.s_addr,peer));
    }
  }
}
void udp_server::send_data(const string &in_string,const struct sockaddr_in &peer)
{
  sendto(sock,in_string.c_str(),in_string.size(),0,(struct sockaddr*)&peer,sizeof(peer));

}
void udp_server::broadcast()
{
  string message;
  pool.get_message(message);
  map<uint32_t,struct sockaddr_in>::iterator it=online.begin();
  for(;it!=online.end();it++)
  {
    send_data(message,it->second);
  }
}
udp_server::~udp_server()
{
  close(sock);
  port=-1;
}


