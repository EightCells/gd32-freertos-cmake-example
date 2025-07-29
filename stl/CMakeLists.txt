add_library(user_stl EXCLUDE_FROM_ALL
    src/rqueue.c
    src/filter.c
)

target_include_directories(user_stl PUBLIC
    inc
)
