// Copyright 2021-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/GetConfidenceRequest
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
#include "custom_interfaces/srv/get_confidence.hpp"
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
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_GetConfidenceRequest_common : public MATLABROS2MsgInterface<custom_interfaces::srv::GetConfidence::Request> {
  public:
    virtual ~ros2_custom_interfaces_msg_GetConfidenceRequest_common(){}
    virtual void copy_from_struct(custom_interfaces::srv::GetConfidence::Request* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::srv::GetConfidence::Request* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_GetConfidenceRequest_common::copy_from_struct(custom_interfaces::srv::GetConfidence::Request* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_GetConfidenceRequest_common::get_arr(MDFactory_T& factory, const custom_interfaces::srv::GetConfidence::Request* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/GetConfidenceRequest");
    }
    return std::move(outArray);
  }
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_GetConfidenceResponse_common : public MATLABROS2MsgInterface<custom_interfaces::srv::GetConfidence::Response> {
  public:
    virtual ~ros2_custom_interfaces_msg_GetConfidenceResponse_common(){}
    virtual void copy_from_struct(custom_interfaces::srv::GetConfidence::Response* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::srv::GetConfidence::Response* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_GetConfidenceResponse_common::copy_from_struct(custom_interfaces::srv::GetConfidence::Response* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_GetConfidenceResponse_common::get_arr(MDFactory_T& factory, const custom_interfaces::srv::GetConfidence::Response* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/GetConfidenceResponse");
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_GetConfidence_service : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_GetConfidence_service(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABSvcServerInterface> generateSvcServerInterface();
    virtual std::shared_ptr<MATLABSvcClientInterface> generateSvcClientInterface();
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_GetConfidence_service::generatePublisherInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2PublisherImpl<custom_interfaces::srv::GetConfidence::Request,ros2_custom_interfaces_msg_GetConfidenceRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2PublisherImpl<custom_interfaces::srv::GetConfidence::Response,ros2_custom_interfaces_msg_GetConfidenceResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSubscriberInterface> 
          ros2_custom_interfaces_GetConfidence_service::generateSubscriberInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2SubscriberImpl<custom_interfaces::srv::GetConfidence::Request,ros2_custom_interfaces_msg_GetConfidenceRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2SubscriberImpl<custom_interfaces::srv::GetConfidence::Response,ros2_custom_interfaces_msg_GetConfidenceResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<void> ros2_custom_interfaces_GetConfidence_service::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
        auto msg = std::make_shared<custom_interfaces::srv::GetConfidence::Request>();
        ros2_custom_interfaces_msg_GetConfidenceRequest_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResponse){
        auto msg = std::make_shared<custom_interfaces::srv::GetConfidence::Response>();
        ros2_custom_interfaces_msg_GetConfidenceResponse_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSvcServerInterface> 
          ros2_custom_interfaces_GetConfidence_service::generateSvcServerInterface(){
    return std::make_shared<ROS2SvcServerImpl<custom_interfaces::srv::GetConfidence,custom_interfaces::srv::GetConfidence::Request,custom_interfaces::srv::GetConfidence::Response,ros2_custom_interfaces_msg_GetConfidenceRequest_common,ros2_custom_interfaces_msg_GetConfidenceResponse_common>>();
  }
  std::shared_ptr<MATLABSvcClientInterface> 
          ros2_custom_interfaces_GetConfidence_service::generateSvcClientInterface(){
    return std::make_shared<ROS2SvcClientImpl<custom_interfaces::srv::GetConfidence,custom_interfaces::srv::GetConfidence::Request,custom_interfaces::srv::GetConfidence::Response,ros2_custom_interfaces_msg_GetConfidenceRequest_common,ros2_custom_interfaces_msg_GetConfidenceResponse_common,rclcpp::Client<custom_interfaces::srv::GetConfidence>::SharedFuture>>();
  }
  matlab::data::StructArray ros2_custom_interfaces_GetConfidence_service::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
	    ros2_custom_interfaces_msg_GetConfidenceRequest_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (custom_interfaces::srv::GetConfidence::Request*)msgPtr, loader);
    }else if(type == eResponse){
        ros2_custom_interfaces_msg_GetConfidenceResponse_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;	
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (custom_interfaces::srv::GetConfidence::Response*)msgPtr, loader);
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_GetConfidenceRequest_common, MATLABROS2MsgInterface<custom_interfaces::srv::GetConfidence::Request>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_GetConfidenceResponse_common, MATLABROS2MsgInterface<custom_interfaces::srv::GetConfidence::Response>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_GetConfidence_service, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1
