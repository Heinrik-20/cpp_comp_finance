add_library(Utils "")

target_sources(
    Utils
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Utils.cpp
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Utils.h
)

target_include_directories(
    Utils
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)