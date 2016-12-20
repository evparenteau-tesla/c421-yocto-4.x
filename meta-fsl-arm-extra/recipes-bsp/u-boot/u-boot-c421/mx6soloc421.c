/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2016 WinSystems, Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/iomux.h>
#include <asm/arch/mx6-pins.h>
#include <asm/errno.h>
#include <asm/gpio.h>
#include <asm/imx-common/iomux-v3.h>
#include <asm/imx-common/boot_mode.h>
#include <mmc.h>
#include <netdev.h>
#include <asm/arch/crm_regs.h>
#include <linux/fb.h>
#include <ipu_pixfmt.h>
#include <asm/io.h>
#include <asm/arch/sys_proto.h>
#ifdef CONFIG_SYS_I2C_MXC
#include <i2c.h>
#include <asm/imx-common/mxc_i2c.h>
#endif
#ifdef CONFIG_FEC_MXC
#include <fsl_esdhc.h>
#include <miiphy.h>
#include <micrel.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#define UART_PAD_CTRL  (PAD_CTL_PUS_100K_UP |   \
    PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | \
    PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define USDHC_PAD_CTRL (PAD_CTL_PUS_47K_UP |    \
    PAD_CTL_SPEED_LOW | PAD_CTL_DSE_80ohm | \
    PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define ENET_PAD_CTRL  (PAD_CTL_PUS_100K_UP |   \
    PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | PAD_CTL_HYS)

#define SPI_PAD_CTRL (PAD_CTL_HYS | PAD_CTL_SPEED_MED | \
    PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST)

#define I2C_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_PUE |    \
    PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |   \
    PAD_CTL_DSE_40ohm | PAD_CTL_HYS |   \
    PAD_CTL_ODE | PAD_CTL_SRE_FAST)

void enet_board_init(void);
void udc_pins_setting(void);
void board_gpio_init(void);

/* setup boot device */
enum boot_device ws_get_boot_device(void)
{
    enum boot_device boot_dev = UNKNOWN_BOOT;

    /* SRC_BASE_ADDR = 0x020D8000 */
    uint soc_sbmr = readl(SRC_BASE_ADDR + 0x4);	/* 0x020D8004 = SRC Boot Mode Register 1 (SRC_SBMR1) */
    uint bt_dev_type = (soc_sbmr & 0x00000070) >> 4; /* BOOT_CFG1[6], BOOT_CFG1[4] */

    switch (bt_dev_type) {
        case 0x3:
            boot_dev = SPI_NOR_BOOT;
            break;

        case 0x6:
        case 0x7:
            boot_dev = MMC1_BOOT;
            break;

        default:
            boot_dev = UNKNOWN_BOOT;
            break;
    }

    return boot_dev;
}

int checkboard(void)
{
    printf("Board: SBC-C420DL\n");

    printf("Boot Device: ");

    switch (ws_get_boot_device()) {
        case SPI_NOR_BOOT:
            printf("SPI-NOR\n");
            break;

        case MMC1_BOOT:
            printf("eMMC\n");
            break;

        case UNKNOWN_BOOT:
        default:
            printf("UNKNOWN\n");
            break;
    }

    return 0;
}

/* setup memory */
int dram_init(void)
{
    gd->ram_size = ((ulong)CONFIG_DDR_MB * 1024 * 1024);

    return 0;
}

/* setup uart 1-4 */
iomux_v3_cfg_t const uart1_pads[] = {
    MX6_PAD_CSI0_DAT10__UART1_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_CSI0_DAT11__UART1_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_EIM_D19__UART1_CTS_B | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_EIM_D20__UART1_RTS_B | MUX_PAD_CTRL(UART_PAD_CTRL),
};

iomux_v3_cfg_t const uart2_pads[] = {
    MX6_PAD_EIM_D26__UART2_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_EIM_D27__UART2_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_EIM_D28__UART2_DTE_CTS_B | MUX_PAD_CTRL(UART_PAD_CTRL),
};

