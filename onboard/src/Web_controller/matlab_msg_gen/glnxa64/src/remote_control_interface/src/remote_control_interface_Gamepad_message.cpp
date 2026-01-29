// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for remote_control_interface/Gamepad
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
#include "remote_control_interface/msg/gamepad.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class REMOTE_CONTROL_INTERFACE_EXPORT ros2_remote_control_interface_msg_Gamepad_common : public MATLABROS2MsgInterface<remote_control_interface::msg::Gamepad> {
  public:
    virtual ~ros2_remote_control_interface_msg_Gamepad_common(){}
    virtual void copy_from_struct(remote_control_interface::msg::Gamepad* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const remote_control_interface::msg::Gamepad* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_remote_control_interface_msg_Gamepad_common::copy_from_struct(remote_control_interface::msg::Gamepad* msg, const matlab::data::Struct& arr,
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
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_remote_control_interface_msg_Gamepad_common::get_arr(MDFactory_T& factory, const remote_control_interface::msg::Gamepad* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","x","y","rise","sink","yaw","pitch"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("remote_control_interface/Gamepad");
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
    }
    return std::move(outArray);
  } 
class REMOTE_CONTROL_INTERFACE_EXPORT ros2_remote_control_interface_Gamepad_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_remote_control_interface_Gamepad_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_remote_control_interface_Gamepad_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<remote_control_interface::msg::Gamepad,ros2_remote_control_interface_msg_Gamepad_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_remote_control_interface_Gamepad_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<remote_control_interface::msg::Gamepad,ros2_remote_control_interface_msg_Gamepad_common>>();
  }
  std::shared_ptr<void> ros2_remote_control_interface_Gamepad_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<remote_control_interface::msg::Gamepad>();
    ros2_remote_control_interface_msg_Gamepad_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_remote_control_interface_Gamepad_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_remote_control_interface_msg_Gamepad_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (remote_control_interface::msg::Gamepad*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_remote_control_interface_msg_Gamepad_common, MATLABROS2MsgInterface<remote_control_interface::msg::Gamepad>)
CLASS_LOADER_REGISTER_CLASS(ros2_remote_control_interface_Gamepad_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER