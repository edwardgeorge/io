//metadoc ZMQ copyright Edward George
//metadoc ZMQ license BSD revised
//metadoc ZMQ category Example
/*metadoc ZMQ description
ZMQ Bindings
*/
#include "IoNumber.h"
#include "IoState.h"
#include "IoZMQ.h"

static const char *protoId = "ZMQ";

IoTag *IoZMQ_newTag(void *state)
{
        IoTag *tag = IoTag_newWithName_("ZMQ");
        IoTag_state_(tag, state);

        IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoZMQ_free);
        IoTag_markFunc_(tag, (IoTagMarkFunc *)IoZMQ_mark);
        IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoZMQ_rawClone);
        return tag;
}

IoObject *IoZMQ_proto(void *state)
{
        IoZMQ *self = IoObject_new(state);
        IoObject_tag_(self, IoZMQ_newTag(state));
        IoState_registerProtoWithId_((IoState *)state, self, protoId);
        {
                IoMethodTable methodTable[] = {
                {NULL, NULL},
                };
                IoObject_addMethodTable_(self, methodTable);
        }
        IoObject_setSlot_to_(self, IOSYMBOL("ZMQ_REQ"), IONUMBER(ZMQ_REQ));
        IoObject_setSlot_to_(self, IOSYMBOL("ZMQ_REP"), IONUMBER(ZMQ_REP));
        return self;
}

IoObject *IoZMQ_rawClone(IoZMQ *proto)
{
        IoObject *self = IoObject_rawClonePrimitive(proto);
        return self;
}

IoObject *IoZMQ_new(void *state)
{
        IoObject *proto = IoState_protoWithId_((IoState *)state, protoId);
        return IOCLONE(proto);
}

IoObject *IoZMQ_mark(IoZMQ* self)
{
        return self;
}

void IoZMQ_free(IoZMQ *self)
{
}
