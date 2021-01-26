#include <errno.h>
#include <mime_streams.hpp>
#include <stdexcept>

namespace epdfcrypt {

base64_mime_stream_filter::base64_mime_stream_filter(bool encoder)
{
    filter_ = g_mime_filter_basic_new(GMIME_CONTENT_ENCODING_BASE64, encoder ? TRUE : FALSE);
}

base64_mime_stream_filter::~base64_mime_stream_filter()
{
    g_object_unref(filter_);
}

} // namespace epdfcrypt
