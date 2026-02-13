'''
Tests ros publishing for the Command Line Interface

Ways to see test results: 
	colcon test --event-handlers console_cohesion+
	pytest -v -s
'''

import pytest
import rclpy
import time

from pwm_cli.cli_console import *
from pwm_cli.cli_publisher import *


'''
Initializes ROS before running any rests, then shuts it down when finished testing
'''
@pytest.fixture(scope='module')
def init_ros():
	rclpy.init()
	yield
	rclpy.shutdown()


'''
Pass by parameter for any tests working with the HeartbeatPublisher
Creates a HeartbeatPublisher and passes it through, then destroys after use
'''
@pytest.fixture
def setup_heartbeat(init_ros):
	heartbeat = HeartbeatPublisher()
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


# --- HELPER FUNCTIONS ---

'''
Wraps time.time()
Used to prevent error with lambda not recognizing time.time()
'''
def get_time():
	return time.time()


# --- BEGIN TESTS ---
	# --- NOTE ---
		# Most tests should rely on setup_publish_pwm(),
		# but at least a couple tests should exist that actually set up a subscriber

# Makes sure that publish_pwm pytest fixture works properly
def test_basic_ros(setup_publish_pwm):
	cli = setup_publish_pwm
	assert cli.publish_pwm([1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]) == [1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]


# Test that publishing to cli_heartbeat is recieved every 0.25 seconds
def test_heartbeat(setup_heartbeat):
	heartbeat = setup_heartbeat
	msg = True
	recieve_times = []

	subscriber = heartbeat.create_subscription(Bool, "cli_heartbeat", lambda msg: recieve_times.append(get_time()), 10)

	# Runs until it publishes and recieves 10 messages on ROS
	for x in range(0, 20):
		rclpy.spin_once(heartbeat, timeout_sec=0.3)

	# Check that >90% of messages were recieved
	assert len(recieve_times) == 10

	# Check that all messages are within one second of each other
	for time in range(len(recieve_times) - 1):
		assert recieve_times[time + 1] - recieve_times[time] < 1

	heartbeat.destroy_subscription(subscriber)



# WARNING: Waiting on up-to-date info on the pwm sets, so not all pwm sets listed are accurate
def test_untimed_default_power_pwms(setup_publish_pwm):
	publisher = setup_publish_pwm
	STOP = 1500
	FWD = 1780
	REV = 1220

	command = RobotCommand("Stop")
	command.pwm = command.command_dictionary()["Stop"]
	assert publisher.publish_pwm(command.pwm) == [STOP, STOP, STOP, STOP, STOP, STOP, STOP, STOP]

	command = RobotCommand("Move Forwards")
	command.pwm = command.command_dictionary()["Move Forwards"]
	assert publisher.publish_pwm(command.pwm) == [STOP, STOP, STOP, STOP, FWD, REV, FWD, REV]

	command = RobotCommand("Move Backwards")
	command.pwm = command.command_dictionary()["Move Backwards"]
	assert publisher.publish_pwm(command.pwm) == [STOP, STOP, STOP, STOP, REV, FWD, REV, FWD]

	command = RobotCommand("Strafe Left")
	command.pwm = command.command_dictionary()["Strafe Left"]
	assert publisher.publish_pwm(command.pwm) == [STOP, STOP, STOP, STOP, REV, REV, FWD, FWD]

	command = RobotCommand("Strafe Right")
	command.pwm = command.command_dictionary()["Strafe Right"]
	assert publisher.publish_pwm(command.pwm) == [STOP, STOP, STOP, STOP, FWD, FWD, REV, REV]

	command = RobotCommand("Rise")
	command.pwm = command.command_dictionary()["Rise"]
	assert publisher.publish_pwm(command.pwm) == [REV, FWD, REV, FWD, STOP, STOP, STOP, STOP]

	command = RobotCommand("Sink")
	command.pwm = command.command_dictionary()["Sink"]
	assert publisher.publish_pwm(command.pwm) == [FWD, REV, FWD, REV, STOP, STOP, STOP, STOP]

	command = RobotCommand("Yaw Counterclockwise")
	command.pwm = command.command_dictionary()["Yaw Counterclockwise"]
	assert publisher.publish_pwm(command.pwm) == [STOP, STOP, STOP, STOP, REV, REV, REV, REV]

	command = RobotCommand("Yaw Clockwise")
	command.pwm = command.command_dictionary()["Yaw Clockwise"]
	assert publisher.publish_pwm(command.pwm) == [STOP, STOP, STOP, STOP, FWD, FWD, FWD, FWD]

	command = RobotCommand("Pitch Forwards")
	command.pwm = command.command_dictionary()["Pitch Forwards"]
	assert publisher.publish_pwm(command.pwm) == [REV, REV, FWD, FWD, STOP, STOP, STOP, STOP]

	command = RobotCommand("Pitch Backwards")
	command.pwm = command.command_dictionary()["Pitch Backwards"]
	assert publisher.publish_pwm(command.pwm) == [FWD, FWD, REV, REV, STOP, STOP, STOP, STOP]

	command = RobotCommand("Roll Left")
	command.pwm = command.command_dictionary()["Roll Left"]
	assert publisher.publish_pwm(command.pwm) == [REV, FWD, REV, FWD, STOP, STOP, STOP, STOP]

	command = RobotCommand("Roll Right")
	command.pwm = command.command_dictionary()["Roll Right"]
	assert publisher.publish_pwm(command.pwm) == [FWD, REV, FWD, REV, STOP, STOP, STOP, STOP]
