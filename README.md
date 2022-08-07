## Introduction

[中文](README-zh.md) | [English](README.md)

This is a repository for learning data structures and algorithms, implemented with C.

## Prerequisite

- gnu autotools, install on macos: 

```
brew install autoconf automake libtool
```

- [check](https://github.com/libcheck/check) for unit test, install on macos:

```
brew install check
```

## Build

clone this repo, and then: 
```sh
autoreconf --install
./configure
make
```

if autoreconfg command is not found, please check autotools is installed, and `PATH` environment variable is set correctly.

## Test
```sh
make check
```

## TODO

#### Tree

- [x] binary search tree
- [x] avl tree
