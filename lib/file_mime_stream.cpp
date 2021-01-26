#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <mime_streams.hpp>
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


namespace epdfcrypt {


file_mime_stream::file_mime_stream(const std::string& filename)
    : filename_(filename)
{
    int fd = open(filename.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if(fd == -1)
        throw std::runtime_error(
            std::string("file mime stream creation failed: "
                        "cannot open file: ") + filename
                        + ", reason: " + g_strerror(errno));

    stream_ = g_mime_stream_fs_new(fd);

    // g_mime_stream_fs_set_owner(stream_, TRUE);
}


file_mime_stream::file_mime_stream()
{
    char temporary_filename[] = "/tmp/epdfcryptXXXXXX";
    int fd = mkstemp(temporary_filename);

    if(fd == -1)
        throw std::runtime_error(std::string("failed to open ")
            + temporary_filename + ": " + g_strerror(errno));

    filename_ = temporary_filename;

    stream_ = g_mime_stream_fs_new(fd);
    // g_mime_stream_fs_set_owner(stream_, TRUE);
}


file_mime_stream::~file_mime_stream()
{
    flush();
    g_object_unref(stream_);
}


const std::string& file_mime_stream::filename() const
{
    return filename_;
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
