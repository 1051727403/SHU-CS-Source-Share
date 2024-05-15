cmake_minimum_required(VERSION 3.21)
project(MyTreeAndForest)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyTreeAndForest main.cpp Assistance.h ChildSiblingTree.h ChildSiblingTreeNode.h
        Node.h LinkQueue.h)

