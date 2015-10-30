#ifndef ENUM_H
#define ENUM_H

#include <cstdint>

enum class choice : std::int8_t {Betray, RemainSilent};
enum class Mode : std::int8_t {Detailed, Fast, Tournament};
enum class Result : std::int8_t {Fail, Success};
#endif