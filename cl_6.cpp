#include "cl_6.h"

cl_6::cl_6(cl_base* p_head_object, string s_object_name): cl_base(p_head_object, s_object_name) {
}

int cl_6::get_class_number() {
    return 6;
}

void cl_6::signal(string & message) {
    cout << endl << "Signal from " << get_absolute_path();
    message += " (class: " + to_string(get_class_number()) + ")";
}

void cl_6::handler(string message) {
    cout << endl << "Signal to " << get_absolute_path() << " Text: " << message;
}
