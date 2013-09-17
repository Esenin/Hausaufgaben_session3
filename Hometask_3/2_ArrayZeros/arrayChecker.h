#pragma once

template<typename Type>
//!
//! \brief The ArrayChecker class
//! can check array for zero value
class ArrayChecker
{
public:
    ArrayChecker(Type *array, int const size)
        : mArray(array)
        , mSize(size)
    {
    }

    bool hasZeros() const
    {
        for (int i = 0; i < mSize; i++)
        {
            if (mArray[i] == 0)
                return true;
        }
        return false;
    }
private:
    Type *mArray;
    int mSize;
};

