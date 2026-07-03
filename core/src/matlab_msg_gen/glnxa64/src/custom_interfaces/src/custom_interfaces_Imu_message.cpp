// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for custom_interfaces/Imu
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
#include "custom_interfaces/msg/imu.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_msg_Imu_common : public MATLABROS2MsgInterface<custom_interfaces::msg::Imu> {
  public:
    virtual ~ros2_custom_interfaces_msg_Imu_common(){}
    virtual void copy_from_struct(custom_interfaces::msg::Imu* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const custom_interfaces::msg::Imu* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_custom_interfaces_msg_Imu_common::copy_from_struct(custom_interfaces::msg::Imu* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //imu_fusion
        const matlab::data::StructArray imu_fusion_arr = arr["imu_fusion"];
        auto msgClassPtr_imu_fusion = getCommonObject<sensor_msgs::msg::Imu>("ros2_sensor_msgs_msg_Imu_common",loader);
        msgClassPtr_imu_fusion->copy_from_struct(&msg->imu_fusion,imu_fusion_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'imu_fusion' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'imu_fusion' is wrong type; expected a struct.");
    }
    try {
        //mag_array
        const matlab::data::StructArray mag_array_arr = arr["mag_array"];
        auto msgClassPtr_mag_array = getCommonObject<sensor_msgs::msg::MagneticField>("ros2_sensor_msgs_msg_MagneticField_common",loader);
        msgClassPtr_mag_array->copy_from_struct(&msg->mag_array,mag_array_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'mag_array' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'mag_array' is wrong type; expected a struct.");
    }
    try {
        //pressure
        const matlab::data::StructArray pressure_arr = arr["pressure"];
        auto msgClassPtr_pressure = getCommonObject<sensor_msgs::msg::FluidPressure>("ros2_sensor_msgs_msg_FluidPressure_common",loader);
        msgClassPtr_pressure->copy_from_struct(&msg->pressure,pressure_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pressure' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'pressure' is wrong type; expected a struct.");
    }
    try {
        //ahrs_database
        const matlab::data::StructArray ahrs_database_arr = arr["ahrs_database"];
        auto msgClassPtr_ahrs_database = getCommonObject<nav_msgs::msg::Odometry>("ros2_nav_msgs_msg_Odometry_common",loader);
        msgClassPtr_ahrs_database->copy_from_struct(&msg->ahrs_database,ahrs_database_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'ahrs_database' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'ahrs_database' is wrong type; expected a struct.");
    }
    try {
        //roll
        const matlab::data::TypedArray<double> roll_arr = arr["roll"];
        msg->roll = roll_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'roll' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'roll' is wrong type; expected a double.");
    }
    try {
        //pitch
        const matlab::data::TypedArray<double> pitch_arr = arr["pitch"];
        msg->pitch = pitch_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pitch' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'pitch' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_custom_interfaces_msg_Imu_common::get_arr(MDFactory_T& factory, const custom_interfaces::msg::Imu* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","imu_fusion","mag_array","pressure","ahrs_database","roll","pitch"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("custom_interfaces/Imu");
    // imu_fusion
    auto currentElement_imu_fusion = (msg + ctr)->imu_fusion;
    auto msgClassPtr_imu_fusion = getCommonObject<sensor_msgs::msg::Imu>("ros2_sensor_msgs_msg_Imu_common",loader);
    outArray[ctr]["imu_fusion"] = msgClassPtr_imu_fusion->get_arr(factory, &currentElement_imu_fusion, loader);
    // mag_array
    auto currentElement_mag_array = (msg + ctr)->mag_array;
    auto msgClassPtr_mag_array = getCommonObject<sensor_msgs::msg::MagneticField>("ros2_sensor_msgs_msg_MagneticField_common",loader);
    outArray[ctr]["mag_array"] = msgClassPtr_mag_array->get_arr(factory, &currentElement_mag_array, loader);
    // pressure
    auto currentElement_pressure = (msg + ctr)->pressure;
    auto msgClassPtr_pressure = getCommonObject<sensor_msgs::msg::FluidPressure>("ros2_sensor_msgs_msg_FluidPressure_common",loader);
    outArray[ctr]["pressure"] = msgClassPtr_pressure->get_arr(factory, &currentElement_pressure, loader);
    // ahrs_database
    auto currentElement_ahrs_database = (msg + ctr)->ahrs_database;
    auto msgClassPtr_ahrs_database = getCommonObject<nav_msgs::msg::Odometry>("ros2_nav_msgs_msg_Odometry_common",loader);
    outArray[ctr]["ahrs_database"] = msgClassPtr_ahrs_database->get_arr(factory, &currentElement_ahrs_database, loader);
    // roll
    auto currentElement_roll = (msg + ctr)->roll;
    outArray[ctr]["roll"] = factory.createScalar(currentElement_roll);
    // pitch
    auto currentElement_pitch = (msg + ctr)->pitch;
    outArray[ctr]["pitch"] = factory.createScalar(currentElement_pitch);
    }
    return std::move(outArray);
  } 
class CUSTOM_INTERFACES_EXPORT ros2_custom_interfaces_Imu_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_custom_interfaces_Imu_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_custom_interfaces_Imu_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<custom_interfaces::msg::Imu,ros2_custom_interfaces_msg_Imu_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_custom_interfaces_Imu_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<custom_interfaces::msg::Imu,ros2_custom_interfaces_msg_Imu_common>>();
  }
  std::shared_ptr<void> ros2_custom_interfaces_Imu_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<custom_interfaces::msg::Imu>();
    ros2_custom_interfaces_msg_Imu_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_custom_interfaces_Imu_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_custom_interfaces_msg_Imu_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (custom_interfaces::msg::Imu*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_msg_Imu_common, MATLABROS2MsgInterface<custom_interfaces::msg::Imu>)
CLASS_LOADER_REGISTER_CLASS(ros2_custom_interfaces_Imu_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER