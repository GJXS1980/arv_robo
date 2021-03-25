cmake_minimum_required(VERSION 3.0.2)
project(arvlidar_ros)

set(ARVLIDAR_SDK_PATH "./sdk/")

FILE(GLOB ARVLIDAR_SDK_SRC 
  "${ARVLIDAR_SDK_PATH}/src/arch/linux/*.cpp"
  "${ARVLIDAR_SDK_PATH}/src/hal/*.cpp"
  "${ARVLIDAR_SDK_PATH}/src/*.cpp"
)

find_package(catkin REQUIRED COMPONENTS
  rosconsole
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

include_directories(
  ${ARVLIDAR_SDK_PATH}/include
  ${ARVLIDAR_SDK_PATH}/src
  ${catkin_INCLUDE_DIRS}
)

###################################
## catkin specific configuration ##
###################################
catkin_package()

###########
## Build ##
###########
add_executable(arvlidarNode_A1 src/node_A1.cpp ${ARVLIDAR_SDK_SRC})
target_link_libraries(arvlidarNode_A1 ${catkin_LIBRARIES})

add_executable(arvlidarNode_A2 src/node_A2.cpp ${ARVLIDAR_SDK_SRC})
target_link_libraries(arvlidarNode_A2 ${catkin_LIBRARIES})

add_executable(arvlidarNodeClient src/client.cpp)
target_link_libraries(arvlidarNodeClient ${catkin_LIBRARIES})

#############
## Install ##
#############

install(TARGETS arvlidarNode_A1  arvlidarNode_A2 arvlidarNodeClient
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch rviz sdk
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  USE_SOURCE_PERMISSIONS
)
