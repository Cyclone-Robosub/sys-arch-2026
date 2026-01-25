'''
Tests input parsing for the Command Line Interface

Ways to see test results: 
	colcon test --event-handlers console_cohesion+
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




