# nvidia
1. 
```bash
sudo apt-get install nvidia-418
```

# cuda
1. 查看版本
   [CUDA版本](https://blog.csdn.net/weixin_42069606/article/details/105198845)
2. 对nouveau禁用
```bash
sudo gedit /etc/modprobe.d/blacklist-nouveau.conf
```
 新建的文件中输入：
```bash
blacklist nouveau
options nouveau modeset=0
```
 保存文件并退出，然后在终端执行如下命令：
```bash
sudo update-initramfs -u
```
 检查禁用是否成功：
```bash
lspci | grep nouveau
```
如果未成功，重启
3. 下载、安装CUDA
[下载网站](https://developer.nvidia.com/cuda-10.0-download-archive?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1804&target_type=runfilelocal)
安装：
```bash
sudo sh cuda_***_linux.run (你下载的runfile安装包名字）
```
4.设置环境(在主目录下的~/.bashrc文件添加如下路径)
```bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-10.0/lib64
export PATH=$PATH:/usr/local/cuda-10.0/bin
export CUDA_HOME=$CUDA_HOME:/usr/local/cuda-10.0
```
5. 检测是否安装成功
```bash
 cd /usr/local/cuda/samples/1_Utilities/deviceQuery
sudo make
./deviceQuery
```
result为pass则为成功,如果不行，进行下面操作
```bash
ubuntu-drivers devices
sudo ubuntu-drivers autoinstall #自动安装
```

# cudnn
1. 查看
   [地址](https://www.tensorflow.org/install/source)

2.下载并安装<br>
解压缩：tar -xzvf cudnn-9.0-linux-x64-v7.tgz
[下载网站](https://developer.nvidia.com/rdp/cudnn-download)

```bash
sudo cp cuda/include/cudnn.h /usr/local/cuda/include
sudo cp cuda/lib64/libcudnn* /usr/local/cuda/lib64
sudo chmod a+r /usr/local/cuda/include/cudnn.h /usr/local/cuda/lib64/libcudnn*
```
查看cudnn版本 
```bash
cat /usr/local/cuda/include/cudnn.h | grep CUDNN_MAJOR -A 2
```
[参考网站](https://blog.csdn.net/zhiman_zhong/article/details/91491780)

# tensorflow
python2:
```bash
sudo pip install -i https://pypi.tuna.tsinghua.edu.cn/simple/ --upgrade tensorflow
```
python3:
```bash
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple/ --upgrade tensorflow
```

# pytorch



