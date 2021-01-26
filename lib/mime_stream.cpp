#include <errno.h>
#include <mime_streams.hpp>
#include <stdexcept>

namespace epdfcrypt {

mime_stream::mime_stream() : stream_(NULL)
{
}

mime_stream::~mime_stream()
{
}

GMimeStream* mime_stream::stream() const
{
    return stream_;
}

bool mime_stream::read(std::string& buffer) const
{
    char raw_buffer[8192];

    ssize_t ret = g_mime_stream_read(stream_, raw_buffer, sizeof(raw_buffer));

    if (ret == 0)
        return false;

    if (ret == -1)
        throw std::runtime_error(std::string("read error: ") + g_strerror(errno));

    buffer.assign(raw_buffer, ret);
    return true;
}

void mime_stream::write(const std::string& buffer)
{
    ssize_t total = buffer.length(), written = 0;

    do {
        ssize_t ret = g_mime_stream_write(stream_, buffer.c_str() + written, total - written);

        if (ret == 0)
            return;

        if (ret < 0)
            throw std::runtime_error(std::string("write error: ") + g_strerror(errno));
        written += ret;

    } while (written < total);
}

void mime_stream::seek(off_t off, seek_pos pos) const
{
    GMimeSeekWhence whence;

    switch (pos) {

    case SET:
        whence = GMIME_STREAM_SEEK_SET;
        break;

    case CUR:
        whence = GMIME_STREAM_SEEK_CUR;
        break;

    case END:
    default:
        whence = GMIME_STREAM_SEEK_END;
    }

    if (g_mime_stream_seek(stream_, static_cast<gint64>(off), whence) == -1)
        throw std::runtime_error(std::string("seek error: ") + g_strerror(errno));
}

void mime_stream::flush()
{
    g_mime_stream_flush(stream_);
}

void mime_stream::cat(const mime_stream& from)
{
    if (&from == this)
        return;

    // This doesn't work with filtered streams (random behaviour)
    if (!GMIME_IS_STREAM_FILTER(from.stream()))
        from.seek(0, SET);

    std::string buffer;

    while (from.read(buffer))
        write(buffer);

    flush();
}

std::string mime_stream::content() const
{
    std::string buffer, content;

    // This doesn't work with filtered streams (random behaviour)
    if (!GMIME_IS_STREAM_FILTER(stream_))
        seek(0, SET);

    while (read(buffer))
        content += buffer;

    return content;
}

} // namespace epdfcrypt
