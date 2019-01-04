/**
 * @file	: ini.c
 * @brief	: ini 配置文件读写
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

static char *skip_whitespace(char *pc_s)
{
	while (isspace(*pc_s))
	{
		++ pc_s;
	}
	return pc_s;
}

static int32_t compare_section(char *pc_src, char *pc_dst)
{
	while ((']' != *pc_dst))
	{
		if (*pc_dst ++ != *pc_src ++)
			return -1;
	}

	return 0;
}

FILE *ini_open(const char *pc_inifile, const char *pc_open_type)
{
	if (NULL == pc_inifile)
	{
		loge("ini_open invalid param!");
		return NULL;
	}

	return fopen(pc_inifile, pc_open_type);
}

int32_t ini_read(FILE *pf_file, ini_type_e em_type, char *pc_key, void *pv_value, uint32_t ui_len)
{
	char ac_line[256] = {0};
	char ac_key[CFG_STR_LEN] = {0};
	char ac_val[CFG_STR_LEN] = {0};
	char *pc_temp = NULL;
	uint32_t ui_cur_pos = 0;
	uint32_t *pui_value = (uint32_t *)pv_value;
	char *pc_value = (char *)pv_value;

	if ((NULL == pf_file) || (NULL == pc_key) || (NULL == pv_value) || (0 >= ui_len))
	{
		loge("ini_write invalid input param!");
		return -1;
	}

//	rewind(pf_file);
	while (!feof(pf_file))
	{
        if (NULL == fgets(ac_line, sizeof(ac_line), pf_file))
			continue;

		pc_temp = strrchr(ac_line, '\n');
		if (pc_temp) {
			*pc_temp = '\0';
		}
     
		pc_temp = skip_whitespace(ac_line);
        if ('#' == *pc_temp)
        {
        	//logi("is comment");
        	continue;
        }

        if (('\n' == *pc_temp) || ('\r' == *pc_temp) || ('\t' == *pc_temp) || ('\0' == *pc_temp))
        {
        	continue;
        }

        if (('[' == pc_temp[0]))
        {
        	ui_cur_pos = ftell(pf_file);
        	fseek(pf_file, ui_cur_pos - (strlen(pc_temp)), SEEK_SET);
        	break;
        }

        sscanf(pc_temp, "%[^=]=%[^=]", ac_key, ac_val);
        if ((0 == strcmp(ac_key, pc_key)) && strlen(ac_val))
        {
        	switch (em_type)
        	{
        	case INI_TYPE_UINT:
    			*pui_value = strtoul(ac_val, NULL, 10);
			break;

        	case INI_TYPE_STRING:
				printf("len: %d\n", (uint32_t)strlen(ac_val));
				strncpy(pc_value, ac_val, ui_len-1);
			break;

        	default:
        		break;
        	}
        	break;
        }
    }

	return 0;
}

int32_t ini_write(FILE *pf_file, ini_type_e em_type, char *pc_key, void *pv_value, uint32_t ui_len)
{
	uint32_t ui_value = 0;
	char *pc_value = NULL;

	if ((NULL == pf_file) || (NULL == pc_key) || (NULL == pv_value) || (0 >= ui_len))
	{
		loge("ini_write invalid input param!");
		return -1;
	}

	switch (em_type)
	{
	case INI_TYPE_UINT:
		ui_value = *(uint32_t *)pv_value;
//		logi("write key = %s value = %d", pc_key, ui_value);
		fprintf(pf_file, "%s=%d\n", pc_key, ui_value);
		break;

	case INI_TYPE_STRING:
		pc_value = (char *)pv_value;
//		logi("write key = %s value = %s", pc_key, pc_value);
		fprintf(pf_file, "%s=%s\n", pc_key, pc_value);
		break;

	default:
		break;
	}

	return 0;
}

int32_t ini_op(ini_op_e em_op, FILE *pf_file, ini_type_e em_type, char *pc_key, void *pv_value, uint32_t ui_len)
{
	int32_t i_ret = 0;

	if ((NULL == pf_file) || (NULL == pc_key) || (NULL == pv_value) || (0 >= ui_len))
	{
		loge("ini_op invalid input param!");
		return -1;
	}

	switch (em_op)
	{
	case INI_OP_SET:
		i_ret = ini_write(pf_file, em_type, pc_key, pv_value, ui_len);
		break;

	case INI_OP_GET:
		i_ret = ini_read(pf_file, em_type, pc_key, pv_value, ui_len);
		break;

	default:

		break;
	}
	return i_ret;
}

int32_t ini_write_section(FILE *pf_file, char *pc_section)
{
	fprintf(pf_file, "%s\n", pc_section);
	return 0;
}

int32_t ini_read_section(FILE *pf_file, char *pc_section)
{
	char ac_line[256] = {0};
	char *pc_temp = NULL;

//	logi("pc_section: %s 1", pc_section);
	while (!feof(pf_file))
	{
        if (NULL == fgets(ac_line, sizeof(ac_line), pf_file))
			continue;

		pc_temp = strrchr(ac_line, '\n');
		if (pc_temp) {
			*pc_temp = '\0';
		}

        pc_temp = skip_whitespace(ac_line);
        if ('#' == *pc_temp)
        {
 //       	logi("is comment");
        	continue;
        }

        if (('\n' == *pc_temp) || ('\r' == *pc_temp) || ('\t' == *pc_temp) || ('\0' == *pc_temp))
        {
        	continue;
        }

        if (('[' == pc_temp[0]))
        {
        	if (0 == compare_section(pc_temp, pc_section))
        	{
//        		logi("1 match section  %s",pc_section);
            	return 0;
        	}
        }
	}

	return -1;
}

int32_t ini_op_section(ini_op_e em_op, FILE *pf_file, char *pc_section)
{
	int32_t i_ret = 0;

	switch (em_op)
	{
	case INI_OP_SET:
		i_ret = ini_write_section(pf_file, pc_section);
		break;

	case INI_OP_GET:
		i_ret = ini_read_section(pf_file, pc_section);
		break;

	default:

		break;
	}

	return i_ret;
}

void ini_close(FILE *pf_file)
{
	if (NULL == pf_file)
	{
		loge("ini_close invalid param!");
		return;
	}
	fclose(pf_file);

	return;
}

#ifdef __cplusplus
}
#endif
