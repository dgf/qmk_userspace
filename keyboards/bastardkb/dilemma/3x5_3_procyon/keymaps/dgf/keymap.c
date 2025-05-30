/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 * Copyright 2025 Danny Gräf <deep@dagnu.de> (@dgf)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include QMK_KEYBOARD_H

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_MEDIA,
    LAYER_NAVIGATION,
    LAYER_POINTER,
    LAYER_SYMBOLS,
    LAYER_NUMERAL,
    LAYER_FUNCTION,
    LAYER_CHARACTERS,
};

// Automatically enable sniping-mode on the pointer layer.
#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

// left thumb
#define DEL_FUN LT(LAYER_FUNCTION, KC_DEL)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)

// right thumb
#define TAB_PTR LT(LAYER_POINTER, KC_TAB)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define ESC_MED LT(LAYER_MEDIA, KC_ESC)

// left base home row
#define B_CTL_A LCTL_T(KC_A)
#define B_ALT_R RALT_T(KC_R)
#define B_GUI_S LGUI_T(KC_S)
#define B_SFT_T LSFT_T(KC_T)
#define B_PTR_Z LT(LAYER_POINTER, KC_Z)
#define B_CHR_D LT(LAYER_CHARACTERS, KC_D)

// right hand home row
#define B_SFT_N RSFT_T(KC_N)
#define B_GUI_E RGUI_T(KC_E)
#define B_ALT_I RALT_T(KC_I)
#define B_CTL_O RCTL_T(KC_O)

// characters
enum custom_keycodes {
    CH_EURO = SAFE_RANGE,
    CH_SZ_L, // ß
    CH_AE_L, // ä
    CH_AE_U, // Ä
    CH_OE_L, // ö
    CH_OE_U, // Ö
    CH_UE_L, // ü
    CH_UE_U, // Ü
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CH_EURO:
                send_string(SS_DOWN(X_LOPT) SS_LSFT("2") SS_UP(X_LOPT));
                break;
            case CH_SZ_L:
                send_string(SS_LOPT("s"));
                break;
            case CH_AE_L:
                send_string(SS_LOPT("u") "a");
                break;
            case CH_AE_U:
                send_string(SS_LOPT("u") SS_LSFT("a"));
                break;
            case CH_OE_L:
                send_string(SS_LOPT("u") "o");
                break;
            case CH_OE_U:
                send_string(SS_LOPT("u") SS_LSFT("o"));
                break;
            case CH_UE_L:
                send_string(SS_LOPT("u") "u");
                break;
            case CH_UE_U:
                send_string(SS_LOPT("u") SS_LSFT("u"));
                break;
        }
    }
    return true;
}

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       B_CTL_A, B_ALT_R, B_GUI_S, B_SFT_T,    KC_G,       KC_M, B_SFT_N, B_GUI_E, B_ALT_I, B_CTL_O,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       B_PTR_Z,    KC_X,    KC_C, B_CHR_D,    KC_V,       KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         DEL_FUN, BSP_NUM, ENT_SYM,    TAB_PTR, SPC_NAV, ESC_MED
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_MEDIA] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, KC_BRMD, KC_BRMU, XXXXXXX, XXXXXXX,     EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX,    XXXXXXX, RM_HUEU, RM_SATU, RM_SPDU, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       RM_PREV, RM_VALD, RM_VALU, RM_NEXT, RM_TOGG,    XXXXXXX, RM_HUED, RM_SATD, RM_SPDD, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_MUTE, KC_MPLY, KC_MSTP,    XXXXXXX, XXXXXXX, _______
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_NAVIGATION] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,    XXXXXXX, _______, _______, _______, _______,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_CAPS, CW_TOGG, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_DEL, KC_BSPC,  KC_ENT,    XXXXXXX, _______, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_POINTER] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, MS_WHLD, MS_WHLU, XXXXXXX, XXXXXXX,    XXXXXXX,DPI_RMOD, DPI_MOD,S_D_RMOD, S_D_MOD,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, XXXXXXX,    XXXXXXX, _______, _______, _______, _______,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_BTN3, KC_BTN2, KC_BTN1,    _______, XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______, _______, _______, _______, XXXXXXX,     KC_DQT,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, XXXXXXX, _______,    KC_UNDS, KC_LPRN, KC_RPRN
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_NUMERAL] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______, _______, _______, _______, XXXXXXX,    KC_QUOT,    KC_4,    KC_5,    KC_6,  KC_EQL,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, _______, XXXXXXX,    KC_MINS,    KC_0,  KC_DOT
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_FUNCTION] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR,    KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______, _______, _______, _______, XXXXXXX,    XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, XXXXXXX, XXXXXXX,     KC_TAB,  KC_SPC,  KC_ESC
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
  [LAYER_CHARACTERS] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, CH_AE_L, CH_AE_U, CH_EURO, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______, _______, _______, _______, XXXXXXX,    XXXXXXX, CH_OE_L, CH_OE_U, CH_SZ_L, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, KC_RALT, XXXXXXX, _______, XXXXXXX,    XXXXXXX, CH_UE_L, CH_UE_U, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_DEL, KC_BSPC,  KC_ENT,     KC_TAB,  KC_SPC,  KC_ESC
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
};
// clang-format on

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_copy[]       = {DEL_FUN, BSP_NUM, COMBO_END};
const uint16_t PROGMEM combo_paste[]      = {BSP_NUM, ENT_SYM, COMBO_END};
const uint16_t PROGMEM combo_lock_left[]  = {DEL_FUN, BSP_NUM, ENT_SYM, COMBO_END};
const uint16_t PROGMEM combo_lock_right[] = {TAB_PTR, SPC_NAV, ESC_MED, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_copy, LGUI(KC_C)),
    COMBO(combo_paste, LGUI(KC_V)),
    COMBO(combo_lock_left, LCTL(LGUI(KC_Q))),
    COMBO(combo_lock_right, LCTL(LGUI(KC_Q))),
};
#endif // COMBO_ENABLE

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE
