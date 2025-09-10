#include "application.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include <stack>

TYPE_SIGNAL class_number_to_signal(int class_number) {
    switch (class_number) {
    case 1:
        return SIGNAL_D(application::signal);
    case 2:
        return SIGNAL_D(cl_2::signal);
    case 3:
        return SIGNAL_D(cl_3::signal);
    case 4:
        return SIGNAL_D(cl_4::signal);
    case 5:
        return SIGNAL_D(cl_5::signal);
    case 6:
        return SIGNAL_D(cl_6::signal);
    }
    return nullptr;
}

TYPE_HANDLER class_number_to_handler(int class_number) {
    switch (class_number) {
    case 1:
        return HANDLER_D(application::handler);
    case 2:
        return HANDLER_D(cl_2::handler);
    case 3:
        return HANDLER_D(cl_3::handler);
    case 4:
        return HANDLER_D(cl_4::handler);
    case 5:
        return HANDLER_D(cl_5::handler);
    case 6:
        return HANDLER_D(cl_6::handler);
    }
    return nullptr;
}

application::application(cl_base* parent): cl_base(parent) {}

int application::exec_app() {
    TYPE_SIGNAL signal_f;
    TYPE_HANDLER handler_f;
    this->set_state_branch(1);
    string command, input, message;
    int new_state;
    cl_base* extra_object_ptr;
    cl_base* target_object_ptr;
    this->printBranch();
    cin >> command;
    while (command != "END") {
        cin >> input;
        extra_object_ptr = this->get_object_by_path(input);
        if (extra_object_ptr == nullptr) {
            cout << endl << "Object " << input << " not found";
            cin >> input;
            continue;
        }
        if (command == "EMIT") {
            getline(cin, message);
            int n = extra_object_ptr->get_class_number();
            extra_object_ptr->emit_signal(class_number_to_signal(n), message);
        } else if (command == "SET_CONNECT") {
            cin >> input;
            target_object_ptr = this->get_object_by_path(input);
            if (target_object_ptr == nullptr) {
                cout << endl << "Handler object " << input << " not found";
                continue;
            }
            signal_f = class_number_to_signal(extra_object_ptr->get_class_number());
            handler_f = class_number_to_handler(target_object_ptr->get_class_number());
            extra_object_ptr->set_connect(signal_f, target_object_ptr, handler_f);
        } else if (command == "DELETE_CONNECT") {
            cin >> input;
            target_object_ptr = this->get_object_by_path(input);
            if (target_object_ptr == nullptr) {
                cout << endl << "Handler object " << input << " not found";
                continue;
            }
            signal_f = class_number_to_signal(extra_object_ptr->get_class_number());
            handler_f = class_number_to_handler(target_object_ptr->get_class_number());
            extra_object_ptr->remove_connect(signal_f, target_object_ptr, handler_f);
        } else if (command == "SET_CONDITION") {
            cin >> new_state;
            extra_object_ptr->setState(new_state);
        }
        cin >> command;
    }
    return 0;
}

int application::get_class_number() {
    return 1;
}

void application::signal(string & message) {
    cout << endl << "Signal from " << get_absolute_path();
    message += " (class: " + to_string(get_class_number()) + ")";
}

void application::handler(string message) {
    cout << endl << "Signal to " << get_absolute_path() << " Text: " << message;
}

void application::build_tree_objects() {
    cout << "Object tree";
    string path, child_name;
    int tmp;
    cin >> child_name;
    this->setName(child_name);
    cl_base* parent_node_ptr;
    cl_base* last_created_node_ptr = this;
    cin >> path;
    while (path != "endtree") {
        cin >> child_name >> tmp;
        parent_node_ptr = last_created_node_ptr->get_object_by_path(path);
        if (parent_node_ptr == nullptr) {
            this->printBranch();
            cout << endl << "The head object " << path << " is not found";
            exit(1);
        }
        if (parent_node_ptr->get_child_by_name(child_name) != nullptr)
            cout << endl << path << " Dubbing the names of subordinate objects";
        else {
            switch (tmp) {
            case 1:
                last_created_node_ptr = new application(parent_node_ptr);
                break;
            case 2:
                last_created_node_ptr = new cl_2(parent_node_ptr, child_name);
                break;
            case 3:
                last_created_node_ptr = new cl_3(parent_node_ptr, child_name);
                break;
            case 4:
                last_created_node_ptr = new cl_4(parent_node_ptr, child_name);
                break;
            case 5:
                last_created_node_ptr = new cl_5(parent_node_ptr, child_name);
                break;
            case 6:
                last_created_node_ptr = new cl_6(parent_node_ptr, child_name);
                break;
            }
        }
        cin >> path;
    }
    cl_base* target_ptr;
    string target_path;
    cin >> path;
    while (path != "end_of_connections") {
        cin >> target_path;
        parent_node_ptr = get_object_by_path(path);
        target_ptr = get_object_by_path(target_path);
        TYPE_SIGNAL signal_f = class_number_to_signal(parent_node_ptr->get_class_number());
        TYPE_HANDLER handler_f = class_number_to_handler(target_ptr->get_class_number());
        parent_node_ptr->set_connect(signal_f, target_ptr, handler_f);
        cin >> path;
    }
}
