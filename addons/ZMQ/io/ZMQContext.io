ZMQContext do (
    socket := method(type, ZMQSocket clone setContext(self))
)
