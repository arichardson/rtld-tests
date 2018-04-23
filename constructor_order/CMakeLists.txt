
add_executable(constructor_order constructor_order.cpp)

add_library(constructor_order_lib SHARED constructor_order.cpp)
target_compile_definitions(constructor_order_lib PRIVATE -DVALID_SHLIB)

add_executable(constructor_order_with_lib constructor_order.cpp)
target_compile_definitions(constructor_order_lib PRIVATE -DUSE_SHLIB)
target_link_libraries(constructor_order_with_lib constructor_order_lib)

install(TARGETS constructor_order constructor_order_with_lib constructor_order_lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
