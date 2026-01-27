# `dvl`

## What is it?
[comment]: # (TODO: provide a brief summary of the package)

## How do I use it?
[comment]: # (TODO: provide a summary of the steps to use the node. In this case, that's probably just a summary of the things that the node publishes, and the services it provides.)
The package is called `dvl` and the node is called `dvl`, so to run it type `ros2 run dvl dvl`.

## What nodes/topics/services does depend on?
[comment]: # (TODO: add any dependencies from other packages. This means any nodes that it expects to be running, any topics it subscribes to, or any services that it calls. If there aren't any, put "none.")
- Nodes: 
- Topics:
- Services:

## custom data types 
[comment]: # (TODO: move the following to the custom interfaces README file, following the format used there)

VR\
    TwistWithCovariance.msg: float vx = 0, vy = 0, vx = 0, covariance = 0\
    Bool.msg: bool valid = false\
    UInt8.msg : uint8_t status = 0\
    the later fields are kinda iffy bc jazzy doesn't really have them separate\
    Float32.msg : altitude = 0\
    Float32.msg : fom = 0\
    Float32MultiArray.msg: time_of_validity = 0, time_of_transmission = 0, 
    time = 0\
DRR\
    Pose.msg: float x = 0, y = 0, z = 0, roll = 0, pitch = 0, yaw = 0\
    Bool.msg : bool status = false\
    Float32.msg : float time_stamp = 0\
    Float32.msg : pos_std = 0