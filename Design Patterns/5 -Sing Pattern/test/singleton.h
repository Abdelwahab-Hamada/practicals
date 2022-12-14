#ifndef SINGLETON_H
#define SINGLETON_H
#include <atomic>
#include <mutex>
#include <cstdint>
#include <cassert>
#include <iostream>

extern std::mutex cout_mutex;

struct Singleton {

  static Singleton& instance( void );

  // Other public methods
  void whoami( void );
  void increment( void );
  // Accessors
  size_t get_count( void ) const { return m_count; }
  static size_t get_refs( void ) { return s_refs; }

private: //deletes don't need to be private, but it's of no interest publically either
  Singleton( const Singleton& rhs ) = delete;  // copy constructor
  const Singleton& operator=( const Singleton& rhs ) = delete;  // copy assignment
  Singleton( const Singleton&& rhs ) = delete;  // move constructor
  const Singleton& operator=( const Singleton&& rhs ) = delete;  // move assignment
  Singleton( void ); // Default constructor
  ~Singleton( void ); // Destructor
  // attributes
  std::atomic<size_t> m_count{0U};
  static std::atomic<size_t> s_refs;
};
#endif

////////////////////////////////////////////////////////////////////////////////
//
//   Copyright 2017 Doulos Inc.
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////