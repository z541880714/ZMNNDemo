cmake_minimum_required(VERSION 3.0)

project(mnn-module)
#====================================直接引入第三方 so=================================

set(LIBROOT_DIR ${MNN_DIR})

#[[
include_directories(${LIBROOT_DIR}/include/
        ${LIBROOT_DIR}/source/
        ${LIBROOT_DIR}/express/
        ${LIBROOT_DIR}/tools/
        ${LIBROOT_DIR}/codegen/
        ${LIBROOT_DIR}/schema/current/
        ${LIBROOT_DIR}/3rd_party/
        ${LIBROOT_DIR}/3rd_party/flatbuffers/include
        ${LIBROOT_DIR}/3rd_party/half
        ${LIBROOT_DIR}/3rd_party/imageHelper
        ${LIBROOT_DIR}/3rd_party/OpenCLHeaders/
        )

#设置so库的目录
# arm64-v8a   armeabi-v7a
set(SO_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../jni/arm64-v8a)
message(WARNING ===========>${SO_LIB_DIR})

add_library(MNN SHARED IMPORTED)
set_target_properties(MNN PROPERTIES IMPORTED_LOCATION ${SO_LIB_DIR}/libMNN.so)

add_library(MNN_CL SHARED IMPORTED)
set_target_properties(MNN_CL PROPERTIES IMPORTED_LOCATION ${SO_LIB_DIR}/libMNN_CL.so)

add_library(MNN_Express SHARED IMPORTED)
set_target_properties(MNN_Express PROPERTIES IMPORTED_LOCATION ${SO_LIB_DIR}/libMNN_Express.so)

add_library(MNN_GL SHARED IMPORTED)
set_target_properties(MNN_GL PROPERTIES IMPORTED_LOCATION ${SO_LIB_DIR}/libMNN_GL.so)

add_library(MNN_Vulkan SHARED IMPORTED)
set_target_properties(MNN_Vulkan PROPERTIES IMPORTED_LOCATION ${SO_LIB_DIR}/libMNN_Vulkan.so)

add_library(mnncore SHARED IMPORTED)
set_target_properties(mnncore PROPERTIES IMPORTED_LOCATION ${SO_LIB_DIR}/libmnncore.so)


find_library(log-lib log)

FILE(GLOB SOURCE_DIR *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_DIR})

target_link_libraries(myDemo
        MNN MNN_CL MNN_Express MNN_GL MNN_Vulkan mnncore
        ${log-lib}
        )
]]

include_directories(${LIBROOT_DIR}/include/
        ${LIBROOT_DIR}/source/
        ${LIBROOT_DIR}/express/
        ${LIBROOT_DIR}/tools/
        ${LIBROOT_DIR}/codegen/
        ${LIBROOT_DIR}/schema/current/
        ${LIBROOT_DIR}/3rd_party/
        ${LIBROOT_DIR}/3rd_party/flatbuffers/include
        ${LIBROOT_DIR}/3rd_party/half
        ${LIBROOT_DIR}/3rd_party/imageHelper
        ${LIBROOT_DIR}/3rd_party/OpenCLHeaders/
        )


find_library(log-lib log)
FILE(GLOB SOURCE_DIR *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_DIR})
add_subdirectory(${MNN_DIR} MNN)
target_link_libraries(${PROJECT_NAME}
        MNN
        ${log-lib}
        )