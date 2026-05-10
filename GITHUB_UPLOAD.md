# GitHub 上传指南

本文档指导您如何将项目上传到 GitHub。

## 前置准备

### 1. 安装 Git
- **Windows**: 下载 [Git for Windows](https://git-scm.com/download/win)
- **Linux**: `sudo apt-get install git`
- **macOS**: `brew install git`

### 2. 配置 Git

```bash
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

### 3. 创建 GitHub 账户

访问 [GitHub](https://github.com) 注册账户。

### 4. 生成 SSH 密钥（可选但推荐）

```bash
ssh-keygen -t ed25519 -C "your.email@example.com"
# 按照提示完成（一般一直按 Enter）

# 复制公钥内容
cat ~/.ssh/id_ed25519.pub
# Windows: type %USERPROFILE%\.ssh\id_ed25519.pub

# 在 GitHub Settings > SSH and GPG keys 中添加公钥
```

## 上传步骤

### 1. 在 GitHub 创建新仓库

1. 登录 GitHub
2. 点击 `+` 图标 > `New repository`
3. 输入仓库名称：`Landlords`（或其他名称）
4. 选择 `Public` 或 `Private`
5. **不要** 勾选 "Initialize this repository with"
6. 点击 `Create repository`

### 2. 初始化本地 Git 仓库

```bash
# 进入项目目录
cd f:\Landlords\Landlords

# 初始化 git
git init

# 添加所有文件
git add .

# 首次提交
git commit -m "Initial commit: Add Landlord card game"
```

### 3. 连接远程仓库

```bash
# 添加远程仓库（用 SSH 或 HTTPS）

# 方式一：使用 SSH（如果已配置）
git remote add origin git@github.com:your-username/Landlords.git

# 方式二：使用 HTTPS
git remote add origin https://github.com/your-username/Landlords.git
```

替换 `your-username` 为您的 GitHub 用户名。

### 4. 上传到 GitHub

```bash
# 第一次推送（创建远程分支）
git branch -M main
git push -u origin main

# 后续推送
git push
```

## 验证上传成功

1. 访问 `https://github.com/your-username/Landlords`
2. 确认所有文件都已上传
3. 检查 README.md 是否正确显示

## 常见问题

### 问题：权限拒绝 (Permission denied)

**解决方案**：
- 如果使用 SSH，检查 SSH 密钥是否正确配置
- 或使用 HTTPS 方式（会要求输入 token）
- 参考：[GitHub 认证文档](https://docs.github.com/en/authentication)

### 问题：Could not resolve host

**解决方案**：
- 检查网络连接
- 尝试：`git config --global --unset https.proxy`

### 问题：文件太大无法上传

**解决方案**：
- 删除 `build/` 目录（应该已在 .gitignore 中）
- 使用 [Git LFS](https://git-lfs.github.com/) 处理大文件

## 上传后的操作

### 1. 添加项目描述

1. 进入项目主页
2. 点击 `Settings`
3. 在 "Description" 中添加简短描述
4. 添加 Topics（标签）：`game`, `dou-dizhu`, `qt`, `cpp`, `ai`

### 2. 启用 GitHub Pages（可选）

如果要创建项目网站：
1. Settings > Pages
2. 选择分支和目录
3. 保存后会生成网站 URL

### 3. 启用 GitHub Actions

项目中已包含 CI/CD 配置，GitHub Actions 会自动运行。

检查状态：项目主页 > Actions 标签

### 4. 配置分支保护（可选）

1. Settings > Branches
2. 点击 "Add rule"
3. 为 `main` 分支设置保护规则
4. 要求 Pull Request review（推荐）

## 后续开发工作流

### 创建特性分支

```bash
# 创建并切换到新分支
git checkout -b feature/new-feature

# 完成开发后，提交
git add .
git commit -m "Add new feature"
git push origin feature/new-feature

# 在 GitHub 上创建 Pull Request
```

### 拉取他人更改

```bash
git pull origin main
```

## 常用 Git 命令

```bash
# 查看状态
git status

# 查看差异
git diff

# 查看提交历史
git log

# 撤销最后一次提交（未 push）
git reset --soft HEAD~1

# 撤销所有本地更改
git checkout -- .

# 克隆仓库
git clone https://github.com/your-username/Landlords.git
```

## 进阶：使用 GitHub CLI

```bash
# 安装 GitHub CLI（可选）
# https://cli.github.com/

# 登录
gh auth login

# 创建仓库
gh repo create Landlords --public

# 推送
git push
```

## 贡献指南

详见项目中的 [CONTRIBUTING.md](CONTRIBUTING.md)

---

**祝您成功上传项目！** 🎉

如有任何问题，欢迎查阅：
- [GitHub 文档](https://docs.github.com)
- [Pro Git 电子书](https://git-scm.com/book/en/v2)
