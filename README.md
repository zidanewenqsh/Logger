# Logger

一个简洁而功能强大的C++日志记录库，支持不同日志级别和彩色输出。

## 功能特点

- 支持五种日志级别：DEBUG、INFO、WARNING、ERROR、FATAL
- 彩色终端输出，不同级别使用不同颜色
- 线程安全（使用互斥锁保护）
- 支持格式化输出（类似printf风格）
- 自动包含时间戳、文件名、行号和函数名
- 跨平台支持（Windows和Unix-like系统）
- 可作为共享库使用

## 构建方法

项目使用CMake构建系统。提供了便捷的build.sh脚本用于在Windows环境下使用Visual Studio 2015（64位）编译：

```bash
# 在Windows上
./build.sh
```

也可以手动使用CMake进行构建：

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## 使用方法

### 基本示例

```cpp
#include "Logger.h"

int main() {
    // 创建日志器实例
    Logger logger;
    
    // 设置日志级别（默认为INFO）
    logger.SetLevel(LogLevel::DEBUG);
    
    // 使用内置宏记录日志
    LOGDEBUG("这是一条调试日志");
    LOGINFO("这是一条信息日志");
    LOGWARNING("这是一条警告日志");
    LOGERROR("这是一条错误日志");
    LOGFATAL("这是一条致命错误日志");
    
    return 0;
}
```

### 格式化输出

```cpp
LOGINFO("用户 %s 登录，ID: %d", username, user_id);
```

### 重定向输出

```cpp
// 输出到文件
std::ofstream log_file("app.log");
logger.SetOutput(&log_file);
```

## 许可证

请参阅项目中的LICENSE文件。
