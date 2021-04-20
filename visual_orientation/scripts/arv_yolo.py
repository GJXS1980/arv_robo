#!/usr/bin/python
# -*- coding: UTF-8 -*-

import rospy
from darknet_ros_msgs.msg import BoundingBoxes
from std_msgs.msg import String, Int32, Float32
from translate import Translator

class YOLO_LABEL():
    def __init__(self):
        self.result = None
        self.yolo_data = None
        self.translator= Translator(to_lang="chinese")
        self.asr_data = 0
        #   初始化ROS节点
        rospy.init_node('yolo_label')
        rospy.Subscriber('/MPU_DATA', Float32, self.mpu_callback)   #   获取陀螺仪数据
        self.pub = rospy.Publisher('/yolo_label_topic', String, queue_size = 1)  #   发布离线命令词识别的命令词话题
        rospy.Subscriber('/yolo_asr_topic', Int32, self.asr_callback)
        
        #   主函数
        while not rospy.is_shutdown():
            if self.result != None:
                self.pub.publish(self.result)
                self.result = None
                self.yolo_data = None

    def yolo_callback(self, data):
        self.yolo_data = data.bounding_boxes[0].Class
	
        if self.yolo_data != None and self.asr_data != 0:
            #   对识别的标签进行翻译
            # translation = self.translator.translate(self.yolo_data)
            # print(type(translation))
            #   转换成字符型
            # translation = translation.encode('unicode-escape').decode('string_escape')
            self.result = "识别到" + chinese[data.bounding_boxes[0].id]
            self.asr_data = 0
            # self.result = str(translation1)

    def asr_callback(self, data):
        self.asr_data = data
  
if __name__ == '__main__':
    YOLO_LABEL()
