#include<iostream>
#include "udp_client.h"

using namespace std;

udp_client::udp_client(string server_ip,int server_port)
{
  server.sin_family=AF_INET;
  server.sin_port=htons(server_port);
  server.sin_addr.s_addr=inet_addr(server_ip.c_str());


}
void udp_client::init_client()
{
  sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0)
  {
    cerr<<"socket error"<<endl;
    return ;
  }
}
void udp_client::recv_data(string &out_string)
{
  char buf[SIZE];
  struct sockaddr_in peer;
  socklen_t len =sizeof(peer);
  ssize_t s=recvfrom(sock,buf,SIZE,0,(struct sockaddr*)&peer,&len);
  if(s>0)
  {
    buf[s]=0;
    out_string=buf;
  }
}
void udp_client::send_data(const string &in_string)
{
  sendto(sock,in_string.c_str(),in_string.size(),0,(struct sockaddr*)&server,sizeof(server));

}
udp_client::~udp_client()
{
  close(sock);
}


