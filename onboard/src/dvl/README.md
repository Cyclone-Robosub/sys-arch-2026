custom data types 
VR
    TwistWithCovariance.msg: float vx = 0, vy = 0, vx = 0, covariance = 0
    Bool.msg: bool valid = false
    UInt8.msg : uint8_t status = 0
    // the later fields are kinda iffy bc jazzy doesn't really have them separate
    Float32.msg : altitude = 0
    Float32.msg : fom = 0
    Float32MultiArray.msg: time_of_validity = 0, time_of_transmission = 0, time = 0
    


DRR
    Pose.msg: float x = 0, y = 0, z = 0, roll = 0, pitch = 0, yaw = 0
    Bool.msg : bool status = false
    Float32.msg : float time_stamp = 0
    Float32.msg : pos_std = 0

