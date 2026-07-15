# Basic Validator for Mission Files

## Features
Only 
- Checks that each command has the required input ports and nothing else
- Checks that the input ports have assigned values
- Checks that the main_tree_to_execute field is filled

## Usage
How to run or use the application:
```bash
python3 validate_mission/validate_mission.py ['FILENAME']
```
The script assumes that the mission files are located in 
onboard/src/behaviortree_ros2/mission_tree_files
mission.xsd describes the XML schema that is checked by the script validate_mission.py to validate the mission file passed as parameter

## Interpreting Results
Error messages should be pretty clear; however, line numbers are always one off, so subtract one or look around the line number given
If you see something along the lines of The value '0.2,0.2,0.2,0.1' is not accepted by the pattern '\s*-?[0-9]+(\.[0-9]+)?\s*,\s*-?[0-9]+(\.[0-9]+)?\s*,\s*-?[0-9]+(\.[0-9]+)?\s*,\s*-?[0-9]+(\.[0-9]+)?\s*,\s*-?[0-9]+(\.[0-9]+)?\s*,\s*-?[0-9]+(\.[0-9]+)?\s*'
The pattern is a regex pattern and means that the value is not of the correct type