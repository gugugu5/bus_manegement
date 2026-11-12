#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std; namespace fs = std::filesystem;
const string DATA_DIR="data", USER_FILE=DATA_DIR+"/users.txt", RESERVATION_FILE=DATA_DIR+"/reservations.txt";
struct User{string phone,name,password;}; struct Passenger{string name,phone;int seat=0;}; struct Bus{int id,hour;vector<bool> seats=vector<bool>(16,false);vector<Passenger> passengers;};
void prepareData(){fs::create_directories(DATA_DIR);if(!fs::exists(USER_FILE)){ofstream out(USER_FILE);out<<"13800138000|演示乘客|123456\n";}if(!fs::exists(RESERVATION_FILE))ofstream(RESERVATION_FILE).close();}
vector<User> loadUsers(){vector<User> a;ifstream in(USER_FILE);string l;while(getline(in,l)){stringstream s(l);User u;getline(s,u.phone,'|');getline(s,u.name,'|');getline(s,u.password);if(!u.phone.empty())a.push_back(u);}return a;}
void saveUser(const User&u){ofstream o(USER_FILE,ios::app);o<<u.phone<<'|'<<u.name<<'|'<<u.password<<'\n';}
int priceByStops(int n){return n==1?70:n==2?100:120;} bool reserve(Bus&b,const Passenger&p){if(p.seat<1||p.seat>15||b.seats[p.seat])return false;b.seats[p.seat]=true;b.passengers.push_back(p);return true;}
void showPassengers(const Bus&b){cout<<"\n车辆 "<<b.id<<" 号乘客信息\n";if(b.passengers.empty()){cout<<"暂无预约\n";return;}for(auto&p:b.passengers)cout<<p.seat<<" 座  "<<p.name<<"  "<<p.phone<<'\n';}
int main(){prepareData();vector<Bus>buses{{1,6,vector<bool>(16,false),{}},{2,7,vector<bool>(16,false),{}},{3,8,vector<bool>(16,false),{}}};cout<<"=== 云途智能交通预约系统 ===\n1.管理员  2.乘客\n请选择身份：";int role;cin>>role;if(role==1){string pw;cout<<"请输入管理员密码：";cin>>pw;if(pw!="admin123"){cout<<"登录密码错误，无法进入管理员界面。\n";return 0;}cout<<"管理员登录成功。\n";for(auto&b:buses)showPassengers(b);return 0;}if(role!=2){cout<<"身份选择无效。\n";return 0;}string phone;cout<<"请输入手机号：";cin>>phone;auto users=loadUsers();auto it=find_if(users.begin(),users.end(),[&](auto&u){return u.phone==phone;});User cur;if(it!=users.end()){string pw;cout<<"该手机号已注册，请输入密码：";cin>>pw;if(pw!=it->password){cout<<"登录密码错误。\n";return 0;}cur=*it;cout<<"登录成功，欢迎 "<<cur.name<<"。\n";}else{cur.phone=phone;cout<<"手机号未注册，请输入姓名：";cin>>cur.name;cout<<"设置密码：";cin>>cur.password;saveUser(cur);cout<<"注册成功，已写入用户数据库。\n";}cout<<"可预约班次：\n";for(auto&b:buses)cout<<b.id<<". "<<setw(2)<<setfill('0')<<b.hour<<":00  S -> E  余 "<<count(b.seats.begin()+1,b.seats.end(),false)<<" 座\n"<<setfill(' ');int id,seat;cout<<"请输入班次编号和座位号：";cin>>id>>seat;auto b=find_if(buses.begin(),buses.end(),[&](auto&x){return x.id==id;});if(b==buses.end()||!reserve(*b,Passenger{cur.name,cur.phone,seat})){cout<<"预约失败：班次不存在、座位无效或已被占用。\n";return 0;}ofstream out(RESERVATION_FILE,ios::app);out<<cur.phone<<'|'<<id<<'|'<<seat<<'\n';cout<<"预约成功，记录已保存到该手机号账号数据库。票价："<<priceByStops(3)<<" 元\n";}
