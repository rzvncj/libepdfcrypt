#ifndef __CHARSET_DETECTOR_HPP_INCLUDED__
#define __CHARSET_DETECTOR_HPP_INCLUDED__


#include <string>
#include <unicode/ucsdet.h>


namespace epdfcrypt {


class charset_detector {

public:
    charset_detector();
    ~charset_detector();

public:
    std::string charset(const std::string& text);

private:
    charset_detector(const charset_detector&);
    charset_detector& operator=(const charset_detector&);

private:
    UCharsetDetector *detector_;
};


}


#endif // __CHARSET_DETECTOR_HPP_INCLUDED__



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
