project(riot-launcher)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE
        riot::lib
)

target_sources(${PROJECT_NAME} PRIVATE
        main.cpp
)