/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2016 WinSystems, Inc.
 *
 * Configuration settings for the MX6DL WinSystems SBC-C421 board.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __MX6DLC421_CONFIG_H
#define __MX6DLC421_CONFIG_H

#include <asm/arch/imx-regs.h>
#include <asm/imx-common/gpio.h>
#include "mx6_common.h"
#include <linux/sizes.h>

#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_MX6DL 1

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_BOARD_POSTCLK_INIT
#define CONFIG_ARCH_CPU_INIT

#define CONFIG_CMDLINE_TAG
#define CONFIG_REVISION_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/* Hardware drivers */
#define CONFIG_MXC_GPIO
#define CONFIG_MXC_SPI
#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE        UART1_BASE
#define CONFIG_BAUDRATE             115200
#define CONFIG_SYS_BAUDRATE_TABLE   {9600, 19200, 38400, 57600, 115200}
#define CONFIG_IMX_THERMAL

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN       (2 * 1024 * 1024)

/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_SIZE    128

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX           1

/* Command definition */
#define CONFIG_CMDLINE_EDITING
#define CONFIG_BOOTDELAY            3
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2  "> "
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMD_BMODE
#define CONFIG_CMD_BOOTZ
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_CMD_I2C
#define CONFIG_CMD_FUSE
#ifdef CONFIG_CMD_FUSE
#define CONFIG_MXC_OCOTP
#endif
#define CONFIG_CMD_SF
#define CONFIG_CMD_MMC
#define CONFIG_CMD_ENV
#undef CONFIG_CMD_IMLS

/* usb */
#define CONFIG_USB_EHCI
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_EHCI_MX6
#define CONFIG_MXC_USB_PORTSC	    (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_USB_EHCI_HCD
#define CONFIG_USB_UHCI

/* ethernet */
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE                ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE         RGMII
#define CONFIG_ETHPRIME             "FEC"
#define CONFIG_FEC_MXC_PHYADDR      0
#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL
#define CONFIG_PHY_MICREL_KSZ9021
#define CONFIG_ARP_TIMEOUT          200UL
#define CONFIG_NET_RETRY_COUNT      1

#define CONFIG_SYS_TEXT_BASE        0x17800000

#define CONFIG_MFG_ENV_SETTINGS \
        "mfgtool_args=setenv bootargs console=ttymxc0,115200n8 " \
        "rdinit=/linuxrc " \
        "g_mass_storage.stall=0 g_mass_storage.removable=1 " \
        "g_mass_storage.idVendor=0x066F g_mass_storage.idProduct=0x37FF "\
        "g_mass_storage.iSerialNumber=\"\" "\
        "enable_wait_mode=off "\
        "\0" \
        "initrd_addr=0x12C00000\0" \
        "initrd_high=0xffffffff\0" \
        "bootcmd_mfg=run mfgtool_args; bootz ${loadaddr} ${initrd_addr} ${fdt_addr};\0"

/* boot from SPI-NOR */
#if defined(CONFIG_SYS_BOOT_SPINOR)

#define	CONFIG_EXTRA_ENV_SETTINGS \
        "netdev=eth0\0"                                         \
        "ethprime=FEC0\0"                                       \
        "uboot=u-boot.imx\0"                                    \
        "kernel=zImage\0"                                       \
        "ip_config=ip=none\0 "                                  \
        "fdt_file=imx6solo-c421.dtb\0"                          \
        "fdt_addr=0x18000000\0"                                 \
        "fdt_high=0xffffffff\0"                                 \
        "bootargs=console=ttymxc0,115200n8 "                    \
            "root=/dev/ram0 partid=3 rw ${ip_config}\0"         \
        "recovery_addr=0x80000\0"                               \
        "recovery_size=0x380000\0"                              \
        "dtb_addr=0x70000\0"                                    \
        "bootcmd_sf= "                                          \
            "sf probe; "                                        \
            "sf read ${loadaddr} ${recovery_addr} ${recovery_size}; " \
            "sf read ${fdt_addr} ${dtb_addr} 0x10000; "         \
            "bootz ${loadaddr} - ${fdt_addr};\0"                \
        "bootcmd=run bootcmd_sf\0"

/* boot from SD */
#else

