/* 
 * CTTSRK's swedish to svorak gergoplex layout.
 *
 * a.k.a. se2svorak
 *
 * Tested with the standard windows Swedish layout and the macos Swedish pro
 * layouts. Finnish should also work since afaik it's identical in both cases.
 *
 * The design rationale is to have zero configuration plug and play svorak on
 * any computer configured for a regular Swedish or Finnish keyboard. There
 * are a few caveats on mac: Macos needs to be configured for the 'pro'
 * version of either Swedish or Finnish layout. Also, the following keys on
 * mac have different combos:
 *
 *           |  \  {  }
 *
 * So provide some kludgy hacks for switching the keyboard between pc and mac
 * modes, see ADJ_PC and ADJ_MAC. This also currently switches the alt and gui
 * keys to provide a more consistent crossplatform experience. The switch
 * persists over power cycles.
 *
 * This layout favours programming over access to special diacritics, hence
 * dead keys are replaced with live ones. Dead keys are relegated to the
 * extras layer.
 *
 * The F* function keys are increasingly irrelevant, especially F5 and up, so
 * use the real estate for more interesting keys.
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "keymap_swedish.h"

#define MACPIPE A(SE_7)
#define MACBSLS S(MACPIPE)
#define MACLCBR S(SE_LBRC)
#define MACRCBR S(SE_RBRC)

enum se2svorak_layers {
    BASEPC,
    BASEMAC,
    SYMPC,
    SYMMAC,
    NUM,
    EXTRA,
};


enum se2svorak_keycodes {
    LI_CIRC = SAFE_RANGE,
    LI_GRV,
    LI_TILD,
    ADJ_PC,
    ADJ_MAC,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LI_CIRC:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_RBRC) SS_UP(X_LSFT) " ");
        }
        break;
    case LI_GRV:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_EQL) SS_UP(X_LSFT) " ");
        }
        break;
    case LI_TILD:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_RBRC) SS_UP(X_RALT) " ");
        }
        break;
    case ADJ_PC:
        if (record->event.pressed) {
            set_single_persistent_default_layer(BASEPC);
        }
        return false;
        break;
    case ADJ_MAC:
        if (record->event.pressed) {
            set_single_persistent_default_layer(BASEMAC);
        }
        return false;
        break;
    }
    return true;
};

/* CHORDS, see gergoplex.def
 *
 * Common fast letter combinations seem unsuitable for chording. Fast
 * combinations seem to be those that move from outer fingers to inner
 * fingers, like 'th' and 'nt'. Maybe 'sn' as well, but I haven't tested it.
 *
 * 'rc' is also fast, but not common, and 'cr' in turn is common but not fast
 * (because it moves from inner finger to outer). This rules out the dvorak
 * right hand home row, but everything else seems ok for chording for now.
 *
 * Possibly it's more accurate to call them 'slurred' rather than 'fast'.
 *
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |     |    esc    |     |     |              |     |     | backspace |     |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |     |    tab    |     |     |              |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |     |     |     |     |     |              |     |     |   enter   |     |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 *                 +-----+-------+-----+  +-----+-------+-----+
 *                 |     |       |     |  |     |       |     |
 *                 +-----+-------+     |  |     +-------+-----+
 *                               |     |  |     |
 *                               +-----+  +-----+
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DEFAULT
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * | ' * | , ; | . : |  P  |  Y  |              |  F  |  G  |  C  |  R  |  L  |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |  A  |  O  |  E  |  U  |  I  |              |  D  |  H  |  T  |  N  |  S  |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |shift|  Q  |  J  |  K  |  X  |              |  B  |  M  |  W  |  V  |  Z  |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+shift+
 *                 +-----+-------+-----+  +-----+-------+-----+
 *                 | alt | space |     |  |     |control| win |
 *                 +-----+-------+ num |  | sym +-------+-----+
 *                 mac cmd       |     |  |     |       mac opt
 *                               +-----+  +-----+
 */
[BASEPC] = LAYOUT_gergoplex(
SE_QUOT, SE_COMM, SE_DOT, SE_P,  SE_Y,       SE_F,  SE_G,  SE_C,  SE_R, SE_L, 
SE_A,    SE_O,    SE_E,   SE_U,  KC_I,       SE_D,  SE_H,  SE_T,  SE_N, SE_S,
KC_LSFT, SE_Q,    SE_J,   SE_K,  SE_X,       SE_B,  SE_M,  SE_W,  SE_V, MT(MOD_RSFT, SE_Z),
             KC_LALT, KC_SPC, MO(NUM),       MO(SYMPC), KC_RCTL, KC_RWIN
),

