'''
Tests input parsing for the Command Line Interface
'''
import builtins
import pytest
import time

from pwm_cli.cli_console import main
from pwm_cli.cli_publisher import *

'''
Pass by parameter for any tests that need to override input()
Stores default input() function to reset when test is finished running
'''
@pytest.fixture
def simulate_input():
	store_input = input
	yield
	builtins.input = store_input

'''
Pass by parameter for any tests that need to check print() results
Stores default print() function to reset when test is finished running
'''
@pytest.fixture
def catch_output():
	store_print = print
	print_outputs = []
	builtins.print = lambda output: print_outputs.append(output)
	yield print_outputs
	builtins.print = store_print

'''
Outputs the next string in a list each time it is called
If called with "wait {num}" it will wait for that many seconds
Used to override input() function for testing the main loop of cli_console
'''
def input_iterator(outputs: list[str]):
	iterator = iter(outputs)
	def my_input(input = None):
		next_input = next(iterator)
		if "wait " in next_input:
			time.sleep(float(next_input[5:]))
			return next(iterator)
		return next_input
	return my_input

# Used to denote the first important value of catch_output, as the info() command prints 24 times on program start
INFO_OFFSET = 25


# --- BEGIN TESTS ---

	# --- DEMO TESTS ---

# Shows overriding the input() function with a lambda that outputs a set string
def test_example_input(simulate_input):
	builtins.input = lambda: "Overriding input() with a lambda"
	output = input()
	assert output == "Overriding input() with a lambda"


	# --- MAIN LOOP TESTS ---

def test_end_session(simulate_input, catch_output):
	builtins.input = input_iterator(["end session"])
	main()
	output_list = catch_output
	assert output_list[INFO_OFFSET] == "Goodbye!"


		# --- INVALID INPUT TESTS ---

# Tests that cli_console can handle invalid command inputs
def test_invalid_commands(simulate_input, catch_output):
	builtins.input = input_iterator(["vnkjvbiwcjvnjc j", "end session"])
	main()
	output_list = catch_output
	assert output_list[INFO_OFFSET] == "vnkjvbiwcjvnjc j is not a valid command. Type 'help' for valid commands."


# Tests that cli_console can handle invalid time inputs
def test_invalid_times(simulate_input, catch_output):
	builtins.input = input_iterator(["time: ", "t: ", "time: . ", "t: . ", "end session"])
	main()
	output_list = catch_output
	for out_num in range(0, 4):
		assert output_list[INFO_OFFSET + out_num] == "Invalid time inputted\n"


# Tests that cli_console can handle invalid default power inputs
def test_invalid_set_power(simulate_input, catch_output):
	builtins.input = input_iterator(["set power ", "set power . ", "set power 0","set power 101", "set power 999", "end session"])
	main()
	output_list = catch_output
	for out_num in range(0, 5):
		assert output_list[INFO_OFFSET + out_num] == "Invalid default power inputted\n"


# Tests that cli_console can handle invalid power inputs
def test_invalid_powers(simulate_input, catch_output):
	builtins.input = input_iterator(["power: ", "p: ", "power: . ", "p: . ", "p: 999", "end session"])
	main()
	output_list = catch_output
	for out_num in range(0, 5):
		assert output_list[INFO_OFFSET + out_num] == "Invalid power inputted\n"


# Tests that cli_console can handle invalid custom pwm inputs
def test_invalid_custom_pwms(simulate_input, catch_output):
	builtins.input = input_iterator([
		"custom [1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000]",
		"custom [2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000]",
		"custom [1000]",
		"custom [1500]",
		"custom [2000]",
		"custom [2000, 1000]",
		"custom [2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000]",
		"custom [1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]",
		"custom [1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500] p: 50 t: 20",
		"custom p: 50 t: 20 [1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]",
		"end session"])
	main()
	output_list = catch_output
	assert output_list[INFO_OFFSET] == "Invalid custom pwms inputted: ['1000', '1000', '1000', '1000', '1000', '1000', '1000', '1000']\n"
	assert output_list[INFO_OFFSET+1] == "Invalid custom pwms inputted: ['2000', '2000', '2000', '2000', '2000', '2000', '2000', '2000']\n"
	assert output_list[INFO_OFFSET+2] == "Invalid custom pwms inputted: ['1000'] (Note: 1 pwm recieved, expected 8)\n"
	assert output_list[INFO_OFFSET+3] == "Invalid custom pwms inputted: ['1500'] (Note: 1 pwm recieved, expected 8)\n"
	assert output_list[INFO_OFFSET+4] == "Invalid custom pwms inputted: ['2000'] (Note: 1 pwm recieved, expected 8)\n"
	assert output_list[INFO_OFFSET+5] == "Invalid custom pwms inputted: ['2000', '1000'] (Note: 2 pwms recieved, expected 8)\n"
	assert output_list[INFO_OFFSET+6] == "Invalid custom pwms inputted: ['2000', '2000', '2000', '2000', '2000', '2000', '2000', '2000', '2000'] (Note: 9 pwms recieved, expected 8)\n"
	assert output_list[INFO_OFFSET+7] == "Invalid custom pwms inputted: ['1500', '1500', '1500', '1500', '1500', '1500', '1500', '1500', '1500'] (Note: 9 pwms recieved, expected 8)\n"
	assert output_list[INFO_OFFSET+8] == "Invalid custom pwms inputted: ['1500', '1500', '1500', '1500', '1500', '1500', '1500', '1500', '1500'] (Note: 9 pwms recieved, expected 8)\n"


# Tests that cli_console can handle invalid run and stop thruster commands
def test_invalid_thruster(simulate_input, catch_output):
	builtins.input = input_iterator([
		"run thruster",
		"run thruster 0", "yes",
		"stop thruster",
		"stop thruster 8",
		"stop thruster 100000",
		"run thruster 8",
		"run thruster 100000",
		"run thruster 0 pwm: 1099",
		"run thruster 0 pwm: 1901",
		"run thruster 0 pwm: 10000000000000",
		"run thruster 0 pwm:",
		"run thruster 1 t:6", "yes",
		"end session"])
	main()
	output_list = catch_output
	expected_outputs = [
		"No thruster number inputted\n",
		"No thruster number inputted\n",
		"Invalid thruster number inputted: 8, max 7\n",
		"Invalid thruster number inputted: 100000, max 7\n",
		"Invalid thruster number inputted: 8, max 7\n",
		"Invalid thruster number inputted: 100000, max 7\n",
		"Invalid thruster pwm inputted: 1099\n",
		"Invalid thruster pwm inputted: 1901\n",
		"Invalid thruster pwm inputted: 10000000000000\n",
		"No thruster pwm inputted\n",
		"Note: Custom times are ignored for thruster commands.\n"
	]
	for i in range(0,len(expected_outputs)):
		assert output_list[INFO_OFFSET+i] == expected_outputs[i]


		# --- VALID INPUT TESTS ---

# Check that default power correctly updates after 'set power' is processed
def test_set_power(simulate_input, catch_output):
	builtins.input = input_iterator([
		"forwards", "yes", "current command",
		"set power 100",
		"forwards", "yes", "current command",
		"backwards", "yes", "current command",
		"strafe left", "yes", "current command",
		"run thruster 0", "yes", "current command",
		"set power 10",
		"run thruster 3", "yes", "current command",
		"forwards", "yes", "current command",
		"backwards", "yes", "current command",
		"strafe left", "yes", "current command",
		"run thruster 0", "yes", "current command",
		"end session"
		])
	main()
	output_list = catch_output
	expected_outputs = [
		"Current Command: Move Forwards at 70% power\n",
		"Set default power to 100%\n",
		"Current Command: Move Forwards at 100% power\n",
		"Current Command: Move Backwards at 100% power\n",
		"Current Command: Strafe Left at 100% power\n",
		"Current Command: Run Thruster 0 at 1900\n",
		"Set default power to 10%\n",
		"Current Command: Run Thrusters 0 at 1900, 3 at 1540\n",
		"Current Command: Move Forwards at 10% power\n",
		"Current Command: Move Backwards at 10% power\n",
		"Current Command: Strafe Left at 10% power\n",
		"Current Command: Run Thruster 0 at 1540\n"
	]
	for i in range(0,len(expected_outputs)):
		assert output_list[INFO_OFFSET+i] == expected_outputs[i]


# Check that get_current_command() works as expected
def test_current_command(simulate_input, catch_output):
	builtins.input = input_iterator([
		"current command",
		"forwards", "yes", "current command",
		"backwards", "yes", "current command",
		"backwards t:5 p:60", "yes", "current command",
		"strafe left", "yes", "current command",
		"strafe right", "yes", "current command",
		"roll right t: 5 p:60", "yes", "current command",
		"custom [1200, 1100, 1100, 1100, 1100, 1100, 1100, 1100] t: 5", "yes", "current command",
		"run thruster 0", "yes", "current command",
		"run thruster 5 pwm:1300", "yes", "current command",
		"stop thruster 0", "current command",
		"stop thruster 5", "current command",
		"custom [1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100] t: 5", "yes", "current command",
		"set power 20", "current command",
		"forwards", "yes", "current command",
		"stop", "current command",
		"forwards", "yes", "info", "current command",
		"help", "current command",
		"end session"
	])
	main()
	output_list = catch_output
	expected_outputs = [
		"There is no currently active command\n",
		"Current Command: Move Forwards at 70% power\n",
		"Current Command: Move Backwards at 70% power\n",
		"Current Command: Move Backwards at 60% power for 5 seconds\n",
		"Current Command: Strafe Left at 70% power\n",
		"Current Command: Strafe Right at 70% power\n",
		"Current Command: Roll Right at 60% power for 5 seconds\n",
		"Current Command: Custom pwm ['1200', '1100', '1100', '1100', '1100', '1100', '1100', '1100'] for 5 seconds\n",
		"Current Command: Run Thruster 0 at 1780\n",
		"Current Command: Run Thrusters 0 at 1780, 5 at 1300\n",
		"Current Command: Run Thruster 5 at 1300\n",
		"There is no currently active command\n",
		"Current Command: Custom pwm ['1100', '1100', '1100', '1100', '1100', '1100', '1100', '1100'] for 5 seconds\n",
		"Set default power to 20%\n",
		"Current Command: Custom pwm ['1100', '1100', '1100', '1100', '1100', '1100', '1100', '1100'] for 5 seconds\n",
		"Current Command: Move Forwards at 20% power\n",
		"There is no currently active command\n",
	]
	for i in range(0,len(expected_outputs)):
		assert output_list[INFO_OFFSET+i] == expected_outputs[i]

	assert output_list[INFO_OFFSET*2 + len(expected_outputs)+1] ==\
		   output_list[INFO_OFFSET*3 + len(expected_outputs)+3] ==\
		   "Current Command: Move Forwards at 20% power\n"


# Check that creating a robot command with a custom power works as expected
def test_custom_powers(simulate_input, catch_output):
	builtins.input = input_iterator([
		"forwards", "yes", "current command",
		"forwards p:60", "yes", "current command",
		"forwards p:80", "yes", "current command",
		"forwards p:10", "yes", "current command",
		"forwards p:1", "yes", "current command",
		"forwards p:99", "yes", "current command",
		"forwards p:20", "yes", "current command",
		"pitch up", "yes", "current command",
		"pitch up p:60", "yes", "current command",
		"pitch up p:80", "yes", "current command",
		"pitch up p:10", "yes", "current command",
		"pitch up p:1", "yes", "current command",
		"pitch up p:99", "yes", "current command",
		"pitch up p:20", "yes", "current command",
		"forwards p:50", "yes", "current command",
		"backwards p:50", "yes", "current command",
		"strafe left p:50", "yes", "current command",
		"strafe right p:50", "yes", "current command",
		"rise p:50", "yes", "current command",
		"sink p:50", "yes", "current command",
		"yaw counter clockwise p:50", "yes", "current command",
		"yaw clockwise p:50", "yes", "current command",
		"pitch up p:50", "yes", "current command",
		"pitch down p:50", "yes", "current command",
		"roll left p:50", "yes", "current command",
		"roll right p:50", "yes", "current command",
		"run thruster 0 p:50", "yes", "current command",
		"end session"
	])
	main()
	output_list = catch_output
	expected_outputs = [
		"Current Command: Move Forwards at 70% power\n",
		"Current Command: Move Forwards at 60% power\n",
		"Current Command: Move Forwards at 80% power\n",
		"Current Command: Move Forwards at 10% power\n",
		"Current Command: Move Forwards at 1% power\n",
		"Current Command: Move Forwards at 99% power\n",
		"Current Command: Move Forwards at 20% power\n",
		"Current Command: Pitch Up at 70% power\n",
		"Current Command: Pitch Up at 60% power\n",
		"Current Command: Pitch Up at 80% power\n",
		"Current Command: Pitch Up at 10% power\n",
		"Current Command: Pitch Up at 1% power\n",
		"Current Command: Pitch Up at 99% power\n",
		"Current Command: Pitch Up at 20% power\n",
		"Current Command: Move Forwards at 50% power\n",
		"Current Command: Move Backwards at 50% power\n",
		"Current Command: Strafe Left at 50% power\n",
		"Current Command: Strafe Right at 50% power\n",
		"Current Command: Rise at 50% power\n",
		"Current Command: Sink at 50% power\n",
		"Current Command: Yaw Counterclockwise at 50% power\n",
		"Current Command: Yaw Clockwise at 50% power\n",
		"Current Command: Pitch Up at 50% power\n",
		"Current Command: Pitch Down at 50% power\n",
		"Current Command: Roll Left at 50% power\n",
		"Current Command: Roll Right at 50% power\n",
		"Current Command: Run Thruster 0 at 1700\n",
	]
	for i in range(0,len(expected_outputs)):
		assert output_list[INFO_OFFSET+i] == expected_outputs[i]


