cmake_minimum_required(VERSION 3.10)


project(ArmorDetector)



set(CMAKE_CXX_STANDARD 17)



find_package(OpenCV REQUIRED)



include_directories(
    ${OpenCV_INCLUDE_DIRS}
)



add_executable(
    ArmorDetector

    main.cpp
    armor_detector.cpp

)



target_link_libraries(
    ArmorDetector

    ${OpenCV_LIBS}

)
