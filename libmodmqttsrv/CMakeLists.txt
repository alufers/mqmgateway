add_library(modmqttsrv
    SHARED
    config.cpp 
    config.hpp
    conv_name_parser.cpp
    conv_name_parser.hpp
    logging.cpp
    logging.hpp
    modbus_client.cpp 
    modbus_client.hpp 
    modbus_context.cpp
    modbus_context.hpp
    modbus_scheduler.cpp
    modbus_scheduler.hpp
    modbus_thread.cpp
    modbus_thread.hpp
    modbus_types.hpp
    modmqtt.cpp 
    modmqtt.hpp 
    mosquitto.cpp
    mosquitto.hpp
    mqttclient.cpp
    mqttclient.hpp
    mqttobject.cpp
    mqttobject.hpp
    register_poll.cpp
    register_poll.hpp
)

set_property(TARGET modmqttsrv PROPERTY CXX_STANDARD 17)

target_include_directories (modmqttsrv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(modmqttsrv PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(modmqttsrv PROPERTIES SOVERSION 1)

find_package(PkgConfig REQUIRED)
find_package(yaml-cpp REQUIRED)

pkg_check_modules(Mosquitto IMPORTED_TARGET libmosquitto REQUIRED)

target_link_libraries(modmqttsrv 
    PkgConfig::Mosquitto 
    yaml-cpp
    ${YAML_CPP_LIBRARIES} 
    ${Boost_LIBRARIES} 
    ${LIBMODBUS_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
)
