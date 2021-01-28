#include "charset_detector.hpp"
#include <boost/locale.hpp>
#include <cstring>
#include <epdf.hpp>
#include <fstream>
#include <libgen.h>
#include <memory>
#include <mime_streams.hpp>
#include <sstream>
#include <stdexcept>

namespace epdfcrypt {

epdf::epdf(const std::string& utf8_font_filename, bool embed_utf8_font, float font_size, float margin)
    : font_size_(font_size), margin_(margin), document_(nullptr), font_(nullptr), current_page_(nullptr),
      utf8_font_filename_(utf8_font_filename), embed_utf8_font_(embed_utf8_font)
{
    document_ = HPDF_New(error_handler, nullptr);

    HPDF_SetCompressionMode(document_, HPDF_COMP_ALL);
    HPDF_SetPageMode(document_, HPDF_PAGE_MODE_USE_NONE);

    current_page_ = HPDF_AddPage(document_);
}

epdf::~epdf()
{
    HPDF_Free(document_);
}

void epdf::attach(const std::string& filename)
{
    HPDF_AttachFile(document_, filename.c_str());
}

void epdf::set_password(const std::string& password)
{
    std::string owner_pass = password + "-owner";

    HPDF_SetPassword(document_, owner_pass.c_str(), password.c_str());
    HPDF_SetEncryptionMode(document_, HPDF_ENCRYPT_R3, 16);
}

void epdf::add_text(const std::string& text)
{
    if (text.empty())
        return;

    charset_detector cd;
    std::string      output_text = charset_setup(cd.charset(text), text);

    HPDF_Page_SetFontAndSize(current_page_, font_, font_size_);
    HPDF_Page_BeginText(current_page_);

    HPDF_Page_MoveTextPos(current_page_, margin_, HPDF_Page_GetHeight(current_page_) - margin_ - font_size_);

    std::stringstream ss(text);
    std::string       line;

    while (std::getline(ss, line))
        add_line(line);

    HPDF_Page_EndText(current_page_);
}

std::string epdf::base64()
{
    memory_mime_stream mem_stream;
    write_base64(mem_stream);

    return mem_stream.content();
}

void epdf::write(const std::string& filename, bool base64)
{
    if (!base64) {
        HPDF_SaveToFile(document_, filename.c_str());
        return;
    }

    file_mime_stream base64_stream(filename);
    write_base64(base64_stream);
}

size_t epdf::size()
{
    HPDF_SaveToStream(document_);
    return HPDF_GetStreamSize(document_);
}

void epdf::add_line(const std::string& line)
{
    std::string output_text = line;

    do {

        HPDF_UINT len = 0;

        if (!line.empty()) {

            len = HPDF_Page_MeasureText(current_page_, output_text.c_str(), HPDF_Page_GetWidth(current_page_) - 20,
                                        HPDF_TRUE, nullptr);

            if (!len)
                len = HPDF_Page_MeasureText(current_page_, output_text.c_str(), HPDF_Page_GetWidth(current_page_) - 20,
                                            HPDF_FALSE, nullptr);

            std::string real_line = output_text.substr(0, len);
            HPDF_Page_ShowText(current_page_, real_line.c_str());
        }

        HPDF_Page_MoveTextPos(current_page_, 0, -font_size_);
        HPDF_PageAttr attr = (HPDF_PageAttr)current_page_->attr;

        if (attr->text_pos.y <= margin_) {

            HPDF_Page_EndText(current_page_);
            current_page_ = HPDF_AddPage(document_);

            HPDF_Page_SetFontAndSize(current_page_, font_, font_size_);
            HPDF_Page_BeginText(current_page_);

            HPDF_Page_MoveTextPos(current_page_, margin_, HPDF_Page_GetHeight(current_page_) - margin_ - font_size_);
        }

        output_text = output_text.substr(len);

    } while (!output_text.empty());
}

void epdf::write_base64(mime_stream& output)
{
    HPDF_SaveToStream(document_);
    HPDF_ResetStream(document_);

    memory_mime_stream raw_stream;

    for (;;) {

        HPDF_BYTE   buf[4096];
        HPDF_UINT32 siz = sizeof(buf);
        HPDF_ReadFromStream(document_, buf, &siz);

        if (siz == 0)
            break;

        std::string str_buf(reinterpret_cast<char*>(buf), siz);
        raw_stream.write(str_buf);
    }

    raw_stream.seek(0, mime_stream::SET);

    base64_mime_stream_filter base64_filter;
    filtered_mime_stream      filtered_stream(raw_stream);
    filtered_stream.add_filter(base64_filter);

    output.cat(filtered_stream);
}

void epdf::error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* /* user_data */)
{
    std::stringstream ss;

    ss << "HPDF error [error_no: " << std::showbase << std::hex << error_no << ", detail_no: " << detail_no << "]";

    throw std::runtime_error(ss.str());
}

