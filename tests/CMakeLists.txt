add_executable(test test_pet.cpp)

target_link_libraries(test PUBLIC pet)

target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/external) 