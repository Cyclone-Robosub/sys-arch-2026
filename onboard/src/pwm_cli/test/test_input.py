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


# Tests that cli_console can handle invalid power inputs
def test_invalid_powers(simulate_input, catch_output):
	builtins.input = input_iterator(["power: ", "p: ", "power: . ", "p: . ", "p: 999", "end session"])
	main()
	output_list = catch_output
	for out_num in range(0, 5):
		assert output_list[INFO_OFFSET + out_num] == "Invalid power inputted\n"


		# --- VALID INPUT TESTS ---

# Check that default power correctly updates after 'set power' is processed
def test_set_power(simulate_input, catch_output):
	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


# DESCRIPTION
def test_current_command(simulate_input, catch_output):
	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


# DESCRIPTION
def test_custom_powers(simulate_input, catch_output):
	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


# DESCRIPTION
def test_custom_times(simulate_input, catch_output):
	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


# DESCRIPTION
def test_robot_commands(simulate_input, catch_output):
	# TODO
	builtins.input = input_iterator(["", "end session"])
	main()


def test_repeated_custom_pwm(simulate_input, catch_output):
	builtins.input = input_iterator(["custom [1500, 1200, 1500, 1200, 1500, 1200, 1500, 1200]", 
								  	 "yes", "current command", "end session"])
	main()
	output_list = catch_output
	pwms = ['1500', '1200', '1500', '1200', '1500', '1200', '1500', '1200']
	assert output_list[INFO_OFFSET] == f"Current Command: Custom pwm {pwms}\n"


# DESCRIPTION
def test_timed_commands(simulate_input, catch_output):
	# TODO
	builtins.input = input_iterator(["wait 1", "end session"])
	main()
