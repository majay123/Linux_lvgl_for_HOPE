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
 * @Date         : 2022-09-19 13:24:36
 * @LastEditors  : MCD
 * @LastEditTime : 2022-10-06 13:27:17
 * @FilePath     : /Linux_lvgl_for_HOPE/main.c
 * @Description  :
 *
 * ******************************************
 */

#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lv_hope_demos/lv_hope_demo.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl/lvgl.h"
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define DISP_BUF_SIZE (5 * 1024 * 1024)

int main(void)
{
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];
    static lv_color_t buf1[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, buf1, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res = 480;
    disp_drv.ver_res = 480;
    disp_drv.sw_rotate = 1;
    disp_drv.rotated = LV_DISP_ROT_180;
    // lv_disp_set_rotation(&disp_drv, LV_DISP_ROT_180);
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb = evdev_read;
    /* lv_indev_t *mouse_indev =  */ lv_indev_drv_register(&indev_drv_1);

    // /*Set a cursor for the mouse*/
    // LV_IMG_DECLARE(mouse_cursor_icon)
    // lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    // lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    // lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/

    /*Create a Demo*/
    // lv_demo_widgets();
    // lv_obj_t * demo_obj = lv_label_create(lv_scr_act());
    // lv_label_set_text(demo_obj, "Hello World");
    // lv_obj_align(demo_obj, LV_ALIGN_CENTER, 0, 0);
    // lv_demo_music();
    // lv_demo_keypad_encoder();
    // lv_demo_widgets();
    lv_hope_demo_net_info();
    // _my_test_lv_ui();

    /*Handle LitlevGL tasks (tickless mode)*/
    while (1) {
        // lv_tick_inc(5);
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if (start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
