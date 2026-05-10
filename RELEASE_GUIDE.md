# GitHub Release 和 EXE 上传指南

本文档说明如何在 GitHub 上发布可执行文件（EXE）和其他预编译二进制文件。

## 📦 关于可执行文件上传

### 为什么要发布可执行文件？

- **便利用户**: 用户可以直接下载运行，无需编译
- **跨平台**: 为不同操作系统提供预编译版本
- **稳定发布**: 标记重要的稳定版本
- **版本管理**: 清楚地追踪每个版本

### 什么文件应该发布？

✅ **应该上传**：
- `Landlords.exe` - Windows 可执行文件
- 配置文件和资源文件（图片、音效等）
- 依赖库（如 Qt DLL）
- README 和使用说明

❌ **不应该上传到 Release**：
- 源代码（已在仓库中）
- 构建文件（build/、debug/ 等）
- IDE 配置文件（.pro.user 等）
- 临时文件

## 🚀 方式1：手动发布（推荐用于测试版）

### 步骤 1：创建 Release 标签

```bash
# 为当前提交创建标签
git tag v1.0.0

# 添加标签信息
git tag -a v1.0.0 -m "Release version 1.0.0 - Complete Landlord Game"

# 推送标签到 GitHub
git push origin v1.0.0
```

### 步骤 2：在 GitHub 上创建 Release

1. 访问项目的 "Releases" 页面
   ```
   https://github.com/YOUR_USERNAME/Landlords/releases
   ```

2. 点击 "Draft a new release"

3. 选择标签：`v1.0.0`

4. 填写 Release 信息：
   ```
   Title: Landlords v1.0.0 - Complete Release
   
   Description:
   ## What's New 🎉
   - Complete game implementation
   - AI opponent with DouZero
   - Full score tracking
   - Cross-platform support
   
   ## Downloads
   - Windows: Landlords.exe
   - Linux: Landlords (64-bit)
   
   ## Installation
   Windows: Download and run Landlords.exe
   Linux: chmod +x Landlords && ./Landlords
   
   ## System Requirements
   - Windows 10/11 or Linux
   - 200MB disk space
   - 2GB RAM
   
   ## Known Issues
   - None at this release
   
   ## Contributors
   - [Team member names]
   ```

5. 上传文件：点击 "Attach binaries"
   - Landlords.exe
   - Landlords (Linux 版本，如有)
   - Landlords.app (macOS 版本，如有)

6. 选择 "This is a pre-release" 或 "Latest release"

7. 点击 "Publish release"

## 🔄 方式2：自动发布（使用 GitHub Actions）

我们的项目中 `.github/workflows/build.yml` 已配置自动构建。可以进一步配置自动发布：

### 更新工作流配置

编辑 `.github/workflows/build.yml` 添加发布步骤：

```yaml
- name: Create Release
  if: startsWith(github.ref, 'refs/tags/')
  uses: actions/create-release@v1
  env:
    GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
  with:
    tag_name: ${{ github.ref }}
    release_name: Release ${{ github.ref }}
    body: |
      ## Changes in this Release
      See CHANGELOG.md for details
    draft: false
    prerelease: false

- name: Upload Release Asset (Windows)
  if: startsWith(github.ref, 'refs/tags/')
  uses: actions/upload-release-asset@v1
  env:
    GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
  with:
    upload_url: ${{ steps.create_release.outputs.upload_url }}
    asset_path: ./Landlords/release/Landlords.exe
    asset_name: Landlords.exe
    asset_content_type: application/octet-stream
```

使用自动构建后，只需要：
```bash
git tag v1.0.0
git push origin v1.0.0
```

GitHub Actions 会自动构建、创建 Release 并上传文件！

## 📋 预发布检查清单

在创建 Release 前，确保：

- [ ] 代码已提交并推送到 main 分支
- [ ] 所有测试通过
- [ ] 代码已清理（无调试代码）
- [ ] CHANGELOG.md 已更新
- [ ] 版本号已更新
- [ ] EXE 文件已测试可正常运行

### 测试 EXE

```bash
# Windows 上测试 EXE
f:\Landlords\Landlords.exe

# 检查是否能启动和运行游戏
# 检查 UI 是否正常显示
# 测试基本功能（开始游戏、出牌等）
```

## 📦 打包可执行文件

### Windows - 使用 Qt 部署工具

```bash
# 进入编译输出目录
cd f:\Landlords\Landlords\build\Desktop_Qt_5_15_2_MinGW_32_bit-Release\release\

# 使用 Qt 部署工具（如果已安装）
windeployqt Landlords.exe

# 这会自动复制所需的 DLL 文件
# 生成包含所有依赖的文件夹
```

