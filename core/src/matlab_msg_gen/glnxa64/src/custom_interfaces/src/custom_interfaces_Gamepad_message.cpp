// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/Gamepad
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)
#pragma warning(disable : 4265)
#pragma warning(disable : 4456)
#pragma warning(disable : 4458)
#pragma warning(disable : 4946)
#pragma warning(disable : 4244)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif //_MSC_VER
#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/gamepad.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_Gamepad_common : public MATLABROS2MsgInterface<custom_interfaces::msg::Gamepad> {
  public:
    virtual ~ros2_custom_interfaces_msg_Gamepad_common(){}
    virtual void copy_from_struct(custom_interfaces::msg::Gamepad* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::msg::Gamepad* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_Gamepad_common::copy_from_struct(custom_interfaces::msg::Gamepad* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //x
        const matlab::data::TypedArray<float> x_arr = arr["x"];
        msg->x = x_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a single.");
    }
    try {
        //y
        const matlab::data::TypedArray<float> y_arr = arr["y"];
        msg->y = y_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a single.");
    }
    try {
        //rise
        const matlab::data::TypedArray<float> rise_arr = arr["rise"];
        msg->rise = rise_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'rise' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'rise' is wrong type; expected a single.");
    }
    try {
        //sink
        const matlab::data::TypedArray<float> sink_arr = arr["sink"];
        msg->sink = sink_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'sink' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'sink' is wrong type; expected a single.");
    }
    try {
        //yaw
        const matlab::data::TypedArray<float> yaw_arr = arr["yaw"];
        msg->yaw = yaw_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'yaw' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'yaw' is wrong type; expected a single.");
    }
    try {
        //pitch
        const matlab::data::TypedArray<float> pitch_arr = arr["pitch"];
        msg->pitch = pitch_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pitch' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'pitch' is wrong type; expected a single.");
    }
    try {
        //cross_button
        const matlab::data::TypedArray<bool> cross_button_arr = arr["cross_button"];
        msg->cross_button = cross_button_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'cross_button' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'cross_button' is wrong type; expected a logical.");
    }
    try {
        //square_button
        const matlab::data::TypedArray<bool> square_button_arr = arr["square_button"];
        msg->square_button = square_button_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'square_button' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'square_button' is wrong type; expected a logical.");
    }
    try {
        //triangle_button
        const matlab::data::TypedArray<bool> triangle_button_arr = arr["triangle_button"];
        msg->triangle_button = triangle_button_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'triangle_button' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'triangle_button' is wrong type; expected a logical.");
    }
    try {
        //circle_button
        const matlab::data::TypedArray<bool> circle_button_arr = arr["circle_button"];
        msg->circle_button = circle_button_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'circle_button' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'circle_button' is wrong type; expected a logical.");
    }
    try {
        //dpad_down
        const matlab::data::TypedArray<bool> dpad_down_arr = arr["dpad_down"];
        msg->dpad_down = dpad_down_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'dpad_down' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'dpad_down' is wrong type; expected a logical.");
    }
    try {
        //dpad_left
        const matlab::data::TypedArray<bool> dpad_left_arr = arr["dpad_left"];
        msg->dpad_left = dpad_left_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'dpad_left' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'dpad_left' is wrong type; expected a logical.");
    }
    try {
        //dpad_up
        const matlab::data::TypedArray<bool> dpad_up_arr = arr["dpad_up"];
        msg->dpad_up = dpad_up_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'dpad_up' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'dpad_up' is wrong type; expected a logical.");
    }
    try {
        //dpad_right
        const matlab::data::TypedArray<bool> dpad_right_arr = arr["dpad_right"];
        msg->dpad_right = dpad_right_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'dpad_right' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'dpad_right' is wrong type; expected a logical.");
    }
    try {
        //bumper_left
        const matlab::data::TypedArray<bool> bumper_left_arr = arr["bumper_left"];
        msg->bumper_left = bumper_left_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'bumper_left' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'bumper_left' is wrong type; expected a logical.");
    }
    try {
        //bumper_right
        const matlab::data::TypedArray<bool> bumper_right_arr = arr["bumper_right"];
        msg->bumper_right = bumper_right_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'bumper_right' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'bumper_right' is wrong type; expected a logical.");
    }
    try {
        //start
        const matlab::data::TypedArray<bool> start_arr = arr["start"];
        msg->start = start_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'start' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'start' is wrong type; expected a logical.");
    }
    try {
        //select
        const matlab::data::TypedArray<bool> select_arr = arr["select"];
        msg->select = select_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'select' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'select' is wrong type; expected a logical.");
    }
    try {
        //joystick_press_left
        const matlab::data::TypedArray<bool> joystick_press_left_arr = arr["joystick_press_left"];
        msg->joystick_press_left = joystick_press_left_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'joystick_press_left' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'joystick_press_left' is wrong type; expected a logical.");
    }
    try {
        //joystick_press_right
        const matlab::data::TypedArray<bool> joystick_press_right_arr = arr["joystick_press_right"];
        msg->joystick_press_right = joystick_press_right_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'joystick_press_right' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'joystick_press_right' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_Gamepad_common::get_arr(MDFactory_T& factory, const custom_interfaces::msg::Gamepad* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","x","y","rise","sink","yaw","pitch","cross_button","square_button","triangle_button","circle_button","dpad_down","dpad_left","dpad_up","dpad_right","bumper_left","bumper_right","start","select","joystick_press_left","joystick_press_right"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/Gamepad");
    // x
    auto currentElement_x = (msg + ctr)->x;
    outArray[ctr]["x"] = factory.createScalar(currentElement_x);
    // y
    auto currentElement_y = (msg + ctr)->y;
    outArray[ctr]["y"] = factory.createScalar(currentElement_y);
    // rise
    auto currentElement_rise = (msg + ctr)->rise;
    outArray[ctr]["rise"] = factory.createScalar(currentElement_rise);
    // sink
    auto currentElement_sink = (msg + ctr)->sink;
    outArray[ctr]["sink"] = factory.createScalar(currentElement_sink);
    // yaw
    auto currentElement_yaw = (msg + ctr)->yaw;
    outArray[ctr]["yaw"] = factory.createScalar(currentElement_yaw);
    // pitch
    auto currentElement_pitch = (msg + ctr)->pitch;
    outArray[ctr]["pitch"] = factory.createScalar(currentElement_pitch);
    // cross_button
    auto currentElement_cross_button = (msg + ctr)->cross_button;
    outArray[ctr]["cross_button"] = factory.createScalar(currentElement_cross_button);
    // square_button
    auto currentElement_square_button = (msg + ctr)->square_button;
    outArray[ctr]["square_button"] = factory.createScalar(currentElement_square_button);
    // triangle_button
    auto currentElement_triangle_button = (msg + ctr)->triangle_button;
    outArray[ctr]["triangle_button"] = factory.createScalar(currentElement_triangle_button);
    // circle_button
    auto currentElement_circle_button = (msg + ctr)->circle_button;
    outArray[ctr]["circle_button"] = factory.createScalar(currentElement_circle_button);
    // dpad_down
    auto currentElement_dpad_down = (msg + ctr)->dpad_down;
    outArray[ctr]["dpad_down"] = factory.createScalar(currentElement_dpad_down);
    // dpad_left
    auto currentElement_dpad_left = (msg + ctr)->dpad_left;
    outArray[ctr]["dpad_left"] = factory.createScalar(currentElement_dpad_left);
    // dpad_up
    auto currentElement_dpad_up = (msg + ctr)->dpad_up;
    outArray[ctr]["dpad_up"] = factory.createScalar(currentElement_dpad_up);
    // dpad_right
    auto currentElement_dpad_right = (msg + ctr)->dpad_right;
    outArray[ctr]["dpad_right"] = factory.createScalar(currentElement_dpad_right);
    // bumper_left
    auto currentElement_bumper_left = (msg + ctr)->bumper_left;
    outArray[ctr]["bumper_left"] = factory.createScalar(currentElement_bumper_left);
    // bumper_right
    auto currentElement_bumper_right = (msg + ctr)->bumper_right;
    outArray[ctr]["bumper_right"] = factory.createScalar(currentElement_bumper_right);
    // start
    auto currentElement_start = (msg + ctr)->start;
    outArray[ctr]["start"] = factory.createScalar(currentElement_start);
    // select
    auto currentElement_select = (msg + ctr)->select;
    outArray[ctr]["select"] = factory.createScalar(currentElement_select);
    // joystick_press_left
    auto currentElement_joystick_press_left = (msg + ctr)->joystick_press_left;
    outArray[ctr]["joystick_press_left"] = factory.createScalar(currentElement_joystick_press_left);
    // joystick_press_right
    auto currentElement_joystick_press_right = (msg + ctr)->joystick_press_right;
    outArray[ctr]["joystick_press_right"] = factory.createScalar(currentElement_joystick_press_right);
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_Gamepad_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_Gamepad_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_Gamepad_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<custom_interfaces::msg::Gamepad,ros2_custom_interfaces_msg_Gamepad_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_custom_interfaces_Gamepad_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<custom_interfaces::msg::Gamepad,ros2_custom_interfaces_msg_Gamepad_common>>();
  }
  std::shared_ptr<void> ros2_custom_interfaces_Gamepad_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<custom_interfaces::msg::Gamepad>();
    ros2_custom_interfaces_msg_Gamepad_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_custom_interfaces_Gamepad_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_custom_interfaces_msg_Gamepad_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (custom_interfaces::msg::Gamepad*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_Gamepad_common, MATLABROS2MsgInterface<custom_interfaces::msg::Gamepad>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_Gamepad_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER