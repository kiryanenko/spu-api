/*
  structure.hpp
        - definitions of structure template class with it's void specialization
        - this is the base interface class in SPU library

  Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
                  Alex Popov <alexpopov@bmsru.ru>
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

#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include "key.hpp"
#include "fields.hpp"
#include "base_structure.hpp"

namespace SPU
{

/***************************************
  Structure template class declaration
***************************************/

/* Template Structure class definition */
template<typename KeyFieldNameType = void>
class Structure
{
private:
  BaseStructure base;
  Key<KeyFieldNameType> key;

public:
  Structure(FieldLengthVector<KeyFieldNameType> fields_length_vector) : base(), key(fields_length_vector) {}

  /*************************************
    Redefinitions of BaseStructure
    commands with composite key
  *************************************/

  rslt_t insert(FieldDataVector<KeyFieldNameType> fields_data_vector, value_t value, flags_t flags = NO_FLAGS)
  {
    return base.insert(key.compile(fields_data_vector), value, flags);
  }
};


/***************************************
  Structure special class declaration
***************************************/

/* Structure class void specialization witch is only BaseStructure son */
template<>
class Structure<void> : public BaseStructure
{
public:
  Structure() : BaseStructure() {}
};

} /* namespace SPU */

#endif /* STRUCTURE_HPP */