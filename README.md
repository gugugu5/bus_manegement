# 云途智能交通预约系统

这是一个基于 C++17、MFC 和 SQLite 的 Windows 桌面预约系统。

## 构建

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
.\build\Debug\YuntuTraffic.exe
```

需要 Visual Studio 2022 Build Tools（MSVC v143、MFC/ATL、Windows SDK）和 CMake 3.25+。

## 默认账号

- 管理员账号：`guanliyuan`
- 管理员密码：`123456`

## 已实现功能

乘客注册/登录、日期和上下车站查询、S-A-B-E 双向班次、5×4 分段座位图、70/100/120 元分段票价、事务下单、冲突校验、取消释放座位、我的订单，以及管理员班次/车辆/乘客/订单/营业统计管理。

运行数据保存在 `data/traffic.db`。程序首次启动会自动建表、迁移旧数据库并生成默认班次。
