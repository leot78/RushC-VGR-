cmake_minimum_required(VERSION 3.10)
project("UnLock Legacy" C)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic")

set (SRC
  src/map.c
  src/object.c
  src/player.c
  src/move.c
  src/lock.c
  src/enemy.c
  src/color.c
  src/random_string_gen.c
  src/text.c
  src/sprite.c
  src/timer.c
  )

set (TSRC
  src/msdl.c)

add_executable(UnLock_Legacy ${TSRC} ${SRC})
target_link_libraries(UnLock_Legacy SDL2 SDL2_ttf SDL2_mixer SDL2_image) 
