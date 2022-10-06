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
 * @Date         : 2022-10-06 12:54:20
 * @LastEditors  : MCD
 * @LastEditTime : 2022-10-06 13:35:41
 * @FilePath     : /Linux_lvgl_for_HOPE/lv_hope_demos/src/lv_hope_demo_net_info/lv_net_info.c
 * @Description  : 
 * 
 * ******************************************
 */
#include "../../../lv_drivers/display/fbdev.h"
#include "../../../lv_drivers/indev/evdev.h"
#include "../../../lvgl/lvgl.h"
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static struct Lan_info {
    char device[8];   /* 网卡信息 */
    char cable[16];   /* 连接状态 */
    char dhcp[8];     /* DHCP模式 */
    char mac[24];     /* mac地址 */
    char ipaddr[16];  /* IP地址 */
    char gateway[16]; /* 网关 */
    char netmask[16]; /* 子网掩码 */
} Lan_info = {"eth1", "UP", "YES", "18:31:bf:2f:f6:25", "192.168.2.11", "192.168.2.1", "255.255.255.0"};

static lv_obj_t *g_btn_run_dhcp;            /* 刷新网卡句柄 */
static lv_obj_t *g_table_lan_info;          /* LAN信息表格句柄 */
static lv_timer_t *g_wifi_scan_task_handle; /* 定时器任务句柄 */

static void set_cell_value(lv_obj_t *table);

static void run_dhcp_event_handler(lv_event_t *evt)
{
    lv_event_code_t code = lv_event_get_code(evt);

    // printf("get code = %d\n", code);
    if (code == LV_EVENT_CLICKED) {
        printf("up button!!\n");
        set_cell_value(g_table_lan_info);
    }
    else if (code == LV_EVENT_PRESSED) {
        printf("down button!!\n");
        lv_label_set_text(lv_obj_get_child(g_btn_run_dhcp, 0), LV_SYMBOL_REFRESH " Retrieve IP address(DHCPC) btn down");
    }
}

// 定时扫描连接状态
static void lv_task_lan_cable_scan(lv_timer_t *task)
{
    // get_lan_info();
    set_cell_value(g_table_lan_info);
}

static void set_cell_value(lv_obj_t *table)
{
    /* fill the first column */
    lv_table_set_cell_value(table, 0, 0, "Cable");
    lv_table_set_cell_value(table, 1, 0, "DHCP");
    lv_table_set_cell_value(table, 2, 0, "MAC");
    lv_table_set_cell_value(table, 3, 0, "IP-addr");
    lv_table_set_cell_value(table, 4, 0, "Gateway");
    lv_table_set_cell_value(table, 5, 0, "Netmask");

    /* fill the second column */
    lv_table_set_cell_value(table, 0, 1, "Connect " LV_SYMBOL_OK);
    lv_table_set_cell_value(table, 1, 1, Lan_info.dhcp);
    lv_table_set_cell_value(table, 2, 1, Lan_info.mac);
    lv_table_set_cell_value(table, 3, 1, Lan_info.ipaddr);
    lv_table_set_cell_value(table, 4, 1, Lan_info.gateway);
    lv_table_set_cell_value(table, 5, 1, Lan_info.netmask);

    if (strstr(Lan_info.cable, "DOWN") != NULL) {
        // lv_obj_add_state(g_btn_run_dhcp, LV_STATE_DISABLED | LV_STATE_CHECKED);
        lv_label_set_text(lv_obj_get_child(g_btn_run_dhcp, 0), LV_SYMBOL_WARNING " The network cable is not connected");
        lv_table_set_cell_value(table, 0, 1, "Not connected " LV_SYMBOL_WARNING);
    }
    else {
        // lv_obj_add_state(g_btn_run_dhcp, LV_STATE_DISABLED | LV_STATE_CHECKED);
        // lv_label_set_text(lv_obj_get_child(g_btn_run_dhcp, 0), LV_SYMBOL_REFRESH " Retrieve IP address(DHCPC)");
        lv_label_set_text(lv_obj_get_child(g_btn_run_dhcp, 0), LV_SYMBOL_REFRESH " Retrieve IP address(DHCPC) btn up");
    }
}

void lv_hope_demo_net_info(void)
{
    lv_obj_t *obj_layout;
    static lv_style_t obj_layout_style; /* 容器样式 */

    printf("start first demo for HOPE net info UI!\n");

    lv_style_init(&obj_layout_style);
    lv_style_set_pad_row(&obj_layout_style, 20);
    lv_style_set_border_opa(&obj_layout_style, 0);

    /* layout init */
    obj_layout = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_layout, LV_PCT(100), LV_PCT(100));
    lv_obj_set_layout(obj_layout, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj_layout, LV_FLEX_FLOW_COLUMN);
    lv_obj_center(obj_layout);
    lv_obj_add_style(obj_layout, &obj_layout_style, 0);

    /* create title */
    lv_obj_t *label_title = lv_label_create(obj_layout);
    lv_obj_set_width(label_title, LV_PCT(100));
    lv_obj_set_style_text_font(label_title, &lv_font_montserrat_26, 0);
    lv_obj_set_style_text_align(label_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(label_title, "LAN");
    lv_obj_align(label_title, LV_ALIGN_CENTER, 0, 0);

    /* Get ip address(DHCP) button */
    g_btn_run_dhcp = lv_btn_create(obj_layout);
    lv_obj_set_width(obj_layout, LV_PCT(100));

    /* this can add more btn click event */
    lv_obj_add_event_cb(g_btn_run_dhcp, run_dhcp_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(g_btn_run_dhcp, run_dhcp_event_handler, LV_EVENT_PRESSED, NULL);

    lv_obj_t *label = lv_label_create(g_btn_run_dhcp);
    lv_label_set_text(label, LV_SYMBOL_REFRESH " Retrieve IP address(DHCPC) btn up");
    lv_obj_center(label);

    /* NET info */
    g_table_lan_info = lv_table_create(obj_layout);
    lv_obj_set_style_text_font(g_table_lan_info, &lv_font_montserrat_18, 0);
    lv_obj_set_width(g_table_lan_info, LV_PCT(100));
    lv_obj_set_style_pad_all(g_table_lan_info, 0, 0);
    lv_obj_set_style_border_side(g_table_lan_info, 0, 0);

    lv_table_set_col_width(g_table_lan_info, 0, 115);
    lv_table_set_col_width(g_table_lan_info, 1, 320);

    set_cell_value(g_table_lan_info);
    // g_wifi_scan_task_handle = lv_timer_create(lv_task_lan_cable_scan, 5000, NULL);  // 10秒定时器任务
}