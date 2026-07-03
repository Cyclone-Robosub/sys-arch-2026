// Copyright 2021-2022 The MathWorks, Inc.
// Common copy functions for btcpp_ros2_interfaces/GetTreesRequest
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
#include "btcpp_ros2_interfaces/srv/get_trees.hpp"
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
class BTCPP_ROS2_INTERFACES_EXPORT ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common : public MATLABROS2MsgInterface<btcpp_ros2_interfaces::srv::GetTrees::Request> {
  public:
    virtual ~ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common(){}
    virtual void copy_from_struct(btcpp_ros2_interfaces::srv::GetTrees::Request* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::srv::GetTrees::Request* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common::copy_from_struct(btcpp_ros2_interfaces::srv::GetTrees::Request* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common::get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::srv::GetTrees::Request* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("btcpp_ros2_interfaces/GetTreesRequest");
    }
    return std::move(outArray);
  }
class BTCPP_ROS2_INTERFACES_EXPORT ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common : public MATLABROS2MsgInterface<btcpp_ros2_interfaces::srv::GetTrees::Response> {
  public:
    virtual ~ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common(){}
    virtual void copy_from_struct(btcpp_ros2_interfaces::srv::GetTrees::Response* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::srv::GetTrees::Response* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common::copy_from_struct(btcpp_ros2_interfaces::srv::GetTrees::Response* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //tree_ids
        const matlab::data::CellArray tree_ids_cellarr = arr["tree_ids"];
        size_t nelem = tree_ids_cellarr.getNumberOfElements();
        for (size_t idx=0; idx < nelem; ++idx){
        	const matlab::data::CharArray tree_ids_arr = tree_ids_cellarr[idx];
        	msg->tree_ids.push_back(tree_ids_arr.toAscii());
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'tree_ids' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'tree_ids' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common::get_arr(MDFactory_T& factory, const btcpp_ros2_interfaces::srv::GetTrees::Response* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","tree_ids"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("btcpp_ros2_interfaces/GetTreesResponse");
    // tree_ids
    auto currentElement_tree_ids = (msg + ctr)->tree_ids;
    auto tree_idsoutCell = factory.createCellArray({currentElement_tree_ids.size(),1});
    for(size_t idxin = 0; idxin < currentElement_tree_ids.size(); ++ idxin){
    	tree_idsoutCell[idxin] = factory.createCharArray(currentElement_tree_ids[idxin]);
    }
    outArray[ctr]["tree_ids"] = tree_idsoutCell;
    }
    return std::move(outArray);
  } 
class BTCPP_ROS2_INTERFACES_EXPORT ros2_btcpp_ros2_interfaces_GetTrees_service : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_btcpp_ros2_interfaces_GetTrees_service(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABSvcServerInterface> generateSvcServerInterface();
    virtual std::shared_ptr<MATLABSvcClientInterface> generateSvcClientInterface();
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_btcpp_ros2_interfaces_GetTrees_service::generatePublisherInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2PublisherImpl<btcpp_ros2_interfaces::srv::GetTrees::Request,ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2PublisherImpl<btcpp_ros2_interfaces::srv::GetTrees::Response,ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSubscriberInterface> 
          ros2_btcpp_ros2_interfaces_GetTrees_service::generateSubscriberInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2SubscriberImpl<btcpp_ros2_interfaces::srv::GetTrees::Request,ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2SubscriberImpl<btcpp_ros2_interfaces::srv::GetTrees::Response,ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<void> ros2_btcpp_ros2_interfaces_GetTrees_service::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
        auto msg = std::make_shared<btcpp_ros2_interfaces::srv::GetTrees::Request>();
        ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResponse){
        auto msg = std::make_shared<btcpp_ros2_interfaces::srv::GetTrees::Response>();
        ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSvcServerInterface> 
          ros2_btcpp_ros2_interfaces_GetTrees_service::generateSvcServerInterface(){
    return std::make_shared<ROS2SvcServerImpl<btcpp_ros2_interfaces::srv::GetTrees,btcpp_ros2_interfaces::srv::GetTrees::Request,btcpp_ros2_interfaces::srv::GetTrees::Response,ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common,ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common>>();
  }
  std::shared_ptr<MATLABSvcClientInterface> 
          ros2_btcpp_ros2_interfaces_GetTrees_service::generateSvcClientInterface(){
    return std::make_shared<ROS2SvcClientImpl<btcpp_ros2_interfaces::srv::GetTrees,btcpp_ros2_interfaces::srv::GetTrees::Request,btcpp_ros2_interfaces::srv::GetTrees::Response,ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common,ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common,rclcpp::Client<btcpp_ros2_interfaces::srv::GetTrees>::SharedFuture>>();
  }
  matlab::data::StructArray ros2_btcpp_ros2_interfaces_GetTrees_service::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
	    ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (btcpp_ros2_interfaces::srv::GetTrees::Request*)msgPtr, loader);
    }else if(type == eResponse){
        ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;	
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (btcpp_ros2_interfaces::srv::GetTrees::Response*)msgPtr, loader);
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_btcpp_ros2_interfaces_msg_GetTreesRequest_common, MATLABROS2MsgInterface<btcpp_ros2_interfaces::srv::GetTrees::Request>)
CLASS_LOADER_REGISTER_CLASS(ros2_btcpp_ros2_interfaces_msg_GetTreesResponse_common, MATLABROS2MsgInterface<btcpp_ros2_interfaces::srv::GetTrees::Response>)
CLASS_LOADER_REGISTER_CLASS(ros2_btcpp_ros2_interfaces_GetTrees_service, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1
