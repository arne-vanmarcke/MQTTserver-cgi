cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project (MQTTCgi)

add_executable(MQTTCgi mqttcgi.c)

include_directories(/usr/include/mariadb /usr/include/mariadb/mysql)

target_link_libraries(MQTTCgi mariadb)