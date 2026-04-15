#include "cpp_package.hpp"

using namespace rclcpp;

CPP_Template::CPP_Template() {
    
}

#ifndef ENABLE_TESTING

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto cpp_template = std::make_shared<CPP_Template>();
    rclcpp::spin(cpp_template);
    
    rclcpp::shutdown();
    
    return 0;
}
#endif

