# Set Module Name
SET(MODULE_NAME featurepoint-extraction-and-matching)

# message
MESSAGE( STATUS "Configuring module: ${MODULE_NAME} ...")

# Include Directories
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/thirdparty/opencv/src/opencv-4.9/build/include)

# Link Directories
LINK_DIRECTORIES(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Recursive get all files
FILE( GLOB_RECURSE ALL_FILES *.h *.inl *.c *.cpp *.mm)

# Group
GROUP_FILES(ALL_FILES ${CMAKE_CURRENT_SOURCE_DIR})

# Add library
ADD_EXECUTABLE(${MODULE_NAME} ${ALL_FILES} CMakeLists.txt)

IF(WIN32)
	TARGET_LINK_LIBRARIES(${MODULE_NAME} 
		debug ${PROJECT_SOURCE_DIR}/thirdparty/opencv/src/opencv-4.9/build/x64/vc16/lib/opencv_world490d.lib
		optimized ${PROJECT_SOURCE_DIR}/thirdparty/opencv/src/opencv-4.9/build/x64/vc16/lib/opencv_world490.lib)

	# Copy dlls &{CMAKE_BUILD_TYPE} is empty!!!
	ADD_CUSTOM_COMMAND(
		TARGET ${MODULE_NAME} PRE_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy 
		${PROJECT_SOURCE_DIR}/thirdparty/opencv/src/opencv-4.9/build/x64/vc16/bin/opencv_world490d.dll 
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/opencv_world490d.dll)

	ADD_CUSTOM_COMMAND(
		TARGET ${MODULE_NAME} PRE_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy 
		${PROJECT_SOURCE_DIR}/thirdparty/opencv/src/opencv-4.9/build/x64/vc16/bin/opencv_world490.dll 
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/opencv_world490.dll)

	# Copy opencv_videoio_ffmpeg490_64.dll
	ADD_CUSTOM_COMMAND(
		TARGET ${MODULE_NAME} PRE_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy 
		${PROJECT_SOURCE_DIR}/thirdparty/opencv/src/opencv-4.9/build/bin/opencv_videoio_ffmpeg490_64.dll 
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/opencv_videoio_ffmpeg490_64.dll)

	ADD_CUSTOM_COMMAND(
		TARGET ${MODULE_NAME} PRE_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy 
		${PROJECT_SOURCE_DIR}/thirdparty/opencv/src/opencv-4.9/build/bin/opencv_videoio_ffmpeg490_64.dll 
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/opencv_videoio_ffmpeg490_64.dll)
ENDIF()

# Set Folder
SET_TARGET_PROPERTIES(${MODULE_NAME} PROPERTIES FOLDER "")

# Message
MESSAGE(STATUS "Configure success!")
