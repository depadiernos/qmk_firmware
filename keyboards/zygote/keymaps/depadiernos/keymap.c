#include "zygote.h"
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers
{
	_QWERTY,
	_LOWER,
	_RAISE,
    _ADJUST
};

enum custom_keycodes
{
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

// Fillers to make layering more clear
#define XXXXXXX KC_NO
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_NO,     KC_NO,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,  \
  KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_NO,     KC_NO,   KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN,  \
  KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_TAB,    KC_ESC,  KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  \
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,  KC_BSPC, RAISE,     LOWER,   KC_SPC,  KC_GRV, KC_MINS, KC_QUOT, KC_ENT   \
),

[_LOWER] = LAYOUT_ortho_4x12( \
  KC_1,     KC_2,   KC_3,    KC_4,    KC_5,    KC_NO,       KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  _______, _______, _______, _______, _______, KC_NO,       KC_NO,   KC_VOLU, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,  \
  _______, _______, _______, _______, _______, _______,     _______, KC_VOLD, KC_LBRC, KC_RBRC, KC_LCBR, KC_RBRC,    \
  _______, _______, _______, _______, _______, _______,     _______, _______, _______, KC_EQL,  KC_BSLS, _______ \
),

[_RAISE] = LAYOUT_ortho_4x12( \
  KC_1,     KC_2,   KC_3,    KC_4,    KC_5,    KC_NO,       KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  _______, _______, _______, _______, _______, KC_NO,       KC_NO,   KC_VOLU, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,  \
  _______, _______, _______, _______, _______, _______,     _______, KC_VOLD, KC_LBRC, KC_RBRC, KC_LCBR, KC_RBRC,    \
  _______, _______, _______, _______, _______, _______,     _______, _______, _______, KC_EQL,  KC_BSLS, _______ \
),

[_ADJUST] = LAYOUT_ortho_4x12( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,       KC_NO,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,    \
  KC_F11,  KC_F12,  _______, _______, _______, KC_NO,       KC_NO,   KC_VOLU,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  \
  _______, _______, _______, _______, _______, _______,     _______, KC_VOLD,  _______, _______, _______, _______,    \
  _______, _______, _______, _______, KC_DEL,  _______,     _______, KC_PSCR, _______, _______, _______, _______ \
)

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}



void matrix_scan_user(void) {
		return;
};
