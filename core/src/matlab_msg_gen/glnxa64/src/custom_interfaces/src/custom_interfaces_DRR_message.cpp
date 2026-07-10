// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/DRR
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
#include "custom_interfaces/msg/drr.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_DRR_common : public MATLABROS2MsgInterface<custom_interfaces::msg::DRR> {
  public:
    virtual ~ros2_custom_interfaces_msg_DRR_common(){}
    virtual void copy_from_struct(custom_interfaces::msg::DRR* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::msg::DRR* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_DRR_common::copy_from_struct(custom_interfaces::msg::DRR* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //time_stamp
        const matlab::data::TypedArray<int64_t> time_stamp_arr = arr["time_stamp"];
        msg->time_stamp = time_stamp_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time_stamp' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time_stamp' is wrong type; expected a int64.");
    }
    try {
        //position
        const matlab::data::StructArray position_arr = arr["position"];
        auto msgClassPtr_position = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
        msgClassPtr_position->copy_from_struct(&msg->position,position_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a struct.");
    }
    try {
        //angle
        const matlab::data::StructArray angle_arr = arr["angle"];
        auto msgClassPtr_angle = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
        msgClassPtr_angle->copy_from_struct(&msg->angle,angle_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angle' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'angle' is wrong type; expected a struct.");
    }
    try {
        //pos_std
        const matlab::data::TypedArray<float> pos_std_arr = arr["pos_std"];
        msg->pos_std = pos_std_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pos_std' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'pos_std' is wrong type; expected a single.");
    }
    try {
        //status
        const matlab::data::TypedArray<uint8_t> status_arr = arr["status"];
        msg->status = status_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'status' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'status' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_DRR_common::get_arr(MDFactory_T& factory, const custom_interfaces::msg::DRR* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","time_stamp","position","angle","pos_std","status"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/DRR");
    // time_stamp
    auto currentElement_time_stamp = (msg + ctr)->time_stamp;
    outArray[ctr]["time_stamp"] = factory.createScalar(currentElement_time_stamp);
    // position
    auto currentElement_position = (msg + ctr)->position;
    auto msgClassPtr_position = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
    outArray[ctr]["position"] = msgClassPtr_position->get_arr(factory, &currentElement_position, loader);
    // angle
    auto currentElement_angle = (msg + ctr)->angle;
    auto msgClassPtr_angle = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
    outArray[ctr]["angle"] = msgClassPtr_angle->get_arr(factory, &currentElement_angle, loader);
    // pos_std
    auto currentElement_pos_std = (msg + ctr)->pos_std;
    outArray[ctr]["pos_std"] = factory.createScalar(currentElement_pos_std);
    // status
    auto currentElement_status = (msg + ctr)->status;
    outArray[ctr]["status"] = factory.createScalar(currentElement_status);
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_DRR_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_DRR_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_DRR_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<custom_interfaces::msg::DRR,ros2_custom_interfaces_msg_DRR_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_custom_interfaces_DRR_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<custom_interfaces::msg::DRR,ros2_custom_interfaces_msg_DRR_common>>();
  }
  std::shared_ptr<void> ros2_custom_interfaces_DRR_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<custom_interfaces::msg::DRR>();
    ros2_custom_interfaces_msg_DRR_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_custom_interfaces_DRR_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_custom_interfaces_msg_DRR_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (custom_interfaces::msg::DRR*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_DRR_common, MATLABROS2MsgInterface<custom_interfaces::msg::DRR>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_DRR_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER