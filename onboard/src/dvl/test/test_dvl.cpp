#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "sensor-data.hpp"

class TestDVLInterface : public::testing::Test {
    protected:
        std::share_ptr<DVL> dvl;
        std::string& port; //need to replace with file placeholder

        void SetUp() override {
            if (!rclcpp::ok()) {
                rclcpp::init(0, nullptr);
            }
        }

        void TearDown() override {
            dvl.reset();
        }

        void createDVL(){
            dvl = std::make_shared<DVL>(port);
        }

};

/**
 * @brief Test dvl construction
 */
TEST_F(TestDVLInterface, DVLConstruction) {
    ASSERT_NO_THROW({
        createDVL();
    });

    ASSERT_NE(dvl, nullptr);
    EXPECT_EQ(dvl->getname(), std::string("DVL"));
}

/**
 * @brief Test DVL reading Velocity
 */
 TEST_F(TestDVLInterface, ReadVelocityReport){
    createDVL();

    dvl.readVelocityReport()
 }

 /**
 * @brief Test DVL reading DRReport
 */
 TEST_F(TestDVLInterface, ReadDRReport){
    
 }

 /**
 * @brief Test DVL reading Config
 */
 TEST_F(TestDVLInterface, ReadVelocityReport){
    
 }

 /**
 * @brief Test DVL setting Config
 */
 TEST_F(TestDVLInterface, DVLSetConfig){
    
 }

 /**
 * @brief Test DVL setting serial protocol
 */
 TEST_F(TestDVLInterface, DVLSetSerialProtocol){
    
 }

 /**
 * @brief Test resetting DRR 
 */
 TEST_F(TestDVLInterface, ResetDRR){
    
 }

 /**
 * @brief Test resetting Gyro
 */
 TEST_F(TestDVLInterface, ResetGyro){
    
 }