### Windows - 手动打包

需要的文件：
```
Landlords.exe
├── Qt5Core.dll
├── Qt5Gui.dll
├── Qt5Widgets.dll
├── Qt5Multimedia.dll
├── platforms/          (Qt 平台插件)
├── imageformats/       (图像格式插件)
├── images/             (游戏资源)
└── README.txt          (说明文件)
```

### 创建压缩包

```bash
# Windows (使用 PowerShell)
Compress-Archive -Path "Landlords_Package" -DestinationPath "Landlords-v1.0.0-Windows.zip"

# Linux (使用 tar)
tar -czf Landlords-v1.0.0-Linux.tar.gz Landlords_Package/
```

## 📥 发布不同平台的版本

### Windows 版本
```
Landlords-v1.0.0-Windows.zip
├── Landlords.exe
├── Qt DLL 文件
├── 平台插件
└── README.txt
```

### Linux 版本
```
Landlords-v1.0.0-Linux.tar.gz
├── Landlords (可执行文件)
├── 依赖库
└── README.txt
```

### macOS 版本
```
Landlords-v1.0.0-macOS.dmg
└── Landlords.app/
```

## 🔐 文件大小考虑

- GitHub Release 对单个文件的大小限制较少
- 但下载速度会受影响
- 建议：
  - EXE 大小 < 100MB
  - 压缩包 < 50MB
  - 删除不必要的调试符号

### 优化 EXE 大小

```bash
# Release 模式编译（已默认）
qmake Landlords.pro -config release

# 移除调试符号
strip Landlords.exe  # Linux/macOS
objcopy --strip-all Landlords.exe  # Windows
```

## 📝 版本号约定

采用语义化版本（Semantic Versioning）：

```
v MAJOR.MINOR.PATCH

例如：
v1.0.0 - 首个正式版本
v1.1.0 - 添加新功能
v1.0.1 - 修复 bug
```

## 🎯 Release 标题模板

```
Landlords v1.0.0 - [版本名称]

例如：
v1.0.0 - Complete Release
v1.1.0 - AI Improvements & Bug Fixes
v2.0.0 - Major Update with Online Features
```

## 📄 Release 说明模板

```markdown
## 🎉 What's New
- Feature 1
- Feature 2
- Bug fix

## 📦 Downloads
- Windows: Landlords-v1.0.0-Windows.zip (45MB)
- Linux: Landlords-v1.0.0-Linux.tar.gz (38MB)

## 💻 System Requirements
- Windows 10/11 (64-bit)
- 2GB RAM
- 200MB disk space

## 🚀 Installation
1. Download the appropriate version for your OS
2. Extract the archive
3. Run Landlords.exe (Windows) or ./Landlords (Linux)

## 🐛 Known Issues
- Issue 1 (workaround: ...)

## 📚 Documentation
- [Build Guide](BUILD.md)
- [User Guide](README.md)
- [Changelog](CHANGELOG.md)

## 🙏 Thanks
Special thanks to contributors and Qt community
```

## 🔄 更新现有 Release

如果需要修改已发布的 Release：

1. 访问 Release 页面
2. 点击 "Edit"
3. 修改信息或文件
4. 点击 "Update release"

## 🗑️ 删除 Release

```bash
# 本地删除标签
git tag -d v1.0.0

# 远程删除标签
git push origin --delete v1.0.0

# 也可以在 GitHub 网页界面删除 Release
```

## 📊 管理多个版本

GitHub 会自动按时间倒序显示所有 Release。

- **Latest Release**: 最新稳定版本
- **Pre-release**: 测试版本
- **Older Releases**: 归档版本

## 💡 最佳实践

1. **版本控制**: 使用语义化版本
2. **文档完整**: 提供详细的发布说明
3. **测试充分**: Release 前测试所有功能
4. **清晰命名**: 使用明确的文件名
5. **更新文档**: 及时更新 README 和文档
6. **保留历史**: 保留旧版本供参考

## 🔗 相关链接

- [GitHub Releases 文档](https://docs.github.com/en/repositories/releasing-projects-on-github/about-releases)
- [Semantic Versioning](https://semver.org/lang/zh-CN/)
- [Qt Deployment Guide](https://doc.qt.io/qt-5/windows-deployment.html)

---

**提示**: 推荐创建一个 "Release Checklist" Issue 模板，以规范发布流程。
