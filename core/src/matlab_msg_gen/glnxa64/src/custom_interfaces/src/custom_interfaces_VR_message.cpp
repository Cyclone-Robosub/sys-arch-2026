// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/VR
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
#include "custom_interfaces/msg/vr.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_VR_common : public MATLABROS2MsgInterface<custom_interfaces::msg::VR> {
  public:
    virtual ~ros2_custom_interfaces_msg_VR_common(){}
    virtual void copy_from_struct(custom_interfaces::msg::VR* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::msg::VR* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_VR_common::copy_from_struct(custom_interfaces::msg::VR* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //velocity_data
        const matlab::data::StructArray velocity_data_arr = arr["velocity_data"];
        auto msgClassPtr_velocity_data = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
        msgClassPtr_velocity_data->copy_from_struct(&msg->velocity_data,velocity_data_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'velocity_data' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'velocity_data' is wrong type; expected a struct.");
    }
    try {
        //altitude
        const matlab::data::TypedArray<float> altitude_arr = arr["altitude"];
        msg->altitude = altitude_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'altitude' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'altitude' is wrong type; expected a single.");
    }
    try {
        //fom
        const matlab::data::TypedArray<float> fom_arr = arr["fom"];
        msg->fom = fom_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'fom' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'fom' is wrong type; expected a single.");
    }
    try {
        //time
        const matlab::data::TypedArray<float> time_arr = arr["time"];
        msg->time = time_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time' is wrong type; expected a single.");
    }
    try {
        //covariance
        const matlab::data::StructArray covariance_arr = arr["covariance"];
        auto msgClassPtr_covariance = getCommonObject<std_msgs::msg::Float32MultiArray>("ros2_std_msgs_msg_Float32MultiArray_common",loader);
        msgClassPtr_covariance->copy_from_struct(&msg->covariance,covariance_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'covariance' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'covariance' is wrong type; expected a struct.");
    }
    try {
        //time_of_validity
        const matlab::data::TypedArray<int64_t> time_of_validity_arr = arr["time_of_validity"];
        msg->time_of_validity = time_of_validity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time_of_validity' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time_of_validity' is wrong type; expected a int64.");
    }
    try {
        //time_of_transmission
        const matlab::data::TypedArray<int64_t> time_of_transmission_arr = arr["time_of_transmission"];
        msg->time_of_transmission = time_of_transmission_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'time_of_transmission' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'time_of_transmission' is wrong type; expected a int64.");
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
    try {
        //valid
        const matlab::data::CharArray valid_arr = arr["valid"];
        const std::string valid_str = valid_arr.toAscii();
        msg->valid = valid_str[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'valid' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'valid' is wrong type; expected a char.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_VR_common::get_arr(MDFactory_T& factory, const custom_interfaces::msg::VR* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","velocity_data","altitude","fom","time","covariance","time_of_validity","time_of_transmission","status","valid"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/VR");
    // velocity_data
    auto currentElement_velocity_data = (msg + ctr)->velocity_data;
    auto msgClassPtr_velocity_data = getCommonObject<geometry_msgs::msg::Vector3>("ros2_geometry_msgs_msg_Vector3_common",loader);
    outArray[ctr]["velocity_data"] = msgClassPtr_velocity_data->get_arr(factory, &currentElement_velocity_data, loader);
    // altitude
    auto currentElement_altitude = (msg + ctr)->altitude;
    outArray[ctr]["altitude"] = factory.createScalar(currentElement_altitude);
    // fom
    auto currentElement_fom = (msg + ctr)->fom;
    outArray[ctr]["fom"] = factory.createScalar(currentElement_fom);
    // time
    auto currentElement_time = (msg + ctr)->time;
    outArray[ctr]["time"] = factory.createScalar(currentElement_time);
    // covariance
    auto currentElement_covariance = (msg + ctr)->covariance;
    auto msgClassPtr_covariance = getCommonObject<std_msgs::msg::Float32MultiArray>("ros2_std_msgs_msg_Float32MultiArray_common",loader);
    outArray[ctr]["covariance"] = msgClassPtr_covariance->get_arr(factory, &currentElement_covariance, loader);
    // time_of_validity
    auto currentElement_time_of_validity = (msg + ctr)->time_of_validity;
    outArray[ctr]["time_of_validity"] = factory.createScalar(currentElement_time_of_validity);
    // time_of_transmission
    auto currentElement_time_of_transmission = (msg + ctr)->time_of_transmission;
    outArray[ctr]["time_of_transmission"] = factory.createScalar(currentElement_time_of_transmission);
    // status
    auto currentElement_status = (msg + ctr)->status;
    outArray[ctr]["status"] = factory.createScalar(currentElement_status);
    // valid
    auto currentElement_valid = (msg + ctr)->valid;
    outArray[ctr]["valid"] = factory.createCharArray(std::string(1,currentElement_valid));
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_VR_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_VR_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_VR_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<custom_interfaces::msg::VR,ros2_custom_interfaces_msg_VR_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_custom_interfaces_VR_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<custom_interfaces::msg::VR,ros2_custom_interfaces_msg_VR_common>>();
  }
  std::shared_ptr<void> ros2_custom_interfaces_VR_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<custom_interfaces::msg::VR>();
    ros2_custom_interfaces_msg_VR_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_custom_interfaces_VR_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_custom_interfaces_msg_VR_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (custom_interfaces::msg::VR*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_VR_common, MATLABROS2MsgInterface<custom_interfaces::msg::VR>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_VR_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER