add_executable(src main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_include_directories(src PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(src PUBLIC cxx_std_17)
target_compile_definitions(src PRIVATE SFML_STATIC)

target_link_libraries(src ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})