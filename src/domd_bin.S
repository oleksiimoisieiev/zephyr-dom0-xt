/*
 * Copyright (c) 2023 EPAM Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 */

.section .img_domd,"a"

/* DomD binary from include/ dir */
.incbin		"domd_img.bin"

.section .dtb_domd,"a"

/* DomD dtb from include/ dir */
.incbin		"domd.dtb"

.section .img_unikraft,"a"

/* unikraft binary with pvcalls */
.incbin 	"helloworld_xen-arm64"

.section .dtb_unikraft,"a"

/* dtb file for the unikraft domains */
.incbin		"unikernel.dtb"
