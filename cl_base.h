#ifndef __CL_BASE_H
#define __CL_BASE_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)

using namespace std;

class cl_base;
typedef void(cl_base::*TYPE_SIGNAL)(string &);
typedef void(cl_base::*TYPE_HANDLER)(string);

class cl_base {
    struct connect {
        TYPE_SIGNAL signal_ptr;
        cl_base* target_ptr;
        TYPE_HANDLER handler_ptr;
    };
private:
    int state = 0;
    cl_base* parent;
    vector <cl_base*> children;
    string name;
    vector<connect*> connects;
public:
    cl_base(cl_base* parent, string name = "Object_root");
    ~cl_base();
    bool setName(string name);
    string get_name() const;
    cl_base* get_parent() const;
    cl_base* get_child_by_name(string name);
    cl_base* findObjOnBranch(string name);
    cl_base* findObjOnTree(string name);
    void printBranch(int level = 0);
    void printBranchWithState(int level = 0);
    void setState(int state);
    bool set_parent(cl_base* new_parent);
    void remove_child_by_name(string child_name);
    cl_base* get_object_by_path(string path);
    void set_connect(TYPE_SIGNAL signal_ptr, cl_base* target_ptr, TYPE_HANDLER handler_ptr);
    void remove_connect(TYPE_SIGNAL signal_ptr, cl_base* target_ptr, TYPE_HANDLER handler_ptr);
    void emit_signal(TYPE_SIGNAL signal_ptr, string & command);
    string get_absolute_path();
    virtual int get_class_number();
    void set_state_branch(int new_state);
};

#endif
