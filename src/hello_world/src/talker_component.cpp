// Copyright 2014 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <cstdio>

#include <chrono>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace hello_world {

class TalkerComponent : public rclcpp::Node {
 public:
  // コンストラクター引数をNodeOptionsに変更
  explicit TalkerComponent(const rclcpp::NodeOptions& options)
      : Node("talker_component", options), count_(0) {
    auto publish_message = [this]() -> void {
      // ゼロコピーのためには，送信するメッセージがUniquePtrであることが大事
      // publish関数自体はメッセージの参照も受け取るが，その場合はコピーが発生する
      auto msg = std::make_unique<std_msgs::msg::String>();
      msg->data = "Hello World! " + std::to_string(count_++);

      RCLCPP_INFO(this->get_logger(), "[%p] %s", msg.get(), msg->data.c_str());
      // UniquePtrなのでstd::move()でmoveする
      pub_->publish(std::move(msg));
    };

    rclcpp::QoS qos(rclcpp::KeepLast(10));
    pub_ = create_publisher<std_msgs::msg::String>("chatter", qos);
    timer_ = create_wall_timer(std::chrono::seconds(1), publish_message);
  }

 private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  uint32_t count_;
};

}  // namespace hello_world

// クラスローダーにコンポーネントを登録
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(hello_world::TalkerComponent)
