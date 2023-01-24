RGB_MATRIX_EFFECT(DOLPH_ALPHA)
RGB_MATRIX_EFFECT(DOLPH_GAME)
RGB_MATRIX_EFFECT(DOLPH_GAME_RAINBOW)
//
// RGB_MATRIX_EFFECT(RAINBOW_WASD)
//
// RGB_MATRIX_EFFECT(SOLID_REACTIVE_WIDE2)
// RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTIWIDE2)
// RGB_MATRIX_EFFECT(SOLID_REACTIVE_NEXUS2)
// RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTINEXUS2)
//
// RGB_MATRIX_EFFECT(indicator_gradient)
// RGB_MATRIX_EFFECT(indicator_cycle_all)
// RGB_MATRIX_EFFECT(indicator_static)
//

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool dolph_is_wasd(uint8_t i) {
    return i == 17 || i == 31 || i == 32 || i == 33;
}
bool dolph_is_hjkl(uint8_t i) {
    return i == 36 || i == 37 || i == 38 || i == 39;
}
bool dolph_is_arrows(uint8_t i) {
    return i == 56 || i == 64 || i == 65 || i == 66;
}
bool dolph_is_symbols(uint8_t i) {
    return i == 26 || i == 27 || i == 28 || i == 40 || i == 41 || i == 52 || i == 53 || i == 54;
}

static HSV d_hsv_k, d_hsv_m, d_hsv_i, d_hsv_u, delta;
static RGB d_rgb_k, d_rgb_m, d_rgb_i, d_rgb_u;

static void dolph_init(effect_params_t* params) {
    #ifndef DOLPH_HSV_KEYLIGHT
    #define DOLPH_HSV_KEYLIGHT rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v
    #endif
    #ifndef DOLPH_HSV_MODIFIER
    #define DOLPH_HSV_MODIFIER (rgb_matrix_config.hsv.h + rgb_matrix_config.speed), rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v
    #endif
    #ifndef DOLPH_HSV_INDICATOR
    #define DOLPH_HSV_INDICATOR DOLPH_HSV_KEYLIGHT
    #endif
    #ifndef DOLPH_HSV_UNDERGLOW
    #define DOLPH_HSV_UNDERGLOW DOLPH_HSV_KEYLIGHT
    #endif

    // rgb_matrix_sethsv_noeeprom(DOLPH_HSV_KEYLIGHT);
    rgb_matrix_sethsv(DOLPH_HSV_KEYLIGHT);

    d_hsv_k = (HSV){DOLPH_HSV_KEYLIGHT};
    d_hsv_m = (HSV){DOLPH_HSV_MODIFIER};
    d_hsv_i = (HSV){DOLPH_HSV_INDICATOR};
    d_hsv_u = (HSV){DOLPH_HSV_UNDERGLOW};

    d_rgb_k = rgb_matrix_hsv_to_rgb(d_hsv_k);
    d_rgb_m = rgb_matrix_hsv_to_rgb(d_hsv_m);
    d_rgb_i = rgb_matrix_hsv_to_rgb(d_hsv_i);
    d_rgb_u = rgb_matrix_hsv_to_rgb(d_hsv_u);
}

///////////////////

void dolph_alpha_init(effect_params_t* params) {
    // RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // for (uint8_t i = led_min; i < led_max; i++) {
    //     RGB_MATRIX_TEST_LED_FLAGS();
    //     if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
    //         if (dolph_is_arrows(i)) {
    //             rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
    //         } else {
    //             rgb_matrix_set_color(i, d_rgb_m.r, d_rgb_m.g, d_rgb_m.b);
    //         }
    //     } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
    //         if (dolph_is_symbols(i)) {
    //             rgb_matrix_set_color(i, d_rgb_i.r, d_rgb_i.g, d_rgb_i.b);
    //         } else {
    //             rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
    //         }
    //     } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
    //         rgb_matrix_set_color(i, d_rgb_i.r, d_rgb_i.g, d_rgb_i.b);
    //     } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
    //         rgb_matrix_set_color(i, d_rgb_u.r, d_rgb_u.g, d_rgb_u.b);
    //     } else {
    //         rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
    //     }
    // }
}

