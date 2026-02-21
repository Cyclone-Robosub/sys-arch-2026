'''
Tests input parsing for the Command Line Interface

Ways to see test results: 
	colcon test --event-handlers console_cohesion+
		--pytest-args --packages-select pwm_cli (If I need to only run pwm_cli tests)
	pytest -v -s
'''
import builtins
import pytest


'''
Pass by parameter for any tests that need to override input()
Stores default input() function to reset when test is finished running
'''
@pytest.fixture
def simulate_input():
	store_input = input
	yield
	builtins.input = store_input


# --- BEGIN TESTS ---

def test_example_input(simulate_input):
	builtins.input = lambda: "Overriding input() with a lambda"
	output = input()
	assert output == "Overriding input() with a lambda"


def test_multiple_input_lambda():
	builtins.input = lambda: {"Input 1" : "This is input 1", "Input 2" : "This is input 2"}
	input1 = input()["Input 1"]
	input2 = input()["Input 2"]
	assert input1 == "This is input 1"
	assert input2 == "This is input 2"

