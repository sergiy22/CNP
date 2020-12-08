project(Prak8)

include_directories(include)
file(GLOB SRC src/*.java src/*.jxxx)
add_executable(${PROJECT_NAME} ${SRC} src/HelloWorld.java)

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES})
