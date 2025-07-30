# gd32 mcu freertos cmake example
本仓库是一个 GD32 MCU移植 FreeRTOS 的参考项目。使用 arm-none-eabi 工具链和 cmake 构建工具。具体芯片型号为 GD32F427ZGT6 。


- 参考 [FreeRTOS 移植指南](https://www.freertos.org/zh-cn-cmn-s/Documentation/02-Kernel/03-Supported-devices/01-FreeRTOS-porting-guide)，portable选择GCC/ARM_CM4F和heap_4，修改了启动文件以使能硬件 FPU。SVC、Pend、Systick中断位于port.c中。
- 同时移植 [FreeRTOS-CLI 命令行工具](https://www.freertos.org/zh-cn-cmn-s/Documentation/03-Libraries/02-FreeRTOS-plus/03-FreeRTOS-plus-CLI/01-FreeRTOS-plus-CLI) ，使用串口传输，波特率115200。默认有task-stats功能查看各任务状态。

