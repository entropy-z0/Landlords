# EXE 文件上传到 GitHub 最佳实践

本文档详细说明如何将 Landlords.exe 上传到 GitHub 及最佳实践。

## ⚠️ 重要提示

### GitHub 限制

- **文件大小**: GitHub Release 支持单个文件最大 2GB
- **推荐大小**: 单个文件 < 100MB（更快下载）
- **存储限制**: 公开仓库无限，私有仓库看账户

### 什么可以上传

✅ **允许上传到 Release**：
- 可执行文件（EXE、DMG、AppImage）
- 压缩包（ZIP、TAR.GZ）
- 依赖库文件
- 资源包

❌ **不应上传到仓库**：
- 源代码已在 main 分支
- 编译中间文件（build/ 目录）
- IDE 配置文件

## 📦 推荐方案：GitHub Release

### 为什么用 Release 而不是直接提交 EXE？

| 方式 | 优点 | 缺点 |
|------|------|------|
| **Release** | 版本清晰，下载快，独立管理 | 需要手动上传或配置 CI/CD |
| **仓库中** | 简单直接 | 仓库变臃肿，克隆变慢，混乱 |

**结论**：✅ 强烈推荐使用 Release

## 🚀 快速操作步骤（3 步）

### 第一步：准备 EXE 和依赖文件

EXE 需要的文件：
```
Landlords-v1.0.0-Windows/
├── Landlords.exe              ← 主程序
├── Qt5Core.dll                ← Qt 核心库
├── Qt5Gui.dll                 ← Qt GUI 库
├── Qt5Widgets.dll             ← Qt Widgets 库
├── Qt5Multimedia.dll          ← Qt 多媒体库
├── platforms/                 ← Qt 平台插件
│   └── qwindows.dll
├── imageformats/              ← 图片格式支持
│   ├── qjpeg.dll
│   └── qpng.dll
├── images/                    ← 游戏资源
│   └── [游戏图片文件]
├── README.txt                 ← 使用说明
└── LICENSE.txt                ← 许可证
```

#### 获取依赖文件

**方法 A：使用 windeployqt（最简单）**

```bash
# 进入编译输出目录
cd f:\Landlords\Landlords\build\Desktop_Qt_5_15_2_MinGW_32_bit-Release\release\

# 使用 Qt 部署工具
windeployqt --release Landlords.exe

# 这会自动复制所有所需的 DLL 和插件
# 生成的文件已准备好发布
```

**方法 B：手动收集（如果 windeployqt 不可用）**

从 Qt 安装目录复制：
- `Qt/5.15.2/mingw81_32/bin/` 中的 DLL 文件
- `Qt/5.15.2/mingw81_32/plugins/` 中的插件

### 第二步：创建压缩包

使用 PowerShell 或 7-Zip：

```powershell
# 压缩成 ZIP（PowerShell）
$source = "f:\Landlords\Landlords-v1.0.0-Windows"
$destination = "f:\Landlords\Landlords-v1.0.0-Windows.zip"
Compress-Archive -Path $source -DestinationPath $destination
```

或使用 7-Zip：
```bash
7z a Landlords-v1.0.0-Windows.zip Landlords-v1.0.0-Windows/
```

### 第三步：创建 Release 并上传

#### 方法 A：网页界面（图形化）

1. 访问: https://github.com/YOUR_USERNAME/Landlords/releases/new

2. 填写信息：
   - **Tag**: `v1.0.0`
   - **Title**: `Landlords v1.0.0 - Complete Release`
   - **Description**: (见下面的模板)

3. 上传文件：
   - 点击 "Attach binaries by dropping them here or selecting them."
   - 选择 `Landlords-v1.0.0-Windows.zip`

4. 发布：
   - 点击 "Publish release"

#### 方法 B：Git 标签自动化

```bash
# 创建标签
git tag -a v1.0.0 -m "Release: Landlord Game v1.0.0"

# 推送标签
git push origin v1.0.0

# 然后访问网页添加文件和说明
```

## 📝 Release 说明模板

