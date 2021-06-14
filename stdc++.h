// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2021 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

// 17.4.1.2 Headers

// C
#ifndef _GLIBCXX_NO_ASSERT
#if __has_include("cassert")
#include <cassert>
#endif
#endif
#if __has_include("cctype")
#include <cctype>
#endif
#if __has_include("cerrno")
#include <cerrno>
#endif
#if __has_include("cfloat")
#include <cfloat>
#endif
#if __has_include("ciso646")
#include <ciso646>
#endif
#if __has_include("climits")
#include <climits>
#endif
#if __has_include("clocale")
#include <clocale>
#endif
#if __has_include("cmath")
#include <cmath>
#endif
#if __has_include("csetjmp")
#include <csetjmp>
#endif
#if __has_include("csignal")
#include <csignal>
#endif
#if __has_include("cstdarg")
#include <cstdarg>
#endif
#if __has_include("cstddef")
#include <cstddef>
#endif
#if __has_include("cstdio")
#include <cstdio>
#endif
#if __has_include("cstdlib")
#include <cstdlib>
#endif
#if __has_include("cstring")
#include <cstring>
#endif
#if __has_include("ctime")
#include <ctime>
#endif
#if __has_include("cwchar")
#include <cwchar>
#endif
#if __has_include("cwctype")
#include <cwctype>
#endif

#if __cplusplus >= 201103L
#if __has_include("ccomplex")
#include <ccomplex>
#endif
#if __has_include("cfenv")
#include <cfenv>
#endif
#if __has_include("cinttypes")
#include <cinttypes>
#endif
#if __has_include("cstdalign")
#include <cstdalign>
#endif
#if __has_include("cstdbool")
#include <cstdbool>
#endif
#if __has_include("cstdint")
#include <cstdint>
#endif
#if __has_include("ctgmath")
#include <ctgmath>
#endif
#if __has_include("cuchar")
#include <cuchar>
#endif
#endif

// C++
#if __has_include("algorithm")
#include <algorithm>
#endif
#if __has_include("bitset")
#include <bitset>
#endif
#if __has_include("complex")
#include <complex>
#endif
#if __has_include("deque")
#include <deque>
#endif
#if __has_include("exception")
#include <exception>
#endif
#if __has_include("fstream")
#include <fstream>
#endif
#if __has_include("functional")
#include <functional>
#endif
#if __has_include("iomanip")
#include <iomanip>
#endif
#if __has_include("ios")
#include <ios>
#endif
#if __has_include("iosfwd")
#include <iosfwd>
#endif
#if __has_include("iostream")
#include <iostream>
#endif
#if __has_include("istream")
#include <istream>
#endif
#if __has_include("iterator")
#include <iterator>
#endif
#if __has_include("limits")
#include <limits>
#endif
#if __has_include("list")
#include <list>
#endif
#if __has_include("locale")
#include <locale>
#endif
#if __has_include("map")
#include <map>
#endif
#if __has_include("memory")
#include <memory>
#endif
#if __has_include("new")
#include <new>
#endif
#if __has_include("numeric")
#include <numeric>
#endif
#if __has_include("ostream")
#include <ostream>
#endif
#if __has_include("queue")
#include <queue>
#endif
#if __has_include("set")
#include <set>
#endif
#if __has_include("sstream")
#include <sstream>
#endif
#if __has_include("stack")
#include <stack>
#endif
#if __has_include("stdexcept")
#include <stdexcept>
#endif
#if __has_include("streambuf")
#include <streambuf>
#endif
#if __has_include("string")
#include <string>
#endif
#if __has_include("typeinfo")
#include <typeinfo>
#endif
#if __has_include("utility")
#include <utility>
#endif
#if __has_include("valarray")
#include <valarray>
#endif
#if __has_include("vector")
#include <vector>
#endif

#if __cplusplus >= 201103L
#if __has_include("array")
#include <array>
#endif
#if __has_include("atomic")
#include <atomic>
#endif
#if __has_include("chrono")
#include <chrono>
#endif
#if __has_include("codecvt")
#include <codecvt>
#endif
#if __has_include("condition_variable")
#include <condition_variable>
#endif
#if __has_include("forward_list")
#include <forward_list>
#endif
#if __has_include("future")
#include <future>
#endif
#if __has_include("initializer_list")
#include <initializer_list>
#endif
#if __has_include("mutex")
#include <mutex>
#endif
#if __has_include("random")
#include <random>
#endif
#if __has_include("ratio")
#include <ratio>
#endif
#if __has_include("regex")
#include <regex>
#endif
#if __has_include("scoped_allocator")
#include <scoped_allocator>
#endif
#if __has_include("system_error")
#include <system_error>
#endif
#if __has_include("thread")
#include <thread>
#endif
#if __has_include("tuple")
#include <tuple>
#endif
#if __has_include("typeindex")
#include <typeindex>
#endif
#if __has_include("type_traits")
#include <type_traits>
#endif
#if __has_include("unordered_map")
#include <unordered_map>
#endif
#if __has_include("unordered_set")
#include <unordered_set>
#endif
#endif

#if __cplusplus >= 201402L
#if __has_include("shared_mutex")
#include <shared_mutex>
#endif
#endif

#if __cplusplus >= 201703L
#if __has_include("any")
#include <any>
#endif
#if __has_include("charconv")
#include <charconv>
#endif
// #include <execution>
#if __has_include("filesystem")
#include <filesystem>
#endif
#if __has_include("optional")
#include <optional>
#endif
#if __has_include("memory_resource")
#include <memory_resource>
#endif
#if __has_include("string_view")
#include <string_view>
#endif
#if __has_include("variant")
#include <variant>
#endif
#endif

#if __cplusplus > 201703L
#if __has_include("barrier")
#include <barrier>
#endif
#if __has_include("bit")
#include <bit>
#endif
#if __has_include("compare")
#include <compare>
#endif
#if __has_include("concepts")
#include <concepts>
#endif
#if __cpp_impl_coroutine
#if __has_include("coroutine")
# include <coroutine>
#endif
#endif
#if __has_include("latch")
#include <latch>
#endif
#if __has_include("numbers")
#include <numbers>
#endif
#if __has_include("ranges")
#include <ranges>
#endif
#if __has_include("span")
#include <span>
#endif
#if __has_include("stop_token")
#include <stop_token>
#endif
#if __has_include("semaphore")
#include <semaphore>
#endif
#if __has_include("source_location")
#include <source_location>
#endif
#if __has_include("syncstream")
#include <syncstream>
#endif
#if __has_include("version")
#include <version>
#endif
#endif
