# Landlords Game - 项目规划文档

## 项目信息

- **项目名称**：Landlords（斗地主游戏）
- **学校**: 深圳香港中文大学 (CUHKSZ)
- **课程**: CSC3002 - C/C++ Programming
- **项目类型**: 小组作业
- **技术栈**：Qt 5, C++, DouZero AI
- **许可证**：LGPL v3
- **状态**：✅ 功能完整，已发布

## 项目目标

创建一个功能完整的斗地主游戏，集成AI对手，提供良好的用户体验，展示C++编程和Qt GUI开发的最佳实践。

## 核心需求

- [x] 完整的游戏规则实现
- [x] 图形用户界面
- [x] 人机对战功能
- [x] 游戏得分统计
- [x] AI模型集成

## 技术栈

### 前端
- **框架**: Qt 5.15.2
- **语言**: C++11
- **UI**: Qt Widgets
- **构建**: qmake

### 后端
- **AI**: DouZero 深度强化学习
- **模型**: 预训练的斗地主策略模型
- **脚本**: Python 集成

### 平台支持
- Windows (MinGW)
- Linux (GCC)
- macOS (Clang)

## 核心模块架构

### GameControl（游戏控制器）
- 游戏流程管理
- 出牌逻辑处理
- 游戏状态机
- 得分计算
- 玩家轮次管理

### Card & PlayHand（牌和手型）
- 牌的表示和管理
- 手型识别和验证
- 手型比较规则
- 牌型合法性检查

### Player & Robot（玩家和机器人）
- 玩家基类
- 用户玩家实现（鼠标交互）
- AI机器人实现（DouZero集成）
- 出牌策略和决策

### UI Components（界面组件）
- GamePanel（游戏主面板）
- CardPanel（卡牌显示）
- ScorePanel（得分面板）
- EndingPanel（游戏结束面板）
- ButtonGroup（按钮组）

## 游戏规则支持

✅ 所有标准牌型
  - 单牌、对牌、三张
  - 三带一、三带二
  - 顺子、连对、飞机
  - 飞机带翅膀、四带二
  - 王炸、炸弹

✅ 完整的出牌规则
  - 牌型匹配
  - 大小比较
  - 炸弹压制

✅ 正确的得分计算
  - 底分计算
  - 炸弹倍数翻倍
  - 地主和农民分数结算

✅ 炸弹倍数机制
  - 每个炸弹翻倍
  - 王炸加倍

## 已实现特性

### 游戏流程
- [x] 发牌流程
- [x] 抢地主流程
- [x] 出牌流程
- [x] 结算流程
- [x] 重新开始

### 用户界面
- [x] 卡牌展示
- [x] 实时状态显示
- [x] 得分统计
- [x] 动画效果
- [x] 音效反馈

### AI功能
- [x] DouZero模型集成
- [x] 智能出牌
- [x] 实时决策
- [x] 难度配置

### 游戏配置
- [x] 难度设置（可扩展）
- [x] 游戏参数调整
- [x] 音效开关

## 待实现特性

- [ ] 多人在线对战（网络模块）
- [ ] 更多游戏模式（PvP、排位赛）
- [ ] 游戏回放功能（录制和回放）
- [ ] 成就系统（徽章、解锁）
- [ ] 排行榜（云端同步）
- [ ] 移动端适配（Android/iOS）
- [ ] 国际化支持（多语言）
- [ ] 主题系统（UI换肤）

## 文件结构

