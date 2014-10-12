#include "logging.h"

void initialize_logger() {
    el::Configurations conf;
    conf.setToDefault();
    conf.set(el::Level::Global, el::ConfigurationType::Filename, "bomberman.log");
    el::Loggers::reconfigureAllLoggers(conf);
}

bool file_exists(const char* file_name) {
  std::ifstream file(file_name);
  return file.good();
}
