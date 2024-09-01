// Author: Jake Rieger
// Created: 8/25/2024.
//

#pragma once

#include "Shared/Types.h"

#include <typeindex>

class EventDispatcher;

class IEvent {
public:
    explicit IEvent(int id) : mId(id) {}
    virtual ~IEvent() = default;

    [[nodiscard]] int GetId() const {
        return mId;
    }

protected:
    const int mId = 0;
};

class IEventListener {
public:
    virtual ~IEventListener()                 = default;
    virtual void OnEvent(const IEvent& event) = 0;
};

template<typename EventType>
class SpecificEventListener final : public IEventListener {
public:
    using Callback = std::function<void(const EventType&)>;
    explicit SpecificEventListener(Callback cb) : mCallback(cb) {}

    void OnEvent(const IEvent& event) override {
        mCallback(static_cast<const EventType&>(event));
    }

private:
    Callback mCallback;
};

class EventDispatcher {
public:
    template<typename EventType>
    void RegisterListener(std::function<void(const EventType&)> callback) {
        const std::type_index typeIndex(typeid(EventType));
        mListeners[typeIndex].emplace_back(
          std::make_shared<SpecificEventListener<EventType>>(callback));
    }

    void Dispatch(const IEvent& event) {
        const std::type_index typeIndex(typeid(event));
        const auto it = mListeners.find(typeIndex);
        if (it != mListeners.end()) {
            for (const auto& listener : it->second) {
                listener->OnEvent(event);
            }
        }
    }

private:
    Map<std::type_index, Vector<Shared<IEventListener>>> mListeners;
};