iomux_v3_cfg_t const uart3_pads[] = {
    MX6_PAD_SD4_CMD__UART3_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_SD4_CLK__UART3_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_EIM_D30__UART3_CTS_B | MUX_PAD_CTRL(UART_PAD_CTRL),
};

iomux_v3_cfg_t const uart4_pads[] = {
    MX6_PAD_KEY_COL0__UART4_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_KEY_ROW0__UART4_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
    MX6_PAD_CSI0_DAT17__UART4_CTS_B | MUX_PAD_CTRL(UART_PAD_CTRL),
};

static void setup_uart(void)
{
    imx_iomux_v3_setup_multiple_pads(uart1_pads, ARRAY_SIZE(uart1_pads));
    imx_iomux_v3_setup_multiple_pads(uart2_pads, ARRAY_SIZE(uart2_pads));
    imx_iomux_v3_setup_multiple_pads(uart3_pads, ARRAY_SIZE(uart3_pads));
    imx_iomux_v3_setup_multiple_pads(uart4_pads, ARRAY_SIZE(uart4_pads));
}

/* setup i2c */
#ifdef CONFIG_SYS_I2C_MXC

iomux_v3_cfg_t const i2c1_pads[] = {
    MX6_PAD_CSI0_DAT8__I2C1_SDA | MUX_PAD_CTRL(I2C_PAD_CTRL),
    MX6_PAD_CSI0_DAT9__I2C1_SCL | MUX_PAD_CTRL(I2C_PAD_CTRL),
};

iomux_v3_cfg_t const i2c2_pads[] = {
};

iomux_v3_cfg_t const i2c3_pads[] = {
};

static void ws_setup_i2c(unsigned int module_base)
{
    unsigned int reg;

    switch (module_base) {
        case I2C1_BASE_ADDR:
            /* i2c1 #1 */
            imx_iomux_v3_setup_multiple_pads(i2c1_pads, ARRAY_SIZE(i2c1_pads));

            /* Enable i2c clock */
            reg = readl(CCM_CCGR2);
            reg |= 0xC0;
            writel(reg, CCM_CCGR2);

            break;
    
        case I2C2_BASE_ADDR:
            /* i2c1 #2 */
            imx_iomux_v3_setup_multiple_pads(i2c2_pads, ARRAY_SIZE(i2c2_pads));

            /* Enable i2c clock */
            reg = readl(CCM_CCGR2);
            reg |= 0x300;
            writel(reg, CCM_CCGR2);

            break;

        case I2C3_BASE_ADDR:
            /* i2c1 #3 */
            imx_iomux_v3_setup_multiple_pads(i2c3_pads, ARRAY_SIZE(i2c3_pads));

            /* Enable i2c clock */
            reg = readl(CCM_CCGR2);
            reg |= 0xC00;
            writel(reg, CCM_CCGR2);

            break;

        default:
            printf("Invalid I2C base: 0x%x\n", module_base);
            break;
    }
}

#ifdef CONFIG_LDO_BYPASS_CHECK

void ldo_mode_set(int ldo_bypass)
{
}

#endif /* CONFIG_LDO_BYPASS_CHECK */

#endif /* CONFIG_SYS_I2C_MXC */

/* setup spinor */
#ifdef CONFIG_MXC_SPI

#define SPI1_SS0_GPIO	IMX_GPIO_NR(2, 30)

iomux_v3_cfg_t const ecspi1_pads[] = {
    MX6_PAD_EIM_D16__ECSPI1_SCLK | MUX_PAD_CTRL(SPI_PAD_CTRL),
    MX6_PAD_EIM_D17__ECSPI1_MISO | MUX_PAD_CTRL(SPI_PAD_CTRL),
    MX6_PAD_EIM_D18__ECSPI1_MOSI | MUX_PAD_CTRL(SPI_PAD_CTRL),
    MX6_PAD_EIM_EB2__GPIO2_IO30 | MUX_PAD_CTRL(NO_PAD_CTRL),     /* ss0 */
};