RGB rgb_matrix_hsv_to_rgb_rebound(HSV hsv, HSV delta) {
    return rgb_matrix_hsv_to_rgb((HSV){qsub8(qadd8(hsv.h, delta.h), 0), qsub8(qadd8(hsv.s, delta.h), 0), qsub8(qadd8(hsv.v, delta.h), 0)});
}

static bool dolph_alpha_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    d_rgb_k = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);

    delta.h = rgb_matrix_config.hsv.h - d_hsv_k.h;
    delta.s = rgb_matrix_config.hsv.s - d_hsv_k.s;
    delta.v = rgb_matrix_config.hsv.v - d_hsv_k.v;

    d_rgb_m = rgb_matrix_hsv_to_rgb_rebound(d_hsv_m, delta);
    d_rgb_i = rgb_matrix_hsv_to_rgb_rebound(d_hsv_i, delta);
    d_rgb_u = rgb_matrix_hsv_to_rgb_rebound(d_hsv_u, delta);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            if (dolph_is_arrows(i)) {
                rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
            } else {
                rgb_matrix_set_color(i, d_rgb_m.r, d_rgb_m.g, d_rgb_m.b);
            }
        } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
            if (dolph_is_symbols(i)) {
                rgb_matrix_set_color(i, d_rgb_i.r, d_rgb_i.g, d_rgb_i.b);
            } else {
                rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
            }
        } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
            rgb_matrix_set_color(i, d_rgb_i.r, d_rgb_i.g, d_rgb_i.b);
        } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, d_rgb_u.r, d_rgb_u.g, d_rgb_u.b);
        } else {
            rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
        }
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}


// static bool dolph_alpha_run(effect_params_t* params) {
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);

//     for (uint8_t i = led_min; i < led_max; i++) {
//         RGB_MATRIX_TEST_LED_FLAGS();
//         if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
//             if (dolph_is_arrows(i)) {
//                 rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
//             } else {
//                 rgb_matrix_set_color(i, d_rgb_m.r, d_rgb_m.g, d_rgb_m.b);
//             }
//         } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
//             if (dolph_is_symbols(i)) {
//                 rgb_matrix_set_color(i, d_rgb_i.r, d_rgb_i.g, d_rgb_i.b);
//             } else {
//                 rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
//             }
//         } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
//             rgb_matrix_set_color(i, d_rgb_i.r, d_rgb_i.g, d_rgb_i.b);
//         } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
//             rgb_matrix_set_color(i, d_rgb_u.r, d_rgb_u.g, d_rgb_u.b);
//         } else {
//             rgb_matrix_set_color(i, d_rgb_k.r, d_rgb_k.g, d_rgb_k.b);
//         }
//     }

//     return led_max < RGB_MATRIX_LED_COUNT;
// }

///////////////////

static bool use_hjkl;
static void dolph_game_init(effect_params_t* params) {
    use_hjkl = false;
}

bool dolph_game_selector(uint8_t i) {
    return dolph_is_wasd(i) || dolph_is_hjkl(i) || dolph_is_arrows(i) || HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW);
}

static HSV dolph_game_effect(HSV hsv, uint8_t i, uint8_t time) {
    if (dolph_game_selector(i)) {
        hsv.h = g_led_config.point[i].x - time;
    } else {
        hsv.v = 0;
    }
    return hsv;
}

static bool dolph_game_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        if (dolph_game_selector(i)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}


static bool DOLPH_ALPHA(effect_params_t* params) {
  if (params->init) {
      dolph_init(params);
      dolph_alpha_init(params);
  }
  return dolph_alpha_run(params);
}

static bool DOLPH_GAME(effect_params_t* params) {
  if (params->init) {
      dolph_init(params);
      dolph_game_init(params);
  }
  return dolph_game_run(params);
}

static bool DOLPH_GAME_RAINBOW(effect_params_t* params) {
  if (params->init) {
      dolph_init(params);
      dolph_game_init(params);
  }
  return effect_runner_i(params, &dolph_game_effect);
}

///////////////////

// typedef HSV (*ef)(HSV hsv, uint8_t i, uint8_t time);

// static HSV stripe_wasd(HSV hsv, uint8_t i, uint8_t time) {
//     if (i == 17 || i == 31 || i == 32 || i == 33) { // WASD
//         hsv.h = g_led_config.point[i].x - time;
//     } else {
//         hsv.v = 0;
//     }
//     return hsv;
// }

// static bool on(effect_params_t* params, ef effect_func) {
//   RGB_MATRIX_USE_LIMITS(led_min, led_max);
//   for (uint8_t i = led_min; i < led_max; i++) {
//     RGB_MATRIX_TEST_LED_FLAGS();
//     RGB rgb = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, i, 0));
//     rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//   }
//   return led_max < RGB_MATRIX_LED_COUNT;
// }

// bool STATIC_WASD(effect_params_t* params) {
//     return on(params, &stripe_wasd);
// }

// bool RAINBOW_WASD(effect_params_t* params) {
//     return effect_runner_i(params, &stripe_wasd);
// }

///////////////////

// static HSV SOLID_REACTIVE_WIDE_math2(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
//     uint16_t effect = tick - dist > 255 || dist > 32 ? 255 : tick - dist;
//     hsv.v           = qadd8(hsv.v, 255 - effect);
//     return hsv;
// }

// static HSV SOLID_REACTIVE_NEXUS_math2(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
//     uint16_t effect = tick - dist > 255 || ((dx > 8 || dx < -8) && (dy > 8 || dy < -8)) ? 255 : tick - dist;
//     hsv.v           = qadd8(hsv.v, 255 - effect);
//     hsv.h           = rgb_matrix_config.hsv.h + dy / 4;
//     return hsv;
// }

// bool SOLID_REACTIVE_WIDE2(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_WIDE_math2); }
// bool SOLID_REACTIVE_MULTIWIDE2(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_REACTIVE_WIDE_math2); }
// bool SOLID_REACTIVE_NEXUS2(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_NEXUS_math2); }
// bool SOLID_REACTIVE_MULTINEXUS2(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_REACTIVE_NEXUS_math2); }

///////////////////

// static bool indicator_static(effect_params_t* params) {
//     HSV hsv = rgb_matrix_config.hsv;
//     RGB rgb = hsv_to_rgb(hsv);
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);
//     for (uint8_t i = led_min ; i < 74; i++) {
//         rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
//     }
//     for (uint8_t i = 74 ; i < led_max; i++) {
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//     }
//     return led_max < RGB_MATRIX_LED_COUNT;
// }

// bool effect_runner_indicator(effect_params_t* params, i_f effect_func) {
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);

//     uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
//     for (uint8_t i = led_min; i < led_max; i++) {
//         if (i < 74) {
//             rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
//         } else {
//             RGB_MATRIX_TEST_LED_FLAGS();
//             RGB rgb = hsv_to_rgb(effect_func(rgb_matrix_config.hsv, (i - 74), time));
//             rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//         }
//     }
//     return led_max < RGB_MATRIX_LED_COUNT;
// }

// static HSV indicator_gradient_math(HSV hsv, uint8_t i, uint8_t time) {
//     hsv.h = g_led_config.point[i].x - time;
//     return hsv;
// }

// bool indicator_gradient(effect_params_t* params) { return effect_runner_indicator(params, &indicator_gradient_math); }

// static HSV indicator_cycle_all_math(HSV hsv, uint8_t i, uint8_t time) {
//     hsv.h = time;
//     return hsv;
// }

// bool indicator_cycle_all(effect_params_t* params) { return effect_runner_indicator(params, &indicator_cycle_all_math); }

///////////////////

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
