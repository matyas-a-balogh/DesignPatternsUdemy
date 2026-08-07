#pragma once
#include "../../header.h"

template <typename T> struct Observer;

template <typename T> struct Observable {
    vector<Observer<T>*> observers;
public:
    void notify(T& source, const string& field_name) {
        for (auto observer : observers) {
            observer->field_changed(source, field_name);
        }
    }

    void subscribe(Observer<T>& observer) {
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        observers.erase(
            remove(observers.begin(), observers.end(), &observer),
            observers.end()
        );
    }
};