static void setup_spinor(void)
{
    imx_iomux_v3_setup_multiple_pads(ecspi1_pads, ARRAY_SIZE(ecspi1_pads));
    puts("");
    gpio_direction_output(SPI1_SS0_GPIO, 0); 
}

int board_spi_cs_gpio(unsigned bus, unsigned cs)
{
    return (bus == 0 && cs == 0) ? (SPI1_SS0_GPIO) : -1;
}

#endif /* CONFIG_MXC_SPI */

/* setup sd */
#ifdef CONFIG_CMD_MMC

struct fsl_esdhc_cfg usdhc_cfg[1] = {
    {USDHC3_BASE_ADDR}
};

iomux_v3_cfg_t const usdhc3_pads[] = {
    MX6_PAD_SD3_CLK__SD3_CLK | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_CMD__SD3_CMD | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_DAT0__SD3_DATA0 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_DAT1__SD3_DATA1 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_DAT2__SD3_DATA2 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_DAT3__SD3_DATA3 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_DAT4__SD3_DATA4 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_DAT5__SD3_DATA5 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_DAT6__SD3_DATA6 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_DAT7__SD3_DATA7 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
    MX6_PAD_SD3_RST__SD3_RESET | MUX_PAD_CTRL(USDHC_PAD_CTRL),
};

int board_mmc_get_env_dev(int devno)
{
    u32 soc_sbmr = readl(SRC_BASE_ADDR + 0x4);
    u32 dev_no;

    /* BOOT_CFG1[5] - 0 = uSD, 1 = eMMc */
    dev_no = (soc_sbmr & 0x00000020) >> 5;

    return dev_no;
}

int board_mmc_getcd(struct mmc *mmc)
{
    struct fsl_esdhc_cfg *cfg = (struct fsl_esdhc_cfg *)mmc->priv;
    int ret = 0;

    switch (cfg->esdhc_base) {
        case USDHC3_BASE_ADDR:
           ret = 1;
           break;
    }

    return ret;
}

int board_mmc_init(bd_t *bis)
{
    s32 status = 0;
    u32 index = 0;

    /* According to the board_mmc_init() the following map is done: */
    /* (U-boot device node)    (Physical Port) */
    /*    mmc0                    eMMC */
    for (index = 0; index < CONFIG_SYS_FSL_USDHC_NUM; index++)
    {
        switch (index) {
            case 0:
                imx_iomux_v3_setup_multiple_pads(usdhc3_pads, ARRAY_SIZE(usdhc3_pads));
                usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC3_CLK);
                break;

            default:
                printf("Warning: you configured more USDHC controllers"
                    "(%d) then supported by the board (%d)\n",
                    index + 1, CONFIG_SYS_FSL_USDHC_NUM);
                return status;
        }

        status |= fsl_esdhc_initialize(bis, &usdhc_cfg[index]);
    }

    return status;
}

#endif /* CONFIG_CMD_MMC */

/* setup ethernet */
#ifdef CONFIG_FEC_MXC

int mx6_rgmii_rework(struct phy_device *phydev)
{
    unsigned short value;

    phy_write(phydev, MDIO_DEVAD_NONE, MII_CTRL1000, 0x1c00);

    /* ctrl pad skew - reg idx 0x2 addr 0x4 */
    ksz9031_phy_extended_write(phydev, 0x02,
        MII_KSZ9031_EXT_RGMII_CTRL_SIG_SKEW, 
        MII_KSZ9031_MOD_DATA_NO_POST_INC, 0x0000);
    
    /* rx pad skew - reg idx 0x2 addr 0x5 */
    ksz9031_phy_extended_write(phydev, 0x02,
        MII_KSZ9031_EXT_RGMII_RX_DATA_SKEW,
        MII_KSZ9031_MOD_DATA_NO_POST_INC, 0x0000);
    
    /* tx pad skew - reg idx 0x2 addr 0x6 */
    ksz9031_phy_extended_write(phydev, 0x02,
        MII_KSZ9031_EXT_RGMII_TX_DATA_SKEW,
        MII_KSZ9031_MOD_DATA_NO_POST_INC, 0x0000);
    
    /* clock pad skew - reg idx 0x2 addr 0x8 */
    ksz9031_phy_extended_write(phydev, 0x02,
        MII_KSZ9031_EXT_RGMII_CLOCK_SKEW,
        MII_KSZ9031_MOD_DATA_NO_POST_INC, 0x03FF);

    /* enable reg 0 for auto-negotiation */
    value = phy_read(phydev, MDIO_DEVAD_NONE, 0x0);

    /* 100 Mbps	 */
    value |= 0x3200;
    value &= 0xFFBF;
    phy_write(phydev, MDIO_DEVAD_NONE, 0x0, value);

    return 0;
}

