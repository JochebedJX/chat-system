#include"data.h"
#include<iostream>

using namespace std;


data::data()
{
}
void data::serialize(string &out_string)
{
  ValueObj root;
  root["nick_name"]=nick_name;
  root["school"]=school;
  root["message"]=message;
  root["type"]=type;

  Write w;
  w.run(root,out_string);
}
void data::unserialize(string &in_string)
{
  ValueObj root;
  Read r;
  r.run(in_string, root);

  nick_name = root["nick_name"].getstring();
  school = root["school"].getstring();
  message = root["message"].getstring();
  type = root["type"].getstring();

}
data::~data()
{
}
