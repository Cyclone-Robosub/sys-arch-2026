// Copyright 2021-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/ControlModeRequest
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
#include "custom_interfaces/srv/control_mode.hpp"
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
#include "ROS2ServiceTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_ControlModeRequest_common : public MATLABROS2MsgInterface<custom_interfaces::srv::ControlMode::Request> {
  public:
    virtual ~ros2_custom_interfaces_msg_ControlModeRequest_common(){}
    virtual void copy_from_struct(custom_interfaces::srv::ControlMode::Request* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::srv::ControlMode::Request* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_ControlModeRequest_common::copy_from_struct(custom_interfaces::srv::ControlMode::Request* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //mode
        const matlab::data::TypedArray<uint8_t> mode_arr = arr["mode"];
        msg->mode = mode_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'mode' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'mode' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_ControlModeRequest_common::get_arr(MDFactory_T& factory, const custom_interfaces::srv::ControlMode::Request* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","mode"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/ControlModeRequest");
    // mode
    auto currentElement_mode = (msg + ctr)->mode;
    outArray[ctr]["mode"] = factory.createScalar(currentElement_mode);
    }
    return std::move(outArray);
  }
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_ControlModeResponse_common : public MATLABROS2MsgInterface<custom_interfaces::srv::ControlMode::Response> {
  public:
    virtual ~ros2_custom_interfaces_msg_ControlModeResponse_common(){}
    virtual void copy_from_struct(custom_interfaces::srv::ControlMode::Response* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::srv::ControlMode::Response* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_ControlModeResponse_common::copy_from_struct(custom_interfaces::srv::ControlMode::Response* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_ControlModeResponse_common::get_arr(MDFactory_T& factory, const custom_interfaces::srv::ControlMode::Response* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/ControlModeResponse");
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_ControlMode_service : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_ControlMode_service(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABSvcServerInterface> generateSvcServerInterface();
    virtual std::shared_ptr<MATLABSvcClientInterface> generateSvcClientInterface();
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_ControlMode_service::generatePublisherInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2PublisherImpl<custom_interfaces::srv::ControlMode::Request,ros2_custom_interfaces_msg_ControlModeRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2PublisherImpl<custom_interfaces::srv::ControlMode::Response,ros2_custom_interfaces_msg_ControlModeResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSubscriberInterface> 
          ros2_custom_interfaces_ControlMode_service::generateSubscriberInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2SubscriberImpl<custom_interfaces::srv::ControlMode::Request,ros2_custom_interfaces_msg_ControlModeRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2SubscriberImpl<custom_interfaces::srv::ControlMode::Response,ros2_custom_interfaces_msg_ControlModeResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<void> ros2_custom_interfaces_ControlMode_service::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
        auto msg = std::make_shared<custom_interfaces::srv::ControlMode::Request>();
        ros2_custom_interfaces_msg_ControlModeRequest_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResponse){
        auto msg = std::make_shared<custom_interfaces::srv::ControlMode::Response>();
        ros2_custom_interfaces_msg_ControlModeResponse_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSvcServerInterface> 
          ros2_custom_interfaces_ControlMode_service::generateSvcServerInterface(){
    return std::make_shared<ROS2SvcServerImpl<custom_interfaces::srv::ControlMode,custom_interfaces::srv::ControlMode::Request,custom_interfaces::srv::ControlMode::Response,ros2_custom_interfaces_msg_ControlModeRequest_common,ros2_custom_interfaces_msg_ControlModeResponse_common>>();
  }
  std::shared_ptr<MATLABSvcClientInterface> 
          ros2_custom_interfaces_ControlMode_service::generateSvcClientInterface(){
    return std::make_shared<ROS2SvcClientImpl<custom_interfaces::srv::ControlMode,custom_interfaces::srv::ControlMode::Request,custom_interfaces::srv::ControlMode::Response,ros2_custom_interfaces_msg_ControlModeRequest_common,ros2_custom_interfaces_msg_ControlModeResponse_common,rclcpp::Client<custom_interfaces::srv::ControlMode>::SharedFuture>>();
  }
  matlab::data::StructArray ros2_custom_interfaces_ControlMode_service::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
	    ros2_custom_interfaces_msg_ControlModeRequest_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (custom_interfaces::srv::ControlMode::Request*)msgPtr, loader);
    }else if(type == eResponse){
        ros2_custom_interfaces_msg_ControlModeResponse_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;	
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (custom_interfaces::srv::ControlMode::Response*)msgPtr, loader);
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_ControlModeRequest_common, MATLABROS2MsgInterface<custom_interfaces::srv::ControlMode::Request>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_ControlModeResponse_common, MATLABROS2MsgInterface<custom_interfaces::srv::ControlMode::Response>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_ControlMode_service, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1
