SDK_ROOT_DIR=$(dirname "$PWD")
CURRENT_DIR=$(cd $(dirname $0); pwd)
TOOLCHAIN_NAME=arm-gnu-toolchain-12.3.rel1-x86_64-aarch64-none-linux-gnu

INCLUDE_PATH=${SDK_ROOT_DIR}/include
LIB_PATH=${SDK_ROOT_DIR}/lib
COMPILER_PATH=${SDK_ROOT_DIR}/${TOOLCHAIN_NAME}/bin/aarch64-none-linux-gnu-g++

DET_SEG_DIR=${CURRENT_DIR}/det_seg
DET_SEG_CXXSRCS=$(find ${DET_SEG_DIR} -name "*.cpp")
MAIN_CXXSRCS=${CURRENT_DIR}/main.cpp

CFLAGS="-std=gnu++20 -O3 -I${INCLUDE_PATH} -I${DET_SEG_DIR} -L${LIB_PATH}"
LDFLAGS1="-llzma -lnuma -lz -lbz2 -lrtmp -lx264 -lx265 -ldrm -ltbb -lopenjp2 -ljpeg -lpng -lavformat -lavcodec -lavutil -lswscale -lswresample"
LDFLAGS2="-lrknn_api -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lspdp"

${COMPILER_PATH} ${CFLAGS} ${LDFLAGS1} ${LDFLAGS2} ${DET_SEG_CXXSRCS} ${MAIN_CXXSRCS}  -o toolkits.elf