// Disable this once we have List_sp working
#define USE_BAD_CAST_ERROR 1
//Turn these on only if x.nilp() are found in ASSERT(...) statements
#define ALLOW_NIL_OTHER 1
//#define ALLOW_CONS_NIL 1

/*
  File: smart_pointers.h
*/

/*
  Copyright (c) 2014, Christian E. Schafmeister

  CLASP is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  See directory 'clasp/licenses' for full details.

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
/* -^- */

//
// (C) 2004 Christian E. Schafmeister
//

#ifndef _core__pointer_tagging_H
#define _core__pointer_tagging_H

#include <boost/utility/binary.hpp>

#include <iostream>
#include <cstring>

#include <clasp/gctools/globals.h>

extern void lisp_errorUnexpectedNil(type_info const &toType);
extern void lisp_errorBadCast(type_info const &toType, type_info const &fromType, core::T_O *objP);
extern void lisp_errorBadCastFromT_O(type_info const &toType, core::T_O *objP);
extern void lisp_errorBadCastToFixnum_O(type_info const &fromType, core::T_O *objP);
extern void lisp_errorBadCastFromT_OToCons_O(core::T_O *objP);
extern void lisp_errorBadCastFromSymbol_O(type_info const &toType, core::Symbol_O *objP);
extern void lisp_errorDereferencedNonPointer(core::T_O *objP);

namespace core {
  class VaList_S;
  class Code_S;
};

namespace gctools {

template <class T>
class smart_ptr;

void initialize_smart_pointers();

#ifdef _ADDRESS_MODEL_64

 static const uintptr_t alignment = 8;    // 16 byte alignment for all pointers
 static const uintptr_t pointer_size = 8; // 8 byte words 64-bits

#if defined (CLASP_MS_WINDOWS_HOST)
#error "Define a 64bit Fixnum for windows"
#else
                                        //! Fixnum definition for 64 bit system
 typedef intptr_t Fixnum;
#endif

 typedef Fixnum cl_fixnum;
/*! A pointer that is already tagged can be passed to smart_ptr constructors
      by first reinterpret_casting it to Tagged */
 typedef uintptr_t Tagged;

 // DEFINE TAGGING SCHEME

 static const int tag_shift = 3;
 static const int fixnum_bits = 61;
 static const int fixnum_shift = 3;
 static const size_t thread_local_cl_stack_min_size = THREAD_LOCAL_CL_STACK_MIN_SIZE;

 // DEFINE MIN AND MAX CONSTS

 // --- SHORT ---
 static const short most_negative_short = std::numeric_limits<short>::min();
 static const short most_positive_short = std::numeric_limits<short>::max();
 static const unsigned short most_positive_ushort = std::numeric_limits<short>::max();

 // --- INT ---
 static const int most_negative_int = std::numeric_limits<int>::min();
 static const int most_positive_int = std::numeric_limits<int>::max();
 static const unsigned int most_positive_uint = std::numeric_limits<unsigned int>::max();

 // --- LONG ---
 static const long most_negative_long = std::numeric_limits<long>::min();
 static const long most_positive_long = std::numeric_limits<long>::max();
 static const unsigned long most_positive_ulong = std::numeric_limits<unsigned long>::max();

 // --- INT8 ---
 static const int8_t most_negative_int8 = std::numeric_limits<int8_t>::min();
 static const int8_t most_positive_int8 = std::numeric_limits<int8_t>::max();
 static const uint8_t most_positive_uint8 = std::numeric_limits<uint8_t>::max();

 // --- INT16 ---
 static const int16_t most_negative_int16 = std::numeric_limits<int16_t>::min();
 static const int16_t most_positive_int16 = std::numeric_limits<int16_t>::max();
 static const uint16_t most_positive_uint16 = std::numeric_limits<uint16_t>::max();

 // --- INT32 ---
 static const int32_t most_negative_int32 = std::numeric_limits<int32_t>::min();
 static const int32_t most_positive_int32 = std::numeric_limits<int32_t>::max();
 static const uint32_t most_positive_uint32 = std::numeric_limits<uint32_t>::max();

 // --- INT64 ---
 static const int64_t most_negative_int64 = std::numeric_limits<int64_t>::min();
 static const int64_t most_positive_int64 = std::numeric_limits<int64_t>::max();
 static const uint64_t most_positive_uint64 = std::numeric_limits<uint64_t>::max();

 // --- LONG LONG ---
 static const long long most_negative_long_long = std::numeric_limits<long long>::min();
 static const long long most_positive_long_long = std::numeric_limits<long long>::max();
 static const unsigned long long most_positive_unsigned_long_long = std::numeric_limits<unsigned long long>::max();

