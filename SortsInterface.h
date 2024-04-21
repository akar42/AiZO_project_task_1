#pragma once

template<typename T>
class SortsInterface
{
public:
    virtual void setData(T* data, int size) = 0;
    virtual T* getData() = 0;
    virtual void sort(int choser = 0) = 0;
    virtual ~SortsInterface() {}
};