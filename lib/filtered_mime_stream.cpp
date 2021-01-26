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
    g_mime_stream_filter_add(
        reinterpret_cast<GMimeStreamFilter *>(stream_),
        filter.filter());
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
