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
 * @Date         : 2022-10-06 13:09:42
 * @LastEditors  : MCD
 * @LastEditTime : 2022-10-06 13:18:37
 * @FilePath     : /Linux_lvgl_for_HOPE/lv_hope_demo_conf.h
 * @Description  : 
 * 
 * ******************************************
 */

/**
 * @file lv_hope_demo_conf.h
 * Configuration file for v8.1.0-dev
 *
 */
/*
 * COPY THIS FILE AS lv_hope_demo_conf.h
 */

/* clang-format off */
#if 1 /*Set it to "1" to enable the content*/

#ifndef LV_HOPE_DEMO_CONF_H
#define LV_HOPE_DEMO_CONF_H


/*******************
 * GENERAL SETTING
 *******************/

/*********************
 * DEMO USAGE
 *********************/

/*Show some widget*/

/* [Info] About us 1024x600*/
#define LV_USE_HOPE_DEMO_ABOUT_US        1
#if LV_USE_HOPE_DEMO_ABOUT_US
    #define LV_HOPE_ATS3609D             1
#endif

#if 0
/* [Game] Memory game demo, optimized for 1024x600*/
#define LV_USE_HOPE_DEMO_GAME_MEMORY      1

/* [Game] 2048 game demo, optimized for 1024x600*/
#define LV_USE_HOPE_DEMO_GAME_2048        1

/* [Game] Snake game demo, optimized for 1024x600*/
#define LV_USE_HOPE_DEMO_GAME_SNAKE       1

/* [Game] Tron game demo, optimized for 1024x600*/
#define LV_USE_HOPE_DEMO_GAME_TILES       1

/* [Efficiency] Calculator demo, optimized for 1024x600*/
#define LV_USE_HOPE_DEMO_EFF_CALC         1

/* [Efficiency(Linux only)] Weather overview 1024x600*/
#define LV_USE_HOPE_DEMO_WEATHER          0

#endif

#endif /*LV_HOPE_DEMO_CONF_H*/

#endif /*End of "Content enable"*/

