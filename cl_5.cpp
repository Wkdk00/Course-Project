#include "cl_5.h"

cl_5::cl_5(cl_base* p_head_object, string s_object_name): cl_base(p_head_object, s_object_name) {
}

int cl_5::get_class_number() {
    return 5;
}

void cl_5::signal(string & message) {
    cout << endl << "Signal from " << get_absolute_path();
    message += " (class: " + to_string(get_class_number()) + ")";
}

void cl_5::handler(string message) {
    cout << endl << "Signal to " << get_absolute_path() << " Text: " << message;
}
