/*
 * log.h
 *
 *  Created on: Jun 12, 2018
 *      Author: jyin
 */

#ifndef __DBG_H__
#define __DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define logd(format, arg...) printf("DEBUG: " format "\n", ##arg)

#define logi(format, arg...) printf("INFOM: " format "\n", ##arg)

#define logw(format, arg...) printf("WARN: " format "\n", ##arg)

#define loge(format, arg...) printf("ERROR: " format "\n", ##arg)

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DBG_H_ */
