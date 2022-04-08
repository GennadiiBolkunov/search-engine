CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

add_executable(search_engine main.cpp ../include/converter_json.h converter_json.cpp ../include/inverted_index.h inverted_index.cpp tests.cpp ../include/counting_dictionary.h ../include/search_server.h ../include/request_word_set.h search_server.cpp ../include/relative_index.h)
target_include_directories(search_engine PUBLIC ${INCLUDE_DIR})

target_link_libraries(search_engine ${Boost_LIBRARIES})
if (MINGW)
    target_link_libraries(search_engine PUBLIC ws2_32)
endif()

set(JSON_BuildTests OFF)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
enable_testing()

target_link_libraries(search_engine PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(search_engine)


