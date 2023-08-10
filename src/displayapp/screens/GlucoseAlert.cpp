#include "displayapp/screens/GlucoseAlert.h"
#include "components/motor/MotorController.h"
#include "components/settings/Settings.h"
#include "displayapp/InfiniTimeTheme.h"
#include "displayapp/screens/Symbols.h"
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

#define BEATS_PER_MINUTE 50

GlucoseAlert::GlucoseAlert(Pinetime::Controllers::MotorController& motorController, SugarEvent sugarEvent) : motorController {motorController}, sugarEvent {sugarEvent} {
    warningIcon = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_text_static(warningIcon, Symbols::warning);
    lv_obj_set_style_local_text_font(warningIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_sys_48);
    lv_obj_align(warningIcon, nullptr, LV_ALIGN_CENTER, 0, -10);

    warningLabel = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_text_static(warningLabel, GetWarningText());
    lv_obj_align(warningLabel, nullptr, LV_ALIGN_CENTER, 0, 20);

    SetFlash(flasher);

    taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);

    motorController.RunForDuration((uint8_t)500);
}

GlucoseAlert::~GlucoseAlert() {
    lv_obj_clean(lv_scr_act());
}

const char* GlucoseAlert::GetWarningText() {
    switch (sugarEvent) {
        case Pinetime::Applications::SugarEvent::Low:
            return "Low Glucose";
        case Pinetime::Applications::SugarEvent::High:
            return "High Glucose";
        case Pinetime::Applications::SugarEvent::FallRate:
            return "Fall Rate";
    }
}

void GlucoseAlert::Refresh() {
    /* 100% not stolen from Metronome.cpp */
    if (xTaskGetTickCount() - startTime > 60u * configTICK_RATE_HZ / static_cast<uint16_t>(BEATS_PER_MINUTE)) {
      startTime += 60 * configTICK_RATE_HZ / BEATS_PER_MINUTE;
      flasher = !flasher;
      motorController.RunForDuration((uint8_t)50);
      SetFlash(flasher);
    }
}

void GlucoseAlert::SetFlash(bool flash) {
    if (flash) {
        lv_obj_set_style_local_text_color(warningIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
        lv_obj_set_style_local_text_color(warningLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
        lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    } else {
        lv_obj_set_style_local_text_color(warningIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_obj_set_style_local_text_color(warningLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
    }
}

bool GlucoseAlert::OnTouchEvent(Pinetime::Applications::TouchEvents  event) {

  if (event == TouchEvents::SwipeUp) {


  }
  return true;
}
