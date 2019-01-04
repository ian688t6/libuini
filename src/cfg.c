/**
 * @file	: cfg.c
 * @brief	: cfg 配置文件读写
 * @version :
 * @author	: jyin
 * @date	: Jun 19, 2018
 */
#include "os.h"
#include "dbg.h"
#include "ini.h"
#include "cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t cfg_sig_op(cfg_op_e em_op, char *pc_path, void *pv_cfg, handle_op pf_handle)
{
	FILE *pf_ini = NULL;

	switch (em_op)
	{
	case CFG_OP_SET:
		pf_ini = ini_open(pc_path, "w");
		break;

	case CFG_OP_GET:
		pf_ini = ini_open(pc_path, "rb");
		break;
	}

	if ((NULL == pf_ini) || (NULL == pv_cfg) || (NULL == pf_handle))
	{
		loge("ini_open failed");
		return -1;
	}
	pf_handle(em_op, pf_ini, pv_cfg);

	ini_close(pf_ini);

	return 0;
}

int32_t cfg_multi_op(cfg_op_e em_op, char *pc_path, void *pv_cfg, uint32_t ui_size, uint32_t ui_max_cnt, handle_op pf_handle)
{
	uint32_t i 			= 0;
	uint8_t *puc_cfg 	= (uint8_t *)pv_cfg;
	FILE *pf_ini 			= NULL;
	char *pc_section_name 	= NULL;
	char *pc_section_temp 	= NULL;
	char ac_section_temp[32] = {0};
	char ac_section_name[32] = {0};

	switch (em_op)
	{
	case CFG_OP_SET:
		pf_ini = ini_open(pc_path, "w");
		break;

	case CFG_OP_GET:
		pf_ini = ini_open(pc_path, "rb");
		break;
	}

	if ((NULL == pf_ini) || (NULL == pv_cfg) || (NULL == pf_handle) || (1 >= ui_max_cnt))
	{
		loge("ini_open failed");
		return -1;
	}

	pc_section_name = strrchr(pc_path, '/');
	if (NULL == pc_section_name)
	{
		pc_section_name = pc_path;
	}
	else
	{
		pc_section_name ++;
	}
	pc_section_temp = ac_section_temp;
	while ('.' != *pc_section_name)
		*pc_section_temp ++ = *pc_section_name ++;

	for (i = 0; i < ui_max_cnt; i ++)
	{
		snprintf(ac_section_name, sizeof(ac_section_name), "[%s-%d]", ac_section_temp, i);
		if (0 == ini_op_section(em_op, pf_ini, ac_section_name))
		{
			pf_handle(em_op, pf_ini, &puc_cfg[i * ui_size]);
		}
	}

	ini_close(pf_ini);

	return 0;
}

#ifdef __cplusplus
}
#endif
