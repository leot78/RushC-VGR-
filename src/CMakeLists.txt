project("UnLock Legacy" C)

set (SRC
  map.c
  object.c
  )

add_library(game SHARED ${SRC})

set (TSRC
  test.c)

add_executable(tests EXCLUDE_FROM_ALL ${TSRC})
target_link_libraries(tests game)
