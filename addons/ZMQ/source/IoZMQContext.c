//metadoc ZMQContext copyright Edward George
//metadoc ZMQContext license BSD revised
//metadoc ZMQContext category Example
/*metadoc ZMQContext description
ZMQ Bindings
*/
#include "IoNumber.h"
#include "IoState.h"
#include "IoZMQContext.h"

static const char *protoId = "ZMQContext";

IoTag *IoZMQContext_newTag(void *state)
{
        IoTag *tag = IoTag_newWithName_("ZMQContext");
        IoTag_state_(tag, state);

        IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoZMQContext_free);
        IoTag_markFunc_(tag, (IoTagMarkFunc *)IoZMQContext_mark);
        IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoZMQContext_rawClone);
        return tag;
}

IoObject *IoZMQContext_proto(void *state)
{
        IoZMQContext *self = IoObject_new(state);
        IoObject_tag_(self, IoZMQContext_newTag(state));
        IoState_registerProtoWithId_((IoState *)state, self, protoId);
        {
                IoMethodTable methodTable[] = {
                {"getNumIOThreads", IoZMQContext_getNumIOThreads},
                {"setNumIOThreads", IoZMQContext_setNumIOThreads},
                {"getMaxSockets", IoZMQContext_getMaxSockets},
                {"setMaxSockets", IoZMQContext_setMaxSockets},
                {NULL, NULL},
                };
                IoObject_addMethodTable_(self, methodTable);
        }
        return self;
}

IoObject *IoZMQContext_rawClone(IoZMQContext *proto)
{
        IoObject *self = IoObject_rawClonePrimitive(proto);
        IoObject_setDataPointer_(self, zmq_ctx_new());
        return self;
}

IoObject *IoZMQContext_new(void *state)
{
        IoObject *proto = IoState_protoWithId_((IoState *)state, protoId);
        return IOCLONE(proto);
}

IoObject *IoZMQContext_mark(IoZMQContext* self)
{
        return self;
}

void IoZMQContext_free(IoZMQContext *self)
{
        zmq_ctx_destroy(CONTEXT(self));
}

IoObject *IoZMQContext_getNumIOThreads(IoZMQContext *self, IoObject *locals, IoMessage *m)
{
        return IONUMBER(zmq_ctx_get(CONTEXT(self), ZMQ_IO_THREADS));
}

IoObject *IoZMQContext_setNumIOThreads(IoZMQContext *self, IoObject *locals, IoMessage *m)
{
        int num = IoMessage_locals_intArgAt_(m, locals, 0);
        int r = zmq_ctx_set(CONTEXT(self), ZMQ_IO_THREADS, num);
        return (r == 0) ? self : IONIL(self);
}

IoObject *IoZMQContext_getMaxSockets(IoZMQContext *self, IoObject *locals, IoMessage *m)
{
        return IONUMBER(zmq_ctx_get(CONTEXT(self), ZMQ_MAX_SOCKETS));
}

IoObject *IoZMQContext_setMaxSockets(IoZMQContext *self, IoObject *locals, IoMessage *m)
{
        int num = IoMessage_locals_intArgAt_(m, locals, 0);
        int r = zmq_ctx_set(CONTEXT(self), ZMQ_MAX_SOCKETS, num);
        return (r == 0) ? self : IONIL(self);
}
