cmake_minimum_required(VERSION 3.1.0)
project(
   GalileoSDKTest
   VERSION 1.0.0
   LANGUAGES CXX
)
# message(${ROSCPP_INCLUDE_DIRS},"----------============")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -O3 -march=native -fpic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -O3 -march=native -std=c++11 -fpic")


# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(PkgConfig REQUIRED)
pkg_search_module(ROSCPP REQUIRED roscpp)
find_package(Boost REQUIRED COMPONENTS thread filesystem regex system chrono)
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)
catkin_package()


include_directories(
   ${catkin_INCLUDE_DIRS}
   ${PROJECT_SOURCE_DIR}/include
   ${ROSCPP_INCLUDE_DIRS}
   ${PROJECT_SOURCE_DIR}/../../../include
   ${PROJECT_SOURCE_DIR}/../../../GalileoSDK/include
   ${PROJECT_SOURCE_DIR}/../../../iot
   ${PROJECT_SOURCE_DIR}/../../../IotWrapper
)

add_executable(GalileoTest
    ${PROJECT_SOURCE_DIR}/src/GalileoSDKTest.cpp
)



target_link_libraries(GalileoTest
    ${ROSCPP_LINK_LIBRARIES}
    ${PROJECT_SOURCE_DIR}/../../../GalileoSDK/build/libGalileoSDK.so
    ${Boost_LIBRARIES}
)




add_executable(test1
    ${PROJECT_SOURCE_DIR}/src/test.cpp
)
target_link_libraries(test1
${catkin_LIBRARIES}
    ${ROSCPP_LINK_LIBRARIES}
    ${PROJECT_SOURCE_DIR}/../../../GalileoSDK/build/libGalileoSDK.so
    ${Boost_LIBRARIES}
)

add_executable(subscribe_pub
    ${PROJECT_SOURCE_DIR}/src/subscribe_pub.cpp
)
target_link_libraries(subscribe_pub
${catkin_LIBRARIES}
    ${ROSCPP_LINK_LIBRARIES}
    # ${PROJECT_SOURCE_DIR}/../../../GalileoSDK/build/libGalileoSDK.so
    ${Boost_LIBRARIES}
)