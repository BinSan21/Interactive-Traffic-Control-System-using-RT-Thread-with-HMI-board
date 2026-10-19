/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-25     ACER       the first version
 */

#include <rtthread.h>
#include <lvgl.h>
#include <stdio.h>

/* --- IMAGE DECLARATIONS --- */
LV_IMG_DECLARE(ccs_logo);
LV_IMG_DECLARE(dev1); // Ensure dev1.c is in src folder
LV_IMG_DECLARE(dev2); // Ensure dev2.c is in src folder

/* --- GUI OBJECTS --- */
static lv_obj_t *led_red, *led_amber, *led_green;
static lv_obj_t *btn_pedestrian, *txt_status, *txt_timer;

/* --- LOGIC CONTROLS --- */
static rt_thread_t traffic_tid = RT_NULL;
static rt_event_t main_event = RT_NULL;

// Event Flags
#define EVENT_START_GAME   (1 << 0)
#define EVENT_PED_PRESSED  (1 << 1)
#define EVENT_GO_BACK      (1 << 2)
#define EVENT_SHOW_CREDITS (1 << 3)

// Helper return codes
#define STATUS_CONTINUE   0
#define STATUS_EXIT_GAME  1

/* ==========================================
 * SHARED CALLBACKS
 * ==========================================*/
static void back_btn_cb(lv_event_t * e)
{
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        rt_event_send(main_event, EVENT_GO_BACK);
    }
}

/* ==========================================
 * SCREEN 3: CREDITS / CREATOR
 * ==========================================*/
