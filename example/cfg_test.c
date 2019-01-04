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
#include "cfg_test.h"

#ifdef __cplusplus
extern "C" {
#endif

CFG_INI(cfg_stu_info_s)
{
	INI_STRING_OP(cfg_stu_info_s, CFG_STU_NAME, 		ac_name);
	INI_STRING_OP(cfg_stu_info_s, CFG_STU_ID, 			ac_id);
	INI_UINT_OP(cfg_stu_info_s, CFG_STU_AGE, 			ui_age);
	INI_UINT_OP(cfg_stu_info_s, CFG_STU_SCORE, 			ui_score);
}

#ifdef __cplusplus
}
#endif

