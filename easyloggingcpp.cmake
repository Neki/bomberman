# Download the easyloggingcpp library

include(ExternalProject)

set(EASYLOGGINGCPP_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/easylogging")
set(EASYLOGGINGCPP_VERSION "9.75")

ExternalProject_Add(easyloggingcpp
  PREFIX ${EASYLOGGINGCPP_PREFIX}
  URL "https://github.com/easylogging/easyloggingpp/releases/download/v${EASYLOGGINGCPP_VERSION}/easyloggingpp_v${EASYLOGGINGCPP_VERSION}.tar.gz"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_CONFIGURE OFF
  LOG_BUILD OFF)

include_directories("${EASYLOGGINGCPP_PREFIX}/src/easyloggingcpp")

