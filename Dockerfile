# hadolint global ignore=DL3006,DL3008,DL3013
FROM ros:jazzy
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

COPY src /get-started-ros2/src
WORKDIR /get-started-ros2

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install --no-install-recommends \
  ros-dev-tools \
  python3-rosdep \
  && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* "$HOME"/.cache

RUN rosdep update && rosdep install --ignore-src --from-paths src

RUN source /opt/ros/jazzy/setup.bash \
  && colcon build --cmake-args \
  --mixin release compile-commands
