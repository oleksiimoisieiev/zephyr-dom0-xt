#!/bin/bash
west build -b xenvm-qemu -p always
west build -t fix_dtb
west build -t run
