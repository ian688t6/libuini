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
	char					ac_id[CFG_STR_LEN];					/** student id */
	uint32_t				ui_age;					/** student age */
	uint32_t				ui_score;				/** student score */
} cfg_stu_info_s;
CFG_INI_DECLARE(cfg_stu_info_s);

#ifdef __cplusplus
}
#endif

#endif /* CFG_H_ */
