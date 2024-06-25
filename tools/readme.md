## 模型转换

使用convert2rknn工具将导出的pt模型转换为rknn模型。

```bash
# 这里以linux子系统为例：
# 1.通过powershell打开linux子系统
wsl
# 2.在linux子系统环境运行convert2rknn
./convert2rknn.elf --env <rknn_toolkit工具包在linux子系统中的绝对路径> --model <导出模型在linux子系统中的绝对路径> --platform rk3588
```

## rknn_toolkit工具包

用户可根据需要直接使用我们打包好的rknn_toolkit环境包或者参照RKNN官方文档自行安装准备。

| 完整环境包         | 说明                                                         | 官方文档                                                     |
| ------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| rknn-1.7.3.tar.xz  | 用于RK1808/RK1806/RK3399Pro/RV1109/RV1126芯片平台模型转换    | [rknn_toolkit](https://github.com/airockchip/rknn-toolkit)   |
| rknn2-1.6.2.tar.xz | 用于RK3566/RK3568/RK3588/RK3562/RV1103/RV1106芯片平台模型转换 | [rknn_toolkit2](https://github.com/rockchip-linux/rknn-toolkit2) |
| rknn2-2.0.0.tar.xz | 用于RK3566/RK3568/RK3588/RK3576/RK3562/RV1103/RV1106/RK2118芯片平台模型转换 | [rknn_toolkit2](https://github.com/airockchip/rknn-toolkit2) |

