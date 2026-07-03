// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/Goal
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
#include "custom_interfaces/msg/goal.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_Goal_common : public MATLABROS2MsgInterface<custom_interfaces::msg::Goal> {
  public:
    virtual ~ros2_custom_interfaces_msg_Goal_common(){}
    virtual void copy_from_struct(custom_interfaces::msg::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::msg::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_Goal_common::copy_from_struct(custom_interfaces::msg::Goal* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //command_id
        const matlab::data::CharArray command_id_arr = arr["command_id"];
        const std::string command_id_str = command_id_arr.toAscii();
        size_t nelem = 16;
        	std::copy(command_id_arr.begin(), command_id_arr.begin()+nelem, msg->command_id.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'command_id' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'command_id' is wrong type; expected a char.");
    }
    try {
        //waypoint
        const matlab::data::StructArray waypoint_arr = arr["waypoint"];
        auto msgClassPtr_waypoint = getCommonObject<custom_interfaces::msg::Pose6D>("ros2_custom_interfaces_msg_Pose6D_common",loader);
        msgClassPtr_waypoint->copy_from_struct(&msg->waypoint,waypoint_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'waypoint' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'waypoint' is wrong type; expected a struct.");
    }
    try {
        //waypoint_mask
        const matlab::data::StructArray waypoint_mask_arr = arr["waypoint_mask"];
        auto msgClassPtr_waypoint_mask = getCommonObject<custom_interfaces::msg::WaypointMask>("ros2_custom_interfaces_msg_WaypointMask_common",loader);
        msgClassPtr_waypoint_mask->copy_from_struct(&msg->waypoint_mask,waypoint_mask_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'waypoint_mask' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'waypoint_mask' is wrong type; expected a struct.");
    }
    try {
        //tolerance
        const matlab::data::StructArray tolerance_arr = arr["tolerance"];
        auto msgClassPtr_tolerance = getCommonObject<custom_interfaces::msg::Pose6D>("ros2_custom_interfaces_msg_Pose6D_common",loader);
        msgClassPtr_tolerance->copy_from_struct(&msg->tolerance,tolerance_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'tolerance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'tolerance' is wrong type; expected a struct.");
    }
    try {
        //hold_time
        const matlab::data::TypedArray<double> hold_time_arr = arr["hold_time"];
        msg->hold_time = hold_time_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'hold_time' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'hold_time' is wrong type; expected a double.");
    }
    try {
        //object
        const matlab::data::CharArray object_arr = arr["object"];
        const std::string object_str = object_arr.toAscii();
        size_t nelem = 16;
        	std::copy(object_arr.begin(), object_arr.begin()+nelem, msg->object.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'object' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'object' is wrong type; expected a char.");
    }
    try {
        //confidence
        const matlab::data::TypedArray<double> confidence_arr = arr["confidence"];
        msg->confidence = confidence_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'confidence' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'confidence' is wrong type; expected a double.");
    }
    try {
        //trick
        const matlab::data::CharArray trick_arr = arr["trick"];
        const std::string trick_str = trick_arr.toAscii();
        size_t nelem = 16;
        	std::copy(trick_arr.begin(), trick_arr.begin()+nelem, msg->trick.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'trick' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'trick' is wrong type; expected a char.");
    }
    try {
        //duration
        const matlab::data::TypedArray<double> duration_arr = arr["duration"];
        msg->duration = duration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'duration' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'duration' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_Goal_common::get_arr(MDFactory_T& factory, const custom_interfaces::msg::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","command_id","waypoint","waypoint_mask","tolerance","hold_time","object","confidence","trick","duration"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/Goal");
    // command_id
    auto currentElement_command_id = (msg + ctr)->command_id;
    outArray[ctr]["command_id"] = factory.createCharArray(std::string(currentElement_command_id.begin(),currentElement_command_id.end()));
    // waypoint
    auto currentElement_waypoint = (msg + ctr)->waypoint;
    auto msgClassPtr_waypoint = getCommonObject<custom_interfaces::msg::Pose6D>("ros2_custom_interfaces_msg_Pose6D_common",loader);
    outArray[ctr]["waypoint"] = msgClassPtr_waypoint->get_arr(factory, &currentElement_waypoint, loader);
    // waypoint_mask
    auto currentElement_waypoint_mask = (msg + ctr)->waypoint_mask;
    auto msgClassPtr_waypoint_mask = getCommonObject<custom_interfaces::msg::WaypointMask>("ros2_custom_interfaces_msg_WaypointMask_common",loader);
    outArray[ctr]["waypoint_mask"] = msgClassPtr_waypoint_mask->get_arr(factory, &currentElement_waypoint_mask, loader);
    // tolerance
    auto currentElement_tolerance = (msg + ctr)->tolerance;
    auto msgClassPtr_tolerance = getCommonObject<custom_interfaces::msg::Pose6D>("ros2_custom_interfaces_msg_Pose6D_common",loader);
    outArray[ctr]["tolerance"] = msgClassPtr_tolerance->get_arr(factory, &currentElement_tolerance, loader);
    // hold_time
    auto currentElement_hold_time = (msg + ctr)->hold_time;
    outArray[ctr]["hold_time"] = factory.createScalar(currentElement_hold_time);
    // object
    auto currentElement_object = (msg + ctr)->object;
    outArray[ctr]["object"] = factory.createCharArray(std::string(currentElement_object.begin(),currentElement_object.end()));
    // confidence
    auto currentElement_confidence = (msg + ctr)->confidence;
    outArray[ctr]["confidence"] = factory.createScalar(currentElement_confidence);
    // trick
    auto currentElement_trick = (msg + ctr)->trick;
    outArray[ctr]["trick"] = factory.createCharArray(std::string(currentElement_trick.begin(),currentElement_trick.end()));
    // duration
    auto currentElement_duration = (msg + ctr)->duration;
    outArray[ctr]["duration"] = factory.createScalar(currentElement_duration);
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_Goal_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_Goal_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_Goal_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<custom_interfaces::msg::Goal,ros2_custom_interfaces_msg_Goal_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_custom_interfaces_Goal_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<custom_interfaces::msg::Goal,ros2_custom_interfaces_msg_Goal_common>>();
  }
  std::shared_ptr<void> ros2_custom_interfaces_Goal_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<custom_interfaces::msg::Goal>();
    ros2_custom_interfaces_msg_Goal_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_custom_interfaces_Goal_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_custom_interfaces_msg_Goal_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (custom_interfaces::msg::Goal*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_Goal_common, MATLABROS2MsgInterface<custom_interfaces::msg::Goal>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_Goal_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER