'''
Tests input parsing for the Command Line Interface

Ways to see test results: 
	colcon test --event-handlers console_cohesion+ --parallel-workers 1
		(Avoids testing multiple ROS nodes at the same time)
		--pytest-args --packages-select pwm_cli (If I need to only run pwm_cli tests)
	pytest -v -s
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
		return next_input
	return my_input

# Used to denote the first important value of catch_output, as the info() command prints 24 times on program start
INFO_OFFSET = 24


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
	builtins.input = input_iterator(["set power ", "set power . ", "set power 101", "set power 999", "end session"])
	main()
	output_list = catch_output
	for out_num in range(0, 4):
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
	builtins.input = input_iterator([\
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


		# --- VALID INPUT TESTS ---

# Check that default power correctly updates after 'set power' is processed
def test_set_power(simulate_input, catch_output):	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


# Check that get_current_command() works as expected
def test_current_command(simulate_input, catch_output):	# TODO
	builtins.input = input_iterator([\
		"current command",\
		"forwards", "yes", "current command",\
		"forwards t:5 p:60", "yes", "current command",\
		"backwards", "yes", "current command",\
		"backwards t:5 p:60", "yes", "current command",\
		"strafe left", "yes", "current command",\
		"strafe left t: 5 p:60", "yes", "current command",\
		"strafe right", "yes", "current command",\
		"strafe right t: 5 p:60", "yes", "current command",\
		"rise", "yes", "current command",\
		"rise t: 5 p:60", "yes", "current command",\
		"sink", "yes", "current command",\
		"sink t: 5 p:60", "yes", "current command",\
		"yaw counter clockwise", "yes", "current command",\
		"yaw counter clockwise t: 5 p:60", "yes", "current command",\
		"yaw clockwise", "yes", "current command",\
		"yaw clockwise t: 5 p:60", "yes", "current command",\
		"pitch up", "yes", "current command",\
		"pitch up t: 5 p:60", "yes", "current command",\
		"pitch down", "yes", "current command",\
		"pitch down t: 5 p:60", "yes", "current command",\
		"roll left", "yes", "current command",\
		"roll left t: 5 p:60", "yes", "current command",\
		"roll right", "yes", "current command",\
		"roll right t: 5 p:60", "yes", "current command",\
		"custom [1200, 1100, 1100, 1100, 1100, 1100, 1100, 1100]", "yes", "current command",\
		"custom [1200, 1100, 1100, 1100, 1100, 1100, 1100, 1100] t: 5", "yes", "current command",\
		"set power 20", "current command",\
		"forwards", "yes", "current command",\
		"stop", "current command",\
		"forwards", "yes", "info", "current command",\
		"help", "current command",\
		"end session"\
	])
	main()
	output_list = catch_output
	expected_outputs = [
		"There is no currently active command\n",\
		"Current Command: Move Forwards at 70% power\n",\
		"Current Command: Move Forwards at 60% power for 5 seconds\n",\
		"Current Command: Move Backwards at 70% power\n",\
		"Current Command: Move Backwards at 60% power for 5 seconds\n",\
		"Current Command: Strafe Left at 70% power\n",\
		"Current Command: Strafe Left at 60% power for 5 seconds\n",\
		"Current Command: Strafe Right at 70% power\n",\
		"Current Command: Strafe Right at 60% power for 5 seconds\n",\
		"Current Command: Rise at 70% power\n",\
		"Current Command: Rise at 60% power for 5 seconds\n",\
		"Current Command: Sink at 70% power\n",\
		"Current Command: Sink at 60% power for 5 seconds\n",\
		"Current Command: Yaw Counterclockwise at 70% power\n",\
		"Current Command: Yaw Counterclockwise at 60% power for 5 seconds\n",\
		"Current Command: Yaw Clockwise at 70% power\n",\
		"Current Command: Yaw Clockwise at 60% power for 5 seconds\n",\
		"Current Command: Pitch Up at 70% power\n",\
		"Current Command: Pitch Up at 60% power for 5 seconds\n",\
		"Current Command: Pitch Down at 70% power\n",\
		"Current Command: Pitch Down at 60% power for 5 seconds\n",\
		"Current Command: Roll Left at 70% power\n",\
		"Current Command: Roll Left at 60% power for 5 seconds\n",\
		"Current Command: Roll Right at 70% power\n",\
		"Current Command: Roll Right at 60% power for 5 seconds\n",\
		"Current Command: Custom pwm ['1200', '1100', '1100', '1100', '1100', '1100', '1100', '1100']\n",\
		"Current Command: Custom pwm ['1200', '1100', '1100', '1100', '1100', '1100', '1100', '1100'] for 5 seconds\n",\
		"Set default power to 20\n",\
		"Current Command: Custom pwm ['1200', '1100', '1100', '1100', '1100', '1100', '1100', '1100'] for 5 seconds\n",\
		"Current Command: Move Forwards at 20% power\n",\
		"There is no currently active command\n",\
	]
	for i in range(0,len(expected_outputs)):
		assert output_list[INFO_OFFSET+i] == expected_outputs[i]

	assert output_list[INFO_OFFSET*2 + len(expected_outputs)+1] ==\
		   output_list[INFO_OFFSET*3 + len(expected_outputs)+3] ==\
		   "Current Command: Move Forwards at 20% power\n"



# Check that creating a robot command with a custom power works as expected
def test_custom_powers(simulate_input, catch_output):	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


# Check that creating a robot command with a custom time works as expected
def test_custom_times(simulate_input, catch_output):	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


# Tests to make sure that every robot command can be read as expected
def test_robot_commands(simulate_input, catch_output):	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


# Test the custom pwm command can correctly handle custom pwms with entirely unique values, repeated values, and a time before and after.
def test_custom_pwms(simulate_input, catch_output):
	builtins.input = input_iterator([\
		"custom [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900]", "yes", "current command",\
		"custom [1500, 1200, 1500, 1200, 1500, 1200, 1500, 1200]", "yes", "current command",\
		"custom [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900] t: 5", "yes", "current command",\
		"custom t: 5 [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900]", "yes", "current command",\
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
def test_timed_commands(simulate_input, catch_output):	# TODO
	builtins.input = input_iterator(["wait 1", "end session"])
	main()
