#include "cl_2.h"

cl_2::cl_2(cl_base* p_head_object, string s_object_name): cl_base(p_head_object, s_object_name) {
}

int cl_2::get_class_number() {
    return 2;
}

void cl_2::signal(string & message) {
    cout << endl << "Signal from " << get_absolute_path();
    message += " (class: " + to_string(get_class_number()) + ")";
}

void cl_2::handler(string message) {
    cout << endl << "Signal to " << get_absolute_path() << " Text: " << message;
}
