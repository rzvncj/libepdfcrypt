#ifndef __SAFE_EPDF_OBJECT_HPP_INCLUDED__
#define __SAFE_EPDF_OBJECT_HPP_INCLUDED__

namespace epdfcrypt {

// Base class for all classes that call at least one GMIME or haru function.
class safe_epdf_object {

public:
    safe_epdf_object();

    // Base class, virtual destructor
    virtual ~safe_epdf_object() = default;
};

}

#endif // __SAFE_EPDF_OBJECT_HPP_INCLUDED__
