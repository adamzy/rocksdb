//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
//
// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// Must not be included from any .h files to avoid polluting the namespace
// with macros.

#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string>
#include "port/port.h"

// Helper macros that include information about file name and line number
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define PREPEND_FILE_LINE(FMT) ("[" __FILE__ ":" TOSTRING(__LINE__) "] " FMT)

// Don't inclide file/line info in HEADER level
#define ROCKS_LOG_HEADER(LGR, FMT, ...) \
  rocksdb::Log(InfoLogLevel::HEADER_LEVEL, LGR, FMT, ##__VA_ARGS__)

#define ROCKS_LOG_DEBUG(LGR, FMT, ...)                                 \
  rocksdb::Log(InfoLogLevel::DEBUG_LEVEL, LGR, PREPEND_FILE_LINE(FMT), \
               ##__VA_ARGS__)

#define ROCKS_LOG_INFO(LGR, FMT, ...)                                 \
  rocksdb::Log(InfoLogLevel::INFO_LEVEL, LGR, PREPEND_FILE_LINE(FMT), \
               ##__VA_ARGS__)

#define ROCKS_LOG_WARN(LGR, FMT, ...)                                 \
  rocksdb::Log(InfoLogLevel::WARN_LEVEL, LGR, PREPEND_FILE_LINE(FMT), \
               ##__VA_ARGS__)

#define ROCKS_LOG_ERROR(LGR, FMT, ...)                                 \
  rocksdb::Log(InfoLogLevel::ERROR_LEVEL, LGR, PREPEND_FILE_LINE(FMT), \
               ##__VA_ARGS__)

#define ROCKS_LOG_FATAL(LGR, FMT, ...)                                 \
  rocksdb::Log(InfoLogLevel::FATAL_LEVEL, LGR, PREPEND_FILE_LINE(FMT), \
               ##__VA_ARGS__)

#define ROCKS_LOG_BUFFER(LOG_BUF, FMT, ...) \
  rocksdb::LogToBuffer(LOG_BUF, PREPEND_FILE_LINE(FMT), ##__VA_ARGS__)

#define ROCKS_LOG_BUFFER_MAX_SZ(LOG_BUF, MAX_LOG_SIZE, FMT, ...)      \
  rocksdb::LogToBuffer(LOG_BUF, MAX_LOG_SIZE, PREPEND_FILE_LINE(FMT), \
                       ##__VA_ARGS__)

namespace rocksdb {

class Slice;

// Append a human-readable time in micros.
int AppendHumanMicros(uint64_t micros, char* output, int len,
                      bool fixed_format);

// Append a human-readable size in bytes
int AppendHumanBytes(uint64_t bytes, char* output, int len);

// Append a human-readable printout of "num" to *str
extern void AppendNumberTo(std::string* str, uint64_t num);

// Append a human-readable printout of "value" to *str.
// Escapes any non-printable characters found in "value".
extern void AppendEscapedStringTo(std::string* str, const Slice& value);

// Return a string printout of "num"
extern std::string NumberToString(uint64_t num);

// Return a human-readable version of num.
// for num >= 10.000, prints "xxK"
// for num >= 10.000.000, prints "xxM"
// for num >= 10.000.000.000, prints "xxG"
extern std::string NumberToHumanString(int64_t num);

// Return a human-readable version of bytes
// ex: 1048576 -> 1.00 GB
extern std::string BytesToHumanString(uint64_t bytes);

// Return a human-readable version of "value".
// Escapes any non-printable characters found in "value".
extern std::string EscapeString(const Slice& value);

// Parse a human-readable number from "*in" into *value.  On success,
// advances "*in" past the consumed number and sets "*val" to the
// numeric value.  Otherwise, returns false and leaves *in in an
// unspecified state.
extern bool ConsumeDecimalNumber(Slice* in, uint64_t* val);

}  // namespace rocksdb
