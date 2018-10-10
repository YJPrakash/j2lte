/* drivers/video/decon_display/s6e3ha0k_lcd_ctrl.c
 *
 * Samsung SoC MIPI LCD CONTROL functions
 *
 * Copyright (c) 2014 Samsung Electronics
 *
 * Jiun Yu, <jiun.yu@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
//#include "s6e3ha2k_gamma.h"
#include "s6e3ha2k_param.h"
#include "lcd_ctrl.h"
#include "../decon_display/dsim_reg.h"

//#define CONFIG_FB_I80_COMMAND_MODE
//#define GAMMA_PARAM_SIZE 26

/* Porch values. It depends on command or video mode */
#define S6E3HA2K_CMD_VBP	15
#define S6E3HA2K_CMD_VFP	1
#define S6E3HA2K_CMD_VSA	1
#define S6E3HA2K_CMD_HBP	1
#define S6E3HA2K_CMD_HFP	1
#define S6E3HA2K_CMD_HSA	1

/* These need to define */
#define S6E3HA2K_VIDEO_VBP	15
#define S6E3HA2K_VIDEO_VFP	1
#define S6E3HA2K_VIDEO_VSA	1
#define S6E3HA2K_VIDEO_HBP	20
#define S6E3HA2K_VIDEO_HFP	20
#define S6E3HA2K_VIDEO_HSA	20

#define S6E3HA2K_HORIZONTAL	1440
#define S6E3HA2K_VERTICAL	2560
#if 0
struct decon_lcd s6e3ha2k_lcd_info = {
#ifdef CONFIG_FB_I80_COMMAND_MODE
	.mode = COMMAND_MODE,
	.vfp = S6E3HA2K_CMD_VFP,
	.vbp = S6E3HA2K_CMD_VBP,
	.hfp = S6E3HA2K_CMD_HFP,
	.hbp = S6E3HA2K_CMD_HBP,
	.vsa = S6E3HA2K_CMD_VSA,
	.hsa = S6E3HA2K_CMD_HSA,
#else
	.mode = VIDEO_MODE,
	.vfp = S6E3HA2K_VIDEO_VFP,
	.vbp = S6E3HA2K_VIDEO_VBP,
	.hfp = S6E3HA2K_VIDEO_HFP,
	.hbp = S6E3HA2K_VIDEO_HBP,
	.vsa = S6E3HA2K_VIDEO_VSA,
	.hsa = S6E3HA2K_VIDEO_HSA,
#endif
	.xres = S6E3HA2K_HORIZONTAL,
	.yres = S6E3HA2K_VERTICAL,

	/* Maybe, width and height will be removed */
	.width = 70,
	.height = 121,

	/* Mhz */
	.hs_clk = 1100,
	.esc_clk = 20,

	.fps = 60,
	.mic_enabled = 1,
	.mic_ver = MIC_VER_1_2,
};

struct decon_lcd *decon_get_lcd_info(void)
{
	return &s6e3ha2k_lcd_info;
}
#endif
/*
 * 3HA2K lcd init sequence
 *
 * Parameters
 *	- mic_enabled : if mic is enabled, MIC_ENABLE command must be sent
 *	- mode : LCD init sequence depends on command or video mode
 */

void lcd_init(struct decon_lcd *lcd)
{
	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_TEST_KEY_ON_F0,
				ARRAY_SIZE(SEQ_TEST_KEY_ON_F0)) < 0)
		dsim_err("fail to write KEY_ON init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_REG_F2,
				ARRAY_SIZE(SEQ_REG_F2)) < 0)
		dsim_err("fail to write F2 init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_REG_F9,
				ARRAY_SIZE(SEQ_REG_F9)) < 0)
		dsim_err("fail to write F9 init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_SHORT_WRITE, (u32)SEQ_SLEEP_OUT[0], 0) < 0)
		dsim_err("fail to write SLEEP_OUT init command.\n");

	msleep(120);

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_REG_F2,
				ARRAY_SIZE(SEQ_REG_F2)) < 0)
		dsim_err("fail to write F2 init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_SHORT_WRITE, SEQ_TE_ON[0], 0) < 0)
		dsim_err("fail to write TE_on init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_TOUCH_HSYNC,
				ARRAY_SIZE(SEQ_TOUCH_HSYNC)) < 0)
		dsim_err("fail to write TOUCH_HSYNC init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_PENTILE_CONTROL,
				ARRAY_SIZE(SEQ_PENTILE_CONTROL)) < 0)
		dsim_err("fail to write PENTILE_CONTROL init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_COLUMN_ADDRESS,
				ARRAY_SIZE(SEQ_COLUMN_ADDRESS)) < 0)
		dsim_err("fail to write COLUMN_ADDRESS init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_GAMMA_CONDITION_SET,
				ARRAY_SIZE(SEQ_GAMMA_CONDITION_SET)) < 0)
		dsim_err("fail to write GAMMA_CONDITION_SET init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_AID_SET,
				ARRAY_SIZE(SEQ_AID_SET)) < 0)
		dsim_err("fail to write AID_SET init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_ELVSS_SET,
				ARRAY_SIZE(SEQ_ELVSS_SET)) < 0)
		dsim_err("fail to write ELVSS_SET init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_GAMMA_UPDATE,
				ARRAY_SIZE(SEQ_GAMMA_UPDATE)) < 0)
		dsim_err("fail to write GAMMA_UPDATE init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_ACL_OFF,
				ARRAY_SIZE(SEQ_ACL_OFF)) < 0)
		dsim_err("fail to write ACL_OFF init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_ACL_OPR,
				ARRAY_SIZE(SEQ_ACL_OPR)) < 0)
		dsim_err("fail to write ACL_OPR init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_HBM_OFF,
				ARRAY_SIZE(SEQ_HBM_OFF)) < 0)
		dsim_err("fail to write HBM_OFF init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_TSET_GLOBAL,
				ARRAY_SIZE(SEQ_TSET_GLOBAL)) < 0)
		dsim_err("fail to write TSET_GLOBAL init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_TSET,
				ARRAY_SIZE(SEQ_TSET)) < 0)
		dsim_err("fail to write TSET init command.\n");

	if (dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_TEST_KEY_OFF_F0,
				ARRAY_SIZE(SEQ_TEST_KEY_OFF_F0)) < 0)
		dsim_err("fail to write KEY_OFF init command.\n");
}

void lcd_enable(void)
{
	if (dsim_wr_data(MIPI_DSI_DCS_SHORT_WRITE, (u32)SEQ_DISPLAY_ON[0], 0) < 0)
		dsim_err("fail to write DISPLAY_ON command.\n");
}

void lcd_disable(void)
{
	/* This function needs to implement */
}

/*
 * Set gamma values
 *
 * Parameter
 *	- backlightlevel : It is from 0 to 26.
 */
int lcd_gamma_ctrl(u32 backlightlevel)
{
/* This will be implemented
	int ret;
	ret = dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)gamma22_table[backlightlevel],
			GAMMA_PARAM_SIZE);
	if (ret) {
		dsim_err("fail to write gamma value.\n");
		return ret;
	}
*/
	return 0;
}

int lcd_gamma_update(void)
{
/* This will be implemented
	int ret;
	ret = dsim_wr_data(MIPI_DSI_DCS_LONG_WRITE, (u32)SEQ_GAMMA_UPDATE,
			ARRAY_SIZE(SEQ_GAMMA_UPDATE));
	if (ret) {
		dsim_err("fail to update gamma value.\n");
		return ret;
	}
*/
	return 0;
}