int board_phy_config(struct phy_device *phydev)
{
    mx6_rgmii_rework(phydev);

    if (phydev->drv->config)
        phydev->drv->config(phydev);

    return 0;
}

iomux_v3_cfg_t const enet_pads[] = {
    MX6_PAD_ENET_MDIO__ENET_MDIO | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_ENET_MDC__ENET_MDC | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_TXC__RGMII_TXC | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_TD0__RGMII_TD0 | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_TD1__RGMII_TD1 | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_TD2__RGMII_TD2 | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_TD3__RGMII_TD3 | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_TX_CTL__RGMII_TX_CTL | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_ENET_REF_CLK__ENET_TX_CLK | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_RXC__RGMII_RXC | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_RD0__RGMII_RD0 | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_RD1__RGMII_RD1 | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_RD2__RGMII_RD2 | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_RD3__RGMII_RD3 | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_RGMII_RX_CTL__RGMII_RX_CTL | MUX_PAD_CTRL(ENET_PAD_CTRL),
    MX6_PAD_ENET_TX_EN__GPIO1_IO28 | MUX_PAD_CTRL(NO_PAD_CTRL),  /* Micrel RGMII Phy Interrupt */
    MX6_PAD_EIM_BCLK__GPIO6_IO31 | MUX_PAD_CTRL(NO_PAD_CTRL),  /* Micrel RGMII Reset */
};

int board_eth_init(bd_t *bis)
{
    uint32_t base = IMX_FEC_BASE;
    struct mii_dev *bus = NULL;
    struct phy_device *phydev = NULL;
    int ret;

    imx_iomux_v3_setup_multiple_pads(enet_pads, ARRAY_SIZE(enet_pads));

    gpio_direction_output(IMX_GPIO_NR(6, 31), 0);  /* assert PHY rst */
    udelay(1000);
    gpio_set_value(IMX_GPIO_NR(6, 31), 1);  /* deassert PHY rst */

    /* Need 100ms delay to exit from reset. */
    udelay(1000 * 100);

    bus = fec_get_miibus(base, -1);
    if (!bus)
        return 0;

    /* scan phy 0,1,2,3,4,5,6,7 */
    phydev = phy_find_by_mask(bus, 0xff, PHY_INTERFACE_MODE_RGMII);

    if (!phydev) {
        free(bus);
        return 0;
    }
    printf("using phy at %d\n", phydev->addr);
    ret = fec_probe(bis, -1, base, bus, phydev);
    if (ret) {
        printf("FEC MXC: %s:failed\n", __func__);
        free(phydev);
        free(bus);
    }

    return 0;
}

#endif /* CONFIG_FEC_MXC */

