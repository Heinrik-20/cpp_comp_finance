add_library(Oracle "")

target_sources(
    Oracle
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Oracle.cpp
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Oracle.h
)

target_link_libraries(Oracle BinModel)

target_include_directories(
    Oracle
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)