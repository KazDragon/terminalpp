#include "terminalpp/glyph.hpp"
#include <iostream>

namespace terminalpp {

static bool const is_printable_g0_dec[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  false,
/* 0x80 - 0x87 */ false, false, false, false, false, false, false, false,
/* 0x88 - 0x8F */ false, false, false, false, false, false, false, false,
/* 0x90 - 0x97 */ false, false, false, false, false, false, false, false,
/* 0x98 - 0x9F */ false, false, false, false, false, false, false, false,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_g1_dec[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x80 - 0x87 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x88 - 0x8F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x90 - 0x97 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x98 - 0x9F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_g0_uk[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  false,
/* 0x80 - 0x87 */ false, false, false, false, false, false, false, false,
/* 0x88 - 0x8F */ false, false, false, false, false, false, false, false,
/* 0x90 - 0x97 */ false, false, false, false, false, false, false, false,
/* 0x98 - 0x9F */ false, false, false, false, false, false, false, false,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_g1_uk[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x80 - 0x87 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x88 - 0x8F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x90 - 0x97 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x98 - 0x9F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_g0_us_ascii[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  false,
/* 0x80 - 0x87 */ false, false, false, false, false, false, false, false,
/* 0x88 - 0x8F */ false, false, false, false, false, false, false, false,
/* 0x90 - 0x97 */ false, false, false, false, false, false, false, false,
/* 0x98 - 0x9F */ false, false, false, false, false, false, false, false,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_g1_us_ascii[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x80 - 0x87 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x88 - 0x8F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x90 - 0x97 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x98 - 0x9F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_g0_sco[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  false,
/* 0x80 - 0x87 */ false, false, false, false, false, false, false, false,
/* 0x88 - 0x8F */ false, false, false, false, false, false, false, false,
/* 0x90 - 0x97 */ false, false, false, false, false, false, false, false,
/* 0x98 - 0x9F */ false, false, false, false, false, false, false, false,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_g1_sco[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x80 - 0x87 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x88 - 0x8F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x90 - 0x97 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x98 - 0x9F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

// ==========================================================================
// OPERATOR<<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, glyph const &attr)
{
    out << "glyph[";

    // TODO: add glyphs.

    out << "]";

    return out;
}

// ==========================================================================
// IS_PRINTABLE
// ==========================================================================
bool is_printable(glyph const &gly)
{
    bool const *lookup = is_printable_g0_dec;

    switch (gly.character_set_)
    {
    case terminalpp::ansi::character_set::CHARACTER_SET_G0:
        switch (gly.locale_)
        {
        case terminalpp::ansi::character_set::LOCALE_DEC:
            lookup = is_printable_g0_dec;
            break;

        case terminalpp::ansi::character_set::LOCALE_UK:
            lookup = is_printable_g0_uk;
            break;

        case terminalpp::ansi::character_set::LOCALE_US_ASCII:
            lookup = is_printable_g0_us_ascii;
            break;

        case terminalpp::ansi::character_set::LOCALE_SCO:
            lookup = is_printable_g0_sco;
            break;
        }
        break;

    case terminalpp::ansi::character_set::CHARACTER_SET_G1:
        switch (gly.locale_)
        {
        case terminalpp::ansi::character_set::LOCALE_DEC:
            lookup = is_printable_g1_dec;
            break;

        case terminalpp::ansi::character_set::LOCALE_UK:
            lookup = is_printable_g1_uk;
            break;

        case terminalpp::ansi::character_set::LOCALE_US_ASCII:
            lookup = is_printable_g1_us_ascii;
            break;

        case terminalpp::ansi::character_set::LOCALE_SCO:
            lookup = is_printable_g1_sco;
            break;
        }
        break;
    }

    return lookup[terminalpp::u8(gly.character_)];
}

}

