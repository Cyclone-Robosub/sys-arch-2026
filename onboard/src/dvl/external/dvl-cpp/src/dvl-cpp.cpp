#include <dvl-cpp.h>

namespace dvl {

    // Constructor
    DVL(const std::string& port, unsigned long baudrate = 115200) : Node() {
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
        return lastVelocityReport;
    }

    DRR DVL::readDRReport(){
        return lastDRReport;
    }

    // Public Writes
    bool DVL::setSettings(float speed_of_sound, float mounting_rotation_offset, char acoustic_enabled, char dark_mode_enabled, string range_mode, char periodic_cycling_enabled){
        //to do: add setting args
        return sendCommand(CMD_SET_SETTINGS,{std::to_string(speed_of_sound), std::to_string(mounting_rotation_offset), acoustic_enabled, dark_mode_enabled, range_mode, periodic_cycling_enabled});
    }

    bool DVL::resetDR(){
        return sendCommand(CMD_RESET_DR);
    }

    bool DVL::calGyro(){
        return sendCommand(CMD_CALIBRATE_GYRO);
    }

    bool DVL::setSerialProtocol(){
        return sendCommand(CMD_CHANGE_SER_OUTPUT,{"3"}); //currently only can be used to start serial output
    }

    //Private Methods
    //TODO - Add timeout to make sure this doesn't hang
    std::string DVL::readLine() {
        std::string line;
        while (true) {
            std::string chunk = ser.read(1);
            if (chunk.empty()) continue;
            line += chunk;
            if (chunk == "\n" || chunk == "\r") break;
        }
        return line;
    }

    void DVL::parse(const std::vector<uint8_t>& sentence) {
        if (sentence.size() < 4 || sentence[0] != SOP) return;

        char dir = sentence[1];
        char cmd = sentence[2];

        //TODO add checksum validation

        std::string payload(sentence.begin() + 3, sentence.end());
        size_t cs_pos = payload.find(CS);
        if(cs_pos == std::string::npos) return; // no checksum found
        payload = payload.substr(0, cs_pos);

        std::vector<std::string> tokens;
        std::stringstream ss(payload);
        std::string item;
        while(std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (cmd == REC_VR && tokens.size() >= 9) { //parse the velocity report
            lastVelocityReport.vx = std::stof(tokens[0]);
            lastVelocityReport.vy = std::stof(tokens[1]);
            lastVelocityReport.vz = std::stof(tokens[2]);
            lastVelocityReport.altitude = std::stof(tokens[3]);
            lastVelocityReport.fom = std::stof(tokens[4]);
            lastVelocityReport.covariance = std::stof(tokens[5]);
            lastVelocityReport.time_of_validity = std::stof(tokens[6]);
            lastVelocityReport.time_of_transmission = std::stof(tokens[7]);
            lastVelocityReport.time = std::stof(tokens[8]);
            lastVelocityReport.valid = true;
            lastVelocityReport.status = 0; // Could parse status if provided
        } else if(cmd == REC_DRR && tokens.size() >= 8) { //parse the dead reckoning report
            lastDRReport.time_stamp = std::stof(tokens[0]);
            lastDRReport.x = std::stof(tokens[1]);
            lastDRReport.y = std::stof(tokens[2]);
            lastDRReport.z = std::stof(tokens[3]);
            lastDRReport.pos_std = std::stof(tokens[4]);
            lastDRReport.roll = std::stof(tokens[5]);
            lastDRReport.pitch = std::stof(tokens[6]);
            lastDRReport.yaw = std::stof(tokens[7]);
            lastDRReport.status = true;
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
        
        uint8_t crc = 0x00
        for(char c : data) {
            crc = CRC8_TABLE[crc ^ static_cast<uint8_t>(c)];
        }
        msg << CS << std::hex << std::setw(2) << std::setfill('0') << (int)csum << "\n"; //add checksum to the message

        ser.write(msg.str());
        return true;
    }



} //namespace



