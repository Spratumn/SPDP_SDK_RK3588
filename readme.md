本仓库为[SpeedDP](https://www.vizvision.com/product-item-40.html)开发平台配套的rk3588开发套件.

## 模型转换

在`linux`平台下使用`convert2rknn`工具将导出的`pt`模型转换为`rknn`模型。

```bash
# 这里以linux子系统为例：
# 1.通过powershell打开linux子系统
wsl
# 2.在linux子系统环境运行convert2rknn
./convert2rknn.elf --env <rknn_toolkit工具包在linux子系统中的绝对路径> --model <导出模型在linux子系统中的绝对路径> --platform rk3588
```

<font color='red'>注1：用户可根据需要直接使用我们打包好的`rknn2.1.0.tar.gz`环境包或者参照[rknn_toolkit2](https://github.com/airockchip/rknn-toolkit2) 官方文档自行安装准备。</font>

<font color='red'>注2：`convert2rknn`工具须搭配`python3.8`进行使用，因此用户自行安装`rknn_toolkit2`环境时请选择`python3.8`对应的安装包。</font>

## 交叉编译

1. 解压`gcc-arm-12.3-x86_64-aarch64-none-linux-gnu.tar.gz`；
2. 进入`spdp_demo`目录并运行`make.sh`编译脚本。

## 运行测试

1. 首次运行时须将`SDK`根目录`lib`中的库文件拷贝至开发板上`/usr/lib`目录；
2. 将编译生成的`spdp_demo.elf`拷贝至开发板上模型及配置文件所在目录；
3. 准备一张测试图片`test.jpg`,放到`spdp_demo.elf`相同目录,执行`spdp_demo.elf`即可得到输出结果。
