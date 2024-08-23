add_library(BinModel "")

target_sources(
    BinModel
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/BinModel01.cpp
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/BinModel01.h
)

target_include_directories(
    BinModel
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)