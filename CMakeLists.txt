# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

set(ZEPHYR_MODULES ../zephyr-xenlib)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)

set(UTILS_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts)
if (DTC)
  add_custom_target(
    fix_dtb
    DEPENDS ${ZEPHYR_FINAL_EXECUTABLE}
    COMMAND ${UTILS_SCRIPTS_DIR}/fix_dtb.sh ${UTILS_SCRIPTS_DIR}/gicv${QEMU_GIC_VERSION}.tmpl ${ZEPHYR_BINARY_DIR}/virt_gicv${QEMU_GIC_VERSION}.dtb ${ZEPHYR_BINARY_DIR}/zephyr.bin
  )
else()
  message(WARNING "No dtc program")
endif()

project(xen-dom0)

include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add prebuilt to includes so assembler can find this files
include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt)

target_sources(app PRIVATE src/dom0.c src/domd_cfg.c src/domd_bin.S)

include(ExternalProject)
set(XEN_SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../xen)
set(XEN_BINDIR ${CMAKE_CURRENT_BINARY_DIR}/hyp)

ExternalProject_Add(
  hypervisor
  PREFIX ${XEN_BINDIR}
  SOURCE_DIR ${XEN_SRCDIR}/xen
  BINARY_DIR ${XEN_BINDIR}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${MAKE} make -C ${XEN_SRCDIR}/xen O=${XEN_BINDIR}
  CONFIG_QEMU_XEN=y CONFIG_DEBUG=y XSM_ENABLE=y
  XEN_TARGET_ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- HOSTCC=gcc
  INSTALL_COMMAND cp ${XEN_BINDIR}/xen ${ZEPHYR_BINARY_DIR}/xen
  )

add_dependencies(app hypervisor)
