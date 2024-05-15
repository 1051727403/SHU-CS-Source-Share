cmake_minimum_required(VERSION 3.21)
project(MyBinTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyBinTree main.cpp
        Assistance.h Node.h BinTreeNode.h BinaryTree.h LinkQueue.h LinkStack.h)
