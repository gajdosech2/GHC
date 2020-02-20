cmake_minimum_required(VERSION 3.8.2)
Project(GHC_Project LANGUAGES CXX VERSION 1.0.1)

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} PRIVATE
  main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Utils
  COGS
)


if(WIN32 OR CYGWIN)
  set(DEBUG_ENV "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug")
  set(RELEASE_ENV "${CMAKE_CURRENT_SOURCE_DIR}/bin/Release")
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.Cpp.user.props 
"<?xml version=\"1.0\" encoding=\"utf-8\"?> 
<Project DefaultTargets=\"Build\" ToolsVersion=\"15.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
  <PropertyGroup Condition=\"\'$(Configuration)|$(Platform)\'==\'Debug|x64\'\">
    <LocalDebuggerEnvironment>PATH=${DEBUG_ENV}</LocalDebuggerEnvironment>
  </PropertyGroup>
  <PropertyGroup Condition=\"\'$(Configuration)|$(Platform)\'==\'Release|x64\'\">
    <LocalDebuggerEnvironment>PATH=${RELEASE_ENV}</LocalDebuggerEnvironment>
  </PropertyGroup>
  <PropertyGroup Condition=\"\'$(Configuration)|$(Platform)\'==\'RelWithDebInfo|x64\'\">
    <LocalDebuggerEnvironment>PATH=${RELEASE_ENV}</LocalDebuggerEnvironment>
  </PropertyGroup>
  <PropertyGroup Condition=\"\'$(Configuration)|$(Platform)\'==\'MinSizeRel|x64\'\">
    <LocalDebuggerEnvironment>PATH=${RELEASE_ENV}</LocalDebuggerEnvironment>
  </PropertyGroup>
</Project>"
  )
  set_target_properties(${PROJECT_NAME} PROPERTIES VS_USER_PROPS "${PROJECT_NAME}.Cpp.user.props")
  
  
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin
	DESTINATION ${CMAKE_BINARY_DIR})
endif()
