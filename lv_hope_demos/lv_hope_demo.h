/*
 * 
 * 　　┏┓　　　┏┓+ +
 * 　┏┛┻━━━┛┻┓ + +
 * 　┃　　　　　　　┃ 　
 * 　┃　　　━　　　┃ ++ + + +
 *  ████━████ ┃+
 * 　┃　　　　　　　┃ +
 * 　┃　　　┻　　　┃
 * 　┃　　　　　　　┃ + +
 * 　┗━┓　　　┏━┛
 * 　　　┃　　　┃　　　　　　　　　　　
 * 　　　┃　　　┃ + + + +
 * 　　　┃　　　┃
 * 　　　┃　　　┃ +  神兽保佑
 * 　　　┃　　　┃    代码无bug　　
 * 　　　┃　　　┃　　+　　　　　　　　　
 * 　　　┃　 　　┗━━━┓ + +
 * 　　　┃ 　　　　　　　┣┓
 * 　　　┃ 　　　　　　　┏┛
 * 　　　┗┓┓┏━┳┓┏┛ + + + +
 * 　　　　┃┫┫　┃┫┫
 * 　　　　┗┻┛　┗┻┛+ + + +
 * 
 * 
 * 
 * ************Copyright 2022 MCD************
 * 
 * @version      : 
 * @Company      : HOPE
 * @Author       : MCD
 * @Date         : 2022-10-06 13:02:33
 * @LastEditors  : MCD
 * @LastEditTime : 2022-10-06 13:17:17
 * @FilePath     : /Linux_lvgl_for_HOPE/lv_hope_example/lv_hope_demo.h
 * @Description  : 
 * 
 * ******************************************
 */
/**
 * @file lv_100ask_demo.h
 *
 */

#ifndef LV_HOPE_DEMO_H
#define LV_HOPE_DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#    include "lvgl.h"
#else
#    include "../lvgl/lvgl.h"
#endif

#if defined(LV_HOPE_DEMO_CONF_PATH)

#define __LV_TO_STR_AUX(x) #    x
#define __LV_TO_STR(x)     __LV_TO_STR_AUX(x)
#include __LV_TO_STR(LV_HOPE_DEMO_CONF_PATH)
#undef __LV_TO_STR_AUX
#undef __LV_TO_STR

#elif defined(LV_HOPE_DEMO_CONF_INCLUDE_SIMPLE)

#include "lv_hope_demo_conf.h"

#else

#include "../lv_hope_demo_conf.h"

#endif

#include "src/lv_hope_demo_net_info/lv_net_info.h"

/*********************
 *      DEFINES
 *********************/
/*Test  lvgl version*/
#if LV_VERSION_CHECK(8, 0, 0) == 0
#    error "lv_hope_demo: Wrong lvgl version"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_HOPE_DEMO_H*/
