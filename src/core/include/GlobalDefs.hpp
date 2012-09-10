#ifndef GLOBALDEFS_HPP
#define GLOBALDEFS_HPP

// enables poco_debug
#ifdef poco_debug
#undef poco_debug
#endif
#define poco_debug(logger, msg) if ((logger).debug()) (logger).debug(msg); else (void) 0

#include <libintl.h>
#include <glibmm/ustring.h>

#define _(String) gettext(String)
#define gettext_noop(String) String
#define N_(String) gettext_noop (String)

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
typedef Glib::ustring Path;

} // namespace ci

#endif

