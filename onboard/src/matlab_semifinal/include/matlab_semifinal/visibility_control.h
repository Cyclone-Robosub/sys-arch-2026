#ifndef MATLAB_SEMIFINAL__VISIBILITY_CONTROL_H_
#define MATLAB_SEMIFINAL__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MATLAB_SEMIFINAL_EXPORT __attribute__ ((dllexport))
    #define MATLAB_SEMIFINAL_IMPORT __attribute__ ((dllimport))
  #else
    #define MATLAB_SEMIFINAL_EXPORT __declspec(dllexport)
    #define MATLAB_SEMIFINAL_IMPORT __declspec(dllimport)
  #endif
  #ifdef MATLAB_SEMIFINAL_BUILDING_LIBRARY
    #define MATLAB_SEMIFINAL_PUBLIC MATLAB_SEMIFINAL_EXPORT
  #else
    #define MATLAB_SEMIFINAL_PUBLIC MATLAB_SEMIFINAL_IMPORT
  #endif
  #define MATLAB_SEMIFINAL_PUBLIC_TYPE MATLAB_SEMIFINAL_PUBLIC
  #define MATLAB_SEMIFINAL_LOCAL
#else
  #define MATLAB_SEMIFINAL_EXPORT __attribute__ ((visibility("default")))
  #define MATLAB_SEMIFINAL_IMPORT
  #if __GNUC__ >= 4
    #define MATLAB_SEMIFINAL_PUBLIC __attribute__ ((visibility("default")))
    #define MATLAB_SEMIFINAL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MATLAB_SEMIFINAL_PUBLIC
    #define MATLAB_SEMIFINAL_LOCAL
  #endif
  #define MATLAB_SEMIFINAL_PUBLIC_TYPE
#endif
#endif  // MATLAB_SEMIFINAL__VISIBILITY_CONTROL_H_
// Generated 14-Jul-2026 17:20:27
 