#include "cl_3.h"

cl_3::cl_3(cl_base* p_head_object, string s_object_name): cl_base(p_head_object, s_object_name) {
}

int cl_3::get_class_number() {
    return 3;
}

void cl_3::signal(string & message) {
    cout << endl << "Signal from " << get_absolute_path();
    message += " (class: " + to_string(get_class_number()) + ")";
}

void cl_3::handler(string message) {
    cout << endl << "Signal to " << get_absolute_path() << " Text: " << message;
}
