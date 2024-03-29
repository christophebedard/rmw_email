// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/* This header must be included by all EMAIL headers which declare symbols
 * which are defined in the EMAIL library. When not building the EMAIL
 * library, i.e. when using the headers in other package's code, the contents
 * of this header change the visibility of certain symbols which the EMAIL
 * library cannot have, but the consuming code must have inorder to link.
 */

#ifndef EMAIL__VISIBILITY_CONTROL_HPP_
#define EMAIL__VISIBILITY_CONTROL_HPP_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define EMAIL_EXPORT __attribute__ ((dllexport))
    #define EMAIL_IMPORT __attribute__ ((dllimport))
  #else
    #define EMAIL_EXPORT __declspec(dllexport)
    #define EMAIL_IMPORT __declspec(dllimport)
  #endif
  #ifdef EMAIL_BUILDING_DLL
    #define EMAIL_PUBLIC EMAIL_EXPORT
  #else
    #define EMAIL_PUBLIC EMAIL_IMPORT
  #endif
  #define EMAIL_PUBLIC_TYPE EMAIL_PUBLIC
  #define EMAIL_LOCAL
#else
  #define EMAIL_EXPORT __attribute__ ((visibility("default")))
  #define EMAIL_IMPORT
  #if __GNUC__ >= 4
    #define EMAIL_PUBLIC __attribute__ ((visibility("default")))
    #define EMAIL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define EMAIL_PUBLIC
    #define EMAIL_LOCAL
  #endif
  #define EMAIL_PUBLIC_TYPE
#endif

#endif  // EMAIL__VISIBILITY_CONTROL_HPP_
