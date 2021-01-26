#include "init.hpp"
#include <safe_epdf_object.hpp>

namespace epdfcrypt {

safe_epdf_object::safe_epdf_object()
{
    static sys_initializer init;
}

} // namespace egpgcrypt
