#include <errno.h>
#include <mime_streams.hpp>
#include <stdexcept>


namespace epdfcrypt {


mime_stream_filter::mime_stream_filter()
    : filter_(NULL)
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
