cmake_minimum_required(VERSION 2.6)
project(ircbot)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D__LINUX")

add_executable(
ircbot

src/handlermanager.cpp
src/ircbot.cpp
src/main.cpp
src/socket.cpp
src/util.cpp

src/handlers/generic.cpp
src/handlers/join.cpp
src/handlers/nick.cpp
src/handlers/notice.cpp
src/handlers/part.cpp
src/handlers/ping.cpp
src/handlers/privmsg.cpp
src/handlers/quit.cpp
src/handlers/topic.cpp
src/handlers/welcome.cpp
)


target_link_libraries(ircbot)
install(TARGETS ircbot RUNTIME DESTINATION bin)