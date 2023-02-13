/*
 * Copyright (c) 2023 EPAM Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stddef.h>
#include <xen_dom_mgmt.h>
#include <xrun.h>

/* TODO: call xen library initialization routine */
extern void init_root();

void main(void)
{
	/* HACK */
	char *argv[] = {"", "-d", "1"};

	init_root();
	domu_create(NULL, 3, argv);
	xrun_run("/", 0, "test");
}
