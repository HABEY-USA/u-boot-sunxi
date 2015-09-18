/*
 * (C) Copyright 2012-2013 Henrik Nordstrom <henrik@henriknordstrom.net>
 * (C) Copyright 2013 Luke Kenneth Casson Leighton <lkcl@lkcl.net>
 *
 * Configuration settings for the Allwinner A20 (sun7i) CPU
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * A20 specific configuration
 */
#define CONFIG_SUN7I		/* sun7i SoC generation */
#define CONFIG_CLK_FULL_SPEED		912000000

#define CONFIG_SYS_PROMPT		"ad203-sd# "
#define CONFIG_MACH_TYPE		4283

#if defined(CONFIG_SYS_SECONDARY_ON)
#define CONFIG_BOARD_POSTCLK_INIT 1
#endif

/*
 * Include common sunxi configuration where most the settings are
 */
#include <configs/sunxi-common.h>

#define CONFIG_MMC_SUNXI_SLOT 0

/*boot sd*/
#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootm_size=0x10000000\0" \
	"console=ttyS0,115200\0" \
	"panicarg=panic=10\0" \
	"extraargs=\0" \
	"loglevel=8\0" \
	"scriptaddr=0x44000000\0" \
	"device=mmc\0" \
	"partition=0:1\0" \
	"setargs=" \
	  "if test -z \\\\\"$root\\\\\"; then"\
	    " if test \\\\\"$bootpath\\\\\" = \"/boot/\"; then"\
	      " root=\"/dev/mmcblk0p1 rootwait\";"\
	    " else" \
	      " root=\"/dev/mmcblk0p2 rootwait\";"\
	    " fi;"\
	  " fi;"\
	  " setenv bootargs console=${console} root=${root}" \
	  " loglevel=${loglevel} ${panicarg} ${extraargs}" \
	  "\0" \
	"kernel=uImage\0" \
	"bootenv=uEnv.txt\0" \
	"bootscr=boot.scr\0" \
	"script=script.bin\0" \
	"loadbootscr=" \
	  "fatload $device $partition $scriptaddr ${bootscr}" \
	  " || " \
	  "ext2load $device $partition $scriptaddr boot/${bootscr}" \
	  " ||" \
	  "ext2load $device $partition $scriptaddr ${bootscr}" \
	  "\0" \
	"loadbootenv=" \
	  "fatload $device $partition $scriptaddr ${bootenv}" \
	  " || " \
	  "ext2load $device $partition $scriptaddr boot/${bootenv}" \
	  " || " \
	  "ext2load $device $partition $scriptaddr ${bootenv}" \
	  "\0" \
	"loadkernel=" \
	  "if "\
	    "bootpath=/boot/" \
	    " && " \
	    "ext2load $device $partition 0x43000000 ${bootpath}${script}" \
	    " && " \
	    "ext2load $device $partition 0x48000000 ${bootpath}${kernel}" \
	  ";then true; elif " \
	    "bootpath=/" \
	    " && " \
	    "fatload $device $partition 0x43000000 ${script}" \
	    " && " \
	    "fatload $device $partition 0x48000000 ${kernel}" \
	  ";then true; elif " \
	    "bootpath=/" \
	    " && " \
	    "ext2load $device $partition 0x43000000 ${bootpath}${script}" \
	    " && " \
	    "ext2load $device $partition 0x48000000 ${bootpath}${kernel}" \
	  ";then true; else "\
	    "false" \
	  ";fi" \
	  "\0" \
	"autoboot=" \
	  "run loadkernel" \
	  " && " \
	  "run setargs" \
	  " && " \
	  RESET_WATCHDOG \
	  " && " \
	  "bootm 0x48000000" \
	  "\0" \
	"boot_ram=" \
	  "saved_stdout=$stdout;setenv stdout nc;"\
	  "if iminfo 0x41000000; then" \
	    " " RESET_WATCHDOG ";"\
	    " setenv stdout $saved_stdout;" \
	    " source 0x41000000;" \
	  "else" \
	    " setenv stdout $saved_stdout;" \
	  "fi" \
	  "\0" \
	""

#define CONFIG_SYS_BOOT_GET_CMDLINE

#endif /* __CONFIG_H */
