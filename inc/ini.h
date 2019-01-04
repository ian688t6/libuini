/**
 * @file	: ini.h
 * @brief	: ini 配置文件读写
 * @version :
 * @author	: jyin
 * @date	: Jun 19, 2018
 */
#ifndef __INI_H__
#define __INI_H__
#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	INI_TYPE_UINT = 0,
	INI_TYPE_STRING = 1,
} ini_type_e;

typedef enum
{
	INI_OP_GET = 0,
	INI_OP_SET = 1,
} ini_op_e;

extern FILE *ini_open(const char *pc_inifile, const char *pc_open_type);

extern void ini_close(FILE *pf_file);

extern int32_t ini_op(ini_op_e em_op, FILE *pf_file, ini_type_e em_type, char *pc_key, void *pv_value, uint32_t ui_len);

extern int32_t ini_read(FILE *pf_file, ini_type_e em_type, char *pc_key, void *pv_value, uint32_t ui_len);

extern int32_t ini_write(FILE *pf_file, ini_type_e em_type, char *pc_key, void *pv_value, uint32_t ui_len);

extern int32_t ini_op_section(ini_op_e em_op, FILE *pf_file, char *pc_section);

extern int32_t ini_write_section(FILE *pf_file, char *pc_section);

extern int32_t ini_read_section(FILE *pf_file, char *pc_section);

#ifdef __cplusplus
}
#endif
#endif /* LIBCFG_INI_H_ */

