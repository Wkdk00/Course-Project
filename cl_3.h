#ifndef _CL_3_H
#define _CL_3_H
#include "cl_base.h"

class cl_3: public cl_base {
public:
    cl_3(cl_base* p_head_object, string s_object_name);
    int get_class_number();
    void signal(string & message);
    void handler(string message);
};

#endif
