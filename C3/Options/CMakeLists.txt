add_library(Options "")

target_sources(
    Options
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Options.cpp
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Options.h
)

target_link_libraries(Options PRIVATE BinModel)

target_include_directories(
    Options
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)