cmake_minimum_required(VERSION 3.8.2)
Project(GHC_Project LANGUAGES CXX VERSION 1.0.1)

add_executable(${PROJECT_NAME} "")

set(CMAKE_CXX_STANDARD 17)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE GLM_ENABLE_EXPERIMENTAL
    PRIVATE _CRT_SECURE_NO_WARNINGS
)

target_sources(${PROJECT_NAME} PRIVATE
  main.cpp
  src/utils.h
  src/utils.cpp
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    "src"
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})

#find_package(OpenMP REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Utils
  COGS
#  OpenMP::OpenMP_CXX
)


if(WIN32 OR CYGWIN) 
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
	DESTINATION ${CMAKE_BINARY_DIR})
endif()
