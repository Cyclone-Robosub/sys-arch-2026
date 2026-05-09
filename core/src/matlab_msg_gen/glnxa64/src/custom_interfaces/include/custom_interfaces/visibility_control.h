#ifndef CUSTOM_INTERFACES__VISIBILITY_CONTROL_H_
#define CUSTOM_INTERFACES__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define CUSTOM_INTERFACES_EXPORT __attribute__ ((dllexport))
    #define CUSTOM_INTERFACES_IMPORT __attribute__ ((dllimport))
  #else
    #define CUSTOM_INTERFACES_EXPORT __declspec(dllexport)
    #define CUSTOM_INTERFACES_IMPORT __declspec(dllimport)
  #endif
  #ifdef CUSTOM_INTERFACES_BUILDING_LIBRARY
    #define CUSTOM_INTERFACES_PUBLIC CUSTOM_INTERFACES_EXPORT
  #else
    #define CUSTOM_INTERFACES_PUBLIC CUSTOM_INTERFACES_IMPORT
  #endif
  #define CUSTOM_INTERFACES_PUBLIC_TYPE CUSTOM_INTERFACES_PUBLIC
  #define CUSTOM_INTERFACES_LOCAL
#else
  #define CUSTOM_INTERFACES_EXPORT __attribute__ ((visibility("default")))
  #define CUSTOM_INTERFACES_IMPORT
  #if __GNUC__ >= 4
    #define CUSTOM_INTERFACES_PUBLIC __attribute__ ((visibility("default")))
    #define CUSTOM_INTERFACES_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define CUSTOM_INTERFACES_PUBLIC
    #define CUSTOM_INTERFACES_LOCAL
  #endif
  #define CUSTOM_INTERFACES_PUBLIC_TYPE
#endif
#endif  // CUSTOM_INTERFACES__VISIBILITY_CONTROL_H_
// Generated 08-Apr-2026 19:39:11
 