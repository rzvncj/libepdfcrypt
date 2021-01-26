#include <mime_streams.hpp>

namespace epdfcrypt {

filtered_mime_stream::filtered_mime_stream(mime_stream& from)
{
    stream_ = g_mime_stream_filter_new(from.stream());
}

filtered_mime_stream::~filtered_mime_stream()
{
    g_object_unref(stream_);
}

void filtered_mime_stream::add_filter(mime_stream_filter& filter)
{
    g_mime_stream_filter_add(reinterpret_cast<GMimeStreamFilter*>(stream_), filter.filter());
}

} // namespace epdfcrypt