#define CONFIG_EXTRA_ENV_SETTINGS                               \
        CONFIG_MFG_ENV_SETTINGS                                 \
        "netdev=eth0\0"                                         \
        "ethprime=FEC0\0"                                       \
        "uboot=u-boot.imx\0"                                    \
        "kernel=zImage\0"                                       \
        "ip_config=ip=none\0 "                                  \
        "fdt_file=imx6solo-c421.dtb\0"                          \
        "fdt_addr=0x18000000\0"                                 \
        "fdt_high=0xffffffff\0"                                 \
        "bootargs=console=ttymxc0,115200n8 "                    \
            "root=/dev/mmcblk2p2 rootwait rw ${ip_config}\0"    \
        "bootcmd_mmc= "                                         \
            "fatload mmc 0:1 ${loadaddr} ${kernel}; "           \
            "fatload mmc 0:1 ${fdt_addr} ${fdt_file}; "         \
            "bootz ${loadaddr} - ${fdt_addr};\0"                \
        "bootcmd=run bootcmd_mmc\0"

#endif

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE           (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START    0x10000000
#define CONFIG_SYS_MEMTEST_END      0x10010000
#define CONFIG_SYS_MEMTEST_SCRATCH  0x10800000

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR

/* I2C Configs */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_SPEED        100000
#define CONFIG_SYS_I2C_MXC_I2C1

/* SPI Configs */
#define CONFIG_SF_DEFAULT_BUS       0
#define CONFIG_SF_DEFAULT_CS        0
#define CONFIG_SF_DEFAULT_SPEED     20000000
#define CONFIG_SF_DEFAULT_MODE      (SPI_MODE_0)

/* MMC Configs */
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_MMC
#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_BOUNCE_BUFFER
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION
#define CONFIG_SUPPORT_EMMC_BOOT
#define CONFIG_SYS_FSL_ESDHC_ADDR   0
#define CONFIG_SYS_FSL_USDHC_NUM    1
#define CONFIG_SYS_MMC_ENV_DEV      0

#define CONFIG_OF_LIBFDT

/* Stack sizes */
#define CONFIG_STACKSIZE        (128 * 1024)	/* regular stack */

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS    1
#define PHYS_SDRAM_1            MMDC0_ARB_BASE_ADDR
/* 512 MB */
/*#define PHYS_SDRAM_1_SIZE     (512 * 1024 * 1024) */
/* 1 GB */
#define PHYS_SDRAM_1_SIZE       (1u * 1024 * 1024 * 1024)
/* 2 GB */
/*#define PHYS_SDRAM_1_SIZE     (2u * 1024 * 1024 * 1024) */

#define iomem_valid_addr(addr, size) \
    (addr >= PHYS_SDRAM_1 && addr <= (PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))

#define CONFIG_SYS_SDRAM_BASE          PHYS_SDRAM_1
#define CONFIG_SYS_INIT_RAM_ADDR       IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE       IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
    (CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
    (CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
#define CONFIG_SYS_NO_FLASH

/* Monitor at beginning of flash */
#if defined(CONFIG_SYS_BOOT_SPINOR)
#define CONFIG_FSL_ENV_IN_SF
#else
#define CONFIG_FSL_ENV_IN_MMC
#endif

#define CONFIG_ENV_SIZE    (8 * 1024)

#if defined(CONFIG_FSL_ENV_IN_SF)
    #define CONFIG_ENV_IS_IN_SPI_FLASH      1
    #define CONFIG_ENV_SPI_BUS              CONFIG_SF_DEFAULT_BUS
    #define CONFIG_ENV_SPI_CS               CONFIG_SF_DEFAULT_CS
    #define CONFIG_ENV_SPI_MODE             CONFIG_SF_DEFAULT_MODE
    #define CONFIG_ENV_SPI_MAX_HZ           CONFIG_SF_DEFAULT_SPEED
    #define CONFIG_ENV_OFFSET               (5 * 64 * 1024)
    #define CONFIG_ENV_SECT_SIZE            (1 * 64 * 1024)
#elif defined(CONFIG_FSL_ENV_IN_MMC)
    #define CONFIG_ENV_IS_IN_MMC            1
    #define CONFIG_ENV_OFFSET               (8 * 64 * 1024)
#else
    #define CONFIG_ENV_IS_NOWHERE           1
#endif

#endif
