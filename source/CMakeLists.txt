add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

add_executable(try try.cpp)

target_link_libraries(try ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(try glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS try DESTINATION .)

add_executable(animation animation.cpp)

target_link_libraries(animation ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(animation glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS animation DESTINATION .)