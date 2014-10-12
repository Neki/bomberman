#include <iostream>

#include "logging.h"
_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
  initialize_logger();
  _START_EASYLOGGINGPP(argc, argv);
  LOG(INFO) << "Starting bomberman server...";
  return 0;
}
