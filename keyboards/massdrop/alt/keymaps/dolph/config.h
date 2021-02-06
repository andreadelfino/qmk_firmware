#pragma once

// quantum/rgblight_list.h
// #define HSV_WHITE 0, 0, 255
// #define HSV_RED 0, 255, 255
// #define HSV_CORAL 11, 176, 255
// #define HSV_ORANGE 28, 255, 255
// #define HSV_GOLDENROD 30, 218, 218
// #define HSV_GOLD 36, 255, 255
// #define HSV_YELLOW 43, 255, 255
// #define HSV_CHARTREUSE 64, 255, 255
// #define HSV_GREEN 85, 255, 255
// #define HSV_SPRINGGREEN 106, 255, 255
// #define HSV_TURQUOISE 123, 90, 112
// #define HSV_TEAL 128, 255, 128
// #define HSV_CYAN 128, 255, 255
// #define HSV_AZURE 132, 102, 255
// #define HSV_BLUE 170, 255, 255
// #define HSV_PURPLE 191, 255, 255
// #define HSV_MAGENTA 213, 255, 255
// #define HSV_PINK 234, 128, 255
// #define HSV_BLACK 0, 0, 0
// #define HSV_OFF HSV_BLACK
// custom
#define HSV_CREAM 24, 240, 255

#define HSV_KEYLIGHT 128, 255, 200
#define HSV_MODIFIER 212, 255, 200
#define HSV_INDICATOR 0, 0, 255
#define HSV_UNDERGLOW 128, 255, 128

#define DOLPH_HSV_KEYLIGHT HSV_KEYLIGHT
#define DOLPH_HSV_MODIFIER HSV_MODIFIER
#define DOLPH_HSV_INDICATOR HSV_KEYLIGHT
#define DOLPH_HSV_UNDERGLOW HSV_UNDERGLOW

// These are just to make it neater to use builtin HSV values in the keymap
// clang-format off
// #define WHITE {HSV_WHITE}
// #define RED {HSV_RED}
// #define CORAL {HSV_CORAL}
// #define ORANGE {HSV_ORANGE}
// #define GOLDEN {HSV_GOLDENROD}
// #define GOLD {HSV_GOLD}
// #define YELLOW {HSV_YELLOW}
// #define CHART {HSV_CHARTREUSE}
// #define GREEN {HSV_GREEN}
// #define SPRING {HSV_SPRINGGREEN}
// #define TURQ {HSV_TURQUOISE}
// #define TEAL {HSV_TEAL}
// #define CYAN {HSV_CYAN}
// #define AZURE {HSV_AZURE}
// #define BLUE {HSV_BLUE}
// #define PURPLE {HSV_PURPLE}
// #define MAGENT {HSV_MAGENTA}
// #define PINK {HSV_PINK}
// #define CREAM {HSV_CREAM}
// #define M9B59B5 {HSV_9B59B5}
// clang-format on

#define MATRIX_IO_DELAY 50

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #define RGB_DISABLE_TIMEOUT 0 // number of milliseconds to wait until rgb automatically turns off
#define RGB_DISABLE_TIMEOUT 300000 // number of milliseconds to wait until rgb automatically turns off
// #define RGB_DISABLE_AFTER_TIMEOUT 0 // OBSOLETE: number of ticks to wait until disabling effects
// #define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
// #define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_DOLPH_ALPHA // Sets the default mode, if none has been set
// #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE // Sets the default mode, if none has been set
// #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT // Sets the default mode, if none has been set
// #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_UP_DOWN // Sets the default mode, if none has been set
// #define RGB_MATRIX_STARTUP_HUE 0 // Sets the default hue value, if none has been set
// #define RGB_MATRIX_STARTUP_SAT 255 // Sets the default saturation value, if none has been set [UINT8_MAX]
// #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
// #define RGB_MATRIX_STARTUP_SPD 127 // Sets the default animation speed, if none has been set [UINT8_MAX / 2]
// #define RGB_MATRIX_DISABLE_KEYCODES // disables control of rgb matrix by keycodes (must use code functions to control the feature)

// Teal and Blue
// #define RGB_MATRIX_STARTUP_HUE 127 			// Default boot color
// Teal and Blue
// #define RGB_MATRIX_STARTUP_HUE 120 			// Default boot color

// Cyan and Yellow
//#define RGB_MATRIX_STARTUP_HUE 127 			// Default boot color
// Cyan and Green
//#define RGB_MATRIX_STARTUP_HUE 127 			// Default boot color

// #define RGB_MATRIX_STARTUP_SAT 255
// #define RGB_MATRIX_STARTUP_VAL 192

#define DISABLE_RGB_MATRIX_ALPHAS_MODS
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define DISABLE_RGB_MATRIX_BREATHING
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_VAL
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define DISABLE_RGB_MATRIX_CYCLE_ALL
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define DISABLE_RGB_MATRIX_DUAL_BEACON
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
