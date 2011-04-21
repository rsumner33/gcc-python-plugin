#include <Python.h>
#include "gcc-python.h"

/*
  "location_t" is the type used throughout.  Might be nice to expose this directly.

  input.h has: 
    typedef source_location location_t;

  line-map.h has:
      A logical line/column number, i.e. an "index" into a line_map:
          typedef unsigned int source_location;

*/


PyObject *
decl_source_file(tree t)
{
  //printf("DECL_SOURCE_FILE: %s\n", DECL_SOURCE_FILE(t));
    return PyString_FromString(DECL_SOURCE_FILE(t));
}

PyObject *
decl_source_line(tree t)
{
  //printf("DECL_SOURCE_FILE: %s\n", DECL_SOURCE_FILE(t));
    return PyInt_FromLong(DECL_SOURCE_LINE(t));
}

PyObject *
gcc_python_make_wrapper_location(location_t loc)
{
    struct PyGccLocation *location_obj = NULL;
  
    location_obj = PyObject_New(struct PyGccLocation, &gcc_Location);
    if (!location_obj) {
        goto error;
    }

    location_obj->loc = loc;
    /* FIXME: do we need to do something for the GCC GC? */

    //printf("DECL_SOURCE_FILE: %s\n", DECL_SOURCE_FILE(t));
    //printf("DECL_SOURCE_LINE: %i\n", DECL_SOURCE_LINE(t));

    return (PyObject*)location_obj;
      
error:
    return NULL;
}

PyObject *
gcc_python_make_wrapper_tree(tree t)
{
    struct PyGccTree *tree_obj = NULL;
    PyTypeObject* tp;
  
    tp = gcc_python_autogenerated_tree_type_for_tree(t);
    assert(tp);
    printf("tp:%p\n", tp);
    
    tree_obj = PyObject_New(struct PyGccTree, tp);
    if (!tree_obj) {
        goto error;
    }

    tree_obj->t = t;
    /* FIXME: do we need to do something for the GCC GC? */

    printf("DECL_SOURCE_FILE: %s\n", DECL_SOURCE_FILE(t));
    printf("DECL_SOURCE_LINE: %i\n", DECL_SOURCE_LINE(t));

    return (PyObject*)tree_obj;
      
error:
    return NULL;
}
