#include <errno.h>
#include <mime_streams.hpp>
#include <stdexcept>

namespace epdfcrypt {

mime_stream_filter::mime_stream_filter() : filter_(NULL)
{
}

mime_stream_filter::~mime_stream_filter()
{
}

GMimeFilter* mime_stream_filter::filter() const
{
    return filter_;
}

} // namespace epdfcrypt
