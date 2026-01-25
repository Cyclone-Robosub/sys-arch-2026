'''
Tests ros publishing for the Command Line Interface

Ways to see test results: 
	colcon test --event-handlers console_cohesion+
	pytest -v -s
'''

import pytest
import rclpy

from pwm_cli.cli_publisher import *


'''
Initializes ROS before running any rests, then shuts it down when finished testing
'''
@pytest.fixture(scope='module')
def init_ros():
	rclpy.init()
	print("ROS Initialized")
	yield
	rclpy.shutdown()
	print("ROS Shut down")


'''
Pass by parameter for any tests working with the HeartbeatPublisher
Creates a HeartbeatPublisher and passes it through, then destroys after use
'''
@pytest.fixture
def setup_heartbeat(init_ros):
	heartbeat = HeartbeatPublisher()
	rclpy.spin(heartbeat)
	yield heartbeat
	heartbeat.destroy_node()


'''
Pass by parameter for any tests working with the CLIPublisher
Creates a CLIPublisher and passes it through, then destroys after use
'''
@pytest.fixture
def setup_console(init_ros):
	cli = CLIPublisher()
	yield cli
	cli.destroy_node()

'''
Pass by parameter for any tests that need to test publish_pwm()
Uses setup_console() to create a CLIPublisher, then stores and overrides publish_pwm
'''
@pytest.fixture
def setup_publish_pwm(setup_console):
	cli = setup_console
	store_publish_pwm = cli.publish_pwm
	cli.publish_pwm = lambda pwm: pwm
	yield cli
	cli.publish_pwm = store_publish_pwm


# --- BEGIN TESTS ---
	# --- NOTE ---
		# Most tests should rely on setup_publish_pwm(),
		# but at least a couple tests should exist that actually set up a subscriber

def test_basic_ros(setup_publish_pwm):
	cli = setup_publish_pwm
	assert cli.publish_pwm([1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]) == [1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]
