project("UnLock Legacy" C)
    if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
    endif(COMMAND cmake_policy)
    cmake_minimum_required(VERSION 3.10)

set (SRC
  map.c
  object.c
  )

add_library(game SHARED ${SRC})

set (TSRC
  msdl.c)

add_executable(tests EXCLUDE_FROM_ALL ${TSRC})
target_link_libraries(tests game SDL2 SDL2_ttf)