```markdown
# Landlords v1.0.0 - Complete Release

> 📚 CUHKSZ CSC3002 C/C++ Programming 小组作业

## 🎉 功能完整度

- ✅ 完整的斗地主游戏规则
- ✅ AI 对手（DouZero 集成）
- ✅ 图形化用户界面
- ✅ 得分统计系统
- ✅ 跨平台支持

## 📦 下载

- **Windows 64-bit**: `Landlords-v1.0.0-Windows.zip` (42 MB)
- **说明**: Windows 10/11 推荐使用

## 💻 系统要求

- Windows 10 或 Windows 11
- 2GB RAM
- 200MB 磁盘空间
- .NET Framework (通常已预装)

## 🚀 安装和运行

### 简单安装

1. 下载 `Landlords-v1.0.0-Windows.zip`
2. 解压到任意目录
3. 双击 `Landlords.exe` 运行

### 首次启动

游戏首次启动时会初始化资源，请耐心等待。

## 🎮 游戏玩法

- **单击卡牌** - 选择/取消选择
- **出牌按钮** - 确认出牌
- **不出按钮** - 跳过本轮
- **提示按钮** - AI 建议

## 🐛 已知问题

目前没有已知的严重问题。

## 🙋 问题反馈

如遇到问题，请：
1. 检查 [BUILD.md](https://github.com/YOUR_USERNAME/Landlords/blob/main/BUILD.md) 中的故障排除部分
2. 提交 [Issue](https://github.com/YOUR_USERNAME/Landlords/issues)

## 📚 文档

- [README](https://github.com/YOUR_USERNAME/Landlords#readme) - 项目说明
- [编译指南](BUILD.md) - 从源代码构建
- [贡献指南](CONTRIBUTING.md) - 如何参与

## 🙏 感谢

- Qt 框架
- DouZero 项目
- 所有贡献者

---

**发布日期**: 2024年5月
**版本**: 1.0.0
**开源许可**: LGPL v3
```

## 🔄 发布多个版本

如果需要为多个平台发布：

### Windows + Linux 版本

```markdown
## 📦 下载

- **Windows 64-bit**: Landlords-v1.0.0-Windows.zip (42 MB)
- **Linux 64-bit**: Landlords-v1.0.0-Linux.tar.gz (35 MB)
- **源代码**: Source Code (ZIP or TAR.GZ)

## 平台特定说明

### Windows
1. 下载 Windows 版本
2. 解压
3. 运行 Landlords.exe

### Linux
1. 下载 Linux 版本
2. 解压: `tar -xzf Landlords-v1.0.0-Linux.tar.gz`
3. 赋予执行权限: `chmod +x Landlords`
4. 运行: `./Landlords`
```

## 📊 文件大小优化

如果 EXE 体积过大：

### 移除调试符号

```bash
# Windows (MinGW)
strip Landlords.exe

# 可以减少 30-50% 的大小
```

### 使用 UPX 压缩（可选）

```bash
# 安装 UPX
# https://upx.github.io/

upx --best Landlords.exe
```

## 🔐 发布安全性

### 签名和验证

GitHub 会自动为所有 Release 生成校验和。用户可以验证完整性：

```bash
# GitHub 自动提供 SHA256 校验和
# 用户可以验证下载的文件
certUtil -hashfile Landlords.exe SHA256
```

## 📋 发布前检查清单

```
发布前确认：

□ 代码已提交到 main 分支
□ 所有测试通过
□ CHANGELOG 已更新
□ README 信息准确
□ EXE 能正常运行
□ 包含所有必要的依赖文件
□ 没有敏感信息（密钥、密码）
□ 文件大小合理
□ 发布说明清晰完整
□ 标签格式正确（v1.0.0）
```

## 🔄 更新现有 Release

如果需要修改已发布的版本：

1. 访问 Release 页面
2. 点击编辑按钮
3. 修改文件或说明
4. 保存

## 🗑️ 删除旧版本

```bash
# 本地删除标签
git tag -d v0.9.0

# 远程删除
git push origin --delete v0.9.0

# 在 GitHub 网页界面删除 Release
```

## 📈 版本管理最佳实践

1. **使用语义化版本**: v1.0.0 (主版本.次版本.修复版本)
2. **完整的发布说明**: 包括新增功能、已知问题等
3. **保留历史版本**: 便于用户回退
4. **清晰的文件命名**: 包含版本号和平台
5. **及时更新**: Release 发布后更新主 README

## 🎯 总结

| 步骤 | 操作 | 时间 |
|------|------|------|
| 1 | 收集依赖文件 | 5 分钟 |
| 2 | 创建压缩包 | 2 分钟 |
| 3 | 创建 GitHub Release | 5 分钟 |
| 4 | 上传文件和说明 | 5 分钟 |
| **总计** | **完成发布** | **约 17 分钟** |

## 📞 遇到问题？

### EXE 无法运行
- 检查是否缺少 DLL 文件
- 确保 windeployqt 已正确执行
- 检查 Windows 版本兼容性

### 上传失败
- 检查网络连接
- 文件是否超过大小限制
- GitHub token 是否有效

### Release 不显示
- 检查标签是否正确推送
- 仓库可见性是否公开

## 🔗 相关资源

- [GitHub Release 文档](https://docs.github.com/en/repositories/releasing-projects-on-github/about-releases)
- [Qt 部署指南](https://doc.qt.io/qt-5/windows-deployment.html)
- [Semantic Versioning](https://semver.org/lang/zh-CN/)

---

**推荐**: 首次发布时按照此指南，后续维护会更轻松！
