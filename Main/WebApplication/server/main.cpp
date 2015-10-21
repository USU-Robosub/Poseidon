#include "../kernel/Environment.h"

#if SERVER != 1
    #include "rice/Data_Type.hpp"
    #include "rice/Constructor.hpp"
#endif

#include "RCServer.hpp"

int main()
{
    RCServer server;
    server.setPort(4322);
    server.start();
}

#if SERVER != 1
extern "C"
void Init_Server();
void Init_Server()
{
    Rice::Data_Type<RCServer> rb_cRCServer =
        Rice::define_class<RCServer>("Server")
        .define_constructor(Rice::Constructor<RCServer>())
        .define_method("setPort", &RCServer::setPort)
        .define_method("start", &RCServer::start);
}
#endif