[BASEMAC] = LAYOUT_gergoplex(
SE_QUOT, SE_COMM, SE_DOT, SE_P,  SE_Y,       SE_F,  SE_G,  SE_C,  SE_R, SE_L, 
SE_A,    SE_O,    SE_E,   SE_U,  KC_I,       SE_D,  SE_H,  SE_T,  SE_N, SE_S,
KC_LSFT, SE_Q,    SE_J,   SE_K,  SE_X,       SE_B,  SE_M,  SE_W,  SE_V, MT(MOD_RSFT, SE_Z),
             KC_LCMD, KC_SPC, MO(NUM),       MO(SYMMAC), KC_RCTL, KC_ROPT
),

/* SYMBOLS
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |  !  |  @  |  #  |  $  |  %  |              |  =  |  &  |  (  |  )  |  `  |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |  <  | Odia| Adia|Aring|  >  |              |  |  |  ?  |  up |  _  |  ^  |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |shift|  [  |  ]  |  {  |  }  |              |  ~  | left| down|right|  \  |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 *                 +-----+-------+-----+  +-----+-------+-----+
 *                 | home|  end  |     |  |     |       | adj |
 *                 +-----+-------+ bspc|  |     +-------+-----+
 *                               |     |  |     |       toggle pc/mac mode
 *                               +-----+  +-----+
 */
[SYMPC] = LAYOUT_gergoplex(
SE_EXLM, SE_AT,   SE_HASH, SE_DLR,  SE_PERC,     SE_EQL,  SE_AMPR, SE_LPRN, SE_RPRN, LI_GRV,
SE_LABK, SE_ODIA, SE_ADIA, SE_ARNG, SE_RABK,     SE_PIPE, SE_QUES, KC_UP,   SE_UNDS, LI_CIRC,
_______, SE_LBRC, SE_RBRC, SE_LCBR, SE_RCBR,     LI_TILD, KC_LEFT, KC_DOWN, KC_RGHT, SE_BSLS,
                  KC_HOME, KC_END,  KC_BSPC,     _______, _______, ADJ_MAC
),

[SYMMAC] = LAYOUT_gergoplex(
SE_EXLM, SE_AT,   SE_HASH, SE_DLR,  SE_PERC,     SE_EQL,  SE_AMPR, SE_LPRN, SE_RPRN, LI_GRV,
SE_LABK, SE_ODIA, SE_ADIA, SE_ARNG, SE_RABK,     MACPIPE, SE_QUES, KC_UP,   SE_UNDS, LI_CIRC,
_______, SE_LBRC, SE_RBRC, MACLCBR, MACRCBR,     LI_TILD, KC_LEFT, KC_DOWN, KC_RGHT, MACBSLS,
                  KC_HOME, KC_END,  KC_BSPC,     _______, _______, ADJ_PC
),

/* NUMPAD & DEAD KEYS
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * | F1  | F2  | F3  | F4  | pgup|              |  /  |  7  |  8  |  9  |  -  |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * |acute|grave| dia |tilde| pgdn|              |  *  |  4  |  5  |  6  |  +  |
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 * | circ| rmb | mmb | lmb | ins |              |     |  1  |  2  |  3  |enter|
 * +-----+-----+-----+-----+-----+              +-----+-----+-----+-----+-----+
 *                 +-----+-------+-----+  +-----+-------+-----+
 *                 |     |       |     |  |     |   0   |  .  |
 *                 +-----+-------+     |  | del +-------+-----+
 *                               |     |  |     |
 *                               +-----+  +-----+
 */
[NUM] = LAYOUT_gergoplex(
KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PGUP,     KC_PSLS, SE_7, SE_8,  SE_9, KC_PMNS,
SE_ACUT, SE_GRV,  SE_DIAE, SE_TILD, KC_PGDN,     KC_PAST, SE_4, SE_5,  SE_6, KC_PPLS,
SE_CIRC, KC_BTN2, KC_BTN3, KC_BTN1, KC_INS,      KC_NO,   SE_1, SE_2,  SE_3, KC_PENT,
                  _______, _______, _______,     KC_DEL,  SE_0, KC_PCMM
),

};
