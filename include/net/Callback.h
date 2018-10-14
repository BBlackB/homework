#ifndef __NET_DEFINE_H__
#define __NET_DEFINE_H__

#include "TcpConnection.h"

// typedef void (*Handler)(TcpConnection *, int);
// typedef void (*Response)(TcpConnection *ptcp, char *message);
// typedef void (*ConnHandler)(int);

class TcpConnection;
class Channel;
class EventLoop;

using Handler = void (*)(TcpConnection *, int);
using Response = void (*)(TcpConnection *ptcp, const char *message);
using ConnHandler = void (*)(int);

#endif // __NET_DEFINE_H__