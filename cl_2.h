#ifndef __CL_2__H
#define __CL_2__H

#include "cl_base.h"
class cl_2: public cl_base {
public:
    cl_2(cl_base* p_head_object, string s_object_name);
    int get_class_number();
    void signal(string & message);
    void handler(string message);
};

#endif
