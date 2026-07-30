#pragma once
#include "../../header.h"

template <typename T> class Observer {
public:
    virtual void field_changed(
        T& source,
        const string& field_name
    ) = 0;
};
