'''
Takes user input from the command line and publishes a pwm_cli 
'''

import time
import threading
import math

from .cli_publisher import *

# Global variables
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
	global default_power
	current_command = RobotCommand("Stop", default_power, -1, EMERGENCY_BRAKES)

	rclpy.init(args=None)

	global cli
	cli = CLIPublisher()

	global timed_command_thread
	global timer_running

	# Create a seperate thread to spin the heartbeat
	heartbeat_thread = threading.Thread(name="heartbeat_thread", target=spin_heartbeat)
	heartbeat_thread.start()

	# Prints usage info to screen
	info()

	reading_input = True

	'''
	Parses user input and takes action or translates into RobotCommand
		If action is taken, the result is printed to the screen
		If a RobotCommand is created, after confirmation the relevant pwms are published
		Exception is the 'Stop' command, which is a RobotCommand that gets processed immediately
	Ends excecution when the user types 'end session'
	'''
	while (reading_input):
		user_input = input("Input a command: ").lower()

		if (user_input == "end session"):
			break

		# Check whether user input is a valid command
		command = translate_command(user_input)

		# if an invalid command is inputted, warn the user
		if command is None:
			print(f"{user_input} is not a valid command. Type 'help' for valid commands.")
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
				# TODO: Only stops a previous timed command if another timed command is being run. Needs to also shut down prev with an untimed command
				if timed_command_thread is not None and timed_command_thread.is_alive():
					timer_running = False
					timed_command_thread.join()
				timed_command_thread = threading.Thread(name="timed_command_thread", target=run_command_timer, args=[command.time])
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
			return "Invalid default power inputted\n"
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
	if "pitch" in command and "up" in command:
		cmd.name = "Pitch Up"
		cmd.pwm = cmd.command_dictionary()[f"{cmd.name}"]
		return cmd
	if "pitch" in command and "down" in command:
		cmd.name = "Pitch Down"
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

		# Let the substring be the command starting that the opening square bracket
		ss = command[command.index("["):]
		# Find the first pwm
		flt = get_custom_pwm(ss)

		# For each following pwm, search for the next pwm in the substring starting after the previous pwm
		ss = ss[ss.index(f"{flt}") + len(flt):]
		frt = get_custom_pwm(ss)

		ss = ss[ss.index(f"{frt}") + len(frt):]
		rlt = get_custom_pwm(ss)

		ss = ss[ss.index(f"{rlt}") + len(rlt):]
		rrt = get_custom_pwm(ss)

		ss = ss[ss.index(f"{rrt}") + len(rrt):]
		flb = get_custom_pwm(ss)

		ss = ss[ss.index(f"{flb}") + len(flb):]
		frb = get_custom_pwm(ss)

		ss = ss[ss.index(f"{frb}") + len(frb):]
		rlb = get_custom_pwm(ss)

		ss = ss[ss.index(f"{rlb}") + len(rlb):]
		rrb = get_custom_pwm(ss)

		ss = ss[ss.index(f"{rrb}") + len(rrb):]
		extra = get_custom_pwm(ss)

		if (flt is not None and frt is not None and rlt is not None and rrt is not None 
				and flb is not None and frb is not None and rlb is not None and rrb is not None and extra is None):
			cmd.pwm = [flt, frt, rlt, rrt, flb, frb, rlb, rrb]
			return cmd

	return None

'''
Prints a list of all valid commands and examples of how to use them
Does not return a value
'''
def info():
	print("Notes:")
	print("\tWhitespace is ignored in command names")
	print("\tDefault power is 70%")
	print("\n")
	print("Valid User Commands:")
	print("\t'set power {num}'\t\t changes default power for robot commands (as a percentage)")
	print("\t'current command'\t\t prints out the currently active command")
	print("\t'info' or 'help'\t\t resends this message")
	print("\t'end session'\t\t\t ends program excecution")
	print("\n")
	print("Valid Robot Commands:")
	print("\tstop | forwards | backwards | strafe left | strafe right | rise | sink |")
	print("\tyaw counter clockwise | yaw clockwise | pitch up | pitch down | roll left | roll right")
	print("\tcustom [{pwm}, {pwm}, {pwm}, {pwm}, {pwm}, {pwm}, {pwm}, {pwm}]")
	print("\n")
	print("All robot commands have optional power and time fields")
	print("\t'power: {num}' or 'p: {num}' for a custom power (as a percentage)")
	print("\t'time: {num}' or 't: {num}' for a timed command (in seconds)")
	print("\n")
	print("Examples:")
	print("\tForwards p:50 t: 10\t\tForwards at 50% power for 10 seconds")
	print("\tstrafe-left time: 3\t\tStrafe Left at default power for 3 seconds")
	print("\tROLL_RIGHT power: 80\t\tRoll Right at 80% power until stopped")

	print("\n\n")

