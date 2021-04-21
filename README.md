# arv_robo
### 安装依赖
```bash
sudo apt-get install libzbar-dev    \
                                        ros-melodic-serial  \
                                        ros-melodic-amcl    \
                                        ros-melodic-gmapping    \
                                        ros-melodic-map-server  \
                                        ros-melodic-move-base   \
                                        sox
```
###     语音配置
```bash
cd /path/to/arv_robo/arv_voice_system/libs/x64/
sudo cp *.so /usr/lib/
```

### Q&A
Q1. sh: 1: play: not found 
A1：安装依赖
```bash
sudo apt-get install sox
```

Q2.  all CUDA-capable devices are busy or unavailable: No such file or directory
A2：安装完CUDA之后重启


