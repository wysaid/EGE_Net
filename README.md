# EGE 网格变形演示程序

一个使用 EGE (Easy Graphics Engine) 图形库实现的交互式网格变形演示程序。本项目展示了弹性网格的物理模拟效果，用户可以通过鼠标拖拽网格节点来观察网格的弹性变形。

## 项目简介

本项目是一个简单而有趣的图形编程示例，实现了网格的弹性物理模拟。用户可以通过鼠标与网格进行交互，观察网格在外力作用下的变形和恢复过程。这个项目对于学习图形编程、物理模拟以及交互式应用开发的开发者很有参考价值。

**核心特点：**

- 🎮 实时物理模拟的弹性网格
- 🖱️ 流畅的鼠标交互体验
- ⚙️ 可实时调节的弹性强度参数
- 📚 清晰的代码结构，易于理解和学习
- 🔧 现代化的 CMake 构建系统
- 🌍 跨平台编译支持（MSVC、MinGW、GCC）

**代码质量：** 本版本由 wysaid 依据网格变形的物理原理独立编写而成，未借用原版代码，思路清晰，可读性强，是学习实时物理模拟的优秀参考资料。

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

**项目已集成 EGE 库文件，无需额外下载。**

**相关链接：**

- EGE 项目地址：<https://github.com/x-ege/xege>
- EGE 官方文档：<https://xege.org/>
- 库版本：v25.11 及以上

## 环境要求

- **操作系统：** Windows（7 及以上版本）
- **编译工具：** 以下任选一种
  - Visual Studio 2015 或更高版本（推荐）
  - MinGW-w64
  - GCC/Clang with MinGW 工具链
- **C++ 标准：** C++11 或更高版本
- **依赖库：** EGE 图形库（已包含在项目中）

## 快速开始

### 前置要求

本项目采用 **CMake** 构建系统，支持多种编译器。项目已整合 EGE 库文件，无需单独下载和配置。

### 编译方式

#### 方式一：使用 VS Code（推荐）

