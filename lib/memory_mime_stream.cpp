#include <mime_streams.hpp>

namespace epdfcrypt {

memory_mime_stream::memory_mime_stream()
{
    stream_ = g_mime_stream_mem_new();
}

memory_mime_stream::memory_mime_stream(const std::string& content)
{
    size_t len = content.length();
    stream_    = g_mime_stream_mem_new_with_buffer(content.c_str(), len);
}

memory_mime_stream::~memory_mime_stream()
{
    flush();
    g_object_unref(stream_);
}

std::string memory_mime_stream::content() const
{
    std::string ret;
    char        buffer[8192];

    g_mime_stream_seek(stream_, 0, GMIME_STREAM_SEEK_SET);
    size_t len = 0;

    do {
        len = g_mime_stream_read(stream_, buffer, sizeof(buffer));

        if (len <= 0)
            break;

        ret.append(buffer, len);

    } while (len > 0);

    return ret;
}

} // namespace epdfcrypt
