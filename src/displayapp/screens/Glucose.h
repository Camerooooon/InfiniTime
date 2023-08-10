#pragma once

#include "displayapp/screens/Screen.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {

      class Glucose: public Screen {
        void ShowLabel();
      public:
        void OnButtonEvent(lv_obj_t* obj, lv_event_t event);
        Glucose();
        ~Glucose() override;
        bool OnTouchEvent(TouchEvents event) override;

      private:
        lv_obj_t *testLabel;
        lv_obj_t *chartObj;
        lv_chart_series_t* low;
        lv_chart_series_t* med;
        lv_chart_series_t* high;
      };
    }
  }
}
