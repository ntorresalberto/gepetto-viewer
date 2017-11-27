//
//  macros.h
//  gepetto-viewer
//
//  Created by Justin Carpentier, Mathieu Geisert in  November 2014.
//  Copyright (c) 2014 LAAS-CNRS. All rights reserved.
//

#ifndef SCENEVIEWER_MACROS_HH
#define SCENEVIEWER_MACROS_HH

#if __cplusplus > 199711L
#include <memory>
namespace graphics {
  using std::shared_ptr;
  using std::weak_ptr;
  using std::static_pointer_cast;
  using std::dynamic_pointer_cast;
}
#else
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
namespace graphics {
  using boost::shared_ptr;
  using boost::weak_ptr;
  using boost::static_pointer_cast;
  using boost::dynamic_pointer_cast;
}
#endif

#include <osg/ref_ptr>

/** Define default asserting macro */
#define ASSERT(condition, message) \
do { \
if (! (condition)) { \
std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
<< " line " << __LINE__ << ": " << message << std::endl; \
std::exit(EXIT_FAILURE); \
} \
} while (false)

/** Automatic builder of shared_ptr and weak_ptr for a class defined by its className */
#define DEF_CLASS_SMART_PTR(className) \
class className; \
typedef graphics::shared_ptr<className> className##Ptr_t; \
typedef graphics::shared_ptr<const className> className##ConstPtr_t; \
typedef graphics::weak_ptr<className> className##WeakPtr; \
typedef graphics::weak_ptr<const className> className##ConstWeakPtr; \

#define DEF_OSG_CLASS_REF_PTR(className) \
    /*class className;*/ \
    typedef ::osg::ref_ptr< className > className##RefPtr; \
    typedef ::osg::observer_ptr< className > className##ObserverPtr;

#define SCENE_VIEWER_ACCEPT_VISITOR \
  virtual void accept (NodeVisitor& nv) { if (nv.valid(*this)) { nv.apply (*this); } } \
  struct {} __end_with_semicolon__

#endif // SCENEVIEWER_MACROS_HH

