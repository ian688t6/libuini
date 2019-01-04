# libuini
A simple small ini parser library written in C.
-------------

## Purpose
The primary goal of this project was to create a small and simple ini parsing library for the purpose of reading-in and writing ini data files. This project allows for quick parsing by heavily reducing the complexity of the parsing process, making the library well suited for low-memory environments, such as embedded systems.

## Build
``` bash
$ make
$ make exp
```

## Using this library
-luini

## Example
Here is an ini file "cfg_test.ini"
``` bash
stu_name=ian688t6
stu_id=9527
stu_age=31
stu_score=88
```

Declare a ini operation function and struct in header "cfg_test.h" and "cfg_test.c"
The header file "cfg_test.h"
``` c
#ifndef __CFG_TEST_H__
#define __CFG_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CFG_STU_INFO_INI				"cfg_test.ini"
#define CFG_STU_NAME					"stu_name"
#define CFG_STU_ID						"stu_id"
#define CFG_STU_AGE						"stu_age"
#define CFG_STU_SCORE					"stu_score"
/** student */
typedef struct
{
	char					ac_name[CFG_STR_LEN];	/** student name */
	char					ac_id[CFG_STR_LEN];		/** student id */
	uint32_t				ui_age;					/** student age */
	uint32_t				ui_score;				/** student score */
} cfg_stu_info_s;
CFG_INI_DECLARE(cfg_stu_info_s);

#ifdef __cplusplus
}
#endif

#endif /* CFG_H_ */
```
The source file "cfg_test.c"
``` c
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

```

Read or write a ini file
```c
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
```
