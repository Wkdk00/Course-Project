#ifndef __CL_4__H
#define __CL_4__H

#include "cl_base.h"
class cl_4: public cl_base {
public:
    cl_4(cl_base* p_head_object, string s_object_name);
    int get_class_number();
    void signal(string & message);
    void handler(string message);
};

#endif
