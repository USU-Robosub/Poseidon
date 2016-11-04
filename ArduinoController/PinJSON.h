#ifndef PIN_JSON_H
#define PIN_JSON_H

namespace PinJSON {
  char json[] = "{"
    "\"voltage\" : {"
      "\"volt\" : 10"
    "},"
    "\"thrust\" : {"
      "\"left_forward\" : 13,"
      "\"right_forward\" : 12,"
      "\"left_strafe\" : 11,"
      "\"right_strafe\" : 9,"
      "\"front_dive\" : 8,"
      "\"back_dive\" : 7"
    "},"
    "\"light\" : {"
      "\"lights\" : 45"
    "},"
    "\"led\" : {"
      "\"green\" : 22,"
      "\"white\" : 52"
    "},"
    "\"kill_switch\" : {"
      "\"stat_led\" : 22"
    "},"
    "\"esc\" : {"
      "\"gpio\" : [36, 39, 41, 47, 49, 53]"
    "}"
  "}";
}

#endif // PIN_JSON_H
