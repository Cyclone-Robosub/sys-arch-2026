// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/Config
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
#include "custom_interfaces/msg/config.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_Config_common : public MATLABROS2MsgInterface<custom_interfaces::msg::Config> {
  public:
    virtual ~ros2_custom_interfaces_msg_Config_common(){}
    virtual void copy_from_struct(custom_interfaces::msg::Config* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::msg::Config* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_Config_common::copy_from_struct(custom_interfaces::msg::Config* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //speed_of_sound
        const matlab::data::TypedArray<float> speed_of_sound_arr = arr["speed_of_sound"];
        msg->speed_of_sound = speed_of_sound_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'speed_of_sound' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'speed_of_sound' is wrong type; expected a single.");
    }
    try {
        //mounting_rotation_offset
        const matlab::data::TypedArray<float> mounting_rotation_offset_arr = arr["mounting_rotation_offset"];
        msg->mounting_rotation_offset = mounting_rotation_offset_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'mounting_rotation_offset' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'mounting_rotation_offset' is wrong type; expected a single.");
    }
    try {
        //acoustic_enabled
        const matlab::data::CharArray acoustic_enabled_arr = arr["acoustic_enabled"];
        msg->acoustic_enabled = acoustic_enabled_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'acoustic_enabled' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'acoustic_enabled' is wrong type; expected a string.");
    }
    try {
        //dark_mode_enabled
        const matlab::data::CharArray dark_mode_enabled_arr = arr["dark_mode_enabled"];
        msg->dark_mode_enabled = dark_mode_enabled_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'dark_mode_enabled' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'dark_mode_enabled' is wrong type; expected a string.");
    }
    try {
        //range_mode
        const matlab::data::CharArray range_mode_arr = arr["range_mode"];
        msg->range_mode = range_mode_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'range_mode' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'range_mode' is wrong type; expected a string.");
    }
    try {
        //periodic_cycling_enabled
        const matlab::data::CharArray periodic_cycling_enabled_arr = arr["periodic_cycling_enabled"];
        msg->periodic_cycling_enabled = periodic_cycling_enabled_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'periodic_cycling_enabled' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'periodic_cycling_enabled' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_Config_common::get_arr(MDFactory_T& factory, const custom_interfaces::msg::Config* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","speed_of_sound","mounting_rotation_offset","acoustic_enabled","dark_mode_enabled","range_mode","periodic_cycling_enabled"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/Config");
    // speed_of_sound
    auto currentElement_speed_of_sound = (msg + ctr)->speed_of_sound;
    outArray[ctr]["speed_of_sound"] = factory.createScalar(currentElement_speed_of_sound);
    // mounting_rotation_offset
    auto currentElement_mounting_rotation_offset = (msg + ctr)->mounting_rotation_offset;
    outArray[ctr]["mounting_rotation_offset"] = factory.createScalar(currentElement_mounting_rotation_offset);
    // acoustic_enabled
    auto currentElement_acoustic_enabled = (msg + ctr)->acoustic_enabled;
    outArray[ctr]["acoustic_enabled"] = factory.createCharArray(currentElement_acoustic_enabled);
    // dark_mode_enabled
    auto currentElement_dark_mode_enabled = (msg + ctr)->dark_mode_enabled;
    outArray[ctr]["dark_mode_enabled"] = factory.createCharArray(currentElement_dark_mode_enabled);
    // range_mode
    auto currentElement_range_mode = (msg + ctr)->range_mode;
    outArray[ctr]["range_mode"] = factory.createCharArray(currentElement_range_mode);
    // periodic_cycling_enabled
    auto currentElement_periodic_cycling_enabled = (msg + ctr)->periodic_cycling_enabled;
    outArray[ctr]["periodic_cycling_enabled"] = factory.createCharArray(currentElement_periodic_cycling_enabled);
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_Config_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_Config_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_Config_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<custom_interfaces::msg::Config,ros2_custom_interfaces_msg_Config_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_custom_interfaces_Config_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<custom_interfaces::msg::Config,ros2_custom_interfaces_msg_Config_common>>();
  }
  std::shared_ptr<void> ros2_custom_interfaces_Config_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<custom_interfaces::msg::Config>();
    ros2_custom_interfaces_msg_Config_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_custom_interfaces_Config_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_custom_interfaces_msg_Config_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (custom_interfaces::msg::Config*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_Config_common, MATLABROS2MsgInterface<custom_interfaces::msg::Config>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_Config_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER