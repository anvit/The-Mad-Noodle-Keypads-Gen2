#include QMK_KEYBOARD_H

enum my_keycodes {
  YT = SAFE_RANGE,
  NOTN,
  DSCRD,
  VPN,
  SRCH,
  LEDTOGGL,
  EML,
  DLD,
  EMJ_SWT,
  EMJ_TNG,
  EMJ_LAUGH,
  EMJ_HEART,
  EMJ_SML,
  EMJ_EYERL,
};

// enum unicode_names {
//   ENDSH,
//   EMJ_SWT,
//   EMJ_TNG,
//   EMJ_LAUGH,
//   EMJ_HEART,
//   EMJ_SML,
//   EMJ_EYERL,
//   EMDASH
// };

// const uint32_t PROGMEM unicode_map[] = {
//     [EMJ_SWT]  = 0x1F605,  // 😅
//     [EMJ_TNG] = 0x1F61D,  // 😝
//     [EMJ_LAUGH]  = 0x1F602, // 😂
//     [EMJ_HEART]  = 0x2764,  // ❤️
//     [EMJ_SML] = 0x263A,  // ☺️
//     [EMJ_EYERL]  = 0x1F644, // 🙄
//     [EMDASH] = 0x2014
// };    

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,-----------------------.
     * |   EML |  MUTE |  DLD  |  ENCODER - PRESS (MUTE) / KNOB (VOLUME CONTROL)
     * |-------+-------+-------|
     * | SEARCH| DSCRD | NOTION|
     * |-------+-------+-------|
     * | YTUBE |  VPN  |  PLAY |
     * `-----------------------'
     */

    [0] = LAYOUT_ortho_3x3(
      EML, LT(2, KC_MUTE), DLD, 
      SRCH, DSCRD, NOTN,
      YT, VPN, LT(1, KC_MPLY)
      ),

    /* LAYER 1
     * ,------------------------.
     * |   🤷🏼‍♂️   |   🤷🏼‍♂️  |   🤷🏼‍♂️  |  ENCODER - PRESS (NA) / KNOB (Arrow Left/Right)
     * |--------+-------+-------|
     * |   😂   |   😊  |  🙄   |
     * |--------+-------+-------|
     * |   😝   |   😅  |   🤷🏼‍♂️  |
     * `------------------------'
     */

    // Emoji Keys
    // [1] = LAYOUT_ortho_3x3(
    //   KC_TRNS, KC_TRNS, KC_TRNS, 
    //   X(EMJ_LAUGH), X(EMJ_SML), X(EMJ_EYERL),
    //   X(EMJ_TNG), X(EMJ_SWT), KC_TRNS
    //   ),
    
    [1] = LAYOUT_ortho_3x3(
      KC_TRNS, KC_TRNS, KC_TRNS, 
      EMJ_LAUGH, EMJ_SML, EMJ_EYERL,
      EMJ_TNG, EMJ_SWT, KC_TRNS
      ),

    /* LAYER 2 (ENCODER)
     * ,-----------------------.
     * | MODE+ |RGB TOG| MODE- |  ENCODER - PRESS (NA) / KNOB (Hue Control)
     * |-------+-------+-------|
     * |  SPD- |  SPD+ |TGL LED|
     * |-------+-------+-------|
     * |  SAT+ |  SAT- |       |
     * `-----------------------'
     */
    
    [2] = LAYOUT_ortho_3x3(
      RGB_MOD, RGB_TOG, RGB_RMOD, 
      RGB_SPI, RGB_SPD, LEDTOGGL, 
      RGB_SAI, RGB_SAD, KC_TRNS
      )

};

void encoder_update_user(uint8_t index, bool clockwise) {
    
  switch (get_highest_layer(layer_state)) {
      case 1:
          if (clockwise) {
              tap_code(KC_RGHT);
          } else {
              tap_code(KC_LEFT);
          }
          break;
      case 2:
          if (clockwise) {
              rgblight_increase_hue();
          } else {
              rgblight_decrease_hue();
          }
          break;
      default:
          if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
          break;
          
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DLD:
      if (!record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(50) "downloads" SS_DELAY(50) SS_TAP(X_ENTER));
      }
      break;
    case YT:
      if (!record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(50) "firefox youtube.com" SS_DELAY(50) SS_TAP(X_ENTER));
      }
      break;
    case SRCH:
      if (!record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(50) "firefox ecosia.org" SS_DELAY(50) SS_TAP(X_ENTER));
      }
      break;
    case EMJ_SWT:
        if(!record->event.pressed) {
            SEND_STRING(":sweat_smile:");
        }
      break;
    case EMJ_TNG:
        if(!record->event.pressed) {
            SEND_STRING(":stuck_out_tongue_closed_eyes:");
        }
      break;
    case EMJ_LAUGH:
        if(!record->event.pressed) {
            SEND_STRING(":joy:");
        }
      break;
    case EMJ_HEART:
        if(!record->event.pressed) {
            SEND_STRING(":heart:");
        }
      break;
    case EMJ_SML:
        if(!record->event.pressed) {
            SEND_STRING(":relaxed:");
        }
      break;
    case EMJ_EYERL:
        if(!record->event.pressed) {
            SEND_STRING(":face_with_rolling_eyes:");
        }
      break;
    case EML:
      if (!record->event.pressed) {
          SEND_STRING("some.email@outlook.com");
      }
      break;
    case LEDTOGGL:
      if (!record->event.pressed) {
        rgblight_toggle();
      }
      break;
    case NOTN:
      if (!record->event.pressed) {
        SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(100) "Notion" SS_TAP(X_ENTER));
      }
      break;
    case DSCRD:
      if (!record->event.pressed) {
        SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(100) "Discord" SS_TAP(X_ENTER));
      }
      break;
    case VPN:
      if (!record->event.pressed) {
        SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(100) "NordVPN" SS_TAP(X_ENTER));
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
}
