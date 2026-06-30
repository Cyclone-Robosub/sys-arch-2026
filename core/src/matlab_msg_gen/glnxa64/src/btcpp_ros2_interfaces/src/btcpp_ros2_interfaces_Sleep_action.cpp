// Copyright 2022 The MathWorks, Inc.
// Common copy functions for btcpp_ros2_interfaces/SleepGoal
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
#include "btcpp_ros2_interfaces/action/sleep.hpp"
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
class BTCPP_ROS2_INTERFACES_EXPORT btcpp_ros2_interfaces_msg_SleepGoal_common : public MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::Sleep::Goal> {
  public:
    virtual ~btcpp_ros2_interfaces_msg_SleepGoal_common(){}
    virtual void copy_from_struct(btcpp_ros2_interfaces::action::Sleep::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::Sleep::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void btcpp_ros2_interfaces_msg_SleepGoal_common::copy_from_struct(btcpp_ros2_interfaces::action::Sleep::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //msec_timeout
        const matlab::data::TypedArray<int32_t> msec_timeout_arr = arr["msec_timeout"];
        msg->msec_timeout = msec_timeout_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'msec_timeout' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'msec_timeout' is wrong type; expected a int32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T btcpp_ros2_interfaces_msg_SleepGoal_common::get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::Sleep::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","msec_timeout"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("btcpp_ros2_interfaces/SleepGoal");
    // msec_timeout
    auto currentElement_msec_timeout = (msg + ctr)->msec_timeout;
    outArray[ctr]["msec_timeout"] = factory.createScalar(currentElement_msec_timeout);
    }
    return std::move(outArray);
  }

class BTCPP_ROS2_INTERFACES_EXPORT btcpp_ros2_interfaces_msg_SleepResult_common : public MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::Sleep::Result> {
  public:
    virtual ~btcpp_ros2_interfaces_msg_SleepResult_common(){}
    virtual void copy_from_struct(btcpp_ros2_interfaces::action::Sleep::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::Sleep::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void btcpp_ros2_interfaces_msg_SleepResult_common::copy_from_struct(btcpp_ros2_interfaces::action::Sleep::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //done
        const matlab::data::TypedArray<bool> done_arr = arr["done"];
        msg->done = done_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'done' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'done' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T btcpp_ros2_interfaces_msg_SleepResult_common::get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::Sleep::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","done"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("btcpp_ros2_interfaces/SleepResult");
    // done
    auto currentElement_done = (msg + ctr)->done;
    outArray[ctr]["done"] = factory.createScalar(currentElement_done);
    }
    return std::move(outArray);
  }

class BTCPP_ROS2_INTERFACES_EXPORT btcpp_ros2_interfaces_msg_SleepFeedback_common : public MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::Sleep::Feedback> {
  public:
    virtual ~btcpp_ros2_interfaces_msg_SleepFeedback_common(){}
    virtual void copy_from_struct(btcpp_ros2_interfaces::action::Sleep::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::Sleep::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void btcpp_ros2_interfaces_msg_SleepFeedback_common::copy_from_struct(btcpp_ros2_interfaces::action::Sleep::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //cycle
        const matlab::data::TypedArray<int32_t> cycle_arr = arr["cycle"];
        msg->cycle = cycle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'cycle' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'cycle' is wrong type; expected a int32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T btcpp_ros2_interfaces_msg_SleepFeedback_common::get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::Sleep::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","cycle"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("btcpp_ros2_interfaces/SleepFeedback");
    // cycle
    auto currentElement_cycle = (msg + ctr)->cycle;
    outArray[ctr]["cycle"] = factory.createScalar(currentElement_cycle);
    }
    return std::move(outArray);
  }

class BTCPP_ROS2_INTERFACES_EXPORT ros2_btcpp_ros2_interfaces_Sleep_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_btcpp_ros2_interfaces_Sleep_action(){}
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
          ros2_btcpp_ros2_interfaces_Sleep_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<btcpp_ros2_interfaces::action::Sleep::Goal,btcpp_ros2_interfaces_msg_SleepGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<btcpp_ros2_interfaces::action::Sleep::Feedback,btcpp_ros2_interfaces_msg_SleepFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<btcpp_ros2_interfaces::action::Sleep::Result,btcpp_ros2_interfaces_msg_SleepResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_btcpp_ros2_interfaces_Sleep_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<btcpp_ros2_interfaces::action::Sleep::Goal,btcpp_ros2_interfaces_msg_SleepGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<btcpp_ros2_interfaces::action::Sleep::Feedback,btcpp_ros2_interfaces_msg_SleepFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<btcpp_ros2_interfaces::action::Sleep::Result,btcpp_ros2_interfaces_msg_SleepResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_btcpp_ros2_interfaces_Sleep_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<btcpp_ros2_interfaces::action::Sleep,btcpp_ros2_interfaces::action::Sleep::Goal,btcpp_ros2_interfaces::action::Sleep::Feedback::ConstSharedPtr,btcpp_ros2_interfaces::action::Sleep::Result::ConstSharedPtr,btcpp_ros2_interfaces_msg_SleepGoal_common,btcpp_ros2_interfaces_msg_SleepFeedback_common,btcpp_ros2_interfaces_msg_SleepResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_btcpp_ros2_interfaces_Sleep_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<btcpp_ros2_interfaces::action::Sleep,btcpp_ros2_interfaces::action::Sleep::Feedback,btcpp_ros2_interfaces::action::Sleep::Result,btcpp_ros2_interfaces::action::Sleep::Goal::ConstSharedPtr,btcpp_ros2_interfaces_msg_SleepGoal_common,btcpp_ros2_interfaces_msg_SleepFeedback_common,btcpp_ros2_interfaces_msg_SleepResult_common>>();
  }
  std::shared_ptr<void> ros2_btcpp_ros2_interfaces_Sleep_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<btcpp_ros2_interfaces::action::Sleep::Goal>();
        btcpp_ros2_interfaces_msg_SleepGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<btcpp_ros2_interfaces::action::Sleep::Feedback>();
        btcpp_ros2_interfaces_msg_SleepFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<btcpp_ros2_interfaces::action::Sleep::Result>();
        btcpp_ros2_interfaces_msg_SleepResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_btcpp_ros2_interfaces_Sleep_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    btcpp_ros2_interfaces_msg_SleepGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (btcpp_ros2_interfaces::action::Sleep::Goal*)msgPtr, loader);
    }else if(type == eResult){
        btcpp_ros2_interfaces_msg_SleepResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (btcpp_ros2_interfaces::action::Sleep::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        btcpp_ros2_interfaces_msg_SleepFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (btcpp_ros2_interfaces::action::Sleep::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(btcpp_ros2_interfaces_msg_SleepGoal_common, MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::Sleep::Goal>)
CLASS_LOADER_REGISTER_CLASS(btcpp_ros2_interfaces_msg_SleepFeedback_common, MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::Sleep::Feedback>)
CLASS_LOADER_REGISTER_CLASS(btcpp_ros2_interfaces_msg_SleepResult_common, MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::Sleep::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_btcpp_ros2_interfaces_Sleep_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1