// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

enum custom_keycodes { MAC_GLOBE = SAFE_RANGE, MAC_SPOTLIGHT, MAC_DO_NOT_DISTURB, MAC_DICTATION };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC_GLOBE:
            host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
            return false;
        case MAC_SPOTLIGHT:
            host_consumer_send(record->event.pressed ? AC_SEARCH : 0);
            return false;
        case MAC_DO_NOT_DISTURB:
            host_system_send(record->event.pressed ? KC_CANCEL : 0);
            return false;
        case MAC_DICTATION:
            host_consumer_send(record->event.pressed ? QK_MOUSE_CURSOR_LEFT : 0);
            return false;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT(
        KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, MAC_SPOTLIGHT,MAC_DICTATION,MAC_DO_NOT_DISTURB,KC_MPRV,KC_MPLY,KC_MNXT,KC_MUTE,KC_VOLD,KC_VOLU,         KC_F13,  KC_F14,  KC_F15,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC,     MAC_GLOBE,KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,               KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(MAC_FN),            KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                                      KC_RGUI, KC_RALT, MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN, KC_RGHT
    ),


    [MAC_FN] = LAYOUT(
        KC_USB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                    KC_F13, KC_F14, KC_F15,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_NXT,  LT(0, KC_BT1), LT(0, KC_BT2), LT(0, KC_BT3), LT(0, KC_2G4), _______, _______, _______, _______, _______, _______, _______, _______, _______,          EE_CLR,  _______, PDF(WIN_BASE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,          _______, _______,          _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______, _______, _______, _______, _______
    ),


    [WIN_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                         KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC,      KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,               KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(WIN_FN),            KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_RALT, KC_RGUI, MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN, KC_RGHT
    ),


    [WIN_FN] = LAYOUT(
        KC_USB, KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,                   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, PDF(MAC_BASE),
        KC_NXT,  LT(0, KC_BT1), LT(0, KC_BT2), LT(0, KC_BT3), LT(0, KC_2G4), _______, _______, _______, _______, _______, _______, _______, _______, _______,          EE_CLR,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,          _______, _______,          _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on
