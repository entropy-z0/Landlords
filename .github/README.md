# 斗地主游戏 - GitHub 项目配置

## 项目信息

此项目配置用于优化 GitHub 上的项目展示。

## 特性

- ✅ 自动化构建和测试
- ✅ 代码质量检查
- ✅ 问题模板
- ✅ 贡献指南

## 目录结构

```
.github/
├── workflows/          # GitHub Actions 工作流
│   ├── build.yml      # 构建和发布流程
│   └── code-quality.yml # 代码质量检查
└── ISSUE_TEMPLATE/     # Issue 模板
    ├── bug_report.yml  # Bug 报告模板
    └── feature_request.yml # 功能建议模板
```

## 工作流说明

### build.yml
- 自动在 push 和 pull_request 时运行
- 在 Windows 和 Linux 上构建
- 支持发布版本打包

### code-quality.yml
- 运行代码静态分析
- 检查代码格式
- 防止低质量代码合并

## 配置修改

如需修改工作流配置，请编辑 `workflows/` 目录中的 YAML 文件。

## 更多信息

- [GitHub Actions 文档](https://docs.github.com/en/actions)
- [工作流语法](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions)
