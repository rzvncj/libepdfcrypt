#ifndef __EPDF_HPP_INCLUDED__
#define __EPDF_HPP_INCLUDED__

#include <hpdf.h>
#include <safe_epdf_object.hpp>
#include <string>

namespace epdfcrypt {

class mime_stream;

class epdf : private safe_epdf_object {

public:
    epdf(const std::string& utf8_font_filename, bool embed_utf8_font = true, float font_size = 10.0,
         float margin = 10.0);

    ~epdf();

    epdf(const epdf&) = delete;
    epdf& operator=(const epdf&) = delete;

public:
    void        attach(const std::string& filename);
    void        set_password(const std::string& password);
    void        add_text(const std::string& text);
    void        write(const std::string& filename, bool base64 = false);
    std::string base64();
    size_t      size();

private:
    void        write_base64(mime_stream& output);
    std::string charset_setup(const std::string& icu_charset, const std::string& text);
    void        add_line(const std::string& line);
    static void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data);

private:
    float       font_size_;
    float       margin_;
    HPDF_Doc    document_;
    HPDF_Font   font_;
    HPDF_Page   current_page_;
    std::string utf8_font_filename_;
    bool        embed_utf8_font_;
};

}

#endif // __EPDF_HPP_INCLUDED__
