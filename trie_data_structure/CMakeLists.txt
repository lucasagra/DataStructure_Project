cmake_minimum_required(VERSION 3.10)
project(trie_data_structure C)

set(CMAKE_C_STANDARD 99)

add_executable(trie_data_structure main.c headers/tree.h headers/readfile.h)