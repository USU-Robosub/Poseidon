//
// Created by Kyler Jensen on 4/12/17.
//

#ifndef SLAM_OBSERVABLE_H
#define SLAM_OBSERVABLE_H


#include <unordered_set>

namespace slam {

    template<typename T>
    using Listener = void (*)(T);

    template<typename T>
    class Observable {
    private:
        std::unordered_set<Listener<T>> listeners = std::unordered_set<Listener<T>>();

    protected:
        void publish(T value) {
            for(auto listener : listeners) {
                listener(value);
            }
        }

    public:
        void subscribe(Listener<T> listener) {
            listeners.insert(listener);
        }

        void unsubscribe(Listener<T> listener) {
            listeners.erase(listener);
        }

        int subscribers() const {
            return (int) listeners.size();
        }

    };

}


#endif //SLAM_OBSERVABLE_H
