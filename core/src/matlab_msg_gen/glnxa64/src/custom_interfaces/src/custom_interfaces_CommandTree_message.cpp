// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/CommandTree
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
#include "custom_interfaces/msg/command_tree.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_CommandTree_common : public MATLABROS2MsgInterface<custom_interfaces::msg::CommandTree> {
  public:
    virtual ~ros2_custom_interfaces_msg_CommandTree_common(){}
    virtual void copy_from_struct(custom_interfaces::msg::CommandTree* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::msg::CommandTree* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_CommandTree_common::copy_from_struct(custom_interfaces::msg::CommandTree* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //current_subtree
        const matlab::data::CharArray current_subtree_arr = arr["current_subtree"];
        msg->current_subtree = current_subtree_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'current_subtree' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'current_subtree' is wrong type; expected a string.");
    }
    try {
        //current_command
        const matlab::data::CharArray current_command_arr = arr["current_command"];
        msg->current_command = current_command_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'current_command' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'current_command' is wrong type; expected a string.");
    }
    try {
        //status
        const matlab::data::CharArray status_arr = arr["status"];
        msg->status = status_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'status' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'status' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_CommandTree_common::get_arr(MDFactory_T& factory, const custom_interfaces::msg::CommandTree* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","current_subtree","current_command","status"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/CommandTree");
    // current_subtree
    auto currentElement_current_subtree = (msg + ctr)->current_subtree;
    outArray[ctr]["current_subtree"] = factory.createCharArray(currentElement_current_subtree);
    // current_command
    auto currentElement_current_command = (msg + ctr)->current_command;
    outArray[ctr]["current_command"] = factory.createCharArray(currentElement_current_command);
    // status
    auto currentElement_status = (msg + ctr)->status;
    outArray[ctr]["status"] = factory.createCharArray(currentElement_status);
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_CommandTree_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_CommandTree_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_CommandTree_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<custom_interfaces::msg::CommandTree,ros2_custom_interfaces_msg_CommandTree_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_custom_interfaces_CommandTree_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<custom_interfaces::msg::CommandTree,ros2_custom_interfaces_msg_CommandTree_common>>();
  }
  std::shared_ptr<void> ros2_custom_interfaces_CommandTree_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<custom_interfaces::msg::CommandTree>();
    ros2_custom_interfaces_msg_CommandTree_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_custom_interfaces_CommandTree_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_custom_interfaces_msg_CommandTree_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (custom_interfaces::msg::CommandTree*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_CommandTree_common, MATLABROS2MsgInterface<custom_interfaces::msg::CommandTree>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_CommandTree_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER