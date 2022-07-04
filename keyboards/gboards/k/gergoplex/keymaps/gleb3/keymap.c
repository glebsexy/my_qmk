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
 TD_NAV_SYMB = 1,
 EAGER_CMD_A
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    MULTI_TAP
};

// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

// #define EAGER_MT(mod, kc) (QK_MOD_TAP | (((mod)&0x1F) << 8) | ((kc)&0xFF))

// create an eager tap dance definition with custom user params 
#define ACTION_TAP_DANCE_FN_EAGER_MOD(kc1, kc2) {  \
    .fn = { eager_mod_each, eager_mod_finished, eager_mod_reset }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }) \
}

// TD(id) => tap[id](...)

/////////////////////////////////////////////////////////////////////////////////////////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_gergoplex(
    KC_Q,               KC_W,               KC_E, KC_R, KC_T,        KC_Y, KC_U, KC_I,    KC_O,   KC_P, 
    MT(MOD_LGUI, KC_A), KC_S,               KC_D, KC_F, KC_G,        KC_H, KC_J, KC_K,    KC_L,   MT(MOD_LALT, KC_SCLN),
    MT(MOD_RSFT, KC_Z), MT(MOD_LCTL, KC_X), KC_C, KC_V, KC_B,        KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT, KC_SLSH),

    KC_LALT, KC_LGUI, LT(SYMB, KC_SPC),  // left
    TD(TD_NAV_SYMB), KC_RGUI, KC_RCTL   // right
),

/////////////////////////////////////////////////////////////////////////////////////////

[SYMB] = LAYOUT_gergoplex(
    KC_LALT, LALT(KC_LBRC), KC_LCBR, KC_RCBR, KC_GRV,                KC_DEL,  KC_7, KC_8, KC_9, KC_0,
    KC_LGUI, LALT(KC_BSLS), KC_LPRN, KC_RPRN, LALT(KC_SCLN),         KC_RCTL, KC_4, KC_5, KC_6, KC_RALT,
    KC_LSFT, KC_F, KC_LBRC, KC_RBRC, LSFT(LALT(KC_MINS)),            KC_RGUI, KC_1, KC_2, KC_3, KC_RSFT,
    
    _______, _______, _______, // left
    _______, _______, _______  // right
),

//////////////////////////////////////////////////////////////////////////////////////

[NAVIG] = LAYOUT_gergoplex(
    KC_LALT, KC_MPRV, KC_MPLY, KC_MNXT, KC_WH_D,      KC_PGUP,   XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX,
    KC_LGUI, KC_VOLD, KC_VOLU, KC_MUTE, KC_WH_U,      KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_RALT,
    KC_LSFT, KC_F1, KC_F2, KC_F3, KC_F4,              KC_RGUI,   XXXXXXX, XXXXXXX, KC_RCTL,  KC_RSFT,

    _______, _______, _______, // left
    _______, _______, _______  // right
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

//////////////////////////////////////////////////////////

// Tap dance

// Determine the current tap dance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else return MULTI_TAP;
}

// Initialize tap structure associated with tap dance key
static tap ql_tap_state = {
    .is_press_action = true,
    .state = 0
};

void dance_lay_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_move(BASE);
};


// on each key tap
void eager_mod_each(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keymod = pair->kc1;
    uint16_t keycode = pair->kc2;

    // current tap dance state
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_HOLD:
            register_code(keymod);
            break;
        case SINGLE_TAP:
            unregister_code(keymod);
            register_code(keycode);
            break;
        case MULTI_TAP:
            unregister_code(keymod);
            register_code(keycode);
            break;
    }
};

void eager_mod_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keymod = pair->kc1;
    uint16_t keycode = pair->kc2;

    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(keymod);
            register_code(keycode);
            break;
        case MULTI_TAP:
            register_code(keycode);
            break;
    }
};

void eager_mod_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keymod = pair->kc1;
    uint16_t keycode = pair->kc2;

    unregister_code(keymod);
    unregister_code(keycode);

    ql_tap_state.state = 0;
    // switch (state->count) {
    //     case 1:
    //         unregister_code(keymod);
    //         break;
    //     case 2:
    //         unregister_code(keycode);
    //         break;
    // }
};


// on each layer tap
void dance_lay_each(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            layer_move(NAVIG);
            break;
        case 2:
            layer_move(SYMB);
            break;
    }
};

void dance_lay_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_move(NAVIG);
    } else {
        layer_move(SYMB);
    }
};

////////////////////////////////////////////////

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_NAV_SYMB] = ACTION_TAP_DANCE_FN_ADVANCED(dance_lay_each, dance_lay_finished, dance_lay_reset),
    [EAGER_CMD_A] = ACTION_TAP_DANCE_FN_EAGER_MOD(KC_LGUI, KC_A)
};
