#ifndef __MIME_STREAMS_HPP_INCLUDED__
#define __MIME_STREAMS_HPP_INCLUDED__

#include <gmime/gmime.h>
#include <safe_epdf_object.hpp>
#include <string>

namespace epdfcrypt {

class mime_stream : private safe_epdf_object {

public:
    enum seek_pos { SET, CUR, END };

public:
    mime_stream();
    virtual ~mime_stream();

public:
    GMimeStream* stream() const;

    bool read(std::string& buffer) const;
    void write(const std::string& buffer);
    void seek(off_t off, seek_pos pos) const;

    void flush();
    void cat(const mime_stream& from);

    std::string content() const;

private:
    mime_stream(const mime_stream&);
    mime_stream& operator=(const mime_stream&);

protected:
    GMimeStream* stream_;
};

class mime_stream_filter : private safe_epdf_object {

public:
    mime_stream_filter();
    virtual ~mime_stream_filter();

public:
    GMimeFilter* filter() const;

private:
    mime_stream_filter(const mime_stream_filter&);
    mime_stream_filter& operator=(const mime_stream_filter&);

protected:
    GMimeFilter* filter_;
};

class memory_mime_stream : public mime_stream {

public:
    memory_mime_stream();
    memory_mime_stream(const std::string& content);
    virtual ~memory_mime_stream();

public:
    std::string content() const;
};

class file_mime_stream : public mime_stream {

public:
    file_mime_stream(const std::string& filename);
    file_mime_stream();
    virtual ~file_mime_stream();

public:
    const std::string& filename() const;

private:
    std::string filename_;
};

class filtered_mime_stream : public mime_stream {

public:
    filtered_mime_stream(mime_stream& from);
    virtual ~filtered_mime_stream();

public:
    void add_filter(mime_stream_filter& filter);
};

class base64_mime_stream_filter : public mime_stream_filter {

public:
    base64_mime_stream_filter(bool encoder = true);
    ~base64_mime_stream_filter();
};

}

#endif // __MIME_STREAMS_HPP_INCLUDED__