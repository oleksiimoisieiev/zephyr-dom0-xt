/*
 * Copyright (c) 2023 EPAM Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/toolchain.h>

/* DomD binary from include/ dir */
.section .data.domd_img,"a"

GDATA(__img_domd_start)
GDATA(__img_domd_end)

__img_domd_start:
.incbin		"domd_img.bin"
__img_domd_end:

/* DomD dtb from include/ dir */
.section .data.dtb_domd,"a"

GDATA(__dtb_domd_start)
GDATA(__dtb_domd_end)

__dtb_domd_start:
.incbin		"domd.dtb"
__dtb_domd_end:

.section .data.img_unikraft,"a"

GDATA(__img_unikraft_start)
GDATA(__img_unikraft_end)

__img_unikraft_start:
.incbin "helloworld_xen-arm64"
__img_unikraft_end:

.section .data.dtb_unikraft,"a"

GDATA(__dtb_unikraft_start)
GDATA(__dtb_unikraft_end)

__dtb_unikraft_start:
.incbin "unikernel.dtb"
__dtb_unikraft_end:
