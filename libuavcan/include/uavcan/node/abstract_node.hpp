/*
 * Copyright (C) 2014 Pavel Kirienko <pavel.kirienko@gmail.com>
 */

#pragma once

#include <uavcan/impl_constants.hpp>
#include <uavcan/node/scheduler.hpp>
#include <uavcan/node/marshal_buffer.hpp>

namespace uavcan
{
/**
 * This is the abstract node class. If you're going to implement your own node class for your application,
 * please inherit this class so it can be used with default publisher, subscriber, server, etc. classes.
 * Normally you don't need to use directly though - please refer to the class Node<>.
 */
class UAVCAN_EXPORT INode
{
public:
    virtual ~INode() { }
    virtual IPoolAllocator& getAllocator() = 0;
    virtual Scheduler& getScheduler() = 0;
    virtual const Scheduler& getScheduler() const = 0;
    virtual IMarshalBufferProvider& getMarshalBufferProvider() = 0;
    virtual void registerInternalFailure(const char* msg) = 0;

    Dispatcher& getDispatcher()             { return getScheduler().getDispatcher(); }
    const Dispatcher& getDispatcher() const { return getScheduler().getDispatcher(); }

    ISystemClock& getSystemClock()         { return getScheduler().getSystemClock(); }
    MonotonicTime getMonotonicTime() const { return getScheduler().getMonotonicTime(); }
    UtcTime getUtcTime()             const { return getScheduler().getUtcTime(); }

    /**
     * Returns the Node ID of this node.
     * If Node ID was not set yet, an invalid value will be returned.
     */
    NodeID getNodeID() const { return getScheduler().getDispatcher().getNodeID(); }

    /**
     * Sets the Node ID of this node.
     * Node ID can be assigned only once. This method returns true if the Node ID was successfully assigned, otherwise
     * it returns false (e.g. the argument does not represent a valid Node ID, or it was already assigned earlier).
     * As long as a valid Node ID is not set, the node will remain in passive mode.
     */
    bool setNodeID(NodeID nid)
    {
        return getScheduler().getDispatcher().setNodeID(nid);
    }

    /**
     * Whether the node is in passive mode, i.e. can't transmit anything to the bus.
     * Please read the specs to learn more.
     */
    bool isPassiveMode() const { return getScheduler().getDispatcher().isPassiveMode(); }

    /**
     * Same as @ref spin(MonotonicDuration), but the deadline is specified as an absolute time value
     * rather than duration.
     */
    int spin(MonotonicTime deadline)
    {
        return getScheduler().spin(deadline);
    }

    /**
     * Runs the node.
     * Normally your application should not block anywhere else.
     * Block inside this method forever or call it periodically.
     * This method returns 0 if no errors occurred, or a negative error code if something failed (see error.hpp).
     */
    int spin(MonotonicDuration duration)
    {
        return getScheduler().spin(getMonotonicTime() + duration);
    }
};

}
