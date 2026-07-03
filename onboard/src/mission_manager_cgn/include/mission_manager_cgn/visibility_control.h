#ifndef MISSION_MANAGER_CGN__VISIBILITY_CONTROL_H_
#define MISSION_MANAGER_CGN__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MISSION_MANAGER_CGN_EXPORT __attribute__ ((dllexport))
    #define MISSION_MANAGER_CGN_IMPORT __attribute__ ((dllimport))
  #else
    #define MISSION_MANAGER_CGN_EXPORT __declspec(dllexport)
    #define MISSION_MANAGER_CGN_IMPORT __declspec(dllimport)
  #endif
  #ifdef MISSION_MANAGER_CGN_BUILDING_LIBRARY
    #define MISSION_MANAGER_CGN_PUBLIC MISSION_MANAGER_CGN_EXPORT
  #else
    #define MISSION_MANAGER_CGN_PUBLIC MISSION_MANAGER_CGN_IMPORT
  #endif
  #define MISSION_MANAGER_CGN_PUBLIC_TYPE MISSION_MANAGER_CGN_PUBLIC
  #define MISSION_MANAGER_CGN_LOCAL
#else
  #define MISSION_MANAGER_CGN_EXPORT __attribute__ ((visibility("default")))
  #define MISSION_MANAGER_CGN_IMPORT
  #if __GNUC__ >= 4
    #define MISSION_MANAGER_CGN_PUBLIC __attribute__ ((visibility("default")))
    #define MISSION_MANAGER_CGN_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MISSION_MANAGER_CGN_PUBLIC
    #define MISSION_MANAGER_CGN_LOCAL
  #endif
  #define MISSION_MANAGER_CGN_PUBLIC_TYPE
#endif
#endif  // MISSION_MANAGER_CGN__VISIBILITY_CONTROL_H_
// Generated 30-Jun-2026 20:18:09
 