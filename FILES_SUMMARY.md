# GitHub 项目文件清单

本文档总结了为上传到 GitHub 而创建的所有文件及其用途。

## 📋 核心文件清单

### 根目录文件

| 文件名 | 说明 | 优先级 |
|--------|------|--------|
| `.gitignore` | Git 忽略规则 | ⭐⭐⭐ 必须 |
| `README.md` | 项目主文档（中文） | ⭐⭐⭐ 必须 |
| `README_EN.md` | 项目主文档（英文版本） | ⭐⭐ 推荐 |
| `LICENSE` | LGPL v3 许可证 | ⭐⭐⭐ 必须 |
| `BUILD.md` | 编译安装指南 | ⭐⭐ 推荐 |
| `CONTRIBUTING.md` | 贡献指南 | ⭐⭐ 推荐 |
| `CODE_STYLE.md` | 代码规范指南 | ⭐⭐ 推荐 |
| `PROJECT.md` | 项目规划和架构 | ⭐ 参考 |
| `CHANGELOG.md` | 版本更新日志 | ⭐⭐ 推荐 |
| `SECURITY.md` | 安全政策 | ⭐ 参考 |
| `GITHUB_UPLOAD.md` | GitHub 上传指南 | ⭐ 本地用 |
| `requirements.txt` | Python 依赖 | ⭐⭐ 推荐 |
| `.env.example` | 环境变量示例 | ⭐ 可选 |
| `.qmake.conf` | Qt 编译配置 | ⭐ 参考 |

### .github 目录文件

#### `.github/workflows/`
| 文件名 | 说明 | 功能 |
|--------|------|------|
| `build.yml` | 构建工作流 | 自动构建和发布 |
| `code-quality.yml` | 代码质量检查 | 静态分析、格式检查 |

#### `.github/ISSUE_TEMPLATE/`
| 文件名 | 说明 |
|--------|------|
| `bug_report.yml` | Bug 报告模板 |
| `feature_request.yml` | 功能建议模板 |

#### `.github/`
| 文件名 | 说明 |
|--------|------|
| `README.md` | GitHub 配置说明 |

## 📂 文件详细说明

### 必须文件

#### `.gitignore`
- **作用**：排除不需要上传的文件
- **包含**：
  - 编译输出（build/、release/、*.o）
  - IDE 文件（.vscode/、.idea/）
  - 操作系统文件（.DS_Store、Thumbs.db）
  - 执行文件和 DLL
  - Python 缓存

#### `LICENSE`
- **作用**：定义项目许可证（LGPL v3）
- **重要性**：指定项目可以如何使用和修改

#### `README.md`
- **作用**：项目主入口文档
- **包含**：
  - 项目介绍
  - 功能列表
  - 快速开始
  - 项目结构
  - 许可证信息

### 推荐文件

#### `BUILD.md`
- **作用**：详细的编译安装指南
- **目标用户**：想要从源代码编译的开发者

#### `CONTRIBUTING.md`
- **作用**：贡献指南
- **内容**：如何报告 bug、提交功能、提交 PR

#### `CODE_STYLE.md`
- **作用**：代码规范
- **用途**：保持代码一致性和质量

#### `CHANGELOG.md`
- **作用**：版本更新日志
- **更新频率**：每次发布新版本时更新

### 自动化文件

#### GitHub Actions 工作流
- 自动在 push 和 pull_request 时运行
- 可自动构建、测试、发布
- 提高项目质量和可靠性

#### Issue 模板
- 规范 Issue 提交格式
- 方便问题追踪和处理

## 🚀 使用建议

### 本地开发

1. 复制 `.env.example` 为 `.env`
2. 根据需要修改配置
3. 遵循 `CODE_STYLE.md` 编写代码

### 首次提交

```bash
# 初始化
git init
git add .
git commit -m "Initial commit"
git remote add origin <github-url>
git push -u origin main
```

### 版本发布

1. 更新 `CHANGELOG.md`
2. 创建 Git 标签：`git tag v1.0.0`
3. 推送标签：`git push origin v1.0.0`
4. GitHub Actions 会自动构建和发布

## 📚 文件维护

### 需要定期更新的文件

| 文件 | 更新时机 | 负责人 |
|------|---------|--------|
| `README.md` | 项目有重大变更 | 项目维护者 |
| `CHANGELOG.md` | 每次发布新版本 | 项目维护者 |
| `BUILD.md` | 编译流程变更 | 开发者 |
| `CODE_STYLE.md` | 编码规范调整 | 核心开发者 |

### 无需更新的文件

- `.gitignore`（通常不变）
- `LICENSE`（除非更改许可证）
- `.github/` 配置（除非更改 CI/CD）

## 🔍 检查清单

上传前请确认：

- [ ] `.gitignore` 已正确配置
- [ ] `README.md` 内容完整准确
- [ ] `LICENSE` 文件存在
- [ ] 代码符合 `CODE_STYLE.md` 规范
- [ ] `build/` 等临时文件已忽略
- [ ] 敏感信息不在版本控制中
- [ ] 所有文档都是最新的

## 📞 快速参考

### 关键文件修改

- 需要改进项目说明 → 修改 `README.md`
- 需要更新编译步骤 → 修改 `BUILD.md`
- 需要发布新版本 → 更新 `CHANGELOG.md`
- 需要改进代码规范 → 更新 `CODE_STYLE.md`
- 需要添加安全策略 → 修改 `SECURITY.md`

### 常见操作

```bash
# 查看要提交的文件
git status

# 查看某个文件的更改
git diff README.md

# 查看提交历史
git log --oneline

# 添加标签
git tag v1.0.0
git push origin v1.0.0
```

---

**提示**：定期更新这个清单以反映项目的实际情况。
