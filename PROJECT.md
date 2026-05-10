# Landlords Game

## 项目目标

创建一个功能完整的斗地主游戏，集成AI对手，提供良好的用户体验。

## 核心需求

- [x] 完整的游戏规则实现
- [x] 图形用户界面
- [x] 人机对战功能
- [x] 游戏得分统计
- [x] AI模型集成

## 技术栈

- **前端**: Qt 5 C++
- **AI**: DouZero 深度强化学习
- **构建**: qmake/cmake
- **平台**: Windows, Linux, macOS

## 核心模块

### GameControl（游戏控制器）
- 游戏流程管理
- 出牌逻辑处理
- 游戏状态机
- 得分计算

### Card & PlayHand（牌和手型）
- 牌的表示和管理
- 手型识别
- 手型比较

### Player & Robot（玩家和机器人）
- 玩家基类
- 用户玩家实现
- AI机器人实现
- 出牌策略

### UI Components（界面组件）
- GamePanel（游戏面板）
- CardPanel（卡牌显示）
- ScorePanel（得分面板）
- EndingPanel（结束面板）

## 游戏规则支持

✅ 所有标准牌型
✅ 完整的出牌规则
✅ 正确的得分计算
✅ 炸弹倍数机制

## 已实现特性

1. **游戏流程**
   - 发牌
   - 抢地主
   - 出牌
   - 结算

2. **用户界面**
   - 卡牌展示
   - 实时状态显示
   - 得分统计

3. **AI功能**
   - DouZero模型集成
   - 智能出牌

4. **游戏配置**
   - 难度设置（可扩展）
   - 游戏参数调整

## 待实现特性

- [ ] 多人在线对战
- [ ] 更多游戏模式
- [ ] 游戏回放
- [ ] 成就系统
- [ ] 排行榜
- [ ] 移动端适配
- [ ] 国际化

## 文件结构

```
src/
├── core/          # 核心游戏逻辑
├── ui/            # 用户界面
├── ai/            # AI模块
└── utils/         # 工具函数
```

## 构建指令

```bash
# Debug 构建
qmake Landlords.pro
make debug

# Release 构建
qmake Landlords.pro -config release
make release
```

## 测试

- 单元测试
- 集成测试
- UI测试

## 部署

- Windows 安装程序
- Linux 包
- macOS DMG

## 问题追踪

所有问题和任务通过 GitHub Issues 追踪。

## 贡献

参见 CONTRIBUTING.md
