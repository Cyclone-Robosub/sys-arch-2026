#ifndef MATLAB_NODE__VISIBILITY_CONTROL_H_
#define MATLAB_NODE__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MATLAB_NODE_EXPORT __attribute__ ((dllexport))
    #define MATLAB_NODE_IMPORT __attribute__ ((dllimport))
  #else
    #define MATLAB_NODE_EXPORT __declspec(dllexport)
    #define MATLAB_NODE_IMPORT __declspec(dllimport)
  #endif
  #ifdef MATLAB_NODE_BUILDING_LIBRARY
    #define MATLAB_NODE_PUBLIC MATLAB_NODE_EXPORT
  #else
    #define MATLAB_NODE_PUBLIC MATLAB_NODE_IMPORT
  #endif
  #define MATLAB_NODE_PUBLIC_TYPE MATLAB_NODE_PUBLIC
  #define MATLAB_NODE_LOCAL
#else
  #define MATLAB_NODE_EXPORT __attribute__ ((visibility("default")))
  #define MATLAB_NODE_IMPORT
  #if __GNUC__ >= 4
    #define MATLAB_NODE_PUBLIC __attribute__ ((visibility("default")))
    #define MATLAB_NODE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MATLAB_NODE_PUBLIC
    #define MATLAB_NODE_LOCAL
  #endif
  #define MATLAB_NODE_PUBLIC_TYPE
#endif
#endif  // MATLAB_NODE__VISIBILITY_CONTROL_H_
// Generated 07-Jul-2026 19:47:08
 