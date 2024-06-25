SDK_ROOT_DIR=$(dirname "$PWD")
TOOLCHAIN_NAME=arm-gnu-toolchain-12.3.rel1-x86_64-aarch64-none-linux-gnu

INCLUDE_PATH=${SDK_ROOT_DIR}/include
LIB_PATH=${SDK_ROOT_DIR}/lib
COMPILER_PATH=${SDK_ROOT_DIR}/${TOOLCHAIN_NAME}/bin/aarch64-none-linux-gnu-g++

CFLAGS="-std=gnu++20 -O3 -I${INCLUDE_PATH} -L${LIB_PATH}"
LDFLAGS="-lz -ltbb -lopenjp2 -ljpeg -lpng -lrknn_api -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lspdp"

${COMPILER_PATH} ${CFLAGS} ${LDFLAGS} spdp_demo.cpp -o spdp_demo.elf