1. 安装 VS Code 和 [CMake Tools 扩展](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
2. 打开本项目文件夹
3. 选择底部工具栏的编译工具集（如 Visual Studio 2022）
4. 点击 `生成` 按钮，或按 `Ctrl+Shift+B` 快速构建

#### 方式二：使用 Visual Studio

1. 安装 Visual Studio 2015 或更高版本（需要 C++ 开发工具）
2. 用 Visual Studio 直接打开项目文件夹（`文件 → 打开 → 文件夹`）
3. Visual Studio 会自动识别并配置 CMake 项目
4. 在顶部菜单选择 `生成 → 生成全部` 进行编译

#### 方式三：使用命令行

```powershell
# 进入项目目录
cd EGE_Net

# 创建并进入构建目录
mkdir build
cd build

# 生成构建文件（使用默认编译器）
cmake ..

# 执行编译
cmake --build . --parallel 4
```

**对于 MinGW 用户：**

```powershell
cmake .. -G "MinGW Makefiles"
cmake --build . --parallel 4
```

### 运行程序

构建成功后，可执行文件位于：

- **Debug 版本：** `build/Debug/ege-demo.exe`
- **Release 版本：** `build/Release/ege-demo.exe`

双击运行或在命令行执行：

```powershell
./build/Debug/ege-demo.exe
```

### 操作方法

- **🖱️ 鼠标左键拖拽**：点击并拖拽网格上的任意位置，可以拉扯网格观察变形效果
- **➕ `+` 键**：增加网格的弹性强度，网格变得更"硬"
- **➖ `-` 键**：减小网格的弹性强度，网格变得更"软"
- **🚪 `ESC` 键**：退出程序

### 效果展示

![程序运行截图](shortcut.png)

## 技术实现

### 核心算法

程序使用了基于物理的弹性网格模拟算法：

1. **网格初始化**：创建二维网格点阵，每个点存储位置和速度信息
2. **物理更新**：计算每个网格点受到相邻点的弹性力，更新速度和位置
3. **阻尼模拟**：添加能量损失模拟，使网格逐渐趋于稳定
4. **交互处理**：捕捉鼠标位置，固定最近的网格点到鼠标位置

### 代码结构

- `Point` 结构体：存储网格点的位置 (x, y) 和速度 (dx, dy)
- `Net` 类：实现网格的初始化、物理更新、渲染绘制和交互处理
- `main()` 函数：初始化图形窗口，处理主事件循环和用户输入

### 多编译器支持

本项目采用 CMake 构建系统，实现了多编译器的自动适配：

**MSVC 编译器（Visual Studio）：**

- 自动识别 VS 版本（2010, 2015, 2017, 2019, 2022, 2026）
- 自动选择对应版本的预编译库
- 支持 UTF-8 源文件编码
- 启用多线程编译（/MP）加速构建

**GCC/MinGW 编译器：**

- 支持跨编译环境（Linux 编译 Windows 程序）
- 支持 macOS 平台编译
- 自动链接必要的 Windows API 库
- 使用静态链接减少依赖

**编码支持：**

- MSVC 环境下显示中文界面
- MinGW 环境下显示英文界面（避免编码问题）
- 源代码以 UTF-8 编码保存

## 项目结构

```text
EGE_Net/
├── CMakeLists.txt           # CMake 构建配置文件（支持多编译器）
├── main.cpp                 # 主程序源代码
├── README.md                # 项目说明文档（本文件）
├── .vscode/                 # VS Code 配置文件
│   ├── c_cpp_properties.json
│   ├── launch.json          # 调试配置
│   ├── settings.json
│   └── tasks.json           # 构建任务定义
├── build/                   # 构建目录（CMake 生成）
│   ├── Debug/
│   ├── Release/
│   └── ...
├── ege/
│   ├── include/             # EGE 头文件
│   │   ├── ege.h
│   │   ├── graphics.h
│   │   └── ege/             # 子模块头文件
│   └── lib/                 # EGE 预编译库
│       ├── vs2015/          # Visual Studio 2015
│       ├── vs2017/          # Visual Studio 2017
│       ├── vs2019/          # Visual Studio 2019
│       ├── vs2022/          # Visual Studio 2022
│       ├── vs2026/          # Visual Studio 2026
│       ├── mingw64/         # MinGW-w64 (Windows)
│       ├── mingw-w64-debian/# MinGW-w64 (Debian)
│       └── macOS/           # macOS 支持
└── shortcut.png             # 程序运行截图
```

**关键改进：**

- ✅ **现代化构建：** 从 Visual Studio 项目文件升级到 CMake，支持跨平台编译
- ✅ **编译器自动识别：** 根据 MSVC 版本自动选择兼容的库文件
- ✅ **统一构建体验：** VS Code 和 Visual Studio 均提供一致的构建流程
- ✅ **调试配置：** 集成 VS Code 调试配置，支持快速设置断点和单步调试

## 学习建议

如果你是图形编程初学者，建议按以下顺序学习：

1. **熟悉项目构建**：理解 CMake 构建系统的工作原理，学会使用现代构建工具
2. **理解网格结构**：查看 `Point` 结构体和 `Net` 类的定义，理解网格数据的组织方式
3. **研究物理模拟**：重点阅读 `Net::update()` 函数，理解：
   - 如何计算相邻点之间的弹性力
   - 如何利用速度和加速度更新点的位置
   - 如何实现阻尼效果
4. **学习交互处理**：查看 `Net::catchPoint()` 函数和鼠标事件处理代码
5. **尝试参数调整**：修改网格密度、弹性系数、阻尼系数等参数，观察不同效果
6. **性能优化**：学习如何使用并行编译加速构建，理解 Release 版本的优化选项

## 扩展建议

你可以尝试以下扩展来提升项目功能：

- 📊 添加多种网格变形模式（如径向扭曲、波浪形变）
- 🎨 实现网格的纹理映射和颜色渐变
- 🌀 添加更多物理效果（重力、风力、涡流等）
- 💾 支持保存和加载网格状态到文件
- 🎬 添加动画录制功能（导出为视频或图片序列）
- ⚡ 优化物理模拟算法以支持更大规模的网格
- 🎮 实现多点触控交互（触屏设备支持）

## 项目历程

### 重构说明（refactor_with_cmake 分支）

本分支对项目进行了重大现代化改进：

**从旧结构迁移到 CMake：**

- ✅ 删除了 Visual Studio 项目文件（`EGE_Net.sln`、`EGE_Net.vcxproj`）
- ✅ 创建了现代化的 `CMakeLists.txt` 构建配置
- ✅ 添加了 VS Code 开发环境配置（调试、构建任务）
- ✅ 集成了完整的 EGE 库文件（多版本、多编译器支持）

**构建系统改进：**

- 🔧 自动编译器识别和库选择
- 📦 并行编译支持（加速构建过程）
- 🌍 跨平台编译支持（Windows、Linux、macOS）
- 🔐 UTF-8 编码和多语言支持

## 参考资料

- **EGE 官方文档**：<https://xege.org/>
- **EGE GitHub 仓库**：<https://github.com/x-ege/xege>
- **CMake 官方文档**：<https://cmake.org/documentation/>
- **作者博客**：<http://blog.wysaid.org>
- **C++ 标准参考**：<https://cppreference.com/>

## 许可证

本项目代码可自由使用和学习，欢迎参考和借鉴。详见项目根目录的许可证文件。

## 作者与致谢

**主要开发者：** wysaid

**感谢：**

- 感谢 EGE 团队提供的优秀图形库，让图形编程变得简单有趣
- 感谢所有为这个项目提出建议和反馈的贡献者

---

**最后更新**：2025年12月 | **当前分支**：refactor_with_cmake | **EGE 版本**：v25.11+