/* setup gpio */
iomux_v3_cfg_t const gpio_pads[] = {
    MX6_PAD_GPIO_0__GPIO1_IO00 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* pcie_wake_n */
    MX6_PAD_GPIO_1__GPIO1_IO01 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* pcie_dis_n */
    MX6_PAD_GPIO_2__GPIO1_IO02 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* pcie_rst# */
    MX6_PAD_GPIO_3__GPIO1_IO03 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* gpio0 */
    MX6_PAD_GPIO_4__GPIO1_IO04 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* gpio1 */
    MX6_PAD_GPIO_5__GPIO1_IO05 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* gpio2 */
    MX6_PAD_GPIO_6__GPIO1_IO06 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* gpio3 */
    MX6_PAD_GPIO_7__GPIO1_IO07 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* uart4_te */
    MX6_PAD_GPIO_8__GPIO1_IO08 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* id0 */
    MX6_PAD_GPIO_9__GPIO1_IO09 | MUX_PAD_CTRL(NO_PAD_CTRL),         /* id1 */
    MX6_PAD_EIM_D21__GPIO3_IO21 | MUX_PAD_CTRL(NO_PAD_CTRL),        /* usb_hub_reset_n */
    MX6_PAD_CSI0_DAT12__GPIO5_IO30 | MUX_PAD_CTRL(NO_PAD_CTRL),     /* uart2_rxen# */
    MX6_PAD_CSI0_DAT13__GPIO5_IO31 | MUX_PAD_CTRL(NO_PAD_CTRL),     /* uart4_rxen# */
    MX6_PAD_CSI0_DAT14__GPIO6_IO00 | MUX_PAD_CTRL(NO_PAD_CTRL),     /* uart3_rxen# */
    MX6_PAD_CSI0_PIXCLK__GPIO5_IO18 | MUX_PAD_CTRL(NO_PAD_CTRL),    /* uart2_te# */
    MX6_PAD_CSI0_DAT16__GPIO6_IO02 | MUX_PAD_CTRL(NO_PAD_CTRL),     /* uart3_te# */
    MX6_PAD_NANDF_CLE__GPIO6_IO07 | MUX_PAD_CTRL(NO_PAD_CTRL),      /* usb_otg_pwr_en */
    MX6_PAD_NANDF_ALE__GPIO6_IO08 | MUX_PAD_CTRL(NO_PAD_CTRL),      /* spi1_wp# */
    MX6_PAD_NANDF_CS0__GPIO6_IO11 | MUX_PAD_CTRL(NO_PAD_CTRL),      /* pmic_int_n */
    MX6_PAD_NANDF_CS1__GPIO6_IO14 | MUX_PAD_CTRL(NO_PAD_CTRL),      /* usb_otg_oc */
    MX6_PAD_GPIO_16__GPIO7_IO11 | MUX_PAD_CTRL(NO_PAD_CTRL)         /* id2 */
};

void board_gpio_init(void)
{
    imx_iomux_v3_setup_multiple_pads(gpio_pads, ARRAY_SIZE(gpio_pads));

    /* gpio1 */
    /* input bits: 9,8 */
    /* output bits: 26,7,6,5,4,3,2,1,0 */
    gpio_direction_input(IMX_GPIO_NR(1, 9));        /* 9 - id1 */
    gpio_direction_input(IMX_GPIO_NR(1, 8));        /* 8 - id0 */
    gpio_direction_output(IMX_GPIO_NR(1, 7), 0);    /* 7 - uart4_te# */
    gpio_direction_output(IMX_GPIO_NR(1, 6), 0);    /* 6 - gpio3 */
    gpio_direction_output(IMX_GPIO_NR(1, 5), 0);    /* 5 - gpio2 */
    gpio_direction_output(IMX_GPIO_NR(1, 4), 0);    /* 4 - gpio1 */
    gpio_direction_output(IMX_GPIO_NR(1, 3), 0);    /* 3 - gpio0 */
    gpio_direction_output(IMX_GPIO_NR(1, 2), 1);    /* 2 - pcie_rst# */
    gpio_direction_output(IMX_GPIO_NR(1, 1), 1);    /* 1 - pcie_dis_n */
    gpio_direction_output(IMX_GPIO_NR(1, 0), 0);    /* 0 - pcie_wake_n */

    /* gpio3 */
    /* output bits: 21 */
    gpio_direction_output(IMX_GPIO_NR(3, 21), 1);   /* 85 - usb_hub_reset_n */

    /* gpio5 */
    /* output bits: 31,30,18 */
    gpio_direction_output(IMX_GPIO_NR(5, 31), 0);   /* 159 - uart4_rxen# */
    gpio_direction_output(IMX_GPIO_NR(5, 30), 0);   /* 158 - uart2_rxen# */
    gpio_direction_output(IMX_GPIO_NR(5, 18), 0);   /* 146 - uart2_te# */

    /* gpio6 */
    /* input bits: 14,11 */
    /* output bits: 31,8,7,2,0 */
    gpio_direction_output(IMX_GPIO_NR(6, 31), 1);   /* 191 - rgmii_reset_n */
    gpio_direction_input(IMX_GPIO_NR(6, 14));       /* 174 - usb_otg_oc */
    gpio_direction_input(IMX_GPIO_NR(6, 11));       /* 171 - pmic_int_n */
    gpio_direction_output(IMX_GPIO_NR(6, 8), 1);    /* 168 - spi1_wp# */
    gpio_direction_output(IMX_GPIO_NR(6, 7), 1);    /* 167 - usb_otg_pwr_en */
    gpio_direction_output(IMX_GPIO_NR(6, 2), 0);    /* 162 - uart3_te# */
    gpio_direction_output(IMX_GPIO_NR(6, 0), 0);    /* 160 - uart3_rxen# */

    /* gpio7 */
    /* input bits: 11 */
    gpio_direction_input(IMX_GPIO_NR(7, 11));       /* 203 - id2 */
}

