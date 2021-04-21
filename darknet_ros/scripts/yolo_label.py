#!/usr/bin/python
# -*- coding: UTF-8 -*-

import rospy
from darknet_ros_msgs.msg import BoundingBoxes
from std_msgs.msg import String, Int32
from translate import Translator

chinese = ["人","自行车","汽车","摩托车","飞机","公共汽车","火车","卡车","船","交通灯","消防栓","停车标志","停车计时器",
"长凳","鸟","猫","狗","马","羊","奶牛","大象","熊","斑马","长颈鹿","背包","雨伞","手提包","领带","手提箱","飞盘","滑雪",
"滑雪板","运动球","风筝","棒球棒","棒球手套","滑板","冲浪板","网球拍","瓶子","酒杯","杯子","叉","刀","勺子","碗","香蕉",
"苹果","三明治","橙色","西兰花","胡萝卜","热狗","披萨","甜甜圈","蛋糕","椅子","沙发","盆栽植物","床","数字表","厕所",
"电视监视器","笔记本电脑","鼠标","遥远的","键盘","手机","微波炉","烤箱","烤面包机","下沉","冰箱","书","时钟","花瓶","剪刀",
"泰迪熊","吹风机","牙刷"]
class YOLO_LABEL():
    def __init__(self):
        self.result = None
        self.yolo_data = None
        self.translator= Translator(to_lang="chinese")
        self.asr_data = 0
        #   初始化ROS节点
        rospy.init_node('yolo_label')
        rospy.Subscriber('/darknet_ros/bounding_boxes', BoundingBoxes, self.yolo_callback)
        self.pub = rospy.Publisher('/yolo_label_topic', String, queue_size = 1)  #   发布离线命令词识别的命令词话题
        rospy.Subscriber('/yolo_detec_asr_topic', Int32, self.asr_callback)
        
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