 // --- FIXNUM ---
 static const long int most_positive_fixnum = 1152921504606846975;
 static const long int most_negative_fixnum = -1152921504606846976;

#define MOST_POSITIVE_FIXNUM gctools::most_positive_fixnum
#define MOST_NEGATIVE_FIXNUM gctools::most_negative_fixnum
#define FIXNUM_BITS gctools::fixnum_bits

 // --- SIZE ---
 static const size_t most_negative_size = std::numeric_limits<size_t>::min();
 static const size_t most_positive_size = std::numeric_limits<size_t>::max();

 // --- SSIZE ---
 static const ssize_t most_negative_ssize = std::numeric_limits<ssize_t>::min();
 static const ssize_t most_positive_ssize = std::numeric_limits<ssize_t>::max();

 // --- CL_INTPTR_T ---
 static const cl_intptr_t most_negative_cl_intptr = std::numeric_limits<cl_intptr_t>::min();
 static const cl_intptr_t most_positive_cl_intptr = std::numeric_limits<cl_intptr_t>::max();

 // --- PTRDIFF_T ---
 static const ptrdiff_t most_negative_ptrdiff = std::numeric_limits<ptrdiff_t>::min();
 static const ptrdiff_t most_positive_ptrdiff = std::numeric_limits<ptrdiff_t>::max();

#endif // _ADRESS_MODEL_64

#ifdef _ADDRESS_MODEL_32
#error "Add support for 32 bits - squeeze, Squeeze, SQUEEZE!"
#endif

/*! Pointer and immediate value tagging is set up here */
/* FIXNUM's have the lsb set to zero - this allows addition and comparison to be fast */
/* The rest of the bits are the fixnum */
 static const uintptr_t tag_mask    = ZERO_TAG_MASK; // BOOST_BINARY(111);
static const uintptr_t fixnum_tag  = BOOST_BINARY(000); // x000 means fixnum
static const uintptr_t fixnum_mask = BOOST_BINARY(111);
/*! The pointer tags, that point to objects that the GC manages are general_tag and cons_tag
Robert Strandh suggested a separate tag for CONS cells so that there would be a quick CONSP test
for a CONS cell*/
 static const uintptr_t ptr_mask    = ~ZERO_TAG_MASK;
  static const uintptr_t general_tag =  POINTER_GENERAL_TAG; // BOOST_BINARY(001); // means a GENERAL pointer
  static const uintptr_t cons_tag    =  POINTER_CONS_TAG; // BOOST_BINARY(011);    // means a CONS cell pointer
                                                        /*! A test for pointers has the form (potential_ptr&pointer_tag_mask)==pointer_tag_eq */
  static const uintptr_t pointer_tag_mask = POINTER_TAG_MASK; // BOOST_BINARY(101);
  static const uintptr_t pointer_tag_eq   = POINTER_TAG_EQ; // BOOST_BINARY(001);
 /*! code_tag is a tag for a raw code in memory - remove the tag and call the resulting pointer
*/
 static const uintptr_t unused0_tag = BOOST_BINARY(010);
 static const uintptr_t unused1_tag = BOOST_BINARY(100);

 /*! gc_tag is used for headerless objects to indicate that this word is
used by the garbage collector */
 static const uintptr_t gc_tag = ZERO_TAG_MASK; //BOOST_BINARY(111);
 
/*! valist_tag is a tag for va_list(s) on the stack, it is used by Clasp to 
iterate over variable numbers of arguments passed to functions.
Pointers with this tag are NOT moved in memory, the objects valist_tag'd pointers
point to are only ever on the stack.
I hack the va_list structure in X86_64 ABI dependent ways and I will abstract all of the
ABI dependent behavior into a single header file so that it can be implemented for other
ABI's  */
static const uintptr_t valist_tag = BOOST_BINARY(101); // means a valist
                                                       /*! Immediate value tags */
 static const uintptr_t immediate_mask   = BOOST_BINARY(11111);
 static const uintptr_t character_tag    = BOOST_BINARY(00110); // Character
 static const uintptr_t character_shift  = 5;
 static const uintptr_t single_float_tag = BOOST_BINARY(01110); // single-float
 static const uintptr_t single_float_shift = 5;
 static const uintptr_t single_float_mask = 0x1FFFFFFFFF; // single-floats are in these 32+5bits

 struct Immediate_info {
   uintptr_t _kind;
   const char* _name;
 Immediate_info(uintptr_t k, const char* n) : _kind(k), _name(n) {};
 };

 std::vector<Immediate_info> get_immediate_info();

