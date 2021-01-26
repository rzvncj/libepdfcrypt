#include <gmime/gmime.h>
#include "init.hpp"
#include <stdexcept>


namespace epdfcrypt {


sys_initializer::sys_initializer()
{
    g_mime_init(0);
}


sys_initializer::~sys_initializer()
{
}


} // namespace epdfcrypt


/*
  Local Variables:
  mode: c++
  c-basic-offset: 4
  tab-width: 4
  c-indent-comments-syntactically-p: t
  c-tab-always-indent: t
  indent-tabs-mode: nil
  End:
*/

// vim:shiftwidth=4:autoindent:tabstop=4:expandtab:softtabstop=4
