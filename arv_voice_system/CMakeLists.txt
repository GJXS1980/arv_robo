cmake_minimum_required(VERSION 3.0.2)
project(arv_voice_system)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
  rospy
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES castlex_awake
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)


include_directories(include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})
include_directories(
    include
    include/${PROJECT_NAME}
)

##################  awake_node   ########################
add_executable(arv_awake_node src/arv_awake.cpp src/linuxrec.cpp src/speech_recognizer.cpp)
target_link_libraries(arv_awake_node ${catkin_LIBRARIES} -lmsc -lrt -ldl -lpthread -lasound)

##################  tts_node   ########################
add_executable(arv_tts_node src/arv_tts.cpp)
target_link_libraries(arv_tts_node ${catkin_LIBRARIES} -lrt -ldl -lpthread -lmsc)

##################  asr_node   ########################
add_executable(arv_asr_node src/arv_asr.cpp src/speech_recognizer.cpp src/linuxrec.cpp)
target_link_libraries(arv_asr_node ${catkin_LIBRARIES} -lrt -ldl -lpthread -lasound -lmsc)

##################  nlu_node   ########################
add_executable(arv_nlu_node src/arv_nlu.cpp)
target_link_libraries(arv_nlu_node ${catkin_LIBRARIES} -ljsoncpp -lcurl)

##################  voice_nav_node   ########################
add_executable(arv_voice_nav_node src/arv_voice_nav.cpp src/speech_recognizer.cpp src/linuxrec.cpp)
target_link_libraries(arv_voice_nav_node ${catkin_LIBRARIES} -lrt -ldl -lpthread -lasound -lmsc)

##################  yolo_tts   ########################
add_executable(yolo_tts_node src/yolo_tts.cpp src/speech_recognizer.cpp src/linuxrec.cpp)
target_link_libraries(yolo_tts_node ${catkin_LIBRARIES} -lrt -ldl -lpthread -lasound -lmsc)
