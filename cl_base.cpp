#include "cl_base.h"
#include <stack>

cl_base::cl_base(cl_base* parent, string name): parent(parent), name(name) {
    if (parent != nullptr) {
        parent->children.push_back(this);
    }
}

cl_base::~cl_base() {
    cl_base* root_ptr = this;
    while (root_ptr->get_parent() != nullptr) {
        root_ptr = root_ptr->get_parent();
    }
    stack<cl_base*> st;
    st.push(root_ptr);
    while (!st.empty()) {
        cl_base* ptr = st.top();
        st.pop();
        int i = 0;
        while (i < ptr->connects.size()) {
            if (ptr->connects[i]->target_ptr == this) {
                ptr->connects.erase(ptr->connects.begin() + i);
                delete ptr->connects[i];
            } else {
                i++;
            }
        }
        for (i = 0; i < ptr->children.size(); ++i)
            st.push(ptr->children[i]);
    }
    while (!children.empty()) {
        cl_base* tmp_ptr = children[0];
        children.erase(children.begin());
        delete tmp_ptr;
    }
}

string cl_base::get_name() const { return name; }

cl_base* cl_base::get_parent() const { return parent; }

bool cl_base::setName(string name1) {
    if (get_parent() != nullptr && get_parent()->get_child_by_name(name1) != nullptr) {
        return false;
    }
    name = name1;
    return true;
}

cl_base* cl_base::get_child_by_name(string name) {
    for (auto child: children) {
        if (child->name == name) return child;
    }
    return nullptr;
}

cl_base* cl_base::findObjOnBranch(string s_object_name) {
    cl_base* found = nullptr;
    queue <cl_base*> elementsQueue;
    elementsQueue.push(this);
    while(!elementsQueue.empty()) {
        cl_base* elem = elementsQueue.front();
        elementsQueue.pop();
        if (elem->name == s_object_name) {
            if (found != nullptr) {
                return nullptr;
            } else {
                found = elem;
            }
        }
        for (int i = 0; i < elem->children.size(); i++) {
            elementsQueue.push(elem->children[i]);
        }
    }
    return found;
}

cl_base* cl_base::findObjOnTree(string s_object_name) {
    if (parent != nullptr) {
        return parent->findObjOnTree(s_object_name);
    } else {
        return findObjOnBranch(s_object_name);
    }
}

void cl_base::printBranch(int level) {
    cout << endl;
    for (int i = 0; i < level; ++i) {
        cout << " ";
    }
    cout << this->get_name();
    for (int i = 0; i < children.size(); ++i) {
        children[i]->printBranch(level + 1);
    }
}

void cl_base::printBranchWithState(int level) {
    cout << endl;
    for (int i = 0; i < level; ++i) {
        cout << " ";
    }
    if (this->state != 0) {
        cout << this->get_name() << " is ready";
    } else {
        cout << this->get_name() << " is not ready";
    }
    for (int i= 0; i < children.size(); ++i) {
        children[i]->printBranchWithState(level + 1);
    }
}

void cl_base::setState(int state) {
    if (parent == nullptr || parent->state != 0) {
        this->state = state;
    }
    if (state == 0) {
        this->state = state;
        for (int i = 0; i < children.size(); i++) {
            children[i]->setState(state);
        }
    }
}

bool cl_base::set_parent(cl_base* new_parent) {
    if (this->get_parent() == new_parent) {
        return true;
    }
    if (this->get_parent() == nullptr || new_parent == nullptr) {
        return false;
    }
    if (new_parent->get_child_by_name(this->get_name()) != nullptr) {
        return false;
    }
    stack<cl_base*> st;
    st.push(this);
    while (!st.empty()) {
        cl_base* current_node_ptr = st.top();
        st.pop();
        if (current_node_ptr == new_parent) {
            return false;
        }
        for (int i = 0; i < current_node_ptr->children.size(); ++i) {
            st.push(current_node_ptr->children[i]);
        }
    }
    vector<cl_base*> & v = this->get_parent()->children;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i]->get_name() == this->get_name()) {
            v.erase(v.begin() + i);
        }
    }
    new_parent->children.push_back(this);
    return true;
}

void cl_base::remove_child_by_name(string child_name) {
    vector<cl_base*> & v = this->children;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i]->get_name() == child_name) {
            delete v[i];
            v.erase(v.begin() + i);
            return;
        }
    }
}

cl_base* cl_base::get_object_by_path(string path) {
    if (path.empty()) {
        return nullptr;
    }
    if (path == ".") {
        return this;
    }
    if (path[0] == '.') {
        return findObjOnBranch(path.substr(1));
    }
    if (path.substr(0, 2) == "//") {
        return this->findObjOnTree(path.substr(2));
    }
    if (path[0] != '/') {
        size_t slash_index = path.find('/');
        cl_base* child_ptr = this->get_child_by_name(path.substr(0, slash_index));
        if (child_ptr == nullptr || slash_index == string::npos) {
            return child_ptr;
        }
        return child_ptr->get_object_by_path(path.substr(slash_index + 1));
    }
    cl_base* root_ptr = this;
    while (root_ptr->get_parent() != nullptr) {
        root_ptr = root_ptr->get_parent();
    }
    if (path == "/") {
        return root_ptr;
    }
    return root_ptr->get_object_by_path(path.substr(1));
}

void cl_base::set_connect(TYPE_SIGNAL signal_ptr, cl_base* target_ptr, TYPE_HANDLER handler_ptr) {
    for (int i = 0; i < connects.size(); ++i) {
        if (connects[i]->signal_ptr == signal_ptr && connects[i]->target_ptr == target_ptr && connects[i]->handler_ptr == handler_ptr) {
            return;
        }
    }
    connect * new_connect = new connect();
    new_connect->signal_ptr = signal_ptr;
    new_connect->target_ptr = target_ptr;
    new_connect->handler_ptr = handler_ptr;
    connects.push_back(new_connect);
}

void cl_base::remove_connect(TYPE_SIGNAL signal_ptr, cl_base* target_ptr, TYPE_HANDLER handler_ptr) {
    for (int i = 0; i < connects.size(); ++i) {
        if (connects[i]->signal_ptr == signal_ptr && connects[i]->target_ptr == target_ptr && connects[i]->handler_ptr == handler_ptr) {
            delete connects[i];
            connects.erase(connects.begin() + i);
            return;
        }
    }
}

void cl_base::emit_signal(TYPE_SIGNAL signal_ptr, string & command) {
    if (this->state == 0) {
        return;
    }
    (this->*signal_ptr)(command);
    for (int i = 0; i < connects.size(); ++i) {
        if (connects[i]->signal_ptr == signal_ptr) {
            TYPE_HANDLER handler_ptr = connects[i]->handler_ptr;
            cl_base* target_ptr = connects[i]->target_ptr;
            if (target_ptr->state != 0) {
                (target_ptr->*handler_ptr)(command);
            }
        }
    }
}

string cl_base::get_absolute_path() {
    string result;
    stack<string> st;
    cl_base* root_ptr = this;
    while (root_ptr->get_parent() != nullptr) {
        st.push(root_ptr->get_name());
        root_ptr = root_ptr->get_parent();
    }
    while (!st.empty()) {
        result += '/' + st.top();
        st.pop();
    }
    if (result.empty()) {
        return "/";
    }
    return result;
}

int cl_base::get_class_number() {
    return 0;
}

void cl_base::set_state_branch(int new_state) {
    if (get_parent() != nullptr && get_parent()->state == 0) {
        return;
    }
    setState(new_state);
    for (int i = 0; i < children.size(); ++i) {
        children[i]->set_state_branch(new_state);
    }
}
