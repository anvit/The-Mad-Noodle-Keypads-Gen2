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
        SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(50) "Notion" SS_DELAY(50) SS_TAP(X_ENTER));
      }
      break;
    case DSCRD:
      if (!record->event.pressed) {
        SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(50) "Discord" SS_DELAY(50) SS_TAP(X_ENTER));
      }
      break;
    case VPN:
      if (!record->event.pressed) {
        SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(50) "NordVPN" SS_DELAY(50) SS_TAP(X_ENTER));
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
}
