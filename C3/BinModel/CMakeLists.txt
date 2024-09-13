add_library(BinModel "")

target_sources(
    BinModel
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/BinModel.cpp
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/BinModel.h
)

target_include_directories(
    BinModel
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)