# Check that creating a robot command with a custom time works as expected
def test_custom_times(simulate_input, catch_output):
	builtins.input = input_iterator([
		"forwards", "yes", "current command",
		"forwards t:6", "yes", "current command",
		"forwards t:80", "yes", "current command",
		"forwards t:1.5", "yes", "current command",
		"forwards t:1", "yes", "current command",
		"forwards t:99", "yes", "current command",
		"forwards t:892.0625", "yes", "current command",
		"forwards t:2", "yes", "current command",
		"pitch up", "yes", "current command",
		"pitch up t:6", "yes", "current command",
		"pitch up t:80", "yes", "current command",
		"pitch up t:1.5", "yes", "current command",
		"pitch up t:1", "yes", "current command",
		"pitch up t:99", "yes", "current command",
		"pitch up t:892.0625", "yes", "current command",
		"pitch up t:2", "yes", "current command",
		"forwards t:5", "yes", "current command",
		"backwards t:5", "yes", "current command",
		"strafe left t:5", "yes", "current command",
		"strafe right t:5", "yes", "current command",
		"rise t:5", "yes", "current command",
		"sink t:5", "yes", "current command",
		"yaw counter clockwise t:5", "yes", "current command",
		"yaw clockwise t:5", "yes", "current command",
		"pitch up t:5", "yes", "current command",
		"pitch down t:5", "yes", "current command",
		"roll left t:5", "yes", "current command",
		"roll right t:5", "yes", "current command",
		"end session"
	])
	main()
	output_list = catch_output
	expected_outputs = [
		"Current Command: Move Forwards at 70% power\n",
		"Current Command: Move Forwards at 70% power for 6 seconds\n",
		"Current Command: Move Forwards at 70% power for 80 seconds\n",
		"Current Command: Move Forwards at 70% power for 1.5 seconds\n",
		"Current Command: Move Forwards at 70% power for 1 seconds\n",
		"Current Command: Move Forwards at 70% power for 99 seconds\n",
		"Current Command: Move Forwards at 70% power for 892.0625 seconds\n",
		"Current Command: Move Forwards at 70% power for 2 seconds\n",
		"Current Command: Pitch Up at 70% power\n",
		"Current Command: Pitch Up at 70% power for 6 seconds\n",
		"Current Command: Pitch Up at 70% power for 80 seconds\n",
		"Current Command: Pitch Up at 70% power for 1.5 seconds\n",
		"Current Command: Pitch Up at 70% power for 1 seconds\n",
		"Current Command: Pitch Up at 70% power for 99 seconds\n",
		"Current Command: Pitch Up at 70% power for 892.0625 seconds\n",
		"Current Command: Pitch Up at 70% power for 2 seconds\n",
		"Current Command: Move Forwards at 70% power for 5 seconds\n",
		"Current Command: Move Backwards at 70% power for 5 seconds\n",
		"Current Command: Strafe Left at 70% power for 5 seconds\n",
		"Current Command: Strafe Right at 70% power for 5 seconds\n",
		"Current Command: Rise at 70% power for 5 seconds\n",
		"Current Command: Sink at 70% power for 5 seconds\n",
		"Current Command: Yaw Counterclockwise at 70% power for 5 seconds\n",
		"Current Command: Yaw Clockwise at 70% power for 5 seconds\n",
		"Current Command: Pitch Up at 70% power for 5 seconds\n",
		"Current Command: Pitch Down at 70% power for 5 seconds\n",
		"Current Command: Roll Left at 70% power for 5 seconds\n",
		"Current Command: Roll Right at 70% power for 5 seconds\n",
	]
	for i in range(0,len(expected_outputs)):
		assert output_list[INFO_OFFSET+i] == expected_outputs[i]


