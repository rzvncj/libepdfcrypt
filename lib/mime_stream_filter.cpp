#include <errno.h>
#include <mime_streams.hpp>
#include <stdexcept>

namespace epdfcrypt {

GMimeFilter* mime_stream_filter::filter() const
{
    return filter_;
}

} // namespace epdfcrypt
