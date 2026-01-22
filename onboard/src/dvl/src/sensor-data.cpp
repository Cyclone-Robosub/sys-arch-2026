#include <sensor_data.hpp>

namespace dvl {

    // Constructor
    DVL::DVL(const std::string& port, unsigned long baudrate = 115200) : rclcpp::Node {
        //error config definition
        error_config.speed_of_sound = 0.0;
        error_config.mounting_rotation_offset = 0.0;
        error_config.acoustic_enabled = 'x';
        error_config.dark_mode_enabled = 'x';
        error_config.range_mode = 'x';
        error_config.periodic_cycling_enabled = 'x';
        config = error_config; //this will get overwritten by the first successful readConfig

        //serial setup
        ser.setPort(port);
        ser.setBaudrate(baudrate);
        serial::Timeout timeout = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(timeout);
        ser.open();
        if(!ser.isOpen()) {
            throw std::runtime_error("Failed to open serial port");
        }
    }
    
    // Public Reads
    VR DVL::readVelocityReport(){
        if(holdForResponse(REC_VR)){
            return vr;
        } else {
            return error_vr;
        }
        
    }

    DRR DVL::readDRReport(){
        if(holdForResponse(REC_DRR)){
            return drr;
        } else {
            return error_drr;
        }
    }

    std::string DVL::readVersion(){

        sendCommand(CMD_GET_VERSION); 
        
        if(holdForResponse(CMD_GET_VERSION)){
            return version;
        } else {
            version = "x.x.x";
            return version;
        }

    }

    std::string DVL::readDetails(){
        sendCommand(CMD_GET_PRODUCT_DETAIL); 
        
        if(holdForResponse(CMD_GET_PRODUCT_DETAIL)){
            return product_details;
        } else {
            return "x,x,x,x";
        }
    }

    Config DVL::readConfig(){
        sendCommand(CMD_GET_SETTINGS); 
        
        if(holdForResponse(CMD_GET_SETTINGS)){
            return config;
        } else {
            return error_config;
        }
    }


    // Public Writes
    bool DVL::setConfig(float speed_of_sound, float mounting_rotation_offset, char acoustic_enabled, char dark_mode_enabled, std::string range_mode, bool periodic_cycling_enabled){
        //to do: add setting args
        return sendCommand(CMD_SET_SETTINGS,{std::to_string(speed_of_sound), std::to_string(mounting_rotation_offset), acoustic_enabled, dark_mode_enabled, range_mode, std::to_string(periodic_cycling_enabled)});
    }

    bool DVL::resetDRR(){
        sendCommand(CMD_RESET_DR);
        if(holdForResponse(ACK)){
            return true;
        } else{
            return false;
        }
    }

    bool DVL::resetGyro(){
        sendCommand(CMD_CALIBRATE_GYRO);
        if(holdForResponse(ACK)){
            return true;
        } else{
            return false;
        }
    }

    bool DVL::triggerPing(){
        sendCommand(CMD_TRIGGER_PING);
        if(holdForResponse(ACK)){
            return true;
        } else {
            return false;
        }

    }

    bool DVL::setSerialProtocol(int protocol){
        sendCommand(CMD_CHANGE_SER_OUTPUT,{std::to_string(protocol)}); //currently only can be used to start serial output
        if(holdForResponse(ACK)){
            return true;
        } else{
            return false;
        }
    }

    //Private Methods
    bool DVL::holdForResponse(const char expected_response) {
        /*
        Waits until either 10 ms have elapsed or the expected response is received.
        Inputs:
            const std::string& expected_response -- string containing the expected response to the command such as "wrx" or "wra"
        Outputs:
            true or false depending on whether the expected response was found.
        */
        
        using clock = std::chrono::steady_clock;
        constexpr auto TIMEOUT = std::chrono::milliseconds(10);

        auto start = clock::now();
        std::string complete_line;

        while (clock::now() - start < TIMEOUT) {

            complete_line.clear(); //clear the complete line each time a line complete line is parsed 

            while (clock::now() - start < TIMEOUT) { //read until a complete line is found

                std::string partial_line = ser.read(1); //read one char

                if (partial_line.empty()) {
                    continue; //loop again if the the partial line is empty
                }

                complete_line += partial_line; //add the partial line to the complete line

                if (partial_line == "\n" || partial_line == "\r") {
                    break; //break out of the reading loop if an end-of-line char is detected
                }
            }

            //if inner loop timed out without EOL, keep looping
            if (complete_line.empty()) {
                continue; 
            }

            parseResponse(complete_line);

            if (complete_line[2] == 2) {
                return true; //if the expected response was received as the command field of the response
            }
        }

        return false; //return false if the code timed out
    }

