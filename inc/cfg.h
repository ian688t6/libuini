/**
 * @file	: cfg.h
 * @brief	: dvr 配置管理模块
 * @version :
 * @author	: jyin
 * @date	: Jun 19, 2018
 */

#ifndef __CFG_H__
#define __CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ini.h"
#define CFG_STR_LEN 	(64)

typedef enum
{
	CFG_OP_GET = 0,
	CFG_OP_SET = 0x1,
} cfg_op_e;

typedef enum
{
	CFG_TYPE_SINGLE = 0,
	CFG_TYPE_MULTI	= 0x02,
} cfg_type_e;

#define CFG_OP_MASK			(0x01)
#define CFG_TYPE_MASK		(0x02)

#define INI_STRING_OP(name, key, val) \
	ini_op(em_op, pf_ini, INI_TYPE_STRING, key, ((name *)pst_ini)->val, sizeof(((name *)pst_ini)->val))

#define INI_UINT_OP(name, key, val) \
	ini_op(em_op, pf_ini, INI_TYPE_UINT, key, &((name *)pst_ini)->val, sizeof(((name *)pst_ini)->val))

#define CFG_INI(name) \
	void cfg_##name##_cb(cfg_op_e em_op, FILE *pf_ini, void *pst_ini)

#define CFG_INI_DECLARE(name) \
	extern void cfg_##name##_cb(cfg_op_e em_op, FILE *pf_ini, void *pst_ini);

#define CFG_CB(name) cfg_##name##_cb

typedef void (*handle_op)(cfg_op_e em_op, FILE *pf_file, void *pv_cfg);

extern int32_t cfg_sig_op(cfg_op_e em_op, char *pc_path, void *pv_cfg, handle_op pf_handle);

extern int32_t cfg_multi_op(cfg_op_e em_op, char *pc_path, void *pv_cfg, uint32_t ui_size, uint32_t ui_max_cnt, handle_op pf_handle);

static inline int32_t cfg_op(uint32_t ui_op, const char *pc_path, void *pv_cfg, handle_op pf_handle, ...)
{
	int32_t  i_ret		= 0;
	uint32_t ui_opt		= 0;
	uint32_t ui_size	= 0;
	uint32_t ui_max_cnt = 0;
	char 	*pc_cfg		= strdup(pc_path);
	va_list ap;
	
	ui_opt = (ui_op & CFG_OP_MASK);
	if (CFG_TYPE_MULTI == (ui_op & CFG_TYPE_MASK))
	{
		va_start(ap, pf_handle);
		ui_size 	= va_arg(ap, uint32_t);
		ui_max_cnt 	= va_arg(ap, uint32_t);
		va_end(ap);
		i_ret = cfg_multi_op((cfg_op_e)ui_opt, pc_cfg, pv_cfg, ui_size, ui_max_cnt, pf_handle);
	}
	else
	{
		i_ret = cfg_sig_op((cfg_op_e)ui_opt, pc_cfg, pv_cfg, pf_handle);
	}
	free(pc_cfg);

	return i_ret;
}


#ifdef __cplusplus
}
#endif
#endif /* CFG_H_ */
