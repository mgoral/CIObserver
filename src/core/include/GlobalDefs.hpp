#ifndef GLOBALDEFS_HPP
#define GLOBALDEFS_HPP

#include <libintl.h>
#include <glibmm/ustring.h>

#define _(String) gettext(String)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

namespace ci {

typedef Glib::ustring Name;
typedef Glib::ustring Description;
typedef Glib::ustring Url;

} // namespace ci

#endif