```
Landlords/
├── 源代码文件 (*.cpp, *.h)
│   ├── gamecontrol.* - 游戏主控制
│   ├── gamepanel.*   - 游戏面板
│   ├── card.*        - 卡牌类
│   ├── player.*      - 玩家基类
│   ├── userplayer.*  - 用户玩家
│   ├── robot.*       - AI机器人
│   ├── playhand.*    - 出牌手型
│   └── ... 其他UI组件
├── UI设计文件 (*.ui)
│   ├── gamepanel.ui
│   ├── buttongroup.ui
│   └── scorepanel.ui
├── 资源文件
│   ├── res.qrc       - 资源索引
│   ├── images/       - 图片资源
│   └── sounds/       - 音效资源
├── 构建文件
│   ├── Landlords.pro - Qt项目文件
│   └── build/        - 编译输出
├── AI模块
│   ├── DouZero_API-main/ - AI库
│   └── test.py       - 测试脚本
├── 文档
│   ├── README.md     - 中文说明
│   ├── README_EN.md  - 英文说明
│   ├── BUILD.md      - 编译指南
│   └── ... 其他文档
└── LICENSE           - LGPL v3 许可证
```

## 构建和部署

### 编译指令

```bash
# Debug 构建
qmake Landlords.pro
make debug

# Release 构建
qmake Landlords.pro -config release
make release

# 清理
make clean
```

### 部署策略

#### Windows
- MinGW 编译
- 静态链接 Qt 库（可选）
- 生成 EXE 安装程序
- 上传到 Release

#### Linux
- GCC 编译
- 生成 AppImage 或 DEB 包
- 支持依赖管理

#### macOS
- Clang 编译
- 打包为 .app 束
- 生成 DMG 安装镜像

## 代码质量标准

- **编码规范**: 遵循 CODE_STYLE.md
- **注释**: 每个关键函数都有文档注释
- **测试**: 单元测试和集成测试
- **错误处理**: 完整的异常处理
- **性能**: 优化渲染和AI决策速度

## 时间安排

- **第1周**: 需求分析、架构设计
- **第2-3周**: 核心游戏逻辑实现
- **第4周**: UI界面开发
- **第5周**: AI集成和测试
- **第6周**: 优化和文档完善

## 学习成果

通过本项目，学生应该掌握：

1. **C++编程**
   - 面向对象设计
   - 内存管理
   - STL使用
   - 现代C++特性

2. **Qt框架**
   - GUI应用开发
   - 信号和槽机制
   - UI设计
   - 资源管理

3. **游戏开发**
   - 游戏逻辑设计
   - 状态机设计
   - 动画和效果
   - 用户交互

4. **AI集成**
   - 深度学习模型使用
   - Python-C++交互
   - 决策系统

5. **项目管理**
   - 版本控制
   - 文档编写
   - 代码审查
   - 部署发布

## 常见问题

### Q: 为什么选择 Qt？
A: Qt 是跨平台 GUI 开发的最佳选择，具有：
- 优秀的 C++ 支持
- 完整的 UI 组件库
- 强大的信号槽机制
- 广泛的社区支持

### Q: DouZero AI 如何集成？
A: 通过 Python-C++ 交互：
- C++ 调用 Python 脚本获取 AI 决策
- 使用预训练模型
- 异步执行以保持 UI 响应

### Q: 项目规模多大？
A: 约 3000+ 行 C++ 代码，展示了完整的应用开发流程

## 文件清单

### 核心代码文件 (14 对 .h/.cpp)
- gamecontrol, gamepanel, cardpanel
- card, cards, playhand
- player, userplayer, robot
- robotgraplord, robotplayhand
- scorepanel, endingpanel
- buttongroup, mybutton

### 配置文件
- Landlords.pro (Qt 项目文件)
- .gitignore (Git 配置)

### 文档文件
- README.md (中文)
- README_EN.md (英文)
- BUILD.md (编译)
- CODE_STYLE.md (规范)
- CONTRIBUTING.md (贡献)
- CHANGELOG.md (更新日志)
- SECURITY.md (安全)
- PROJECT.md (本文档)

## 参考资源

- [Qt 官方文档](https://doc.qt.io/)
- [C++ 参考](https://en.cppreference.com/w/)
- [DouZero 项目](https://github.com/kwai/DouZero)
- [斗地主规则](https://baike.baidu.com/item/斗地主)

---

**最后更新**: 2024年

本项目展示了 C++ 和 Qt 框架在实际应用开发中的应用，是学习现代 C++ GUI 编程的完整案例。

