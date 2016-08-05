cmake_minimum_required(VERSION 3.5)
project(stone)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        ds/Array.hpp
        ds/ArrayUnitTest.hpp
        stone/AST.hpp
        stone/ASTPrinter.hpp
        common/Common.h
        stone/Data.hpp
        stone/Env.hpp
        stone/Interpreter.hpp
        stone/Lexer.hpp
        main.cpp
        ds/Map.hpp
        stone/MapEnv.hpp
        ds/MapUnitTest.hpp
        stone/Message.hpp
        stone/Parser.hpp
        stone/Reader.hpp
        ds/String.hpp
        ds/StringUnitTest.hpp
        test.stone
        stone/Token.hpp
        ds/TreeMapImpl.hpp
        common/UnitTest.hpp
    README.md stone/FuncSig.hpp ds/Pair.hpp ds/AutoComparable.hpp)

include_directories("${PROJECT_SOURCE_DIR}")

add_executable(stone ${SOURCE_FILES})