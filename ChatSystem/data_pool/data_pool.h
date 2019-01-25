#pragma once
#include<semaphore.h>
#include <iostream>
#include<string>
#include<vector>

using namespace std;
#define NUM 256

class data_pool{
  public:
    data_pool(int _cap=NUM);
    void get_message(string &out_message);
    void put_message(const string &in_message);
    ~data_pool();
  private:
    vector<string> pool;
    int cap;
    int consume_step;
    int product_step;
    sem_t space_sem;
    sem_t message_sem;
};