    bool DVL::parseResponse(std::string& complete_line){

        //identify the command
        char cmd = complete_line[2];

        //strip whitespace and newlines
        complete_line.erase(0, complete_line.find_first_not_of(" \t\r\n"));
        complete_line.erase(complete_line.find_last_not_of(" \t\r\n") + 1);

        // strip checksum "*xx"
        if (complete_line.size() >= 3 &&
            complete_line[complete_line.size() - 3] == '*') {
            complete_line.erase(complete_line.size() - 3);
        }

        //check cmd against each possibility
        switch (cmd) {
            case 'v': //protocol version
                version = complete_line.substr(4);
                return true;
                break;
            case 'w': //product details
                product_details = complete_line.substr(4);
                return true;
                break;
            case 'a': //acknowledge
                return true;
                break;
            case 'c': {//configuration
                std::stringstream ss(complete_line);

                //split up the line into a string array
                std::string field;
                std::vector<std::string> fields;
                while(std::getline(ss, field, ",")) {
                    fields.push_back(field);
                }

                //unpack into config struct
                config.speed_of_sound = std::stof(fields[1]);
                config.mounting_rotation_offset = std::stof(fields[2]);
                config.acoustic_enabled = fields[3][0];
                config.dark_mode_enabled = fields[4][0];
                config.range_mode = fields[5];
                config.periodic_cycling_enabled = fields[6][0];

                return true;
                break;
                }
            case 'z': {//velocity report
                std::stringstream ss(complete_line);
                std::string field;
                std::vector<std::string> fields;

                while (std::getline(ss, field, ',')) {
                    fields.push_back(field);
                }

                vr.vx = std::stof(fields[1]);
                vr.vy = std::stof(fields[2]);
                vr.vz = std::stof(fields[3]);
                vr.valid = fields[4][0];
                vr.altitude = std::stof(fields[5]);
                vr.fom = std::stof(fields[6]);

                for (int i = 0; i < 9; ++i) {
                    vr.covariance[i] = std::stof(fields[7 + i]);
                }

                vr.time_of_validity = std::stoll(fields[16]);
                vr.time_of_transmission = std::stoll(fields[17]);
                vr.time = std::stof(fields[18]);
                vr.status = static_cast<uint8_t>(std::stoul(fields[19], nullptr, 10));
                return true;
                break;
                }
            case 'p': {//dead reckoning report
                std::stringstream ss(complete_line);
                std::string field;
                std::vector<std::string> fields;
                while(std::getline(ss, field, ',')){
                    fields.push_back(field);
                }

                drr.x = std::stof(fields[1]);
                drr.y = std::stof(fields[2]);
                drr.z = std::stof(fields[3]);
                drr.pos_std = std::stof(fields[4]);
                drr.roll = std::stof(fields[5]);
                drr.pitch = std::stof(fields[6]);
                drr.yaw = std::stof(fields[7]);
                drr.status = static_cast<uint8_t>(std::stoul(fields[8], nullptr, 10));
                return true;
                break;
                 }
            case '?': //malformed request
                return false;
                break;
            case '!': //bad checksum
                return false;
                break;
            case 'n': //not acknowledged
                return false;
                break;
            default:
                return false;
                break;
        }

    }

    bool DVL::sendCommand(uint8_t cmd, const std::vector<std::string>& options = {}) { //cmd with optional input args

        std::stringstream msg;

        msg << SOP << DIR_CMD << cmd; //add the start character, the direction, and the command to the output

        for(const auto& opt : options) { //add each option as a comma separated string
            msg << "," << opt;
        }

        // Compute checksum
        uint8_t csum = 0;
        std::string body = msg.str();
        
        uint8_t crc = 0x00;
        for(char c : body) {
            crc = CRC8_TABLE[crc ^ static_cast<uint8_t>(c)];
        }
        msg << CS << std::hex << std::setw(2) << std::setfill('0') << (int)crc << "\n"; //add checksum to the message

        ser.write(msg.str());
        return true;
    }

} //namespace