# 编译和安装指南

本文档详细说明如何编译和安装斗地主游戏。

## 系统要求

- **操作系统**：Windows、Linux 或 macOS
- **编译器**：MinGW（Windows）、GCC 或 Clang
- **Qt版本**：Qt 5.12 或更高版本
- **Python**：3.6 或更高版本（用于AI模型）

## 依赖项

### Qt框架
- Qt Core
- Qt GUI
- Qt Widgets
- Qt Multimedia Network

### Python依赖（可选，用于AI功能）
- numpy
- torch
- DouZero（AI模型库）

## Windows编译步骤

### 1. 安装Qt
- 下载并安装 Qt Creator：https://www.qt.io/download-open-source
- 选择 Qt 5.15.2 版本及 MinGW 编译器

### 2. 打开项目
```bash
# 在 Qt Creator 中打开项目文件
Landlords.pro
```

### 3. 配置编译
- 在 Qt Creator 中选择 Release 或 Debug 配置
- 点击 Build > Build Project

### 4. 运行游戏
```bash
# 编译完成后点击 Run 或按 Ctrl+R
```

## Linux编译步骤

### 1. 安装依赖
```bash
# Ubuntu/Debian
sudo apt-get install qt5-default qt5-qmake build-essential

# Fedora
sudo dnf install qt5-qtbase-devel qt5-qtmultimedia-devel
```

### 2. 编译
```bash
cd Landlords
qmake Landlords.pro
make
```

### 3. 运行
```bash
./Landlords
```

## macOS编译步骤

### 1. 使用Homebrew安装Qt
```bash
brew install qt
```

### 2. 编译
```bash
cd Landlords
qmake Landlords.pro
make
```

### 3. 运行
```bash
./Landlords.app/Contents/MacOS/Landlords
```

## 安装AI模型（可选）

如果要使用AI功能，需要安装DouZero模型：

```bash
# 安装Python依赖
pip install -r requirements.txt

# 下载预训练模型
# 模型文件应放在 DouZero_API-main/baselines/ 目录下
```

## 故障排除

### 问题：找不到Qt库
**解决**：确保Qt安装路径正确配置在系统PATH中

### 问题：编译错误："undefined reference"
**解决**：检查Qt模块是否在 .pro 文件中正确配置

### 问题：游戏无法启动
**解决**：确保所有必要的DLL文件在同一目录，特别是Qt运行时库

## 文件结构

```
Landlords/
├── *.h, *.cpp    - 源代码文件
├── *.ui          - Qt UI 设计文件
├── res.qrc       - 资源文件
├── Landlords.pro - Qt 项目文件
└── build/        - 编译输出目录
```
