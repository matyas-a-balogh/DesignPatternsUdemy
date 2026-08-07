#pragma once
#include "../../header.h"
#include <mutex>

template <typename T> struct Observer;

template <typename T> struct SaferObservable {
    vector<Observer<T>*> observers;
    typedef recursive_mutex mutex_t; // create a type alias for mutex so that it can be recursive, allowing the same thread to lock it multiple times without deadlocking
    // recursive_mutex solves the problem, but people usually dont like it
    mutex_t mtx;
public:
    void notify(T& source, const string& field_name) {
        scoped_lock<mutex_t> lock(mtx); // lock the mutex to ensure thread safety
        for (auto observer : observers) {
            observer->field_changed(source, field_name); // vector is not thread safe, so we need to lock it
        }
    }

    void subscribe(Observer<T>& observer) {
        scoped_lock<mutex_t> lock(mtx);
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {        
        scoped_lock<mutex_t> lock(mtx);
        observers.erase(
            remove(observers.begin(), observers.end(), &observer),
            observers.end()
        );
    }
};