std::string epdf::charset_setup(const std::string& icu_charset, const std::string& text)
{
    if (icu_charset == "UTF-8") {
        HPDF_UseUTFEncodings(document_);
        const char* font_name = HPDF_LoadTTFontFromFile(document_, utf8_font_filename_.c_str(),
                                                        embed_utf8_font_ ? HPDF_TRUE : HPDF_FALSE);

        font_ = HPDF_GetFont(document_, font_name, "UTF-8");

    } else if (icu_charset == "Shift_JIS") {
        HPDF_UseJPEncodings(document_);
        HPDF_UseJPFonts(document_);
        font_ = HPDF_GetFont(document_, "MS-Mincyo", "90ms-RKSJ-H");

    } else if (icu_charset == "EUC-JP") {
        HPDF_UseJPEncodings(document_);
        HPDF_UseJPFonts(document_);
        font_ = HPDF_GetFont(document_, "MS-Mincyo", "EUC-H");

    } else if (icu_charset == "Big5") {
        HPDF_UseCNTEncodings(document_);
        HPDF_UseCNTFonts(document_);
        font_ = HPDF_GetFont(document_, "MingLiU", "ETen-B5-H");

    } else if (icu_charset == "GB18030") {
        HPDF_UseCNSEncodings(document_);
        HPDF_UseCNSFonts(document_);
        font_ = HPDF_GetFont(document_, "SimSun", "GBK-EUC-H");

    } else if (icu_charset == "EUC-KR") {
        HPDF_UseKREncodings(document_);
        HPDF_UseKRFonts(document_);
        font_ = HPDF_GetFont(document_, "Batang", "KSC-EUC-H");

    } else if (icu_charset == "ISO-8859-1") {
        font_ = HPDF_GetFont(document_, "Courier", HPDF_ENCODING_WIN_ANSI);

    } else if (icu_charset == "ISO-8859-2" || icu_charset == "ISO-8859-5" || icu_charset == "ISO-8859-6"
               || icu_charset == "ISO-8859-7" || icu_charset == "ISO-8859-8" || icu_charset == "ISO-8859-9"
               || icu_charset == "KOI8-R") {

        font_ = HPDF_GetFont(document_, "Courier", icu_charset.c_str());

    } else if (icu_charset == "windows-1250") {
        font_ = HPDF_GetFont(document_, "Courier", HPDF_ENCODING_CP1250);

    } else if (icu_charset == "windows-1251") {
        font_ = HPDF_GetFont(document_, "Courier", HPDF_ENCODING_CP1251);

    } else if (icu_charset == "windows-1252") {
        font_ = HPDF_GetFont(document_, "Courier", HPDF_ENCODING_CP1252);

    } else if (icu_charset == "windows-1253") {
        font_ = HPDF_GetFont(document_, "Courier", HPDF_ENCODING_CP1253);

    } else if (icu_charset == "windows-1254") {
        font_ = HPDF_GetFont(document_, "Courier", HPDF_ENCODING_CP1254);

    } else if (icu_charset == "windows-1255") {
        font_ = HPDF_GetFont(document_, "Courier", HPDF_ENCODING_CP1255);

    } else if (icu_charset == "windows-1256") {
        font_ = HPDF_GetFont(document_, "Courier", HPDF_ENCODING_CP1256);

    } else {
        HPDF_UseUTFEncodings(document_);

        const char* font_name = HPDF_LoadTTFontFromFile(document_, utf8_font_filename_.c_str(),
                                                        embed_utf8_font_ ? HPDF_TRUE : HPDF_FALSE);

        font_ = HPDF_GetFont(document_, font_name, "UTF-8");
        return boost::locale::conv::to_utf<char>(text, icu_charset);
    }

    return text;

    /*
        Unhandled (converted to UTF-8) charsets possibly detected by ICU:

        "ISO-2022-JP" // Japanese
        "ISO-2022-CN" // Chinese
        "ISO-2022-KR" // Korean
        "IBM420"      // Hebrew
        "IBM424"      // Arabic
    */
}

} // namespace epdfcrypt
