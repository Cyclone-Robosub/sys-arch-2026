#ifndef SIMPLE_JOYSTICK_CGN__VISIBILITY_CONTROL_H_
#define SIMPLE_JOYSTICK_CGN__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define SIMPLE_JOYSTICK_CGN_EXPORT __attribute__ ((dllexport))
    #define SIMPLE_JOYSTICK_CGN_IMPORT __attribute__ ((dllimport))
  #else
    #define SIMPLE_JOYSTICK_CGN_EXPORT __declspec(dllexport)
    #define SIMPLE_JOYSTICK_CGN_IMPORT __declspec(dllimport)
  #endif
  #ifdef SIMPLE_JOYSTICK_CGN_BUILDING_LIBRARY
    #define SIMPLE_JOYSTICK_CGN_PUBLIC SIMPLE_JOYSTICK_CGN_EXPORT
  #else
    #define SIMPLE_JOYSTICK_CGN_PUBLIC SIMPLE_JOYSTICK_CGN_IMPORT
  #endif
  #define SIMPLE_JOYSTICK_CGN_PUBLIC_TYPE SIMPLE_JOYSTICK_CGN_PUBLIC
  #define SIMPLE_JOYSTICK_CGN_LOCAL
#else
  #define SIMPLE_JOYSTICK_CGN_EXPORT __attribute__ ((visibility("default")))
  #define SIMPLE_JOYSTICK_CGN_IMPORT
  #if __GNUC__ >= 4
    #define SIMPLE_JOYSTICK_CGN_PUBLIC __attribute__ ((visibility("default")))
    #define SIMPLE_JOYSTICK_CGN_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define SIMPLE_JOYSTICK_CGN_PUBLIC
    #define SIMPLE_JOYSTICK_CGN_LOCAL
  #endif
  #define SIMPLE_JOYSTICK_CGN_PUBLIC_TYPE
#endif
#endif  // SIMPLE_JOYSTICK_CGN__VISIBILITY_CONTROL_H_
// Generated 09-May-2026 13:12:43
 