# Tests to make sure that every robot command can be read as expected
def test_robot_commands(simulate_input, catch_output):
	builtins.input = input_iterator([
		"forwards", "yes", "current command",
		"backwards", "yes", "current command",
		"strafe left", "yes", "current command",
		"strafe right", "yes", "current command",
		"rise", "yes", "current command",
		"sink", "yes", "current command",
		"yaw counter clockwise", "yes", "current command",
		"yaw ccw", "yes", "current command",
		"yaw clockwise", "yes", "current command",
		"yaw cw", "yes", "current command",
		"pitch up", "yes", "current command",
		"pitch down", "yes", "current command",
		"roll left", "yes", "current command",
		"roll right", "yes", "current command",
		"custom [1200, 1100, 1100, 1100, 1100, 1100, 1100, 1100]", "yes", "current command",
		"run thruster 0", "yes", "current command",
		"end session"
	])
	main()
	output_list = catch_output
	expected_outputs = [
		"Current Command: Move Forwards at 70% power\n",
		"Current Command: Move Backwards at 70% power\n",
		"Current Command: Strafe Left at 70% power\n",
		"Current Command: Strafe Right at 70% power\n",
		"Current Command: Rise at 70% power\n",
		"Current Command: Sink at 70% power\n",
		"Current Command: Yaw Counterclockwise at 70% power\n",
		"Current Command: Yaw Counterclockwise at 70% power\n",
		"Current Command: Yaw Clockwise at 70% power\n",
		"Current Command: Yaw Clockwise at 70% power\n",
		"Current Command: Pitch Up at 70% power\n",
		"Current Command: Pitch Down at 70% power\n",
		"Current Command: Roll Left at 70% power\n",
		"Current Command: Roll Right at 70% power\n",
		"Current Command: Custom pwm ['1200', '1100', '1100', '1100', '1100', '1100', '1100', '1100']\n",
		"Current Command: Run Thruster 0 at 1780\n",
	]
	for i in range(0,len(expected_outputs)):
		assert output_list[INFO_OFFSET+i] == expected_outputs[i]


# Test the custom pwm command can correctly handle custom pwms with entirely unique values, repeated values, and a time before and after.
def test_custom_pwms(simulate_input, catch_output):
	builtins.input = input_iterator([
		"custom [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900]", "yes", "current command",
		"custom [1500, 1200, 1500, 1200, 1500, 1200, 1500, 1200]", "yes", "current command",
		"custom [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900] t: 5", "yes", "current command",
		"custom t: 5 [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900]", "yes", "current command",
		"end session"])
	main()
	output_list = catch_output
	pwms = ['1500', '1400', '1300', '1200', '1100', '1250', '1550', '1900']
	repeated_pwms = ['1500', '1200', '1500', '1200', '1500', '1200', '1500', '1200']
	assert output_list[INFO_OFFSET] == f"Current Command: Custom pwm {pwms}\n"
	assert output_list[INFO_OFFSET+1] == f"Current Command: Custom pwm {repeated_pwms}\n"
	assert output_list[INFO_OFFSET+2] == f"Current Command: Custom pwm {pwms} for 5 seconds\n"
	assert output_list[INFO_OFFSET+3] == f"Current Command: Custom pwm {pwms} for 5 seconds\n"


# Checks that timed commands work properly. Makes sure timed stop command is overridden whenever a new command is run
def test_timed_commands(simulate_input, catch_output):
	builtins.input = input_iterator([
		# Test 1: Timed -> Timeout
		"forwards t: 0.5", "yes",
		"current command",
		"wait 1",
		"current command",
		# Test 2: Timed -> Timed
		"strafe left t: 1.5", "yes",
		"current command",
		"wait 1",
		"strafe right t: 1.5", "yes",
		"current command",
		"wait 1",
		"current command",
		"wait 1",
		"current command",
		# Test 3: Timed -> Untimed
		"rise t: 0.5", "yes",
		"current command",
		"sink", "yes",
		"current command",
		"wait 1",
		"current command",		
		# Test 4: Timed -> Stop -> Untimed
		"pitch up t: 0.5", "yes",
		"current command",
		"stop",
		"current command",
		"pitch down", "yes",
		"current command",
		"wait 1",
		"current command",
		"end session"])
	main()
	output_list = catch_output
	excepted_outputs = [
		# Test 1
		"Current Command: Move Forwards at 70% power for 0.5 seconds\n",
		"There is no currently active command\n",
		# Test 2
		"Current Command: Strafe Left at 70% power for 1.5 seconds\n",
		"Current Command: Strafe Right at 70% power for 1.5 seconds\n",
		"Current Command: Strafe Right at 70% power for 1.5 seconds\n",
		"There is no currently active command\n",
		# Test 3
		"Current Command: Rise at 70% power for 0.5 seconds\n",
		"Current Command: Sink at 70% power\n",
		"Current Command: Sink at 70% power\n",
		# Test 4
		"Current Command: Pitch Up at 70% power for 0.5 seconds\n",
		"There is no currently active command\n",
		"Current Command: Pitch Down at 70% power\n",
		"Current Command: Pitch Down at 70% power\n",
	]

	for i in range(0, len(excepted_outputs)):
		assert output_list[INFO_OFFSET + i] == excepted_outputs[i]
