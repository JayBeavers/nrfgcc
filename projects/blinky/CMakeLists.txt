cmake_minimum_required (VERSION 2.8)

project (HelloNRF51)

set (CMAKE_BUILD_TYPE  Debug)

set (MBED_SRC_PATH     ../../mbed-src/libraries/mbed)

set(TOOLCHAIN_DIR       /usr/local/gcc-arm-none-eabi-5_2-2015q4/bin)
set(CMAKE_CXX_COMPILER  ${TOOLCHAIN_DIR}/arm-none-eabi-g++)
set(CMAKE_C_COMPILER    ${TOOLCHAIN_DIR}/arm-none-eabi-gcc)
set(SIZE_COMMAND        ${TOOLCHAIN_DIR}/arm-none-eabi-size)
set(OBJCOPY_COMMAND     ${TOOLCHAIN_DIR}/arm-none-eabi-objcopy)

set(MAIN_TARGET        ${PROJECT_NAME}.elf)
enable_language(ASM)

include_directories(
  ${HelloNRF51_SOURCE_DIR}
  ${MBED_SRC_PATH}/api
  ${MBED_SRC_PATH}/hal
  ${MBED_SRC_PATH}/targets/cmsis
  ${MBED_SRC_PATH}/targets/cmsis/TARGET_NORDIC/TARGET_MCU_NRF51822
  ${MBED_SRC_PATH}/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822
  ${MBED_SRC_PATH}/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822/TARGET_NRF51822_MKIT
)

# Generic compiler flags
add_definitions(
  -DSOFTDEVICE_PRESENT
  -DNRF51
  -DBOARD_PCA10031
  -DS130
  -DBLE_STACK_SUPPORT_REQD
  -DBSP_DEFINES_ONLY
  -D__MBED__=1
  -mcpu=cortex-m0
  -mthumb
  -mabi=aapcs
  -Wall
  -O3
  -g3
  )

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -g3 --std=c++11 -fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -g3 --std=gnu99")
set(CMAKE_ASM_FLAGS
    "${COMMON_COMPILE_FLAGS} -x assembler-with-cpp")

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS
    -T../../../mbed-src/libraries/mbed/targets/cmsis/TARGET_NORDIC/TARGET_MCU_NRF51822/TOOLCHAIN_GCC_ARM/TARGET_MCU_NRF51_16K_S130/NRF51822.ld)
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS
    "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -g3 -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections --specs=nosys.specs")

SET(ALL_SOURCES "../main.cpp")
SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/assert.c")
SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/error.c")
SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/gpio.c")
SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822/gpio_api.c")
SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822/pinmap.c")
SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/targets/cmsis/TARGET_NORDIC/TARGET_MCU_NRF51822/TOOLCHAIN_GCC_ARM/startup_NRF51822.s")
SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/targets/cmsis/TARGET_NORDIC/TARGET_MCU_NRF51822/system_nrf51.c")

#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/board.c")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/wait_api.c")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/FileBase.cpp")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/FilePath.cpp")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/FileSystemLike.cpp")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/retarget.cpp")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/ticker_api.c")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/common/us_ticker_api.c")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822/serial_api.c")
#SET(ALL_SOURCES "${ALL_SOURCES};${MBED_SRC_PATH}/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822/us_ticker.c")

add_executable(${MAIN_TARGET} ${ALL_SOURCES})

add_custom_command(
  TARGET ${MAIN_TARGET}
  COMMAND ${SIZE_COMMAND} ${MAIN_TARGET}
  COMMAND ${OBJCOPY_COMMAND} -O binary ${MAIN_TARGET} ${PROJECT_NAME}.bin # convert .elf to .bin
  COMMAND ${OBJCOPY_COMMAND} -O ihex ${MAIN_TARGET} ${PROJECT_NAME}.hex # convert .elf to .hex
  COMMAND srec_cat ../../../mbed-src/libraries/mbed/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822/Lib/s130_nrf51822_1_0_0/s130_nrf51_1.0.0_softdevice.hex -intel ${PROJECT_NAME}.bin -binary -offset 0x1c000 -o combined.hex -intel
)
