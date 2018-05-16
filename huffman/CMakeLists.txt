cmake_minimum_required(VERSION 3.10)
project(huffman_project C)

set(CMAKE_C_STANDARD 99)

add_executable(huffman_project main.c
                ./headers/compress.h
                ./headers/compress/priority_queue.h
                ./headers/compress/hashtable.h
                ./headers/compress/tree.h
                ./headers/compress/decimal_binary.h
                ./headers/compress/readfile.h
                ./headers/compress/huff.h
                ./headers/compress/node.h
                ./headers/compress/stack.h
                ./headers/compress/header.h
                ./headers/decompress.h
                ./headers/decompress/header.h)
