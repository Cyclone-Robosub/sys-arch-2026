# `package_name`

## What is it?
Provide an overview of the package. Specify what it does and how it integrates with the rest of our system, and and provide a brief overview of how it works on a high level.

## How do I use it?
Provide the necessary instructions to interact with the project from a user (not developer) perspective. For example, if your package has a user interface, specify valid inputs and the corresponding behaviour/output. Specify any common error messages or user mistakes, and resolutions.

Provide launch instructions for each node in the package (i.e. `ros2 run package_name node_name` or a launch file instruction).

## What topics/services/actions does the package use for input?
This is for topics that the package subscribes to, services that it responds to when called, and actions that it responds to and performs as a server. List them and provide a brief description of what they mean and are used for.
- Topics:
    - `topic_name`: description
    - `topic_name`: description
- Services:
    - `service_name`: description
    - `service_name`: description
- Actons;
    - `action_name`: description
    - `action_name`: description

## What topics/services/actions does the package use for output?
This is for topics that the package publishes to, services that it calls, and actions that it requests as a client. List them and provide a brief description of what they meand and are used for.
- Topics:
    - `topic_name`: description
    - `topic_name`: description
- Services:
    - `service_name`: description
    - `service_name`: description
- Actions:
    - `action_name`: description
    - `action_name`: description

## What custom message types or libraries does the package use?
This is the place to list all custom messages, services, actions, or libraries (from `/core/src`) that are used in the project. An example of a custom message is `Gamepad.msg`; an example of a custom service is `ControlMode.srv`; an example of of a custom library is `fd_interface`. This provides an easy way to check for breaking changes when we update our API. A simple list sufficies here.
- Messages:
    - `message_type`
    - `message_type`
- Services:
    - `service_type`
    - `service_type`
- Actions:
    - `action_type`
    - `action_type`
- Libraries:
    - `library`
    - `library`

## Notes (Optional)
If there is any extra information that would be useful for a fellow team member to understand the project, include it here.