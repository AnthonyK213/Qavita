aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} QAVITA_SRC)

set(
  PROJECT_SOURCES
  ${QAVITA_SRC}
  ${CMAKE_CURRENT_SOURCE_DIR}/Qavita.ui
  )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(Qavita
    MANUAL_FINALIZATION
    WIN32 ${CMAKE_SOURCE_DIR}/resources/Qavita.rc
    ${PROJECT_SOURCES}
    ${CMAKE_SOURCE_DIR}/resources/Qavita.qrc
    )
  # Define target properties for Android with Qt 6 as:
  #    set_property(TARGET Qavita APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
  #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
  # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(Qavita SHARED
      ${PROJECT_SOURCES}
      )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(Qavita
      ${PROJECT_SOURCES}
      )
  endif()
endif()

target_include_directories(
  Qavita
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(
  Qavita
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Qavita)
endif()
set_target_properties(Qavita PROPERTIES
  ${BUNDLE_ID_OPTION}
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
  )

include(GNUInstallDirs)
install(TARGETS Qavita
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

add_custom_command(
  TARGET Qavita POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_SOURCE_DIR}/resources/icons"
      "$<TARGET_PROPERTY:Qavita,BINARY_DIR>/$<CONFIG>/icons"
  )

if(WIN32)
  add_custom_command(
    TARGET Qavita POST_BUILD
    COMMAND $ENV{QT_DIR}/bin/windeployqt.exe
        $<TARGET_PROPERTY:Qavita,BINARY_DIR>/$<CONFIG>/Qavita.exe
    )
endif()

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(Qavita)
endif()
