//metadoc copyright Edward George 2013

#ifndef IOZMQContext_DEFINED
#define IOZMQContext_DEFINED 1

#define ISZMQContext(self) IoObject_hasCloneFunc_(self, (IoTagCloneFunc *)IoZMQContext_rawClone)
#define CONTEXT(self) ((void *)IoObject_dataPointer(self))

#include "zmq.h"
#include "IoObject.h"
#include "IoSeq.h"

typedef IoObject IoZMQContext;

IoTag *IoZMQContext_newTag(void *state);
IoObject *IoZMQContext_proto(void *state);
IoObject *IoZMQContext_rawClone(IoZMQContext *self);
IoObject *IoZMQContext_mark(IoZMQContext *self);
void IoZMQContext_free(IoZMQContext *self);

IoObject *IoZMQContext_getNumIOThreads(IoZMQContext *self, IoObject *locals, IoMessage *m);
IoObject *IoZMQContext_setNumIOThreads(IoZMQContext *self, IoObject *locals, IoMessage *m);
IoObject *IoZMQContext_getMaxSockets(IoZMQContext *self, IoObject *locals, IoMessage *m);
IoObject *IoZMQContext_setMaxSockets(IoZMQContext *self, IoObject *locals, IoMessage *m);
#endif
