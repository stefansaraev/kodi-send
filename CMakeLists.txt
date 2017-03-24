cmake_minimum_required(VERSION 2.8)
project(kodi-send LANGUAGES CXX)

add_executable(kodi-send kodi-send.cpp)

install(TARGETS kodi-send DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
