cmake_minimum_required(VERSION 3.5)
project(AnalysisTemplate CXX)

set(
        AnalysisTree_Home
        /Users/huangyige/Work/DataAnalysis/gsi/AnalysisTree
        )

set(
        AnalysisTree_Sys
        ${AnalysisTree_Home}/build/AnalysisTree
        )
     
list(
        APPEND 
        CMAKE_PREFIX_PATH 
        $ENV{ROOTSYS}
        )

list(
        APPEND 
        CMAKE_PREFIX_PATH 
        ${AnalysisTree_Sys}
        )

find_package(ROOT 6.24 CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(AnalysisTree REQUIRED)
message(STATUS "CMAKE_PROJECT_NAME ${CMAKE_PROJECT_NAME}")

include_directories(
        ${AnalysisTree_Home}/core 
        ${AnalysisTree_Home}/infra 
        ${CMAKE_CURRENT_SOURCE_DIR} 
        ${Boost_INCLUDE_DIRS}
        )

add_library(MultiplicityTool MultiplicityTool/MultiplicityTool.cxx)
add_library(IdxConstants IdxConstants/IdxConstants.cxx)
add_library(DuplicateRemover DuplicateRemover/DuplicateRemover.cxx)
add_library(CbmCut CbmCut/CbmCut.cxx)
add_library(CentralityTool CentralityTool/CentralityTool.cxx)

include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS} ${AnalysisTree_INCLUDE_DIR})

add_executable(AnalysisExec AnalysisCode.cpp)
target_link_libraries(AnalysisExec ${ROOT_LIBRARIES} AnalysisTreeBase AnalysisTreeInfra MultiplicityTool IdxConstants DuplicateRemover CbmCut CentralityTool)

