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
Used to override input() function for testing the main loop of cli_console
'''
def input_iterator(outputs: list[str]):
	iterator = iter(outputs)
	def my_input(input = None):
		return next(iterator)
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


# Test that the custom pwm command can handle repeated PWMS.
def test_repeated_custom_pwms(simulate_input, catch_output):
	builtins.input = input_iterator(["custom [1500, 1200, 1500, 1200, 1500, 1200, 1500, 1200]", "yes", "current command", "end session"])
	main()
	output_list = catch_output
	pwms = ['1500', '1200', '1500', '1200', '1500', '1200', '1500', '1200']
	assert output_list[INFO_OFFSET] == f"Current Command: Custom pwm {pwms}\n"

def test_custom_pwms(simulate_input, catch_output):
	builtins.input = input_iterator([\
		"custom [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900]", "yes", "current command",\
		"custom [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900] t: 5", "yes", "current command",\
		"custom t: 5 [1500, 1400, 1300, 1200, 1100, 1250, 1550, 1900]", "yes", "current command",\
		"end session"])
	main()
	output_list = catch_output
	pwms = ['1500', '1400', '1300', '1200', '1100', '1250', '1550', '1900']
	assert output_list[INFO_OFFSET] == f"Current Command: Custom pwm {pwms}\n"
	assert output_list[INFO_OFFSET+1] == f"Current Command: Custom pwm {pwms} for 5 seconds\n"
	assert output_list[INFO_OFFSET+2] == f"Current Command: Custom pwm {pwms} for 5 seconds\n"