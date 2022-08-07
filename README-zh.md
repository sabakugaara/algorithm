## 介绍

[中文](README-zh.md) | [English](README.md)

这是一个学习数据结构和算法的仓库，用 C 实现。


## 要求

- gnu autotools, macos 安装命令如下：

```
brew install autoconf automake libtool
```

- 单元测试库 [check](https://github.com/libcheck/check), macos 安装命令如下：

```
brew install check
```

## 构建

克隆仓库到本地后，执行如下命令
```sh
autoreconf --install
./configure
make
```

如果报错 autoreconf 命令不存在，请确认 gnu autotools 是否正确安装，且 `PATH` 环境变量是否包含 `homebrew/bin` 。在作者电脑上，`PATH` 变量如下：


```
${home}/homebrew/bin
```

## 测试

每次更新源码或修改测试后，通过如下命令运行单测
```sh
make check
```

## TODO

#### Tree

- [x] binary search tree
- [x] avl tree
