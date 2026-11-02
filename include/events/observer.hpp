#pragma once

#include <vector>
#include <algorithm>

struct Observer {
    virtual ~Observer() = default;
};

template <typename T>
struct Subject {
    virtual ~Subject() {
        observers.clear();
    }
    virtual void addObserver   ( T* obs ){
        observers.push_back( obs );
    }
    virtual void removeObserver( T* obs ){
        observers.erase( std::remove( observers.begin(), observers.end(), obs ), observers.end() );
    }
protected:
    std::vector<T*> observers;
};
