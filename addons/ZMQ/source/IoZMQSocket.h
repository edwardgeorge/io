//metadoc copyright Edward George 2013

#ifndef IOZMQSocket_DEFINED
#define IOZMQSocket_DEFINED 1

#include <errno.h>
#include "zmq.h"
#include "IoObject.h"
#include "IoSeq.h"
#include "IoError.h"

#define ISZMQSocket(self) IoObject_hasCloneFunc_(self, (IoTagCloneFunc *)IoZMQSocket_rawClone)
#define ZMQERROR(desc) IoError_newWithMessageFormat_(IOSTATE, "%s: %s", desc, zmq_strerror(errno))

typedef IoObject IoZMQSocket;

IoTag *IoZMQSocket_newTag(void *state);
IoObject *IoZMQSocket_proto(void *state);
IoObject *IoZMQSocket_rawClone(IoZMQSocket *self);
IoObject *IoZMQSocket_mark(IoZMQSocket *self);
void IoZMQSocket_free(IoZMQSocket *self);

IoObject *IoZMQSocket_bind(IoZMQSocket *self, IoObject *locals, IoMessage *m);
IoObject *IoZMQSocket_connect(IoZMQSocket *self, IoObject *locals, IoMessage *m);
IoObject *IoZMQSocket_send(IoZMQSocket *self, IoObject *locals, IoMessage *m);
IoObject *IoZMQSocket_recv(IoZMQSocket *self, IoObject *locals, IoMessage *m);
#endif
