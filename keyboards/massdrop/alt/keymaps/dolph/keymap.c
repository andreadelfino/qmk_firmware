#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    DBG_FAC,               //DEBUG Factory light testing (All on white)
    MD_BOOT,               //Restart into bootloader after hold timeout
    //
    D_RGB_K,
    D_RGB_M,
    D_RGB_I,
    D_RGB_U,
    D_RGB_P,
    D_RGB_N,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_END,  \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, KC_MSTP, KC_MPLY,          _______, KC_VOLU, \
        _______, RGB_TOG, _______, RGB_M_P, RGB_M_R, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, TG(2),   _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            MO(2),   _______, KC_HOME, KC_PGDN, KC_END   \
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, D_RGB_K, D_RGB_M, _______, _______, _______, \
        _______, _______, _______, DBG_TOG, _______, _______, _______, _______, DBG_KBD, _______, D_RGB_I, D_RGB_U,          _______, _______, \
        _______, _______, _______, _______, VLK_TOG, _______, _______, DBG_MTRX,D_RGB_P, D_RGB_N, _______, _______,          KC_MSTP, _______, \
        _______, _______, _______,                            DBG_FAC,                            _______, _______, KC_MPRV, KC_MPLY, KC_MNXT  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

uint8_t factory_reset;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_FAC:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                dprintf("Factory reset");
                eeconfig_init();
                // reset_keyboard();
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            // dprintf("rgb_matrix_get_mode(): %d\n", rgb_matrix_get_mode());
            return false;
        //
        case D_RGB_K:
            rgb_matrix_sethsv(DOLPH_HSV_KEYLIGHT);
            return false;
        case D_RGB_M:
            rgb_matrix_sethsv(DOLPH_HSV_MODIFIER);
            return false;
        case D_RGB_I:
            rgb_matrix_sethsv(DOLPH_HSV_INDICATOR);
            return false;
        case D_RGB_U:
            rgb_matrix_sethsv(DOLPH_HSV_UNDERGLOW);
            return false;
        case D_RGB_P:
            rgb_matrix_sethsv(HSV_CREAM);
            return false;
        case D_RGB_N:
            rgb_matrix_sethsv(HSV_CORAL);
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

//
// void startup_user() {}

//
// void shutdown_user() {}

// Runs once when keyboard is plugged in.
void rgb_matrix_init_user(void) {
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // rgb_matrix_sethsv(HSV_KEYLIGHT);
    // rgb_matrix_mode(RGB_MATRIX_CUSTOM_DOLPH_ALPHA);
}

//
void keyboard_post_init_user(void) {
    // rgb_matrix_enable();
}

// Runs constantly in the background, in a loop.
// void matrix_scan_user(void) {
// }

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgb_matrix.md#suspended-state-idsuspended-state

//
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

//
void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}


//////////////////////

#ifdef _______
#   undef _______
#   define _______ {0,0,0}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = {
        // Backlight
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______,
        // Underglow
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    },
    /*
    [0] = {
        // Backlight
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, CHART,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, CHART,   CHART,   CHART,   _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          CHART,   _______,
        _______, _______, _______,                            _______,                            _______, _______, CHART,   CHART,   CHART,
        // Underglow
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
    },
    [1] = {
        // Backlight
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RED,     RED,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RED,
        _______, GOLD,    CORAL,   _______, _______, _______, _______, _______, MAGENT,  BLUE,    WHITE,   GOLD,    GOLD,    _______, ORANGE,
        _______, GOLD,    CORAL,   _______, _______, _______, _______, RED,     {1,0,0}, CYAN,    M9B59B5, _______,          _______, AZURE,
        _______, RED,     _______, _______, _______, RED,     PINK,    YELLOW,  GREEN,   CREAM,   _______, _______,          _______, AZURE,
        _______, _______, _______,                            _______,                            _______, WHITE,   CORAL,   _______, CORAL,
        // Underglow
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
    },
    [2] = {
        // Backlight
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,    CHART,   CHART,   CHART,   CHART,  CHART,   BLUE,
        GOLD,    PINK,    AZURE,   PINK,    TURQ,    TEAL,    _______, RED,     _______,  _______, GREEN,   BLUE,    GOLD,   _______, BLUE,
        TEAL,    MAGENT,  AZURE,   MAGENT,  TURQ,    TEAL,    _______, _______, _______,  _______, _______, _______,         GOLD,    BLUE,
        _______, _______, _______, _______, _______, RED,     RED,     RED,     _______,  _______, _______, _______,         GOLD,    BLUE,
        _______, _______, _______,                            GOLD,                                _______, _______, PURPLE, GOLD,    PURPLE,
        // Underglow
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
    },
    */
};

