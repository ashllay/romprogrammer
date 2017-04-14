project(romprogrammer_cli)
cmake_minimum_required(VERSION 3.4)

add_executable(romprg
  main.c
  ../common/protocol.c
  serial.c
  commands.c
)
