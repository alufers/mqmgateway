#define CATCH_CONFIG_CONSOLE_WIDTH 300

#include <catch2/catch_all.hpp>
#include "libmodmqttsrv/logging.hpp"

int main( int argc, char* argv[] ) {

  modmqttd::Log::init_logging(modmqttd::Log::severity::debug);

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return result;
}
