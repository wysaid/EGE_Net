# EGE 网格变形演示程序

一个使用 EGE (Easy Graphics Engine) 图形库实现的交互式网格变形演示程序。本项目展示了弹性网格的物理模拟效果，用户可以通过鼠标拖拽网格节点来观察网格的弹性变形。

## 项目简介

本项目是一个简单而有趣的图形编程示例，实现了网格的弹性物理模拟。用户可以通过鼠标与网格进行交互，观察网格在外力作用下的变形和恢复过程。这个项目对于学习图形编程、物理模拟以及交互式应用开发的开发者很有参考价值。

**特点：**
- 实时物理模拟的弹性网格
- 流畅的鼠标交互
- 可调节的弹性强度参数
- 清晰的代码结构，易于理解和学习

**代码质量：** 本版本由 wysaid 依据网格变形的物理原理独立编写而成，未借用原版代码，因此思路较为清晰，可读性强，适合作为学习资料。

## 依赖库

本项目使用 [EGE (Easy Graphics Engine)](https://github.com/x-ege/xege) 图形库开发。

### 关于 EGE

EGE (Easy Graphics Engine) 是一个简单易用的 C++ 图形库，专为图形编程初学者设计。它提供了类似 Turbo C 的 BGI 图形库的简单接口，但功能更强大，支持现代 Windows 系统。

**EGE 的主要特性：**
- 简单易学的 API 接口
- 支持基本图形绘制（点、线、矩形、圆等）
- 支持图像处理和显示
- 支持鼠标和键盘交互
- 跨编译器支持（MSVC、MinGW 等）
- 活跃的社区支持

**EGE 项目地址：** https://github.com/x-ege/xege

**EGE 官方文档：** https://xege.org/

## 环境要求

- Windows 操作系统
- C++ 编译器（支持 C++11 或更高版本）
  - Visual Studio 2015 或更高版本（推荐）
  - MinGW-w64
  - 其他支持 Windows 的 C++ 编译器
- EGE 图形库

## 安装配置

### 1. 安装 EGE 图形库

#### Visual Studio 用户

1. 从 [EGE 发布页面](https://github.com/x-ege/xege/releases) 下载最新版本的 EGE 库
2. 解压到任意目录（如 `C:\EGE`）
3. 在 Visual Studio 项目中配置：
   - 在项目属性中添加头文件目录：`C:\EGE\include`
   - 在项目属性中添加库文件目录：`C:\EGE\lib`
   - 在链接器输入中添加：`graphics.lib`

#### MinGW 用户

1. 下载 EGE 源代码或预编译包
2. 配置编译器的 include 和 lib 路径
3. 链接 `graphics.a` 和必要的系统库

详细安装说明请参考 [EGE 官方文档](https://xege.org/)。

### 2. 编译本项目

#### 使用 Visual Studio

1. 打开 `EGE_Net.sln` 解决方案文件
2. 确保已正确配置 EGE 库路径
3. 点击"生成解决方案"进行编译
4. 运行生成的 `EGE_Net.exe`

#### 使用命令行编译（以 g++ 为例）

```bash
g++ -o EGE_Net.exe main.cpp -I<EGE_include_path> -L<EGE_lib_path> -lgraphics64 -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid
```

**注意：** 请将 `<EGE_include_path>` 和 `<EGE_lib_path>` 替换为实际的 EGE 库路径。例如：
```bash
g++ -o EGE_Net.exe main.cpp -IC:\EGE\include -LC:\EGE\lib -lgraphics64 -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid
```

## 使用说明

### 运行程序

双击 `EGE_Net.exe` 运行程序，或在命令行中执行：

```bash
./EGE_Net.exe
```

### 操作方法

- **鼠标左键拖拽**：点击并拖拽网格上的任意位置，可以拉扯网格观察变形效果
- **+ 键**：增加网格的弹性强度
- **- 键**：减小网格的弹性强度
- **ESC 键**：退出程序

### 效果展示

![程序运行截图](https://raw.github.com/wysaid/EGE_Net/master/shortcut.jpg)

## 技术实现

### 核心算法

程序使用了基于物理的弹性网格模拟算法：

1. **网格初始化**：创建二维网格点阵，每个点存储位置和速度信息
2. **物理更新**：计算每个网格点受到相邻点的弹性力，更新速度和位置
3. **阻尼模拟**：添加能量损失模拟，使网格逐渐趋于稳定
4. **交互处理**：捕捉鼠标位置，固定最近的网格点到鼠标位置

### 代码结构

- `Point` 结构体：存储网格点的位置和速度
- `Net` 类：实现网格的初始化、更新、绘制和交互
- `main` 函数：初始化图形窗口，处理主循环和用户输入

### 跨编译器支持

本项目使用预处理宏实现了文本的多语言支持：
- MSVC 编译器下显示中文界面
- 其他编译器（如 MinGW）下显示英文界面

这样可以避免在不同编译器环境下的中文乱码问题。

## 项目结构

```
EGE_Net/
├── main.cpp              # 主程序源代码
├── README.md             # 项目说明文档（本文件）
├── EGE_Net.sln           # Visual Studio 解决方案文件
├── EGE_Net.vcxproj       # Visual Studio 项目文件
└── shortcut.jpg          # 程序运行截图
```

## 学习建议

如果你是图形编程初学者，建议按以下顺序学习：

1. **熟悉 EGE 基础**：先学习 EGE 的基本绘图函数（点、线、图形等）
2. **理解网格结构**：查看 `Point` 和 `Net` 类的定义，理解网格数据的组织方式
3. **研究物理模拟**：重点阅读 `update()` 函数，理解弹性力的计算方法
4. **学习交互处理**：查看 `catchPoint()` 和鼠标事件处理代码
5. **尝试修改参数**：修改网格密度、弹性系数等参数，观察不同效果

## 扩展建议

你可以尝试以下扩展来提升项目：

- 添加多种网格变形模式
- 实现网格的纹理映射
- 添加更多物理效果（重力、风力等）
- 支持保存和加载网格状态
- 添加动画录制功能

## 参考资料

- EGE 官方文档：https://xege.org/
- EGE GitHub 仓库：https://github.com/x-ege/xege
- 作者博客：http://blog.wysaid.org

## 许可证

本项目代码可自由使用和学习，欢迎参考和借鉴。

## 作者

- **wysaid** - 项目作者和维护者

## 致谢

感谢 EGE 团队提供的优秀图形库，让图形编程变得简单有趣。