 static const uintptr_t kind_fixnum = 1;
 static const uintptr_t kind_single_float = 2;
 static const uintptr_t kind_character = 3;
 static const uintptr_t kind_cons = 4;
 static const uintptr_t kind_first_general = 5;
 static const uintptr_t kind_first_alien = 65536;
 static const uintptr_t kind_last_alien = 2 * 65536 - 1;
 static const uintptr_t kind_first_instance = 2 * 65536;

 template <class T>
   T tag(T ptr) { return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(ptr) & tag_mask); };

 template <class T>
   inline bool tagged_consp(T ptr) {
   return (reinterpret_cast<uintptr_t>(tag(ptr)) == cons_tag);
 };
 static const std::string tagged_cons_str = "CONS";

 template <class T>
   inline T tag_cons(T p) {
   GCTOOLS_ASSERT((reinterpret_cast<uintptr_t>(p) & tag_mask) == 0);
   return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(p) + cons_tag);
 }

 template <class T>
   inline T untag_cons(T ptr) {
   GCTOOLS_ASSERT((reinterpret_cast<uintptr_t>(ptr) & tag_mask) == cons_tag);
   return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(ptr) - cons_tag);
 }

 template <class T>
   inline T tag_general(T p) {
   GCTOOLS_ASSERT((reinterpret_cast<uintptr_t>(p) & tag_mask) == 0);
   return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(p) + general_tag);
 }

 template <class T>
   inline T tag_object(T ptr) {
   return tag_general<T>(ptr);
 }
 template <>
   inline core::Cons_O *tag_object<core::Cons_O *>(core::Cons_O *ptr) {
   return tag_cons<core::Cons_O *>(ptr);
 }

 template <class T>
   inline bool tagged_nilp(T ptr) {
   return (reinterpret_cast<void *>(ptr) == global_tagged_Symbol_OP_nil);
 }
 static const std::string tagged_nil_str = "NIL";

 template <class T>
   inline bool tagged_unboundp(T ptr) {
   return (reinterpret_cast<void *>(ptr) == global_tagged_Symbol_OP_unbound);
 }
 static const std::string tagged_unbound_str = "UNBOUND";

 template <class T>
   inline bool tagged_deletedp(T ptr) {
   return (reinterpret_cast<void *>(ptr) == global_tagged_Symbol_OP_deleted);
 }
 static const std::string tagged_deleted_str = "DELETED";

 template <class T>
   inline bool tagged_sameAsKeyp(T ptr) {
   return (reinterpret_cast<void *>(ptr) == global_tagged_Symbol_OP_sameAsKey);
 }
 static const std::string tagged_same_as_key_str = "SAME_AS_KEY";


 template <class T>
   inline T tag_nil() {
   GCTOOLS_ASSERT(tagged_nilp(global_tagged_Symbol_OP_nil));
   return reinterpret_cast<T>(global_tagged_Symbol_OP_nil);
 }
 template <class T>
   inline T tag_unbound() {
   GCTOOLS_ASSERT(tagged_unboundp(global_tagged_Symbol_OP_unbound));
   return reinterpret_cast<T>(global_tagged_Symbol_OP_unbound);
 }
 template <class T>
   inline T tag_deleted() {
   GCTOOLS_ASSERT(tagged_deletedp(global_tagged_Symbol_OP_deleted));
   return reinterpret_cast<T>(global_tagged_Symbol_OP_deleted);
 }
 template <class T>
   inline T tag_sameAsKey() {
   GCTOOLS_ASSERT(tagged_sameAsKeyp(global_tagged_Symbol_OP_sameAsKey));
   return reinterpret_cast<T>(global_tagged_Symbol_OP_sameAsKey);
 }
 template <class T>
   inline T tag_valist(core::VaList_S *p) {
   GCTOOLS_ASSERT((reinterpret_cast<uintptr_t>(p) & tag_mask) == 0);
   return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(p) + valist_tag);
 }
 static const std::string tagged_valist_str = "VALIST";


 template <class T>
   inline T untag_general(T ptr) {
   GCTOOLS_ASSERT((reinterpret_cast<uintptr_t>(ptr) & tag_mask) == general_tag);
   return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(ptr) - general_tag);
 }
 template <class T>
   inline void *untag_valist(T ptr) {
   GCTOOLS_ASSERT((reinterpret_cast<uintptr_t>(ptr) & tag_mask) == valist_tag);
   return reinterpret_cast<core::VaList_S*>(reinterpret_cast<uintptr_t>(ptr) - valist_tag);
 }


 template <class T>
   inline T tag_fixnum(Fixnum fn) {
   return reinterpret_cast<T>((fn << fixnum_shift));
 }

 template <class T>
 inline Fixnum untag_fixnum(T const ptr)
 {
   return (Fixnum)(reinterpret_cast<Fixnum>(ptr) >> fixnum_shift);
 }

 template <class T>
   inline bool tagged_fixnump(T ptr) {
   return ((reinterpret_cast<uintptr_t>(ptr) & fixnum_mask) == fixnum_tag);
 };
 static const std::string tagged_fixnum_str = "FIXNUM";

 template <class T>
   inline T tag_character(int ch) {
   return reinterpret_cast<T>((ch << character_shift) | character_tag);
 }
 template <class T>
   inline int untag_character(T ptr) {
   return (int)(reinterpret_cast<uintptr_t>(ptr) >> character_shift);
 }
 template <class T>
   inline bool tagged_characterp(T ptr) {
   return ((reinterpret_cast<uintptr_t>(ptr) & immediate_mask) == character_tag);
 };
 static const std::string tagged_character_str = "CHARACTER";

 template <class T>
   inline T tag_single_float(float fn) {
   GCTOOLS_ASSERT(sizeof(uintptr_t) == 8);
   GCTOOLS_ASSERT(sizeof(float) == 4);
   uintptr_t val;
   memcpy(&val, &fn, sizeof(fn));
   return reinterpret_cast<T>((val << single_float_shift) + single_float_tag);
 }
 template <class T>
   inline uintptr_t tagged_single_float_masked(T const ptr) {
   return reinterpret_cast<uintptr_t>(reinterpret_cast<uintptr_t>(ptr) & single_float_mask);
 }
 template <class T>
   inline float untag_single_float(T const ptr) {
   GCTOOLS_ASSERT((reinterpret_cast<uintptr_t>(ptr) & immediate_mask) == single_float_tag);
   GCTOOLS_ASSERT(sizeof(uintptr_t) == 8);
   GCTOOLS_ASSERT(sizeof(float) == 4);
   uintptr_t val(reinterpret_cast<uintptr_t>(ptr));
   float result;
   val >>= single_float_shift;
   memcpy(&result, &val, sizeof(result));
   return result;
 }
 template <class T>
   inline bool tagged_single_floatp(T ptr) {
   return ((reinterpret_cast<uintptr_t>(ptr) & immediate_mask) == single_float_tag);
 };
 static const std::string tagged_single_float_str = "SINGLE_FLOAT";


 template <class T>
   inline bool tagged_generalp(T ptr) {
   return ((uintptr_t)(ptr) & tag_mask) == general_tag;
 }
 static const std::string tagged_general_str = "GENERAL";

 template <class T>
   inline bool tagged_valistp(T ptr) {
   return ((reinterpret_cast<uintptr_t>(ptr) & tag_mask) == valist_tag);
 };

 template <class T>
   inline bool tagged_objectp(T ptr) {
   return (reinterpret_cast<uintptr_t>(ptr) & pointer_tag_mask) == pointer_tag_eq;
 }
 static const std::string tagged_object_str = "OBJECT";

 template <class Type>
   inline Type untag_object(Type tagged_obj) {
   GCTOOLS_ASSERT(tagged_objectp(tagged_obj));
   return reinterpret_cast<Type>((uintptr_t)tagged_obj & ptr_mask);
 }

