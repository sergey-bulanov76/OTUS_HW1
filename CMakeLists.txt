cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
	project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}  LANGUAGES CXX)
else()
	project(ip_filter VERSION 0.0.1  LANGUAGES CXX)
endif()

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/gootest"
    "gootest"
)

add_executable(main_ip_filter main.cpp)
add_library(ip_filter ip_filter.cpp)
add_executable(gltest gtests.cpp)

set_target_properties(main_ip_filter ip_filter gltest PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(main_ip_filter PRIVATE
    ip_filter
)

target_link_libraries(gltest PRIVATE
    ip_filter gtest
)

if (MSVC)
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    target_compile_options(main_ip_filter PRIVATE
            /W4
    )
    target_compile_options(ip_filter PRIVATE
            /W4
    )
    target_compile_options(gltest PRIVATE
            /W4
    )
else()
    target_compile_options(main_ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gltest PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS main_ip_filter gltest RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT azbyx@inbox.ru)

include(CPack)

enable_testing()

add_test(gltest gltest)
