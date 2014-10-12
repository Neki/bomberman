#include "logging.h"

void initialize_logger() {
    el::Configurations conf;
    conf.setToDefault();
    conf.set(el::Level::Global, el::ConfigurationType::Filename, "bomberman_server.log");
    el::Loggers::reconfigureAllLoggers(conf);
}

