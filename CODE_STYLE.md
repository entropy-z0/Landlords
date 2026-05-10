# 代码规范指南

本文档定义了项目的代码规范，确保代码质量和一致性。

## C++ 代码规范

### 命名规范

#### 类和结构体
- 使用PascalCase命名
- 示例：`GameControl`, `CardPanel`, `PlayerData`

#### 函数和方法
- 使用camelCase命名
- 示例：`getCardCount()`, `playCard()`, `calculateScore()`

#### 变量和成员
- 使用camelCase命名
- 成员变量前缀用`m_`
- 示例：`m_playerList`, `currentScore`, `isGameRunning`

#### 常量
- 使用UPPER_SNAKE_CASE
- 示例：`MAX_CARD_COUNT`, `DEFAULT_SCORE`

#### 枚举
- 类型使用PascalCase
- 值使用UPPER_SNAKE_CASE
- 示例：`enum class GameState { WAITING, PLAYING, ENDED }`

### 代码风格

#### 缩进和格式
```cpp
// 使用4个空格缩进
if (condition) {
    doSomething();
} else {
    doOtherThing();
}

// 大括号位置
void MyClass::myFunction() {
    // function body
}
```

#### 指针和引用
```cpp
// 指针符号靠近类型
Type* pointer;
Type& reference;
```

#### 注释
```cpp
// 单行注释，注释前有空格

/*
 * 多行注释
 * 每行前缀 * 对齐
 */
```

### Qt 特定规范

#### 信号和槽
```cpp
// 在 .h 文件中声明
signals:
    void cardPlayed(const Card& card);

public slots:
    void onCardSelected(const Card& card);

private slots:
    void updateGameState();
```

#### UI 文件处理
```cpp
// 在 .cpp 中创建UI
m_ui = new Ui::GamePanel();
m_ui->setupUi(this);
```

## 文件组织

### 文件命名
- 头文件：`.h`
- 实现文件：`.cpp`
- Qt设计文件：`.ui`
- 文件名使用小写，单词用下划线分隔（可选），或直接连接

### 文件内容顺序
```cpp
// .h 文件顺序
// 1. 版权和许可证注释
// 2. 包含守卫
// 3. include语句（系统库、Qt库、项目库）
// 4. 前向声明
// 5. 类/结构体定义

// .cpp 文件顺序
// 1. 版权和许可证注释
// 2. include语句
// 3. 命名空间（如果需要）
// 4. 实现代码
```

## 最佳实践

### 内存管理
- 优先使用栈分配
- 使用智能指针管理动态对象
- 避免内存泄漏

```cpp
// 推荐
std::unique_ptr<MyClass> ptr(new MyClass());

// Qt环境下（使用Qt的所有权机制）
MyWidget* widget = new MyWidget(this);  // this作为父对象
```

### 错误处理
```cpp
// 验证参数
if (!isValidCard(card)) {
    qWarning() << "Invalid card:" << card;
    return false;
}
```

### 日志输出
```cpp
// 使用 Qt 的日志系统
qDebug() << "Debug message:" << variable;
qWarning() << "Warning message";
qCritical() << "Critical error";
```

## 代码审查检查清单

- [ ] 代码遵循命名规范
- [ ] 包含必要的注释和文档
- [ ] 没有硬编码的魔法数字（使用常量）
- [ ] 错误处理完整
- [ ] 没有内存泄漏
- [ ] 代码是可读的
- [ ] 没有未使用的变量或函数
- [ ] 编译没有警告

## 更新规范文件

如果发现规范需要更新，请通过Pull Request提议改进。