void create_credits_gui(void)
{
    lv_obj_clean(lv_scr_act());
    lv_obj_t * scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    /* 1. BACK BUTTON */
    lv_obj_t * btn_back = lv_btn_create(scr);
    lv_obj_set_size(btn_back, 40, 40);
    lv_obj_align(btn_back, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_bg_color(btn_back, lv_palette_main(LV_PALETTE_GREY), 0);
    lv_obj_t * lbl_back = lv_label_create(btn_back);
    lv_label_set_text(lbl_back, LV_SYMBOL_LEFT);
    lv_obj_center(lbl_back);
    lv_obj_add_event_cb(btn_back, back_btn_cb, LV_EVENT_CLICKED, NULL);

    /* 2. TITLE */
    lv_obj_t * title = lv_label_create(scr);
    lv_label_set_text(title, "Project Creators");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 15);
    lv_obj_set_style_text_color(title, lv_color_black(), 0);

    /* --- CREATOR 1 (Left Side) --- */
    lv_obj_t * img1 = lv_img_create(scr);
    lv_img_set_src(img1, &dev1);
    lv_obj_align(img1, LV_ALIGN_CENTER, -100, -10);

    lv_obj_t * name1 = lv_label_create(scr);
    // Role on top, Name on bottom
    lv_label_set_text(name1, "Programmer\nSansarona, B");
    lv_obj_set_style_text_align(name1, LV_TEXT_ALIGN_CENTER, 0); // Center align lines
    lv_obj_align_to(name1, img1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_set_style_text_color(name1, lv_color_black(), 0);

    /* --- CREATOR 2 (Right Side) --- */
    lv_obj_t * img2 = lv_img_create(scr);
    lv_img_set_src(img2, &dev2);
    lv_obj_align(img2, LV_ALIGN_CENTER, 100, -10);

    lv_obj_t * name2 = lv_label_create(scr);
    // Role on top, Name on bottom
    lv_label_set_text(name2, "Programmer\nVillauneva, KJ");
    lv_obj_set_style_text_align(name2, LV_TEXT_ALIGN_CENTER, 0); // Center align lines
    lv_obj_align_to(name2, img2, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_set_style_text_color(name2, lv_color_black(), 0);
}

/* ==========================================
 * SCREEN 2: TRAFFIC SIM
 * ==========================================*/
void create_traffic_gui(void)
{
    lv_obj_clean(lv_scr_act());
    lv_obj_t * scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x202020), 0);

    lv_obj_t * btn_back = lv_btn_create(scr);
    lv_obj_set_size(btn_back, 40, 40);
    lv_obj_align(btn_back, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_bg_color(btn_back, lv_palette_main(LV_PALETTE_GREY), 0);
    lv_obj_t * lbl_back = lv_label_create(btn_back);
    lv_label_set_text(lbl_back, LV_SYMBOL_LEFT);
    lv_obj_center(lbl_back);
    lv_obj_add_event_cb(btn_back, back_btn_cb, LV_EVENT_CLICKED, NULL);

    /* Lights */
    led_red = lv_led_create(scr);
    lv_obj_align(led_red, LV_ALIGN_CENTER, -60, -60);
    lv_led_set_color(led_red, lv_palette_main(LV_PALETTE_RED));
    lv_led_off(led_red);
    lv_obj_set_size(led_red, 45, 45);

    led_amber = lv_led_create(scr);
    lv_obj_align(led_amber, LV_ALIGN_CENTER, -60, 0);
    lv_led_set_color(led_amber, lv_palette_main(LV_PALETTE_ORANGE));
    lv_led_off(led_amber);
    lv_obj_set_size(led_amber, 45, 45);

    led_green = lv_led_create(scr);
    lv_obj_align(led_green, LV_ALIGN_CENTER, -60, 60);
    lv_led_set_color(led_green, lv_palette_main(LV_PALETTE_GREEN));
    lv_led_off(led_green);
    lv_obj_set_size(led_green, 45, 45);

    /* Timer */
    txt_timer = lv_label_create(scr);
    lv_label_set_text(txt_timer, "--");
    lv_obj_set_style_text_font(txt_timer, &lv_font_montserrat_16, 0);
    lv_obj_align(txt_timer, LV_ALIGN_CENTER, 60, 0);
    lv_obj_set_style_text_color(txt_timer, lv_color_white(), 0);

    /* Instructions */
    lv_obj_t * info_lights = lv_label_create(scr);
    lv_label_set_text(info_lights, "RED: Stop\nGREEN: Go");
    lv_obj_align(info_lights, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_set_style_text_color(info_lights, lv_color_hex(0xAAAAAA), 0);

    /* Status */
    txt_status = lv_label_create(scr);
    lv_label_set_text(txt_status, "Simulation Active");
    lv_obj_align(txt_status, LV_ALIGN_TOP_MID, 0, 15);
    lv_obj_set_style_text_color(txt_status, lv_color_white(), 0);

    /* Button */
    btn_pedestrian = lv_btn_create(scr);
    lv_obj_align(btn_pedestrian, LV_ALIGN_BOTTOM_MID, 0, -35);
    lv_obj_t * btn_label = lv_label_create(btn_pedestrian);
    lv_label_set_text(btn_label, "RUSH RED LIGHT");

    lv_obj_t * info_btn = lv_label_create(scr);
    lv_label_set_text(info_btn, "*Only works during RED light");
    lv_obj_align(info_btn, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_color(info_btn, lv_color_hex(0xAAAAAA), 0);
}

/* ==========================================
 * SCREEN 1: WELCOME
 * ==========================================*/
static void welcome_btn_cb(lv_event_t * e)
{
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        rt_event_send(main_event, EVENT_START_GAME);
    }
}

static void credits_btn_cb(lv_event_t * e)
{
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        rt_event_send(main_event, EVENT_SHOW_CREDITS);
    }
}

void create_welcome_gui(void)
{
    lv_obj_clean(lv_scr_act());
    lv_obj_t * scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    /* Title & Logo */
    lv_obj_t * title = lv_label_create(scr);
    lv_label_set_text(title, "Traffic Light Simulation");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_set_style_text_color(title, lv_color_black(), 0);

    lv_obj_t * img = lv_img_create(scr);
    lv_img_set_src(img, &ccs_logo);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    /* Start Button */
    lv_obj_t * btn_start = lv_btn_create(scr);
    lv_obj_align(btn_start, LV_ALIGN_BOTTOM_MID, 0, -30);
    lv_obj_set_height(btn_start, 50);
    lv_obj_set_width(btn_start, 180);
    lv_obj_set_style_bg_color(btn_start, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_t * label = lv_label_create(btn_start);
    lv_label_set_text(label, "START SIMULATION");
    lv_obj_center(label);
    lv_obj_add_event_cb(btn_start, welcome_btn_cb, LV_EVENT_CLICKED, NULL);

    /* Credits Button (Text 'Dev' version) */
    lv_obj_t * btn_credits = lv_btn_create(scr);
    lv_obj_set_size(btn_credits, 40, 40);
    lv_obj_align(btn_credits, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_bg_color(btn_credits, lv_palette_main(LV_PALETTE_GREY), 0);

    lv_obj_t * lbl_cred = lv_label_create(btn_credits);
    lv_label_set_text(lbl_cred, "Dev");
    lv_obj_center(lbl_cred);
    lv_obj_add_event_cb(btn_credits, credits_btn_cb, LV_EVENT_CLICKED, NULL);
}

/* ==========================================
 * LOGIC
 * ==========================================*/
static void ped_btn_cb(lv_event_t * e)
{
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        rt_event_send(main_event, EVENT_PED_PRESSED);
    }
}

int wait_seconds_with_interrupt(int seconds, int is_red_phase)
{
    char buf[16];
    for(int i = seconds; i > 0; i--)
    {
        sprintf(buf, "%d", i);
        lv_label_set_text(txt_timer, buf);

        rt_uint32_t recved;
        if (rt_event_recv(main_event, EVENT_PED_PRESSED | EVENT_GO_BACK,
                          RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          rt_tick_from_millisecond(1000), &recved) == RT_EOK)
        {
            if (recved & EVENT_GO_BACK) return STATUS_EXIT_GAME;
            if ((recved & EVENT_PED_PRESSED) && is_red_phase && i > 8) {
                lv_label_set_text(txt_status, "PRIORITY REQUESTED!");
                i = 8;
            }
        }
    }
    lv_label_set_text(txt_timer, "0");
    return STATUS_CONTINUE;
}

static void traffic_thread_entry(void *parameter)
{
    rt_thread_mdelay(1000);

    while(1)
    {
        create_welcome_gui();

        rt_uint32_t recved;
        rt_event_recv(main_event, EVENT_START_GAME | EVENT_SHOW_CREDITS,
                      RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      RT_WAITING_FOREVER, &recved);

        if (recved & EVENT_SHOW_CREDITS) {
            create_credits_gui();
            rt_event_recv(main_event, EVENT_GO_BACK,
                          RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, RT_NULL);
            continue;
        }

        create_traffic_gui();
        lv_obj_add_event_cb(btn_pedestrian, ped_btn_cb, LV_EVENT_CLICKED, NULL);

        while(1)
        {
            /* RED */
            lv_led_on(led_red); lv_led_off(led_amber); lv_led_off(led_green);
            lv_label_set_text(txt_status, "STOP (Red)");
            lv_obj_set_style_text_color(txt_timer, lv_palette_main(LV_PALETTE_RED), 0);
            if (wait_seconds_with_interrupt(20, 1) == STATUS_EXIT_GAME) break;

            /* GREEN */
            lv_led_off(led_red); lv_led_off(led_amber); lv_led_on(led_green);
            lv_label_set_text(txt_status, "GO (Green)");
            lv_obj_set_style_text_color(txt_timer, lv_palette_main(LV_PALETTE_GREEN), 0);
            if (wait_seconds_with_interrupt(20, 0) == STATUS_EXIT_GAME) break;

            /* AMBER */
            lv_led_off(led_green); lv_led_on(led_amber);
            lv_label_set_text(txt_status, "SLOW DOWN");
            lv_obj_set_style_text_color(txt_timer, lv_palette_main(LV_PALETTE_ORANGE), 0);
            lv_label_set_text(txt_timer, "3"); rt_thread_mdelay(1000);
            if (rt_event_recv(main_event, EVENT_GO_BACK, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, 0, RT_NULL) == RT_EOK) break;
            lv_label_set_text(txt_timer, "2"); rt_thread_mdelay(1000);
            if (rt_event_recv(main_event, EVENT_GO_BACK, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, 0, RT_NULL) == RT_EOK) break;
            lv_label_set_text(txt_timer, "1"); rt_thread_mdelay(1000);
            if (rt_event_recv(main_event, EVENT_GO_BACK, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, 0, RT_NULL) == RT_EOK) break;
        }
    }
}

int traffic_app_init(void)
{
    main_event = rt_event_create("main_evt", RT_IPC_FLAG_FIFO);
    traffic_tid = rt_thread_create("traffic", traffic_thread_entry, RT_NULL, 4096, 25, 10);
    if (traffic_tid != RT_NULL) rt_thread_startup(traffic_tid);
    return 0;
}
INIT_APP_EXPORT(traffic_app_init);
