cmake_minimum_required(VERSION 3.10)
project("UnLock Legacy" C)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic")

set (SRC
  map.c
  object.c
  player.c
  move.c
  )

add_library(game SHARED ${SRC})

set (TSRC
  msdl.c)

add_executable(tests EXCLUDE_FROM_ALL ${TSRC})
target_link_libraries(tests game SDL2 SDL2_ttf)
