add_executable(prog main.cpp)

target_include_directories(prog PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(prog PUBLIC cxx_std_17)
target_compile_definitions(prog PRIVATE SFML_STATIC)

target_link_libraries(prog ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})