'''
Describes the currently running RobotCommand, or says no commands are running
returns a string describing current command to user
'''
def get_current_command():
	global current_command
	if current_command.name == "Stop":
		return "There is no currently active command\n"
	
	# Current command string start is dependent on whether the command is a custom pwm
	str_start = f"Current Command: Custom pwm {current_command.pwm}" \
				if current_command.name == "Custom pwm" \
				else f"Current Command: {current_command.name} at {current_command.power}% power"
	
	# Current command string end is dependent on whether the command is timed
	str_end = "\n" if current_command.time == -1 else f" for {current_command.time} seconds"

	return str_start + str_end


'''
Uses find_num_in_string() to look for a valid pwm value (between 1100 and 1900)
string is the string to look through
returns pwm if valid, or None otherwise
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
	has_decimal_point = False
	num = ""

	for char in string:
		if char.isdigit() or (char == '.' and not has_decimal_point):
			num += str(char)
			if char == '.':
				has_decimal_point = True
			if not started:
				started = True
		elif started:
			break
	if num == "" or num == ".":
		return None
	return num

'''
Waits for a timer with a given duration to finish, then sends a stop command
	While waiting, checks whether it needs to terminate early without publishing
duration is the duration the timer will wait in seconds
Does not return a value
'''
def run_command_timer(duration):
	start_time = time.time()
	global timer_running
	while time.time() - start_time < float(duration):
		if not timer_running:
			return
	global current_command
	global cli
	current_command = RobotCommand("Stop")
	cli.publish_pwm(current_command.command_dictionary()["Stop"])

'''
Spins the HeartbeatPublisher
Used as a threading target, as thread(rclpy.spin) crashes program
'''
def spin_heartbeat():
	while (not rclpy.ok):
		pass
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


'''
Used to store the name, power, time, and pwm set for a thruster command
name is the name of the command
power is the percent of full power the command should run at (0-100%)
time is the amount of the time the command should run for, or -1 if it is untimed
pwm is the set of 8 pwms to be sent to the thrusters
'''
class RobotCommand():
	def __init__(self, name = "Stop", power = default_power, time = -1, pwm = EMERGENCY_BRAKES):
		self.name = name
		self.power = power
		self.time = time
		self.pwm = pwm
	
	'''
	Calculates the pwm sets for all commands using the RobotCommand's power
	Returns a dictionary with all calculated pwm sets obtained via their name
	'''
	# NOTE: Could be made more efficient by remaking to check self.name and return only that set
	def command_dictionary(self):
		pwm_fwd = math.floor(PWM_ZERO + 400 * (int(self.power) / 100))
		pwm_rev = math.ceil(PWM_ZERO - 400 * (int(self.power) / 100))
		# pwm order: [flt, frt, rlt, rrt, flb, frb, rlb, rrb]
		return {
			"Stop" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Move Forwards" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_fwd, pwm_rev, pwm_fwd, pwm_rev],
			"Move Backwards" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_rev, pwm_fwd, pwm_rev, pwm_fwd],
			"Strafe Left" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_rev, pwm_rev, pwm_fwd, pwm_fwd],
			"Strafe Right" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_fwd, pwm_fwd, pwm_rev, pwm_rev],
			"Rise" : [pwm_fwd, pwm_rev, pwm_fwd, pwm_rev, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Sink" : [pwm_rev, pwm_fwd, pwm_rev, pwm_fwd, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Yaw Counterclockwise" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_rev, pwm_rev, pwm_rev, pwm_rev],
			"Yaw Clockwise" : [PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO, pwm_fwd, pwm_fwd, pwm_fwd, pwm_fwd],
			"Pitch Up" : [pwm_fwd, pwm_rev, pwm_rev, pwm_fwd, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Pitch Down" : [pwm_rev, pwm_fwd, pwm_fwd, pwm_rev, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Roll Left" : [pwm_rev, pwm_rev, pwm_rev, pwm_rev, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO],
			"Roll Right" : [pwm_fwd, pwm_fwd, pwm_fwd, pwm_fwd, PWM_ZERO, PWM_ZERO, PWM_ZERO, PWM_ZERO]
		}

	'''
	Prints a confirmation message to screen and waits for the user to respond 'yes' or 'no'
	self is the RobotCommand that needs to be confirmed
	Returns whether the command should be run
	'''
	def confirm_command(self):
		# Confirmation string start is dependent on whether the command is a custom pwm
		str_start = f"Are you sure you want to run the Custom pwm {self.pwm}" \
					if self.name == "Custom pwm" \
					else f"Are you sure you want to {self.name} at {self.power}% power"
		# Confirmation string end is dependent on whether the command is timed
		str_end = " until stopped? [yes/no]\n" if self.time == -1 else f" for {self.time} seconds? [yes/no]\n"
		confirm_str = str_start + str_end

		return confirm(confirm_str)