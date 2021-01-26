#include "init.hpp"
#include <gmime/gmime.h>
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
