# Use the base image that has ros and pytorch pre-installed
FROM everything:l4t-r36.4.7

# Set environment variables (replacing -e or --env)
ENV NVIDIA_DRIVER_CAPABILITIES=compute,utility,graphics
ENV PULSE_SERVER=unix:/run/user/1000/pulse/native

# Set the working directory (replacing the manual cd)
WORKDIR /root/sys-arch-2026

RUN apt update && apt install -y \
    ros-jazzy-rosbridge-suite 
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
RUN echo "source /root/sys-arch-2026/install/setup.bash" >> ~/.bashrc

# Python packages
RUN pip install matplotlib
RUN pip install torchvision==0.23.0