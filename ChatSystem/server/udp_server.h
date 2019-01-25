#pragma once
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>
#include<unistd.h>
#include<map>
#include<stdlib.h>
#include "data_pool.h"

using namespace std;

#define SIZE 1024

class udp_server{
  private:
    int sock;
    int port;
    data_pool pool;
    map<uint32_t,struct sockaddr_in> online;

  public:
    udp_server(int _port);
    void init_server();
    void recv_data(string &out_string);
    void broadcast();
    ~udp_server();
  private:
    void send_data(const string &in_string,const struct sockaddr_in &peer);
};




