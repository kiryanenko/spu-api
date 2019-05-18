/*
  libspu.hpp
        - main SPU library include file
        - file defines containers for key and value data and some more type hiders
        - file presents BitFlow class
        - have all need to_string convertors

  Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
                  Alex Popov <alexpopov@bmstu.ru>
                  Bauman Moscow State Technical University

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBSPU_HPP
#define LIBSPU_HPP

#include "spu.h"
#include "data_container_operators.h"

#include <string>

namespace SPU
{

/* SPU key-value pair with SPU's status type */
struct pair_containter
{
  key_t    key;
  value_t  value;
  status_t status;

  explicit pair_containter(status_t s=OK) : status(s) {}
  pair_containter(key_t k, value_t v, status_t s=OK) : key(k), value(v), status(s) {}
};
typedef struct pair_containter pair_t;

/* Class providing bit flow from any type */
class BitFlow
{
private:
  data_t d;

public:
  operator data_t() const          { return d; }
  BitFlow(void)        : d({0})    {}
  BitFlow(data_t data) : d(data)   {}
  BitFlow(u32 data)                { d[0] = (u32)data; d[1] = 0; }
  BitFlow(bool data)               { d[0] = (u32)data; d[1] = 0; }
  BitFlow(short data)              { d[0] = (u32)data; d[1] = 0; }
  BitFlow(int data)                { d[0] = (u32)data; d[1] = 0; }
  BitFlow(long data)               { d[0] = (u32)data; d[1] = (u32)(data>>31)>>1; }
  BitFlow(long long data)          { d[0] = (u32)data; d[1] = (u32)(data>>32); }
  BitFlow(unsigned short data)     { d[0] = (u32)data; d[1] = 0; }
  BitFlow(unsigned long data)      { d[0] = (u32)data; d[1] = (u32)(data>>31)>>1; }
  BitFlow(unsigned long long data) { d[0] = (u32)data; d[1] = (u32)(data>>32); }

     BitFlow operator+(BitFlow& other) { return (data_t) *this + (data_t) other; }
     BitFlow operator-(BitFlow& other) { return (data_t) *this - (data_t) other; }
        u32& operator[](u8 idx)        { return d[idx]; }
  const u32& operator[](u8 idx) const  { return d[idx]; }
             operator bool()           { return (bool) d[0]; }
             operator u8()             { return (u8) d[0]; }
};



/* Convert GSID to string */
std::string to_string(gsid_t gsid);
/* Convert data container to string */
std::string to_string(struct data_container data, bool hex = false);
/* Convert result into string */
std::string to_string(status_t status);
/* Convert key : value pair with status into string */
std::string to_string(pair_t pair, bool hex = false);

} /* namespace SPU */

#endif /* LIBSPU_HPP */