// This returns a string containing info if and which tagged object is given
// as parameter.
 template< typename T >
   std::string tag_str(T tagged_obj)
 {
   if( tagged_consp( tagged_obj )  )
   {
     return tagged_cons_str;
   }

   if( tagged_nilp( tagged_obj )  )
   {
     return tagged_nil_str;
   }

   if( tagged_unboundp( tagged_obj )  )
   {
     return tagged_unbound_str;
   }

   if( tagged_deletedp( tagged_obj )  )
   {
     return tagged_deleted_str;
   }

   if( tagged_sameAsKeyp( tagged_obj )  )
   {
     return tagged_same_as_key_str;
   }

   if( tagged_valistp( tagged_obj )  )
   {
     return tagged_valist_str;
   }

   if( tagged_fixnump( tagged_obj )  )
   {
     return tagged_fixnum_str;
   }

   if( tagged_characterp( tagged_obj )  )
   {
     return tagged_character_str;
   }

   if( tagged_single_floatp( tagged_obj )  )
   {
     return tagged_single_float_str;
   }

   if( tagged_generalp( tagged_obj )  )
   {
     return tagged_general_str;
   }

   if( tagged_objectp( tagged_obj )  )
   {
     return tagged_object_str;
   }

   return "*** UNKNOW_TAG ***";

 }; // tag_str

 template< typename T >
   std::string tag_info(T tagged_obj)
 {
   std::stringstream ss;

   ss << "<object tag info:";
   ss << " type id: " << typeid( T ).name();
   ss << " tag: " << tag_str( tagged_obj );
   ss << ">";

   return ss.str();

 }; // tag_info

}; // namespace gctools

#endif // pointer_tagging
