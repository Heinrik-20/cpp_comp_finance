add_library(DefInt "")

target_sources(
    DefInt
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/DefInt.cpp
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/DefInt.h
)

target_link_libraries(
    DefInt
    PRIVATE
    Functions
)

target_include_directories(
    DefInt
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)