#ifdef CONFIG_USB_EHCI_MX6

iomux_v3_cfg_t const usb_otg1_pads[] = {
    MX6_PAD_NANDF_CLE__GPIO6_IO07 | MUX_PAD_CTRL(NO_PAD_CTRL), /* otg power */
    MX6_PAD_ENET_RX_ER__USB_OTG_ID | MUX_PAD_CTRL(NO_PAD_CTRL) /* otg id */
};

int board_ehci_hcd_init(int port)
{
    switch (port) {
    case 0:
        imx_iomux_v3_setup_multiple_pads(usb_otg1_pads,
            ARRAY_SIZE(usb_otg1_pads));
        break;

    default:
        printf("MXC USB port %d not yet supported\n", port);
        return 1;
    }

    return 0;
}

#endif /* CONFIG_USB_EHCI_MX6 */

#ifdef CONFIG_IMX_UDC

iomux_v3_cfg_t const otg_udc_pads[] = {
    (MX6_PAD_ENET_RX_ER__USB_OTG_ID | MUX_PAD_CTRL(NO_PAD_CTRL)),
};

void udc_pins_setting(void)
{
    imx_iomux_v3_setup_multiple_pads(otg_udc_pads,
        ARRAY_SIZE(otg_udc_pads));

    /* set daisy chain for otg_pin_id on 6q. for 6dl, bit is reserved */
    mxc_iomux_set_gpr_register(1, 13, 1, 0);
}

#endif /*CONFIG_IMX_UDC*/

/* Do not overwrite the console */
/* Use always serial for U-Boot console */
int overwrite_console(void)
{
    return 1;
}

/* the following functions are board specific and override existing functions within the source tree */

int board_early_init_f(void)
{
    setup_uart();

    /* gpio init */
    board_gpio_init();

    return 0;
}

int board_init(void)
{
    /* address of boot parameters */
    gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

    #ifdef CONFIG_SYS_I2C_MXC
    /* i2c init */
    ws_setup_i2c(I2C1_BASE_ADDR);
    #endif

    #ifdef CONFIG_MXC_SPI
    setup_spinor();
    #endif

    return 0;
}

int board_late_init(void)
{
    /* watchdog init */
    imx_iomux_v3_setup_pad(MX6_PAD_SD1_DAT2__WDOG1_B);

    #ifdef CONFIG_ENV_IS_IN_MMC
    board_late_mmc_env_init();
    #endif

    return 0;
}
