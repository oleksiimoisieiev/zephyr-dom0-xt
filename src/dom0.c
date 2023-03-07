/*
 * Copyright (c) 2023 EPAM Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#define DEBUG

#include <stddef.h>
#include <storage.h>
#include <xen_dom_mgmt.h>
#include <xrun.h>
#include <zephyr/kernel.h>

/* TODO: call xen library initialization routine */
extern void init_root();

#if defined(DEBUG)
uint8_t json_msg[] = "{"
	"\"ociVersion\" : \"1.0.1\", "
	"\"vm\" : { "
		"\"hypervisor\": { "
			"\"path\": \"xen\", "
			"\"parameters\": [\"pvcalls=true\"] "
		"}, "
		"\"kernel\": { "
			" \"path\" : \"/lfs/unikernel.bin\", "
			" \"parameters\" : [ \"port=8124\", \"hello world\" ]"
		"} "
	"} "
"}";

extern char __img_unikraft_start[];
extern char __img_unikraft_end[];
extern char __dtb_unikraft_start[];
extern char __dtb_unikraft_end[];

#endif /* DEBUG */

void main(void)
{
	int ret;

	init_root();
	/* xrun_run("/", 0, "test"); */
	printk("dtb = %p\n", (void* )__dtb_unikraft_start);
	ret = debug_write_file("/lfs", "config.json", json_msg, sizeof(json_msg)); /*  */
	printk("Write config.json file ret = %d\n", ret);
	ret = debug_write_file("/lfs", "unikernel.bin",
						__img_unikraft_start,
						__img_unikraft_end - __img_unikraft_start);
	printk("Write unikraft.bim file ret = %d\n", ret);
	ret = debug_write_file("/lfs", "uni.dtb",
						   __dtb_unikraft_start,
						   __dtb_unikraft_end - __dtb_unikraft_start);
	printk("Write unikraft.dtb file ret = %d\n", ret);

	ret = lsdir("/lfs");
	printk("lsdir result = %d\n", ret);
}
