#include <catch2/catch_all.hpp>
#include "mockedserver.hpp"
#include "defaults.hpp"

static const std::string config = R"(
modbus:
  networks:
    - name: tcptest
      address: localhost
      port: 501
mqtt:
  client_id: mqtt_test
  broker:
    host: localhost
  objects:
    - topic: test_switch
      commands:
        - name: set
          register: tcptest.1.2
          register_type: holding
      state:
        register: tcptest.1.2
        register_type: holding
)";

TEST_CASE ("Holding register valid write") {
    MockedModMqttServerThread server(config);
    server.setModbusRegisterValue("tcptest", 1, 2, modmqttd::RegisterType::HOLDING, 0);
    server.start();

    server.waitForPublish("test_switch/availability", REGWAIT_MSEC);
    REQUIRE(server.mqttValue("test_switch/availability") == "1");
    server.waitForPublish("test_switch/state", REGWAIT_MSEC);

    server.publish("test_switch/set", "32");

    server.waitForPublish("test_switch/state", REGWAIT_MSEC);
    REQUIRE(server.mqttValue("test_switch/state") == "32");

    server.stop();
}

TEST_CASE ("Coil register valid write") {
    MockedModMqttServerThread server(config);
    server.setModbusRegisterValue("tcptest", 1, 2, modmqttd::RegisterType::COIL, 0);
    server.start();

    server.waitForPublish("test_switch/availability", REGWAIT_MSEC);
    REQUIRE(server.mqttValue("test_switch/availability") == "1");
    server.waitForPublish("test_switch/state", REGWAIT_MSEC);

    server.publish("test_switch/set", "1");

    server.waitForPublish("test_switch/state", REGWAIT_MSEC);
    REQUIRE(server.mqttValue("test_switch/state") == "1");

    server.stop();
}

TEST_CASE ("Mqtt invalid value should not crash server") {
    MockedModMqttServerThread server(config);
    server.setModbusRegisterValue("tcptest", 1, 2, modmqttd::RegisterType::COIL, 0);
    server.start();


    server.waitForPublish("test_switch/availability", REGWAIT_MSEC);
    REQUIRE(server.mqttValue("test_switch/availability") == "1");
    server.waitForPublish("test_switch/state", REGWAIT_MSEC);

    server.publish("test_switch/set", "hello, world!");
    server.publish("test_switch/set", "1");
    server.waitForPublish("test_switch/state", REGWAIT_MSEC);
    REQUIRE(server.mqttValue("test_switch/state") == "1");

    server.stop();
}
