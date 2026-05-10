# 斗地主游戏 (Landlord Card Game)

![License](https://img.shields.io/badge/license-LGPL%20v3-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Qt](https://img.shields.io/badge/Qt-5.15.2-blue)

一款使用Qt5和C++开发的斗地主游戏，集成了基于深度强化学习的AI对手（DouZero）。这是一个完整的单机版斗地主游戏实现，支持人机对战。

![Game Preview](README/landlord-bk.png)

## 🎮 功能特性

### 核心游戏功能
- ✅ 完整的斗地主游戏规则实现
- ✅ 图形化用户界面
- ✅ 人机对战
- ✅ 游戏得分统计
- ✅ 音效支持

### AI功能
- 🤖 集成DouZero深度学习模型
- 🧠 智能出牌策略
- 📊 多种AI难度（可扩展）

### 用户界面
- 🎨 美观的卡牌界面
- 📱 友好的游戏操作
- 📈 实时得分显示
- 🎯 清晰的游戏流程提示

## 🎯 游戏规则概览

### 基本牌型
| 牌型 | 描述 |
|------|------|
| 王炸 | 大王+小王，最大的牌 |
| 炸弹 | 四张同数值牌 |
| 单牌 | 单张的牌 |
| 对牌 | 数值相同的两张牌 |
| 三张牌 | 数值相同的三张牌 |
| 三带一 | 三张+1张单牌 |
| 三带二 | 三张+1对牌 |
| 顺子 | 五张或更多的连续单牌 |
| 连对 | 三对或更多的连续对牌 |
| 飞机 | 两个或更多的连续三张牌 |

### 游戏角色
- **地主**（1人）：三人下注抢地主，分数最高者为地主
- **农民**（2人）：没有抢到地主的玩家为农民

### 游戏流程
1. 发牌：一人17张，3张做底牌
2. 抢地主：轮流叫地主，分数分别为1分、2分、3分
3. 出牌：地主首先出牌，然后按逆时针顺序出牌
4. 计分：根据底分和倍数（炸弹翻倍）计算得分

详细规则请参考 [游戏规则文档](README.md)

## 🚀 快速开始

### 系统要求
- **操作系统**: Windows, Linux, macOS
- **Qt**: 5.12 或更高版本
- **编译器**: MinGW (Windows) / GCC (Linux) / Clang (macOS)
- **C++ 标准**: C++11 或更高

### 快速安装

#### Windows
1. 安装 [Qt Creator](https://www.qt.io/download-open-source)
2. 打开 `Landlords.pro` 项目文件
3. 选择编译配置（Debug 或 Release）
4. 点击 Build > Build Project
5. 运行游戏

#### Linux/macOS
```bash
# 安装 Qt（以Ubuntu为例）
sudo apt-get install qt5-default qt5-qmake

# 编译项目
cd Landlords
qmake Landlords.pro
make

# 运行游戏
./Landlords
```

详细编译指南请参考 [BUILD.md](BUILD.md)

## 🤖 AI模型使用

项目集成了DouZero AI模型。如要启用AI功能：

```bash
# 安装Python依赖
pip install -r requirements.txt

# 确保模型文件在正确位置
# DouZero_API-main/baselines/ 目录
```

## 📁 项目结构

```
Landlords/
├── *.h, *.cpp          # 游戏核心代码
├── *.ui                # Qt UI 设计文件
├── res.qrc             # 资源文件
├── Landlords.pro       # Qt 项目配置文件
├── test.py             # Python测试脚本
├── DouZero_API-main/   # AI模型库
├── images/             # 游戏图片资源
├── README.md           # 详细文档
├── BUILD.md            # 编译指南
├── CONTRIBUTING.md     # 贡献指南
└── LICENSE             # 许可证 (LGPL v3)
```

### 主要类说明

| 类名 | 说明 |
|------|------|
| `GameControl` | 游戏主控制器 |
| `GamePanel` | 游戏显示面板 |
| `Card` | 卡牌类 |
| `Player` | 玩家基类 |
| `UserPlayer` | 用户玩家 |
| `Robot` | AI机器人 |
| `PlayHand` | 出牌手型 |

## 🎮 游戏操作

### 用户操作
- **点击卡牌**: 选择/取消选择卡牌
- **出牌按钮**: 确认出牌
- **不出按钮**: 跳过本轮
- **提示按钮**: 获得智能出牌建议

## 📊 游戏统计

游戏会自动记录：
- 每局得分
- 赢家统计
- 总获胜次数
- 游戏时间统计

## 🐛 已知问题

- 某些特殊组合的牌型检测可能有边界情况
- AI模型在特定场景下的表现可进一步优化

欢迎提交Issue报告问题！

## 📝 许可证

本项目采用 **LGPL v3** 许可证。详见 [LICENSE](LICENSE) 文件。

## 🤝 贡献

欢迎各种形式的贡献！请参考 [贡献指南](CONTRIBUTING.md)

### 贡献方式
1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 📞 联系我们

- 提交 [Issue](../../issues) 报告问题
- 讨论 [Discussions](../../discussions) 分享想法

## 🙏 致谢

- Qt 框架
- DouZero 深度强化学习库
- 所有贡献者

## 🗺️ 开发计划

- [ ] 多人在线对战
- [ ] 更多游戏模式
- [ ] 移动端适配
- [ ] 国际化支持
- [ ] 游戏回放功能
- [ ] 成就系统

---

**最后更新**: 2024年

如有任何问题或建议，欢迎通过 Issues 联系我们！
