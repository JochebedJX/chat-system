#pragma once

#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string>
#include<unistd.h>
#include<unistd.h>
#include "window.h"
#include "data.h"
#include<pthread.h>

using namespace std;

#define SIZE 1024

class udp_client{
  private:
    int sock;
    struct sockaddr_in server;

  public:
    udp_client(string server_ip,int server_port);
    void init_client();
    void recv_data(string &out_string);
    void send_data(const string &in_string);

    ~udp_client();

};




