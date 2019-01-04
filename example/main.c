#include "os.h"
#include "dbg.h"
#include "cfg.h"
#include "cfg_test.h"

int32_t main(int32_t i_argc, char *pc_argv[])
{
	cfg_stu_info_s st_info;
	
	cfg_op(CFG_OP_GET, CFG_STU_INFO_INI, &st_info, CFG_CB(cfg_stu_info_s));
	logi("stu - name: %s id: %s age: %d score: %d", st_info.ac_name, st_info.ac_id, st_info.ui_age, st_info.ui_score);		
	
	st_info.ui_age = 31;
	cfg_op(CFG_OP_SET, CFG_STU_INFO_INI, &st_info, CFG_CB(cfg_stu_info_s));
	
	cfg_op(CFG_OP_GET, CFG_STU_INFO_INI, &st_info, CFG_CB(cfg_stu_info_s));
	logi("stu - name: %s id: %s age: %d score: %d", st_info.ac_name, st_info.ac_id, st_info.ui_age, st_info.ui_score);		

	return 0;
}


