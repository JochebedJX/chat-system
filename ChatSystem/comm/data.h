#pragma once
#include<iostream>
#include<string>
#include<jsexcept.h>
#include<value.h>
#include<write.h>
#include<read.h>


using namespace std;

class data
{
  public:
    string nick_name;
    string school;
    string message;
    string type;

  public:
    data();
    void serialize(string &out_string);
    void unserialize(string &in_string);
    ~data();
};




