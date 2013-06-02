//metadoc copyright Edward George 2013

#ifndef IOZMQ_DEFINED
#define IOZMQ_DEFINED 1

#include "zmq.h"
#include "IoObject.h"
#include "IoSeq.h"

#define ISZMQ(self) IoObject_hasCloneFunc_(self, (IoTagCloneFunc *)IoZMQ_rawClone)

typedef IoObject IoZMQ;

IoTag *IoZMQ_newTag(void *state);
IoObject *IoZMQ_proto(void *state);
IoObject *IoZMQ_rawClone(IoZMQ *self);
IoObject *IoZMQ_mark(IoZMQ *self);
void IoZMQ_free(IoZMQ *self);
#endif