#   undef _______
#   define _______ KC_TRNS
#endif

//
void set_layer_color(int layer) {
    if (layer == 0) {
        return;
    }
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        // HSV hsv = {
        //     .h = pgm_read_byte(&ledmap[layer][i][0]),
        //     .s = pgm_read_byte(&ledmap[layer][i][1]),
        //     .v = pgm_read_byte(&ledmap[layer][i][2]),
        // };
        // if (hsv.h || hsv.s || hsv.v) {
        //     RGB rgb = hsv_to_rgb(hsv);
        //     float f = (float) rgb_matrix_config.hsv.v / UINT8_MAX;
        //     rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        // } else if (layer == 1) {
        //     // Only deactivate non-defined key LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
        //     // If the values are all false then it's a transparent key and deactivate LED at this layer
        //     rgb_matrix_set_color(i, 0, 0, 0);
        // }
        /*
        else if (layer == 2) {
            HSV hsv2   = {rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v};
            HSV hui    = hsv2;
            HSV hud    = hsv2;
            HSV sai    = hsv2;
            HSV sad    = hsv2;
            HSV vai    = hsv2;
            HSV vad    = hsv2;
            hui.h      = hsv2.h + 8;
            hud.h      = hsv2.h - 8;
            sai.s      = hsv2.s + 16 > 255 ? 255 : hsv2.s + 16;
            sad.s      = hsv2.s - 16 < 0 ? 0 : hsv2.s - 16;
            vai.v      = hsv2.v + 16 > 255 ? 255 : hsv2.v + 16;
            vad.v      = hsv2.v - 16 < 0 ? 0 : hsv2.v - 16;
            RGB rgbHUI = hsv_to_rgb(hui);
            RGB rgbHUD = hsv_to_rgb(hud);
            RGB rgbSAI = hsv_to_rgb(sai);
            RGB rgbSAD = hsv_to_rgb(sad);
            RGB rgbVAI = hsv_to_rgb(vai);
            RGB rgbVAD = hsv_to_rgb(vad);

            switch (i) {
                case 36:
                    rgb_matrix_set_color(i, rgbHUI.r, rgbHUI.g, rgbHUI.b);
                    break;
                case 53:
                    rgb_matrix_set_color(i, rgbHUD.r, rgbHUD.g, rgbHUD.b);
                    break;
                case 54:
                    rgb_matrix_set_color(i, rgbSAI.r, rgbSAI.g, rgbSAI.b);
                    break;
                case 37:
                    rgb_matrix_set_color(i, rgbSAD.r, rgbSAD.g, rgbSAD.b);
                    break;
                case 38:
                    rgb_matrix_set_color(i, rgbVAI.r, rgbVAI.g, rgbVAI.b);
                    break;
                case 55:
                    rgb_matrix_set_color(i, rgbVAD.r, rgbVAD.g, rgbVAD.b);
                    break;
                case 75:
                    rgb_matrix_set_color(i, rgbVAI.r, rgbVAI.g, rgbVAI.b);
                    break;
                case 85:
                    rgb_matrix_set_color(i, rgbVAD.r, rgbVAD.g, rgbVAD.b);
                    break;
            }
        }
        */
    }
}

// extern bool g_suspend_state;
// extern rgb_config_t rgb_matrix_config;
// bool disable_layer_color;

//
// void rgb_matrix_indicators_user(void) {
//     if (g_suspend_state || disable_layer_color || rgb_matrix_get_flags() == LED_FLAG_NONE || rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
//         return;
//     }
//     set_layer_color(get_highest_layer(layer_state));
// }
