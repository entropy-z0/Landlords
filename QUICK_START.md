# 快速启动 - GitHub 上传准备

这是一个快速检查清单，用于在上传到 GitHub 之前验证项目准备情况。

## ✅ 预上传检查清单

### 1. 文件结构验证

```bash
# 进入项目根目录
cd f:\Landlords\Landlords

# 检查必要文件是否存在
ls -la | grep -E "\.gitignore|README|LICENSE|BUILD\.md|CONTRIBUTING"
```

应该看到：
```
.gitignore
README.md
LICENSE
BUILD.md
CONTRIBUTING.md
```

### 2. .gitignore 验证

```bash
# 检查 .gitignore 中的规则
cat .gitignore | head -20

# 查看哪些文件会被忽略
git status --ignored
```

应该看到 `build/`, `release/`, `.DS_Store` 等被忽略。

### 3. 代码质量检查

```bash
# 查看项目总大小（排除 git）
du -sh --exclude=.git .

# 查看最大的文件/目录
du -sh */ | sort -rh | head -10

# 查看源文件数量
find . -name "*.cpp" -o -name "*.h" | wc -l
```

### 4. Git 初始化（如还未初始化）

```bash
# 初始化 Git 仓库
git init

# 配置用户信息
git config user.name "Your Name"
git config user.email "your.email@example.com"

# 添加所有文件
git add .

# 首次提交
git commit -m "Initial commit: Landlord Card Game

- Complete game implementation with Qt5 and C++
- AI opponent using DouZero model
- Full game rules support
- Score tracking and statistics
- Cross-platform support (Windows, Linux, macOS)"

# 查看提交历史
git log --oneline
```

## 📋 上传前的最后检查

### 文档完整性

- [ ] README.md - 项目介绍完整
- [ ] BUILD.md - 编译步骤清晰
- [ ] CONTRIBUTING.md - 贡献指南完善
- [ ] LICENSE - 许可证正确
- [ ] CODE_STYLE.md - 代码规范明确

### 代码质量

- [ ] 没有编译警告
- [ ] 代码注释充分
- [ ] 没有硬编码敏感信息
- [ ] 项目能成功编译和运行

### Git 配置

- [ ] .gitignore 正确配置
- [ ] 所有临时文件都被忽略
- [ ] 大文件不在版本控制中
- [ ] 首次提交成功

## 🚀 立即上传的步骤

### 1. 创建 GitHub 仓库

访问 https://github.com/new 并：
- 输入仓库名：`Landlords`
- 选择公开或私有
- **不要** 初始化 README
- 点击 Create

### 2. 本地配置

```bash
# 添加远程仓库（用你的用户名替换 USERNAME）
git remote add origin https://github.com/USERNAME/Landlords.git

# 或使用 SSH（如果已配置）
# git remote add origin git@github.com:USERNAME/Landlords.git

# 验证
git remote -v
```

### 3. 推送到 GitHub

```bash
# 重命名分支为 main（如果不是）
git branch -M main

# 首次推送（创建远程分支）
git push -u origin main

# 验证成功
git branch -vv
```

### 4. 验证上传

访问 `https://github.com/USERNAME/Landlords` 检查：
- [ ] 所有文件都已上传
- [ ] README.md 显示正确
- [ ] 文件夹结构完整
- [ ] Actions 工作流已激活

## 📊 项目统计

运行以下命令获取项目统计：

```bash
# 行数统计
find . -name "*.cpp" -o -name "*.h" -o -name "*.pro" | xargs wc -l | tail -1

# 文件统计
echo "CPP files: $(find . -name "*.cpp" | wc -l)"
echo "Header files: $(find . -name "*.h" | wc -l)"
echo "UI files: $(find . -name "*.ui" | wc -l)"

# Git 统计（初始化后）
git rev-list --all --count
git log --oneline | wc -l
```

## 🔒 安全检查

```bash
# 检查是否有密钥或令牌暴露
git log --all --grep="password\|token\|secret" --oneline

# 检查文件中是否有硬编码的敏感信息
grep -r "password\|token\|api_key" --include="*.cpp" --include="*.h"

# 检查 .env 文件
ls -la .env* 2>/dev/null || echo "No .env files found (good!)"
```

## 🎯 上传后的建议操作

### 1. 启用 GitHub Pages（可选）

```bash
# 如果想要项目网站
# Settings > Pages > GitHub Pages > main branch > Save
```

### 2. 设置分支保护（可选）

```bash
# 在 Settings > Branches 配置：
# - 要求 PR 审查
# - 要求状态检查通过
```

### 3. 添加主题标签

在项目主页右侧点击 "Topics" 添加：
- `game`
- `dou-dizhu`
- `qt`
- `cpp`
- `ai`
- `reinforcement-learning`

### 4. 添加项目描述

在项目主页右侧的 "Description" 中添加：

```
A complete Dou Dizhu card game implementation using Qt5 and C++, 
featuring AI opponent powered by DouZero deep reinforcement learning model.
斗地主纸牌游戏，使用 Qt5/C++ 开发，集成深度学习 AI 对手。
```

## 📞 常见问题

### Q: 上传后想改变仓库是否公开？
A: Settings > Visibility > Change Visibility

### Q: 想更改 README.md？
A: 编辑 README.md，提交，然后 `git push`

### Q: 如何删除已提交的大文件？
A: 使用 `git-filter-branch` 或 `BFG Repo-Cleaner`

### Q: GitHub Actions 工作流为什么没有运行？
A: 确保已经创建了 `.github/workflows/*.yml` 文件并正确配置

## 🎓 下一步学习

- [GitHub 官方教程](https://docs.github.com)
- [Pro Git 电子书](https://git-scm.com/book/en/v2)
- [GitHub Copilot 使用](https://github.com/features/copilot)

---

**现在您已准备好上传项目到 GitHub！** 🚀

如有任何问题，查阅 [GITHUB_UPLOAD.md](GITHUB_UPLOAD.md)
