本仓库为[SpeedDP](https://www.vizvision.com/product-item-40.html)开发平台配套的rk3588开发套件.


## 交叉编译

进入子项目路径并运行`make.sh`编译脚本.

## 运行测试

1. 首次运行时须将`SDK`根目录`lib`中的库文件拷贝至开发板上`/usr/lib`目录;
2. 将编译生成的`spdp_demo.elf`拷贝至开发板上模型及配置文件所在目录;
3. 准备一张测试图片`test.jpg`,放到`spdp_demo.elf`相同目录,执行`spdp_demo.elf`即可得到输出结果.
