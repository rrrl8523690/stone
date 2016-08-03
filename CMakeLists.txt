cmake_minimum_required(VERSION 3.5)
project(lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        lib/Array.hpp
        lib/ArrayUnitTest.hpp
        lib/AST.hpp
        lib/ASTPrinter.hpp
        lib/common.h
        lib/Data.hpp
        lib/Env.hpp
        lib/Interpreter.hpp
        lib/Iterator.hpp
        lib/Lexer.hpp
        lib/lib.cpp
        lib/Map.hpp
        lib/MapEnv.hpp
        lib/MapUnitTest.hpp
        lib/Message.hpp
        lib/Parser.hpp
        lib/Reader.hpp
        lib/String.hpp
        lib/StringUnitTest.hpp
        lib/test.stone
        lib/Token.hpp
        lib/TreeMapImpl.hpp
        lib/UnitTest.hpp
        README.md)

add_executable(lib ${SOURCE_FILES})