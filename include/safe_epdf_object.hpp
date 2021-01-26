#ifndef __SAFE_EPDF_OBJECT_HPP_INCLUDED__
#define __SAFE_EPDF_OBJECT_HPP_INCLUDED__


namespace epdfcrypt {


// Base class for all classes that call at least one
// GMIME or PoDoFo function
class safe_epdf_object {

public:
    safe_epdf_object();

    // Base class, virtual destructor
    virtual ~safe_epdf_object();
};


}


#endif // __SAFE_EPDF_OBJECT_HPP_INCLUDED__


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
