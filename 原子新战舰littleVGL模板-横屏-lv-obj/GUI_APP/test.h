#ifndef __TEST_H__
#define __TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "lvgl.h"
#include "lv_ex_conf.h"
#endif


void test_start(void);


#ifdef __cplusplus
} /* extern "C" */
#endif




#endif // __TEST_H__
