#include "application.h"

int main() {
    application ob_application(nullptr);
    ob_application.build_tree_objects();
    return (ob_application.exec_app());
}
