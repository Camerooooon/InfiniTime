#include "displayapp/screens/Glucose.h"
#include "displayapp/InfiniTimeTheme.h"
#include <cstdio>
#include <lvgl/src/lv_api_map.h>
#include <lvgl/src/lv_core/lv_disp.h>
#include <lvgl/src/lv_core/lv_obj.h>
#include <lvgl/src/lv_core/lv_obj_style_dec.h>
#include <lvgl/src/lv_misc/lv_area.h>
#include <lvgl/src/lv_widgets/lv_btn.h>
#include <lvgl/src/lv_widgets/lv_chart.h>
#include <systemtask/Messages.h>

using namespace Pinetime::Applications::Screens;

static void btnEventHandler(lv_obj_t* obj, lv_event_t event) {
  auto* screen = static_cast<Glucose*>(obj->user_data);
  screen->OnButtonEvent(obj, event);
}

void Glucose::OnButtonEvent(lv_obj_t* obj, lv_event_t event) {
    printf("Hi\n");
    if (event == LV_EVENT_CLICKED) {

        printf("EVent\n");
        ShowLabel();
    }
}

void Glucose::ShowLabel() {
    lv_label_set_text_static(testLabel, "Yo");
    

}

Glucose::Glucose() {
    testLabel = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_text_static(testLabel, "74");

    chartObj = lv_chart_create(lv_scr_act(), nullptr);

    lv_obj_set_size(chartObj, 200, 240);
    lv_obj_align(chartObj, nullptr, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    lv_chart_set_range(chartObj, 40, 400);

    lv_chart_set_point_count(chartObj, 37);

    lv_obj_set_style_local_line_width(chartObj, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_radius(chartObj, LV_CHART_PART_CURSOR, LV_STATE_DEFAULT, 0);

    low = lv_chart_add_series(chartObj, LV_COLOR_RED);
    med = lv_chart_add_series(chartObj, LV_COLOR_GREEN);
    high = lv_chart_add_series(chartObj, LV_COLOR_YELLOW);

    
    int sugar[] = { 195, 220, 241, 253, 260, 262, 267, 270, 279, 300, 314, 324, 321, 314, 301, 281, 250, 233, 220, 194, 175, 152, 142, 143, 124, 110, 106, 100, 92, 88, 80, 73, 69, 74 };

    for (int i = 0; i<34; i++) {
        lv_chart_series_t* series = nullptr;
        if (sugar[i] < 80) { 
            series = low;
        }else if (sugar[i] < 220) {
            series = med;
        } else {
            series = high;
        }
        series->points[i] = sugar[i];
        if (i>33) {
            return;
        }
        series->points[i+1] = sugar[i+1];
    }
}

Glucose::~Glucose() {
    lv_obj_clean(lv_scr_act());
}

bool Glucose::OnTouchEvent(Pinetime::Applications::TouchEvents  /*event*/) {
    return true;
}
