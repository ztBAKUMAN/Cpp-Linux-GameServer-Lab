# Cpp-Linux-GameServer-Lab
> **From Modern C++ to Linux System Programming: Building an AI-enhanced game server.**
> **To imbue game characters with "souls" for truly lifelike interactions.**

> **从现代 C++ 到 Linux 系统编程：构建一个带有 AI 推理的游戏服务器。**
> **尝试赋予游戏角色“灵魂”，让交互接近真实。**

# Cpp-Linux-GameServer-Lab 🎮

![Language](https://img.shields.io/badge/language-C%2B%2B17%2F20-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Embedded-lightgrey.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![Status](https://img.shields.io/badge/status-Active-orange.svg)

> **Constructing a high-performance game server architecture from scratch.** > **从零构建高性能 C++ 游戏服务器架构之路。**

## 📖 Introduction (项目介绍)

**Cpp-Linux-GameServer-Lab** is an engineering laboratory dedicated to mastering **Modern C++** and **Linux System Programming**. This project serves as a proving ground for building "Project Soul" — a distributed game server architecture.

It bridges the gap between basic syntax and industrial-level implementation, covering:
* **Memory Management**: RAII, Smart Pointers, and Custom Memory Pools.
* **Concurrency**: Thread Pools, Actor Model, and Lock-free structures.
* **Networking**: Reactor pattern based on Epoll and Non-blocking I/O.
* **Architecture**: From monolithic services to microservices.

本项目是一个专注于 **现代 C++** 与 **Linux 系统编程** 的工程实验室。它是由于我个人的 "Project Soul" (灵魂计划) 衍生出的技术验证基地。
本项目旨在填补“语法基础”到“工业级实战”之间的空白，核心覆盖：
* **内存管理**: RAII、智能指针与自定义内存池。
* **并发模型**: 线程池、Actor 模型与无锁数据结构。
* **网络编程**: 基于 Epoll 与非阻塞 I/O 的 Reactor 模式。
* **架构演进**: 从单体服务到微服务架构的探索。

## 🗺️ Roadmap (技术路线图)

### Phase 1: Modern C++ Core (Language Foundation)
*Refactoring legacy C habits into Modern C++ thinking.*
- [x] **Day 01-05**: Environment Setup (CMake/GCC) & Project Engineering.
- [ ] **Smart Pointers**: `std::unique_ptr`, `std::shared_ptr` deep dive.
- [ ] **STL & Algorithms**: Lambda expressions, functional patterns.
- [ ] **OOP**: Polymorphism, Virtual Table internals.

### Phase 2: Linux System Programming (Kernel & OS)
*Understanding the OS underneath the code.*
- [ ] **Process Management**: `fork`, `exec`, Zombie process handling.
- [ ] **IPC**: Shared Memory, Pipes, and Signals.
- [ ] **System Calls**: Direct interaction with Linux Kernel.

### Phase 3: High-Performance Networking (The Core)
*Building the engine.*
- [ ] **Socket API**: TCP/UDP protocols.
- [ ] **IO Multiplexing**: Epoll (Level Triggered vs Edge Triggered).
- [ ] **Reactor Model**: Event-driven architecture implementation.

### Phase 4: Project Soul (Architecture)
*The final integration.*
- [ ] **Game Logic**: State machines and ECS (Entity Component System).
- [ ] **Edge AI**: Integrating NPU inference for game AI.

## 🛠️ Build & Run (构建指南)

This project uses **CMake** for build configuration.

```bash
# 1. Clone the repo
git clone [https://github.com/ztBAKUMAN/Cpp-Linux-GameServer-Lab.git](https://github.com/ztBAKUMAN/Cpp-Linux-GameServer-Lab.git)

# 2. Go to project root
cd Cpp-Linux-GameServer-Lab

# 3. Create build directory
mkdir build && cd build

# 4. Compile
cmake ..
make

# 5. Run specific module (e.g., Day 5)
./bin/day5_run
