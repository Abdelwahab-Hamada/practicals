//This is an example of using a "Meyers" singleton class usable with threads.

#include "singleton.h"

std::mutex cout_mutex;

std::atomic<size_t> Singleton::s_refs{0U};

// This is the key method that returns the singleton reference
Singleton& Singleton::instance( void )
{
  ++s_refs;
  static Singleton instance{};
  volatile int dummy{}; // Prevent optimization issues
  return instance;
}

Singleton::Singleton( void ) // Default constructor
{
  std::cout << "Constructing Singleton" << std::endl;
}

Singleton::~Singleton( void ) // Destructor
{
  std::cout << "Destroying Singleton" << std::endl;
}

void Singleton::whoami( void )
{
  std::lock_guard<std::mutex> lock( cout_mutex );
  printf( "Singleton at @%p\n", this );
}

void Singleton::increment( void ) {
  ++m_count;
}

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