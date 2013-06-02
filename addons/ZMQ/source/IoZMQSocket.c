//metadoc ZMQSocket copyright Edward George
//metadoc ZMQSocket license BSD revised
//metadoc ZMQSocket category Example
/*metadoc ZMQSocket description
ZMQ Bindings
*/
#include <stdlib.h>
#include "IoNumber.h"
#include "IoState.h"
#include "IoSeq.h"
#include "IoZMQSocket.h"
#include "IoZMQContext.h"

#define SOCKET(self) ((void *)IoObject_dataPointer(self))
static const char *protoId = "ZMQSocket";

IoTag *IoZMQSocket_newTag(void *state)
{
        IoTag *tag = IoTag_newWithName_("ZMQSocket");
        IoTag_state_(tag, state);

        IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoZMQSocket_free);
        IoTag_markFunc_(tag, (IoTagMarkFunc *)IoZMQSocket_mark);
        IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoZMQSocket_rawClone);
        return tag;
}

IoObject *IoZMQSocket_proto(void *state)
{
        IoZMQSocket *self = IoObject_new(state);
        IoObject_tag_(self, IoZMQSocket_newTag(state));
        IoState_registerProtoWithId_((IoState *)state, self, protoId);
        {
                IoMethodTable methodTable[] = {
                {"bind", IoZMQSocket_bind},
                {"connect", IoZMQSocket_connect},
                {"send", IoZMQSocket_send},
                {"recv", IoZMQSocket_recv},
                {NULL, NULL},
                };
                IoObject_addMethodTable_(self, methodTable);
        }
        return self;
}

IoObject *IoZMQSocket_rawClone(IoZMQSocket *proto)
{
        IoObject *self = IoObject_rawClonePrimitive(proto);
        IoObject_setDataPointer_(self, 0x0);
        return self;
}

IoObject *IoZMQSocket_new(void *state)
{
        IoObject *proto = IoState_protoWithId_((IoState *)state, protoId);
        return IOCLONE(proto);
}

IoObject *IoZMQSocket_mark(IoZMQSocket* self)
{
        return self;
}

void IoZMQSocket_free(IoZMQSocket *self)
{
        if(SOCKET(self)) {
            zmq_close(SOCKET(self));
            IoObject_setDataPointer_(self, 0x0);
        }
}

IoObject *IoZMQSocket_bind(IoZMQSocket *self, IoObject *locals, IoMessage *m)
{
        void *s;
        IoZMQContext *ctx = IoObject_getSlot_(self, IOSYMBOL("context"));
        IoSymbol *addr = IoMessage_locals_symbolArgAt_(m, locals, 0);
        int type = IoMessage_locals_intArgAt_(m, locals, 1);
        IOASSERT(SOCKET(self) == 0X0, "already initialised");
        IOASSERT(ISZMQContext(ctx), "context slot not set properly");
        s = zmq_socket(CONTEXT(ctx), type);
        if(s == NULL){
            return ZMQERROR("Creating socket failed");
        }
        IoObject_setDataPointer_(self, s);
        if(zmq_bind(SOCKET(self), CSTRING(addr))){
            return ZMQERROR("Binding socket failed");
        }
        return self;
}

IoObject *IoZMQSocket_connect(IoZMQSocket *self, IoObject *locals, IoMessage *m)
{
        void *s;
        IoZMQContext *ctx = IoObject_getSlot_(self, IOSYMBOL("context"));
        IoSymbol *addr = IoMessage_locals_symbolArgAt_(m, locals, 0);
        int type = IoMessage_locals_intArgAt_(m, locals, 1);
        IOASSERT(SOCKET(self) == 0x0, "already initialised");
        IOASSERT(ISZMQContext(ctx), "context slot not set properly");
        s = zmq_socket(CONTEXT(ctx), type);
        if(s == NULL){
            return ZMQERROR("Creating socket failed");
        }
        IoObject_setDataPointer_(self, s);
        if(zmq_connect(SOCKET(self), CSTRING(addr))){
            return ZMQERROR("Connecting socket failed");
        }
        return self;
}

IoObject *IoZMQSocket_send(IoZMQSocket *self, IoObject *locals, IoMessage *m)
{
        IoObject *bufdata = IoMessage_locals_seqArgAt_(m, locals, 0);
        int flags = IoMessage_locals_intArgAt_(m, locals, 1);
        int r = zmq_send(SOCKET(self), CSTRING(bufdata), IOSEQ_LENGTH(bufdata), flags);
        if(r < 0){
            return ZMQERROR("Error sending message");
        }
        return self;
}

IoObject *IoZMQSocket_recv(IoZMQSocket *self, IoObject *locals, IoMessage *m)
{
        int bufsize = IoMessage_locals_intArgAt_(m, locals, 0);
        unsigned char *buf = malloc(sizeof(char) * bufsize);
        int r = zmq_recv(SOCKET(self), buf, bufsize, 0);
        if(r < 0){
            return ZMQERROR("Error receiving message");
        }
        return IoSeq_newWithData_length_(IOSTATE, buf, (r < bufsize ? r : bufsize));
}
