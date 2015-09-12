cmake_minimum_required(VERSION 2.8.12)

project(ktp-thinklight)

find_package(ECM REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(ECMSetupVersion)

find_package(Qt5 REQUIRED COMPONENTS Network)

find_package(KF5 REQUIRED COMPONENTS Config ConfigWidgets I18n)

find_package(KTp REQUIRED)

add_subdirectory(src)
