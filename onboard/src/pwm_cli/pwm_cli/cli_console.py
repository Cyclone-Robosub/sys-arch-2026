'''
Takes user input from the command line and publishes a pwm_cli 
'''

import time
import threading
import math

from .cli_publisher import *

cli = None
default_power = 70
timer_running = False
current_command = None
timed_command_thread = None

# pwm constants
PWM_ZERO = 1500
EMERGENCY_BRAKES = [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO]


def main():
	global current_command
	current_command = RobotCommand("Stop", default_power, -1, EMERGENCY_BRAKES)

	rclpy.init(args=None)

	global cli
	cli = CLIPublisher()

	global timed_command_thread
	global timer_running

	# Create a seperate thread to spin the heartbeat
	heartbeat_thread = threading.Thread(target=spin_heartbeat)
	heartbeat_thread.start()

	info()

	reading_input = True

	# TODO: ADD LOOP HEADING
	while (reading_input):
		user_input = input("Input a command: ").lower()

		if (user_input == "end session"):
			break

		command = translate_command(user_input)

		# if an invalid command is inputted, warn the user
		if command is None:
			print(f"{user_input} is not a valid command")
			continue

		# Valid non-robot commands should output their result
		elif isinstance(command, str):
			print(command)
		
		# A stop command should be processed immediately
		elif command.name == "Stop":
			cli.publish_pwm(command.pwm)
			current_command = RobotCommand("Stop", default_power, -1, EMERGENCY_BRAKES)
		
		# A robot command should be processed after the user confirms it was intended
		elif command.confirm_command():
			cli.publish_pwm(command.pwm)
			if (command.time != -1):
				if timed_command_thread is not None and timed_command_thread.is_alive():
					timer_running = False
					timed_command_thread.join()
				timed_command_thread = threading.Thread(target=run_command_timer,args=[command.time])
				timer_running = True
				timed_command_thread.start()
			current_command = command
	# End of while loop

	reading_input = False

	# Shut down timer thread if it exists
	if timed_command_thread is not None and timed_command_thread.is_alive():
		timer_running = False
		timed_command_thread.join()

	# Stop robot before shutting down cli
	cli.publish_pwm(EMERGENCY_BRAKES)	

	# Stop heartbeat publishing 
	# (.stop() does not exist. There are some issues with trying to stop the heartbeat thread, but it is low priority)
	# heartbeat_thread.stop()
	rclpy.shutdown()

	print("Goodbye!")


'''
Reads a string and takes the action requested or outputs a robot command
command is the string to process
returns a robot command or the result of the non-robot action taken
'''
def translate_command(command):

	if "info" in command or "help" in command:
		info()
		return ""

	global default_power
	
	# Non-Robot Commands
	if "set" in command and "power" in command:
		new_power = find_num_in_string(command[command.index("power"):])
		if new_power == None or int(new_power) > 100:
			return None
		default_power = new_power
		return f"Set default power to {new_power}\n"

	if "current" in command and "command" in command:
		return get_current_command()


	cmd = RobotCommand(power = default_power)

	# Changing settings for a given robot command
	if "power:" in command:
		power = find_num_in_string(command[command.index("power:"):])
		if power is not None and int(power) <= 100:
			cmd.power = power
		else:
			return "Invalid power inputted\n"
	elif "p:" in command:
		power = find_num_in_string(command[command.index("p:"):])
		if power is not None and int(power) <= 100:
			cmd.power = power
		else:
			return "Invalid power inputted\n"

	if "time:" in command:
		cmd.time = find_num_in_string(command[command.index("time:"):])
	elif "t:" in command:
		cmd.time = find_num_in_string(command[command.index("t:"):])
	if cmd.time is None:
		return "Invalid time inputted\n"

	# Robot Commands
	if "stop" in command:
		cmd.name = "Stop"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "forwards" in command:
		cmd.name = "Move Forwards"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "backwards" in command:
		cmd.name = "Move Backwards"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "strafe" in command and "left" in command:
		cmd.name = "Strafe Left"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "strafe" in command and "right" in command:
		cmd.name = "Strafe Right"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "rise" in command:
		cmd.name = "Rise"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "sink" in command:
		cmd.name = "Sink"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "yaw" in command and "counter" in command and "clockwise" in command:
		cmd.name = "Yaw Counterclockwise"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "yaw" in command and "clockwise" in command:
		cmd.name = "Yaw Clockwise"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "pitch" in command and "forwards" in command:
		cmd.name = "Pitch Forwards"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "pitch" in command and "backwards" in command:
		cmd.name = "Pitch Backwards"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "roll" in command and "left" in command:
		cmd.name = "Roll Left"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "roll" in command and "right" in command:
		cmd.name = "Roll Right"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd

	# custom pwm syntax: "Custom pwm [flt, frt, rlt, rrt, flb, frb, rlb, rrb]"
	if "custom" in command and '[' in command and ']' in command:
		cmd.name = "Custom pwm"
		flt = get_custom_pwm(command[command.index("["):])
		frt = get_custom_pwm(command[command.index("{flt}") + len(flt):])
		rlt = get_custom_pwm(command[command.index("{frt}") + len(frt):])
		rrt = get_custom_pwm(command[command.index("{rlt}") + len(rlt):])
		flb = get_custom_pwm(command[command.index("{rrt}") + len(rrt):])
		frb = get_custom_pwm(command[command.index("{flb}") + len(flb):])
		rlb = get_custom_pwm(command[command.index("{frb}") + len(frb):])
		rrb = get_custom_pwm(command[command.index("{rlb}") + len(rlb):])
		extra = get_custom_pwm(command[command.index("{rrb}") + len(rrb):])
		if (flt is not None and frt is not None and rlt is not None and rrt is not None 
				and flb is not None and frb is not None and rlb is not None and rrb is not None and extra is None):
			cmd.pwm = [flt, frt, rlt, rrt, flb, frb, rlb, rrb]
			return cmd

	return None

'''
prints a list of all valid commands and examples of how to use them
does not return a value
'''
def info():
	print("Note: Whitespace is ignored in command names")
	print("\n")
	print("Valid User Commands:")
	print("\t'set power {num}'\t\t changes default power for robot commands (as a percentage)")
	print("\t'current command'\t\t prints out the currently active command")
	print("\t'info' or 'help'\t\t resends this message")
	print("\t'end session'\t\t\t ends program excecution")
	print("\n")
	print("Valid Robot Commands:")
	print("\tstop | forwards | backwards | strafe left | strafe right | rise | sink |")
	print("\tyaw counter clockwise | yaw clockwise | pitch forwards | pitch backwards | roll left | roll right")
	print("\tcustom [{pwm}, {pwm}, {pwm}, {pwm}, {pwm}, {pwm}, {pwm}, {pwm}]")
	print("\n")
	print("All robot commands have optional power and time fields")
	print("'power: {num}' or 'p: {num}' for a custom power (as a percentage)")
	print("'time: {num}' or 't: {num}' for a timed command (in seconds)")
	print("\n\n")

	# Add note that default power is 70%
	# Give examples of valid commands

'''
returns string describing current command to user
'''
def get_current_command():
	global current_command
	if current_command.name == "Stop":
		return "There is no currently active command\n"
	elif current_command.time == -1:
		return f"Current Command: {current_command.name} at {current_command.power}% power\n"
	else:
		return f"Current Command: {current_command.name} for {current_command.time} seconds at {current_command.power}% power\n"


'''
Finds custom pwm value
Checks pwm is found and between 110 and 1990
returns pwm if valid else returns None
'''
def get_custom_pwm(string):
	pwm = find_num_in_string(string)
	if pwm is not None and int(pwm) >= 1100 and int(pwm) <= 1900:
		return pwm
	return None

'''
Looks through a string for the first number in it
string is the string to look through
Returns the number found, or None
'''
def find_num_in_string(string):
	started = False
	is_decimal = False
	num = ""

	for char in string:
		if char.isdigit() or (char == '.' and not is_decimal):
			num += str(char)
			if char == '.':
				is_decimal = True
			if not started:
				started = True
		elif started:
			break
	if num == "":
		return None
	return num

'''
Waits for a timer with a given duration to finish, then sends a stop command
duration is the duration the timer will wait in seconds
Does not return a value
'''
def run_command_timer(duration):
	start_time = time.time
	global timer_running
	while time.time - start_time < duration * 1000:
		if not timer_running:
			return
	global current_command
	global cli
	current_command = RobotCommand("Stop")
	cli.publish_pwm(current_command.command_dictionary()["Stop"])

def spin_heartbeat():
	rclpy.spin(HeartbeatPublisher())

		
'''
Ask user for confirmation until valid response is given
prompt is the statement asking user to confirm command
Returns True if response is yes, or False if no
'''
def confirm(prompt):
	while True:
		response = input(prompt).lower()
		if "yes" in response:
			return True
		elif "no" in response:
			return False

class RobotCommand():
	def __init__(self, name = "Stop", power = default_power, time = -1, pwm = EMERGENCY_BRAKES):
		self.name = name
		self.power = power
		self.time = time
		self.pwm = pwm
		
	# Does this work with custom powers???
	def command_dictionary(self):
		pwm_fwd = math.floor(PWM_ZERO + 400 * (default_power / 100))
		pwm_rev = math.ceil(PWM_ZERO - 400 * (default_power / 100))
		# pwm order: [flt, frt, rlt, rrt, flb, frb, rlb, rrb]
		return {
			"Stop" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Move Forwards" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_fwd, pwm_rev, pwm_fwd, pwm_rev],
			"Move Backwards" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_rev, pwm_fwd, pwm_rev, pwm_fwd],
			"Strafe Left" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_rev, pwm_rev, pwm_fwd, pwm_fwd],
			"Strafe Right" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_fwd, pwm_fwd, pwm_rev, pwm_rev],
			"Rise" : [pwm_rev, pwm_fwd, pwm_rev, pwm_fwd, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Sink" : [pwm_fwd, pwm_rev, pwm_fwd, pwm_rev, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Yaw Counterclockwise" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_rev, pwm_rev, pwm_rev, pwm_rev],
			"Yaw Clockwise" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_fwd, pwm_fwd, pwm_fwd, pwm_fwd],
			"Pitch Forwards" : [pwm_rev, pwm_rev, pwm_fwd, pwm_fwd, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Pitch Backwards" : [pwm_fwd, pwm_fwd, pwm_rev, pwm_rev, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Roll Left" : [pwm_rev, pwm_fwd, pwm_rev, pwm_fwd, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Roll Right" : [pwm_fwd, pwm_rev, pwm_fwd, pwm_rev, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO]
		}

	def confirm_command(self):
		if self.time == -1:
			return confirm(f"Are you sure you want to {self.name} at {self.power}% power until stopped? [yes/no]\n")
		else:
			return confirm(f"Are you sure you want to {self.name} at {self.power}% power for {self.time} seconds? [yes/no]\n")
		

main()