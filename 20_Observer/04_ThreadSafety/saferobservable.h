#pragma once
#include "../../header.h"
#include <mutex>

template <typename T> struct Observer;

template <typename T> struct SaferObservable {
    vector<Observer<T>*> observers;
    typedef mutex mutex_t; // create a type alias for mutex
    mutex_t mtx;
public:
    void notify(T& source, const string& field_name) {
        scoped_lock<mutex_t> lock(mtx); // lock the mutex to ensure thread safety
        for (auto observer : observers) {
            if (observer) // check if the observer is not nullptr - this is how we go around the problem of unsubscribing inside notify
            observer->field_changed(source, field_name); // vector is not thread safe, so we need to lock it
        }
    }

    void subscribe(Observer<T>& observer) {
        scoped_lock<mutex_t> lock(mtx);
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        // lets remove the lock here, because we want to be able to unsubscribe inside notify, which is already locked

        auto it = find(begin(observers), end(observers), &observer);
        if (it != end(observers)) {
            *it = nullptr; // mark the observer as nullptr instead of removing it
        }
        
        // scoped_lock<mutex_t> lock(mtx);
        // observers.erase(
        //     remove(observers.begin(), observers.end(), &observer),
        //     observers.end()
        // );
    }
};
