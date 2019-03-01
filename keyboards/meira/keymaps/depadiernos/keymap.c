#include "meira.h"
#include "lighting.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

// Custom macros
#define SFT_TAB     SFT_T(KC_TAB)               // Tap for Esc, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
#define HPR_TAB     ALL_T(KC_TAB)               // Tap for Tab, hold for Hyper (Super+Ctrl+Alt+Shift)
#define MEH_GRV     MEH_T(KC_GRV)               // Tap for Backtick, hold for Meh (Ctrl+Alt+Shift)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT},
  {KC_LCTL, KC_LALT, KC_LGUI, MEH_GRV, LOWER,   KC_BSPC, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

[_LOWER] = {
  {_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PSCR},
  {_______, _______, _______, _______, _______, _______, KC_UNDS, KC_QUES, KC_PLUS, KC_LCBR, KC_RCBR, _______},
  {_______, _______, _______, _______, _______, _______, KC_MINS, KC_SLSH, KC_EQL,  KC_LBRC, KC_RBRC, _______},
  {_______, _______, _______, _______, _______, KC_DEL,  _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

[_RAISE] = {
  {_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PSCR},
  {_______, _______, _______, _______, _______, _______, KC_UNDS, KC_QUES, KC_PLUS, KC_LCBR, KC_RCBR, _______},
  {_______, _______, _______, _______, _______, _______, KC_MINS, KC_SLSH, KC_EQL,  KC_LBRC, KC_RBRC, _______},
  {_______, _______, _______, _______, _______, KC_DEL,  _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

[_ADJUST] = {
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______, RESET},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______},
  {BACKLIT, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END}
}


};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
#ifdef RGBLIGHT_ENABLE
    rgblight_mode(RGB_current_mode);
#endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
//        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
        if (record->event.pressed) {
            //not sure how to have keyboard check mode and set it to a variable, so my work around
            //uses another variable that would be set to true after the first time a reactive key is pressed.
            if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
            } else {
                TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(16);
#endif
            }
            layer_on(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
#ifdef RGBLIGHT_ENABLE
            rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
#endif
            TOG_STATUS = false;
            layer_off(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed) {
            //not sure how to have keyboard check mode and set it to a variable, so my work around
            //uses another variable that would be set to true after the first time a reactive key is pressed.
            if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
            } else {
                TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(15);
#endif
            }
            layer_on(_RAISE);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
#ifdef RGBLIGHT_ENABLE
            rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
#endif
            layer_off(_RAISE);
            TOG_STATUS = false;
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case ADJUST:
        // FIXME add RGB feedback
        if (record->event.pressed) {
            layer_on(_ADJUST);
        } else {
            layer_off(_ADJUST);
        }
        return false;
        break;
    case BL_TOGG:
#ifdef BACKLIGHT_ENABLE
        if (record->event.pressed) {
            print("Enabling backlight\n");
            backlight_init_ports();
        }
#endif
        return false;
        break;
    case BL_STEP:
        if (record->event.pressed) {
            print("Stepping backlight\n");
#ifdef BACKLIGHT_ENABLE
            print("Really stepping backlight\n");
            backlight_step();
#endif

        }
        return false;
        break;
        //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
#ifdef RGBLIGHT_ENABLE
    case RGB_MOD:
        if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
        }
        return false;
        break;
#endif
//    case BL_INC:
//    		meira_inc_backlight_level();
//    	      return false;
//    		break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

}
