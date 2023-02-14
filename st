#!/bin/bash
west build -b xenvm-qemu
# west build -t fix_dtb
west build -t run
