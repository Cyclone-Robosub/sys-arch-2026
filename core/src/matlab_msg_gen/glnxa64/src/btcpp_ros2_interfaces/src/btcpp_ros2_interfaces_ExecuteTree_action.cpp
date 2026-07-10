// Copyright 2022 The MathWorks, Inc.
// Common copy functions for btcpp_ros2_interfaces/ExecuteTreeGoal
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
#include "btcpp_ros2_interfaces/action/execute_tree.hpp"
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
class BTCPP_ROS2_INTERFACES_EXPORT btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common : public MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::ExecuteTree::Goal> {
  public:
    virtual ~btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common(){}
    virtual void copy_from_struct(btcpp_ros2_interfaces::action::ExecuteTree::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::ExecuteTree::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common::copy_from_struct(btcpp_ros2_interfaces::action::ExecuteTree::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //target_tree
        const matlab::data::CharArray target_tree_arr = arr["target_tree"];
        msg->target_tree = target_tree_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'target_tree' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'target_tree' is wrong type; expected a string.");
    }
    try {
        //payload
        const matlab::data::CharArray payload_arr = arr["payload"];
        msg->payload = payload_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'payload' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'payload' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common::get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::ExecuteTree::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","target_tree","payload"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("btcpp_ros2_interfaces/ExecuteTreeGoal");
    // target_tree
    auto currentElement_target_tree = (msg + ctr)->target_tree;
    outArray[ctr]["target_tree"] = factory.createCharArray(currentElement_target_tree);
    // payload
    auto currentElement_payload = (msg + ctr)->payload;
    outArray[ctr]["payload"] = factory.createCharArray(currentElement_payload);
    }
    return std::move(outArray);
  }

class BTCPP_ROS2_INTERFACES_EXPORT btcpp_ros2_interfaces_msg_ExecuteTreeResult_common : public MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::ExecuteTree::Result> {
  public:
    virtual ~btcpp_ros2_interfaces_msg_ExecuteTreeResult_common(){}
    virtual void copy_from_struct(btcpp_ros2_interfaces::action::ExecuteTree::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::ExecuteTree::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void btcpp_ros2_interfaces_msg_ExecuteTreeResult_common::copy_from_struct(btcpp_ros2_interfaces::action::ExecuteTree::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //node_status
        const matlab::data::StructArray node_status_arr = arr["node_status"];
        auto msgClassPtr_node_status = getCommonObject<btcpp_ros2_interfaces::msg::NodeStatus>("ros2_btcpp_ros2_interfaces_msg_NodeStatus_common",loader);
        msgClassPtr_node_status->copy_from_struct(&msg->node_status,node_status_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'node_status' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'node_status' is wrong type; expected a struct.");
    }
    try {
        //return_message
        const matlab::data::CharArray return_message_arr = arr["return_message"];
        msg->return_message = return_message_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'return_message' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'return_message' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T btcpp_ros2_interfaces_msg_ExecuteTreeResult_common::get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::ExecuteTree::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","node_status","return_message"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("btcpp_ros2_interfaces/ExecuteTreeResult");
    // node_status
    auto currentElement_node_status = (msg + ctr)->node_status;
    auto msgClassPtr_node_status = getCommonObject<btcpp_ros2_interfaces::msg::NodeStatus>("ros2_btcpp_ros2_interfaces_msg_NodeStatus_common",loader);
    outArray[ctr]["node_status"] = msgClassPtr_node_status->get_arr(factory, &currentElement_node_status, loader);
    // return_message
    auto currentElement_return_message = (msg + ctr)->return_message;
    outArray[ctr]["return_message"] = factory.createCharArray(currentElement_return_message);
    }
    return std::move(outArray);
  }

class BTCPP_ROS2_INTERFACES_EXPORT btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common : public MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::ExecuteTree::Feedback> {
  public:
    virtual ~btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common(){}
    virtual void copy_from_struct(btcpp_ros2_interfaces::action::ExecuteTree::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::ExecuteTree::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common::copy_from_struct(btcpp_ros2_interfaces::action::ExecuteTree::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //message
        const matlab::data::CharArray message_arr = arr["message"];
        msg->message = message_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'message' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'message' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common::get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::action::ExecuteTree::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","message"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("btcpp_ros2_interfaces/ExecuteTreeFeedback");
    // message
    auto currentElement_message = (msg + ctr)->message;
    outArray[ctr]["message"] = factory.createCharArray(currentElement_message);
    }
    return std::move(outArray);
  }

class BTCPP_ROS2_INTERFACES_EXPORT ros2_btcpp_ros2_interfaces_ExecuteTree_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_btcpp_ros2_interfaces_ExecuteTree_action(){}
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
          ros2_btcpp_ros2_interfaces_ExecuteTree_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<btcpp_ros2_interfaces::action::ExecuteTree::Goal,btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<btcpp_ros2_interfaces::action::ExecuteTree::Feedback,btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<btcpp_ros2_interfaces::action::ExecuteTree::Result,btcpp_ros2_interfaces_msg_ExecuteTreeResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_btcpp_ros2_interfaces_ExecuteTree_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<btcpp_ros2_interfaces::action::ExecuteTree::Goal,btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<btcpp_ros2_interfaces::action::ExecuteTree::Feedback,btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<btcpp_ros2_interfaces::action::ExecuteTree::Result,btcpp_ros2_interfaces_msg_ExecuteTreeResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_btcpp_ros2_interfaces_ExecuteTree_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<btcpp_ros2_interfaces::action::ExecuteTree,btcpp_ros2_interfaces::action::ExecuteTree::Goal,btcpp_ros2_interfaces::action::ExecuteTree::Feedback::ConstSharedPtr,btcpp_ros2_interfaces::action::ExecuteTree::Result::ConstSharedPtr,btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common,btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common,btcpp_ros2_interfaces_msg_ExecuteTreeResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_btcpp_ros2_interfaces_ExecuteTree_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<btcpp_ros2_interfaces::action::ExecuteTree,btcpp_ros2_interfaces::action::ExecuteTree::Feedback,btcpp_ros2_interfaces::action::ExecuteTree::Result,btcpp_ros2_interfaces::action::ExecuteTree::Goal::ConstSharedPtr,btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common,btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common,btcpp_ros2_interfaces_msg_ExecuteTreeResult_common>>();
  }
  std::shared_ptr<void> ros2_btcpp_ros2_interfaces_ExecuteTree_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<btcpp_ros2_interfaces::action::ExecuteTree::Goal>();
        btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<btcpp_ros2_interfaces::action::ExecuteTree::Feedback>();
        btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<btcpp_ros2_interfaces::action::ExecuteTree::Result>();
        btcpp_ros2_interfaces_msg_ExecuteTreeResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_btcpp_ros2_interfaces_ExecuteTree_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (btcpp_ros2_interfaces::action::ExecuteTree::Goal*)msgPtr, loader);
    }else if(type == eResult){
        btcpp_ros2_interfaces_msg_ExecuteTreeResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (btcpp_ros2_interfaces::action::ExecuteTree::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (btcpp_ros2_interfaces::action::ExecuteTree::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(btcpp_ros2_interfaces_msg_ExecuteTreeGoal_common, MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::ExecuteTree::Goal>)
CLASS_LOADER_REGISTER_CLASS(btcpp_ros2_interfaces_msg_ExecuteTreeFeedback_common, MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::ExecuteTree::Feedback>)
CLASS_LOADER_REGISTER_CLASS(btcpp_ros2_interfaces_msg_ExecuteTreeResult_common, MATLABROS2MsgInterface<btcpp_ros2_interfaces::action::ExecuteTree::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_btcpp_ros2_interfaces_ExecuteTree_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1