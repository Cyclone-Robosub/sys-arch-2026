#ifndef CASCADED_CONTROLLER__VISIBILITY_CONTROL_H_
#define CASCADED_CONTROLLER__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define CASCADED_CONTROLLER_EXPORT __attribute__ ((dllexport))
    #define CASCADED_CONTROLLER_IMPORT __attribute__ ((dllimport))
  #else
    #define CASCADED_CONTROLLER_EXPORT __declspec(dllexport)
    #define CASCADED_CONTROLLER_IMPORT __declspec(dllimport)
  #endif
  #ifdef CASCADED_CONTROLLER_BUILDING_LIBRARY
    #define CASCADED_CONTROLLER_PUBLIC CASCADED_CONTROLLER_EXPORT
  #else
    #define CASCADED_CONTROLLER_PUBLIC CASCADED_CONTROLLER_IMPORT
  #endif
  #define CASCADED_CONTROLLER_PUBLIC_TYPE CASCADED_CONTROLLER_PUBLIC
  #define CASCADED_CONTROLLER_LOCAL
#else
  #define CASCADED_CONTROLLER_EXPORT __attribute__ ((visibility("default")))
  #define CASCADED_CONTROLLER_IMPORT
  #if __GNUC__ >= 4
    #define CASCADED_CONTROLLER_PUBLIC __attribute__ ((visibility("default")))
    #define CASCADED_CONTROLLER_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define CASCADED_CONTROLLER_PUBLIC
    #define CASCADED_CONTROLLER_LOCAL
  #endif
  #define CASCADED_CONTROLLER_PUBLIC_TYPE
#endif
#endif  // CASCADED_CONTROLLER__VISIBILITY_CONTROL_H_
// Generated 02-Jul-2026 21:06:41
 