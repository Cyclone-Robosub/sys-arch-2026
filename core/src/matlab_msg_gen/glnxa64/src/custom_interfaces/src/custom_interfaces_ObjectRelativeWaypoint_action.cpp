// Copyright 2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/ObjectRelativeWaypointGoal
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
#include "custom_interfaces/action/object_relative_waypoint.hpp"
#include "visibility_control.h"
#ifndef FOUNDATION_MATLABDATA_API
#include "MDArray.hpp"
#include "StructArray.hpp"
#include "TypedArrayRef.hpp"
#include "Struct.hpp"
#include "ArrayFactory.hpp"
#include "StructRef.hpp"
#include "Reference.hpp"
#endif
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
#include "ROS2ActionTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT custom_interfaces_msg_ObjectRelativeWaypointGoal_common : public MATLABROS2MsgInterface<custom_interfaces::action::ObjectRelativeWaypoint::Goal> {
  public:
    virtual ~custom_interfaces_msg_ObjectRelativeWaypointGoal_common(){}
    virtual void copy_from_struct(custom_interfaces::action::ObjectRelativeWaypoint::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::action::ObjectRelativeWaypoint::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void custom_interfaces_msg_ObjectRelativeWaypointGoal_common::copy_from_struct(custom_interfaces::action::ObjectRelativeWaypoint::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //tracking_position
        const matlab::data::StructArray tracking_position_arr = arr["tracking_position"];
        auto msgClassPtr_tracking_position = getCommonObject<custom_interfaces::msg::Pose6D>("ros2_custom_interfaces_msg_Pose6D_common",loader);
        msgClassPtr_tracking_position->copy_from_struct(&msg->tracking_position,tracking_position_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'tracking_position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'tracking_position' is wrong type; expected a struct.");
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
        //object
        const matlab::data::CharArray object_arr = arr["object"];
        msg->object = object_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'object' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'object' is wrong type; expected a string.");
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
        //timeout
        const matlab::data::TypedArray<double> timeout_arr = arr["timeout"];
        msg->timeout = timeout_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'timeout' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'timeout' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T custom_interfaces_msg_ObjectRelativeWaypointGoal_common::get_arr(MDFactory_T& factory, const custom_interfaces::action::ObjectRelativeWaypoint::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","tracking_position","waypoint_mask","object","tolerance","hold_time","timeout"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/ObjectRelativeWaypointGoal");
    // tracking_position
    auto currentElement_tracking_position = (msg + ctr)->tracking_position;
    auto msgClassPtr_tracking_position = getCommonObject<custom_interfaces::msg::Pose6D>("ros2_custom_interfaces_msg_Pose6D_common",loader);
    outArray[ctr]["tracking_position"] = msgClassPtr_tracking_position->get_arr(factory, &currentElement_tracking_position, loader);
    // waypoint_mask
    auto currentElement_waypoint_mask = (msg + ctr)->waypoint_mask;
    auto msgClassPtr_waypoint_mask = getCommonObject<custom_interfaces::msg::WaypointMask>("ros2_custom_interfaces_msg_WaypointMask_common",loader);
    outArray[ctr]["waypoint_mask"] = msgClassPtr_waypoint_mask->get_arr(factory, &currentElement_waypoint_mask, loader);
    // object
    auto currentElement_object = (msg + ctr)->object;
    outArray[ctr]["object"] = factory.createCharArray(currentElement_object);
    // tolerance
    auto currentElement_tolerance = (msg + ctr)->tolerance;
    auto msgClassPtr_tolerance = getCommonObject<custom_interfaces::msg::Pose6D>("ros2_custom_interfaces_msg_Pose6D_common",loader);
    outArray[ctr]["tolerance"] = msgClassPtr_tolerance->get_arr(factory, &currentElement_tolerance, loader);
    // hold_time
    auto currentElement_hold_time = (msg + ctr)->hold_time;
    outArray[ctr]["hold_time"] = factory.createScalar(currentElement_hold_time);
    // timeout
    auto currentElement_timeout = (msg + ctr)->timeout;
    outArray[ctr]["timeout"] = factory.createScalar(currentElement_timeout);
    }
    return std::move(outArray);
  }

class CUSTOM_INTERFACES_EXPORT custom_interfaces_msg_ObjectRelativeWaypointResult_common : public MATLABROS2MsgInterface<custom_interfaces::action::ObjectRelativeWaypoint::Result> {
  public:
    virtual ~custom_interfaces_msg_ObjectRelativeWaypointResult_common(){}
    virtual void copy_from_struct(custom_interfaces::action::ObjectRelativeWaypoint::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::action::ObjectRelativeWaypoint::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void custom_interfaces_msg_ObjectRelativeWaypointResult_common::copy_from_struct(custom_interfaces::action::ObjectRelativeWaypoint::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //success
        const matlab::data::TypedArray<bool> success_arr = arr["success"];
        msg->success = success_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'success' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'success' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T custom_interfaces_msg_ObjectRelativeWaypointResult_common::get_arr(MDFactory_T& factory, const custom_interfaces::action::ObjectRelativeWaypoint::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","success"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/ObjectRelativeWaypointResult");
    // success
    auto currentElement_success = (msg + ctr)->success;
    outArray[ctr]["success"] = factory.createScalar(currentElement_success);
    }
    return std::move(outArray);
  }

class CUSTOM_INTERFACES_EXPORT custom_interfaces_msg_ObjectRelativeWaypointFeedback_common : public MATLABROS2MsgInterface<custom_interfaces::action::ObjectRelativeWaypoint::Feedback> {
  public:
    virtual ~custom_interfaces_msg_ObjectRelativeWaypointFeedback_common(){}
    virtual void copy_from_struct(custom_interfaces::action::ObjectRelativeWaypoint::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::action::ObjectRelativeWaypoint::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void custom_interfaces_msg_ObjectRelativeWaypointFeedback_common::copy_from_struct(custom_interfaces::action::ObjectRelativeWaypoint::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T custom_interfaces_msg_ObjectRelativeWaypointFeedback_common::get_arr(MDFactory_T& factory, const custom_interfaces::action::ObjectRelativeWaypoint::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/ObjectRelativeWaypointFeedback");
    }
    return std::move(outArray);
  }

class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_ObjectRelativeWaypoint_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_ObjectRelativeWaypoint_action(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABActClientInterface> generateActClientInterface();
    virtual std::shared_ptr<MATLABActServerInterface> generateActServerInterface();
    virtual matlab::data::StructArray generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap);
    virtual std::shared_ptr<void> generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_ObjectRelativeWaypoint_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<custom_interfaces::action::ObjectRelativeWaypoint::Goal,custom_interfaces_msg_ObjectRelativeWaypointGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<custom_interfaces::action::ObjectRelativeWaypoint::Feedback,custom_interfaces_msg_ObjectRelativeWaypointFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<custom_interfaces::action::ObjectRelativeWaypoint::Result,custom_interfaces_msg_ObjectRelativeWaypointResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_custom_interfaces_ObjectRelativeWaypoint_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<custom_interfaces::action::ObjectRelativeWaypoint::Goal,custom_interfaces_msg_ObjectRelativeWaypointGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<custom_interfaces::action::ObjectRelativeWaypoint::Feedback,custom_interfaces_msg_ObjectRelativeWaypointFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<custom_interfaces::action::ObjectRelativeWaypoint::Result,custom_interfaces_msg_ObjectRelativeWaypointResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_custom_interfaces_ObjectRelativeWaypoint_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<custom_interfaces::action::ObjectRelativeWaypoint,custom_interfaces::action::ObjectRelativeWaypoint::Goal,custom_interfaces::action::ObjectRelativeWaypoint::Feedback::ConstSharedPtr,custom_interfaces::action::ObjectRelativeWaypoint::Result::ConstSharedPtr,custom_interfaces_msg_ObjectRelativeWaypointGoal_common,custom_interfaces_msg_ObjectRelativeWaypointFeedback_common,custom_interfaces_msg_ObjectRelativeWaypointResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_custom_interfaces_ObjectRelativeWaypoint_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<custom_interfaces::action::ObjectRelativeWaypoint,custom_interfaces::action::ObjectRelativeWaypoint::Feedback,custom_interfaces::action::ObjectRelativeWaypoint::Result,custom_interfaces::action::ObjectRelativeWaypoint::Goal::ConstSharedPtr,custom_interfaces_msg_ObjectRelativeWaypointGoal_common,custom_interfaces_msg_ObjectRelativeWaypointFeedback_common,custom_interfaces_msg_ObjectRelativeWaypointResult_common>>();
  }
  std::shared_ptr<void> ros2_custom_interfaces_ObjectRelativeWaypoint_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<custom_interfaces::action::ObjectRelativeWaypoint::Goal>();
        custom_interfaces_msg_ObjectRelativeWaypointGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<custom_interfaces::action::ObjectRelativeWaypoint::Feedback>();
        custom_interfaces_msg_ObjectRelativeWaypointFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<custom_interfaces::action::ObjectRelativeWaypoint::Result>();
        custom_interfaces_msg_ObjectRelativeWaypointResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_custom_interfaces_ObjectRelativeWaypoint_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    custom_interfaces_msg_ObjectRelativeWaypointGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (custom_interfaces::action::ObjectRelativeWaypoint::Goal*)msgPtr, loader);
    }else if(type == eResult){
        custom_interfaces_msg_ObjectRelativeWaypointResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (custom_interfaces::action::ObjectRelativeWaypoint::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        custom_interfaces_msg_ObjectRelativeWaypointFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (custom_interfaces::action::ObjectRelativeWaypoint::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(custom_interfaces_msg_ObjectRelativeWaypointGoal_common, MATLABROS2MsgInterface<custom_interfaces::action::ObjectRelativeWaypoint::Goal>)
CLASS_LOADER_REGISTER_CLASS(custom_interfaces_msg_ObjectRelativeWaypointFeedback_common, MATLABROS2MsgInterface<custom_interfaces::action::ObjectRelativeWaypoint::Feedback>)
CLASS_LOADER_REGISTER_CLASS(custom_interfaces_msg_ObjectRelativeWaypointResult_common, MATLABROS2MsgInterface<custom_interfaces::action::ObjectRelativeWaypoint::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_ObjectRelativeWaypoint_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1