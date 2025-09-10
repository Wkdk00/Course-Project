#include "cl_4.h"

cl_4::cl_4(cl_base* p_head_object, string s_object_name): cl_base(p_head_object, s_object_name) {
}

int cl_4::get_class_number() {
    return 4;
}

void cl_4::signal(string & message) {
    cout << endl << "Signal from " << get_absolute_path();
    message += " (class: " + to_string(get_class_number()) + ")";
}

void cl_4::handler(string message) {
    cout << endl << "Signal to " << get_absolute_path() << " Text: " << message;
}
