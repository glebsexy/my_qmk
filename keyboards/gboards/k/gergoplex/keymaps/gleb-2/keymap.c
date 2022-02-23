/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NAVIG 2 // numbers/motion
#define MEDIA 3 // media

//Tap Dance Declarations
enum {
 TD_CMD_OPT,
 TD_LAY1_LAY2,
 TD_CMD_SYMB
};

/////////////////////////////////////////////////////////////////////////////////////////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_gergoplex(
    KC_Q,               KC_W, KC_E,         KC_R, KC_T,             KC_Y, KC_U, KC_I,    KC_O,   KC_P, 
    MT(MOD_LGUI, KC_A), KC_S, KC_D,         KC_F, KC_G,             KC_H, KC_J, KC_K,    KC_L,   MT(MOD_LALT, KC_SCLN),
    MT(MOD_RSFT, KC_Z), MT(MOD_LCTL, KC_X), KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT, KC_SLSH),

    KC_LALT, TD(TD_CMD_OPT), LT(SYMB, KC_SPC),  // Left
    MO(NAVIG), KC_RGUI, KC_RCTL // Right
),

/////////////////////////////////////////////////////////////////////////////////////////

[SYMB] = LAYOUT_gergoplex(
    KC_LALT, LALT(KC_LBRC), KC_LCBR, KC_RCBR, KC_GRV,                KC_DEL,  KC_7, KC_8, KC_9, KC_0,
    KC_LGUI, LALT(KC_BSLS), KC_LPRN, KC_RPRN, LALT(KC_SCLN),         KC_RCTL, KC_4, KC_5, KC_6, KC_RALT,
    KC_LSFT, RALT(RCTL(KC_DOT)),  KC_LBRC, KC_RBRC, LSFT(LALT(KC_MINS)),   KC_RGUI, KC_1, KC_2, KC_3, KC_RSFT,
    
    _______, _______, _______, // left
    _______, _______, _______ // right
),

//////////////////////////////////////////////////////////////////////////////////////

[NAVIG] = LAYOUT_gergoplex(
    _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_WH_U,           _______, _______, KC_UP, _______, _______,
    KC_LGUI, KC_VOLD, KC_VOLU, KC_MUTE, KC_WH_D,           _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_RALT,
    KC_LSFT, KC_F1, KC_F2, KC_F3, KC_F4,                   _______, _______, _______, _______, KC_RSFT,

    _______, _______, _______, // left
    _______, _______, _______ // right
),

//////////////////////////////////////////////////////////////////////////////////////

[MEDIA] = LAYOUT_gergoplex(
    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
    
    _______, _______, _______,
    _______, _______, _______
),

};

void dance_lay_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_move(NAVIG);
    } else {
        layer_move(SYMB);
    }
};

void dance_lay_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_move(BASE);
};

void td_cmd_symb_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_mods(MOD_BIT(KC_RGUI));
    } else {
        layer_move(SYMB);
    }
};

void td_cmd_symb_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_mods(MOD_BIT(KC_RGUI));
    } else {
        layer_move(BASE);
    }
};

////////////////////////////////////////////////

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CMD_OPT]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LALT),
    [TD_LAY1_LAY2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lay_finished, dance_lay_reset),
    [TD_CMD_SYMB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_cmd_symb_finished, td_cmd_symb_reset)
};