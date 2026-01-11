#pragma once

#include <string>
#include <cstdint>
#include <array>
#include <vector>

namespace dvl {

class DVL {
    public:
        explicit DVL(const std::string& device); //device is the virtual com port device connected to the dvl

        // PUBLIC API //
        std::vector<uint8_t> getData(); //request data from the DVL
        std::vector<uint8_t> getPack();
        std::vector<uint8_t> read(); //read most recent data

    private:

        // PRIVATE CONSTANTS //
        // Protocol definitions
        const char SOP = 'w'; //start of package
        const char EOP = '\n'; //end of package
        const char DIR_CMD = 'c'; //command
        const char DIR_RESP = 'r'; //response
        const char CHECKSUM = '*';

        const char CMD_GET_VERSION = 'v';
        const char CMD_GET_PAYLOAD_SIZE = 'n';
        const char CMD_GET_BUFFER_LENGTH = 'l';
        const char CMD_GET_DIAGNOSTIC = 'd';
        const char CMD_GET_SETTINGS = 'c';
        const char CMD_SET_SETTINGS = 's';
        const char CMD_QUEUE_PACKET = 'q';
        const char CMD_FLUSH = 'f';
        const char RESP_GOT_PACKET = 'p';
        const char VELOCITY_REPORT = 'x';

        const char All_VALID[10] = {CMD_GET_VERSION, CMD_GET_PAYLOAD_SIZE, 
            CMD_GET_BUFFER_LENGTH, CMD_GET_DIAGNOSTIC, CMD_GET_SETTINGS,
            CMD_SET_SETTINGS, CMD_QUEUE_PACKET, CMD_FLUSH, RESP_GOT_PACKET,
            VELOCITY_REPORT}; //list of valid commands

        // PRIVATE METHODS //

        bool is_checksum(char ch); //check if a character is CHECKSUM
        std::array<uint8_t,3> do_format_checksum(uint8_t checksum); //reformat integer checksum the characters '*xx' for serial
        std::array<uint8_t,3> checksum_for_buffer(std::vector<uint8_t> data); //calculate checksum for the data buffer
        void parse(std::vector<uint8_t> sentence); //parse a buffer and set public output fields accordingly

        
        






}


}