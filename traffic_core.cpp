#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 第一版核心模型：4 个站点、每车 15 座、每天 3 班，便于课堂理解。
struct Passenger { string name, phone; int seat = 0; };
struct Bus { int id, hour; vector<bool> seats = vector<bool>(16, false); vector<Passenger> passengers; };

int priceByStops(int stops) { return stops == 1 ? 70 : stops == 2 ? 100 : 120; }

void printSeats(const Bus& bus) {
    cout << "座位图（* 已预约，. 可选）\n";
    for (int i = 1; i <= 15; ++i) {
        cout << setw(2) << i << (bus.seats[i] ? "*  " : ".  ");
        if (i % 5 == 0) cout << '\n';
    }
}

bool reserve(Bus& bus, const Passenger& passenger) {
    if (passenger.seat < 1 || passenger.seat > 15 || bus.seats[passenger.seat]) return false;
    bus.seats[passenger.seat] = true;
    bus.passengers.push_back(passenger);
    return true;
}

void showPassenger(const Bus& bus) {
    cout << "\n车辆 " << bus.id << " 号乘客信息\n";
    if (bus.passengers.empty()) { cout << "暂无预约\n"; return; }
    for (const auto& p : bus.passengers)
        cout << p.seat << " 座  " << p.name << "  " << p.phone << '\n';
}

int main() {
    vector<Bus> buses{
        Bus{1, 6, vector<bool>(16, false), {}},
        Bus{2, 7, vector<bool>(16, false), {}},
        Bus{3, 8, vector<bool>(16, false), {}}
    };
    cout << "=== 云途智能交通预约系统（C++ 核心演示）===\n";
    cout << "站点：S 起点站 / A 中央公园 / B 科技园 / E 滨水站\n";
    cout << "请输入手机号登录：";
    string phone; cin >> phone;
    cout << "登录成功。请选择身份：1.乘客  2.管理员\n选择：";
    int role; cin >> role;
    if (role == 1) {
        cout << "可预约班次：\n";
        for (const auto& bus : buses) {
            int remaining = count(bus.seats.begin() + 1, bus.seats.end(), false);
            cout << bus.id << ". " << setw(2) << setfill('0') << bus.hour << ":00  S -> E  余 "
                 << remaining << " 座\n" << setfill(' ');
        }
        int busId, seat; cout << "输入班次编号和座位号（如 1 3）："; cin >> busId >> seat;
        auto it = find_if(buses.begin(), buses.end(), [busId](const Bus& b) { return b.id == busId; });
        if (it == buses.end()) { cout << "班次不存在\n"; return 0; }
        Passenger p{"演示乘客", phone, seat};
        if (reserve(*it, p)) cout << "预约成功：" << it->hour << ":00，座位 " << seat << "，票价 120 元\n";
        else cout << "预约失败：座位号无效或已被预约\n";
    } else {
        for (const auto& bus : buses) showPassenger(bus);
        cout << "管理员可在此基础上增加班次、修改发车时间和统计营业额。\n";
    }
    return 0;
}
