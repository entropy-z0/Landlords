# Landlord Card Game (斗地主游戏)

![License](https://img.shields.io/badge/license-LGPL%20v3-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Qt](https://img.shields.io/badge/Qt-5.15.2-blue)
![Course](https://img.shields.io/badge/CUHKSZ-CSC3002-green)

> **📚 Course Project**: This project is a group assignment for CSC3002 C/C++ Programming course at The Chinese University of Hong Kong, Shenzhen (CUHKSZ)

A complete Dou Dizhu (Landlord) card game implementation developed with Qt5 and C++, featuring an AI opponent powered by DouZero deep reinforcement learning model. This is a fully-featured single-player card game with human-computer gameplay.

## 🎮 Features

### Core Game Functionality
- ✅ Complete Dou Dizhu game rules implementation
- ✅ Graphical user interface
- ✅ Human vs AI gameplay
- ✅ Game score tracking and statistics
- ✅ Sound effects support

### AI Features
- 🤖 Integrated DouZero deep learning model
- 🧠 Intelligent card play strategy
- 📊 Multiple difficulty levels (extensible)

### User Interface
- 🎨 Beautiful card game interface
- 📱 User-friendly operations
- 📈 Real-time score display
- 🎯 Clear game flow prompts

## 📚 Project Information

- **University**: The Chinese University of Hong Kong, Shenzhen (CUHKSZ)
- **Course**: CSC3002 - C/C++ Programming
- **Project Type**: Group Assignment
- **Programming Language**: C++ (Qt Framework)
- **License**: LGPL v3

## 🎯 Game Rules Overview

### Basic Card Types
| Card Type | Description |
|-----------|-------------|
| Rocket (王炸) | Big Joker + Small Joker, highest rank |
| Bomb (炸弹) | Four cards of the same rank |
| Single (单牌) | Single card |
| Pair (对牌) | Two cards of the same rank |
| Triple (三张牌) | Three cards of the same rank |
| Triple + 1 (三带一) | Three + 1 single |
| Triple + 2 (三带二) | Three + 1 pair |
| Straight (顺子) | Five or more consecutive singles (no 2s/Jokers) |
| Straight Pair (连对) | Three or more consecutive pairs (no 2s/Jokers) |
| Airplane (飞机) | Two or more consecutive triples (no 2s/Jokers) |

### Game Roles
- **Landlord** (1 player): Highest bidder in the auction phase, plays alone
- **Peasants** (2 players): Other players, team up to beat the landlord

### Game Flow
1. **Deal**: 17 cards per player, 3 cards in the bottom
2. **Auction**: Players bid for the landlord role (1, 2, or 3 points)
3. **Play**: Landlord plays first, then players take turns playing cards
4. **Scoring**: Calculate points based on base score and multipliers (bombs double the score)

## 🚀 Quick Start

### System Requirements
- **Operating System**: Windows, Linux, or macOS
- **Qt**: 5.12 or higher
- **Compiler**: MinGW (Windows) / GCC (Linux) / Clang (macOS)
- **C++ Standard**: C++11 or higher

### Quick Installation

#### Windows - Option 1: Pre-built Executable
Download `Landlords.exe` from the [Releases](../../releases) page and run directly (Windows 10/11).

#### Windows - Option 2: Build from Source
1. Install [Qt Creator](https://www.qt.io/download-open-source)
2. Open `Landlords.pro` project file
3. Select build configuration (Debug or Release)
4. Click Build > Build Project
5. Run the game

#### Linux/macOS
```bash
# Install Qt (Ubuntu example)
sudo apt-get install qt5-default qt5-qmake

# Build project
cd Landlords
qmake Landlords.pro
make

# Run game
./Landlords
```

For detailed build instructions, see [BUILD.md](BUILD.md)

## 🤖 AI Model Setup

The project integrates the DouZero AI model. To enable AI features:

```bash
# Install Python dependencies
pip install -r requirements.txt

# Ensure model files are in correct location
# Place model files in: DouZero_API-main/baselines/
```

## 📁 Project Structure

```
Landlords/
├── *.h, *.cpp              # Game core implementation
├── *.ui                    # Qt UI design files
├── res.qrc                 # Resource files
├── Landlords.pro           # Qt project configuration
├── test.py                 # Python test script
├── DouZero_API-main/       # AI model library
├── images/                 # Game image resources
├── README.md               # Detailed documentation (Chinese)
├── BUILD.md                # Build and installation guide
├── CONTRIBUTING.md         # Contribution guidelines
├── CODE_STYLE.md           # Code style guide
└── LICENSE                 # License (LGPL v3)
```

### Main Classes

| Class | Purpose |
|-------|---------|
| `GameControl` | Main game controller |
| `GamePanel` | Game display panel |
| `Card` | Card representation |
| `Player` | Player base class |
| `UserPlayer` | Human player |
| `Robot` | AI player |
| `PlayHand` | Card play hand |

## 🎮 Game Operations

### User Controls
- **Click card**: Select/deselect card
- **Play button**: Confirm card play
- **Pass button**: Skip current turn
- **Hint button**: Get AI suggestion for best play

## 📊 Game Statistics

The game automatically records:
- Score per game
- Win/loss statistics
- Total wins
- Game duration statistics

## 🐛 Known Issues

- Some edge cases in card type detection may exist
- AI model performance can be further optimized in specific scenarios

We welcome bug reports via [Issues](../../issues)!

## 💻 Technical Stack

### Frontend
- **Framework**: Qt 5.15.2
- **Language**: C++11
- **UI Framework**: Qt Widgets
- **Graphics**: Qt Graphics View
- **Multimedia**: Qt Multimedia

### AI Backend
- **Model**: DouZero (Deep Reinforcement Learning)
- **Language**: Python
- **Dependencies**: PyTorch, NumPy

### Build System
- **Qt Tools**: qmake, Qt Creator

## 🔧 Development

### Building from Source

**Windows (MinGW):**
```bash
cd Landlords
qmake Landlords.pro
mingw32-make
```

**Linux:**
```bash
cd Landlords
qmake Landlords.pro
make
```

### Code Style
Please refer to [CODE_STYLE.md](CODE_STYLE.md) for our coding conventions.

## 🤝 Contributing

We welcome all kinds of contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md)

### How to Contribute
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📞 Contact & Support

- Submit [Issues](../../issues) to report bugs or suggest features
- Join [Discussions](../../discussions) to share ideas
- Check [FAQ](BUILD.md#troubleshooting) for common issues

## 🙏 Acknowledgments

- Qt Framework and Qt Creator community
- DouZero project and contributors
- CUHKSZ CSC3002 course instructors
- All project contributors

## 📚 Documentation

- [中文 README](README.md) - Chinese documentation
- [Build Guide](BUILD.md) - Detailed build instructions
- [Code Style](CODE_STYLE.md) - C++ coding conventions
- [Contributing Guide](CONTRIBUTING.md) - How to contribute
- [Changelog](CHANGELOG.md) - Version history

## 🗺️ Future Plans

- [ ] Multiplayer online play
- [ ] Additional game modes
- [ ] Mobile port
- [ ] Internationalization support
- [ ] Game replay functionality
- [ ] Achievement system
- [ ] Ranking leaderboard

## 📜 License

This project is licensed under the **LGPL v3** License - see the [LICENSE](LICENSE) file for details.

LGPL v3 License allows:
- ✅ Commercial use
- ✅ Modification
- ✅ Distribution
- ⚠️ Must disclose source and license

---

**Last Updated**: 2024

**For Chinese documentation, please see [README.md](README.md)**

If you have any questions or suggestions, feel free to reach out through [Issues](../../issues) or [Discussions](../../discussions)! 🎉
