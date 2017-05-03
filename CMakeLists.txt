cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("cmake/HunterGate.cmake")
HunterGate(
    URL  "https://github.com/ruslo/hunter/archive/v0.18.47.tar.gz"
    SHA1 "f0c476a3a0f9edd6182936d8c4460811f112189c"
    LOCAL
)

project(yadisk-client)

set(YDCLIENT_VERSION_MAJOR 0)
set(YDCLIENT_VERSION_MINOR 1)
set(YDCLIENT_VERSION_PATCH 0)
set(YDCLIENT_VERSION_TWEAK 0)
set(YDCLIENT_VERSION ${YDCLIENT_VERSION_MAJOR}.${YDCLIENT_VERSION_MINOR}.${YDCLIENT_VERSION_PATCH})
set(YDCLIENT_VERSION_STRING "v${YDCLIENT_VERSION}")

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_EXAMPLES "Build examples" ON)

hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED system filesystem)

hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

hunter_add_package(nlohmann-json)
find_package(nlohmann-json REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB ${PROJECT_NAME}_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*) 

add_library(yadisk-client ${${PROJECT_NAME}_SOURCES})

target_link_libraries(yadisk-client
	Boost::filesystem Boost::system 
	OpenSSL::SSL OpenSSL::Crypto 
	CURL::libcurl 
	nlohmann-json::nlohmann-json
)

target_include_directories(yadisk-client PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

if(BUILD_TESTS)
	enable_testing()
	hunter_add_package(Catch)
	find_package(Catch CONFIG REQUIRED)
	file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*/*.cpp)
	add_executable(check ${TEST_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp)
	target_link_libraries(check yadisk-client Catch::Catch)
	add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes")	
endif()

if(BUILD_EXAMPLES)
	file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
	foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
		get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
		add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
		target_link_libraries(${EXAMPLE_NAME} yadisk-client)
		install(TARGETS ${EXAMPLE_NAME}
				RUNTIME DESTINATION bin
				)
	endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

install(TARGETS yadisk-client
		EXPORT yadisk-client-config
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

install(EXPORT yadisk-client-config
		NAMESPACE yadisk-client
		DESTINATION cmake
)
