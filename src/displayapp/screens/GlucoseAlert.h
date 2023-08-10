#pragma once

#include "components/motor/MotorController.h"
#include "displayapp/screens/Screen.h"
#include <portmacro_cmsis.h>

namespace Pinetime {
  namespace Applications {
      enum class SugarEvent { Low, High, FallRate, SensorError };
    namespace Screens {

      class GlucoseAlert: public Screen {
      public:
        GlucoseAlert(Controllers::MotorController& motorController, SugarEvent sugarEvent);
        ~GlucoseAlert() override;
        void Refresh() override;
        void SetFlash(bool flash);
        bool OnTouchEvent(TouchEvents event) override;

      private:
        const char* GetWarningText();
        const lv_color_t GetWarningColor();
        Controllers::MotorController& motorController;
        SugarEvent sugarEvent;
        lv_obj_t *warningIcon;
        lv_obj_t *warningLabel;
        TickType_t startTime = 0;
        lv_task_t* taskRefresh;
        bool flasher = false;
      };
    }
  }
}
