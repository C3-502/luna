#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include "../../util/common_inc.h"

namespace luna {

namespace http {

int handle_message(TcpConnectionPtr connection);

}

}


#endif // HTTPHANDLER_H
