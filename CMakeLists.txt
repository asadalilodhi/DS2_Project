cmake_minimum_required(VERSION 3.10)
project(EventTrafficPredictor)

set(CMAKE_CXX_STANDARD 17)

# 1. First find and setup dependencies
include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

# 2. cURL configuration
set(CURL_INCLUDE_DIR "C:/curl/curl-8.13.0_1-win64-mingw/include")
set(CURL_LIBRARY "C:/curl/curl-8.13.0_1-win64-mingw/lib/libcurl.a")

# 3. Create your executable
add_executable(traffic_system
    src/main.cpp
    src/datastructures/IntervalTree.cpp
    src/TrafficData.cpp
    src/Graph.cpp

)

# 4. Include directories
target_include_directories(traffic_system PRIVATE
    ${JSON_INCLUDE_DIR}       # For json.hpp
    ${CURL_INCLUDE_DIR}       # For curl/curl.h
    ${CMAKE_SOURCE_DIR}/src   # For local headers
)

# 5. Link libraries
# target_link_libraries(traffic_system PRIVATE
#     nlohmann_json::nlohmann_json
#     ${CURL_LIBRARY}


# )
target_link_libraries(traffic_system PRIVATE
    ${CURL_LIBRARY}
    nlohmann_json::nlohmann_json
    ws2_32  # Windows sockets
    wldap32 # Windows LDAP
    crypt32 # Crypto API (may be needed)
    normaliz # For Unicode support
    # for MinGW:
    -lws2_32
    -lwldap32
)
