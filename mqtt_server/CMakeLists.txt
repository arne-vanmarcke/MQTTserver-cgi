cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project (MQTTServer)

add_executable(MQTTServer mqttServer.c)

include_directories(/usr/include/mariadb /usr/include/mariadb/mysql)

target_link_libraries(MQTTServer paho-mqtt3c mariadb)