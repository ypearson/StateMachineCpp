#!/usr/bin/env bash

export CI_COMMIT_BRANCH=$(git branch --show-current)
source .setupenv

if [[ "$1" == "l" ]]; then
    # echo "Local build"
    DOCKER=""
else
    # echo "Docker build"
    IMAGE_PATH=...
    IMAGE=PROJECT/stm32_buildtools
    DOCKER="docker run\
    --env TARGET_NAME=${TARGET_NAME}\
    --env GIT_BRANCH_NAME=${GIT_BRANCH_NAME}\
    --volume ${VOL_NAME}:${DOCKER_BUILD_PATH}\
    ${IMAGE_PATH}/${IMAGE}"
fi

DOCKER=""

pre_build () {
    cd firmware
    find App/ -regex '.*\.\(cpp\|hpp\)' -exec clang-format --verbose -style=file -i {} \;
    cd ..
}

build() {
    cd firmware
    rm -rf build && $DOCKER cmake -B build -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    $DOCKER make format -C build
    $DOCKER make -C build -j12
    find build -name ${TARGET_NAME}*.bin -exec cp $TOP/firmware/{} $TOP/firmware/build/${TARGET_NAME}.bin \;
    git checkout App/Src/build_information.cpp
    cd ..
    linux_build
}

linux_build() {
    cd linux
    ./build.sh
    cd ..
}

post_build() {
    cd python; ./get_rule.sh; cd ..
}

flash() {
    cd firmware
    cd STM32CubeProgrammer
    ./flash.sh ../build/$TARGET_NAME.bin
    cd ..
}

debug() {
    (st-util > /dev/null 2>&1 &) &&\
    arm-none-eabi-gdb -x $TOP/.gdbinit -tui $BUILD_PATH/${TARGET_NAME}.elf
}

if [[ "$1" == "d" ]]; then
    pre_build && build && flash && debug
    pkill st-util
    elif [[ "$1" == "f" ]]; then
    pre_build && build && post_build && flash
    elif [[ "$1" == "g" ]]; then
    pre_build && build && post_build && flash && picocom -b 1500000 /dev/ttyACM0
    elif [[ "$1" == "c" ]]; then
    pre_build
else
    pre_build && build && post_build
fi

