#pragma once

template<typename Type>
//!
//! \brief The ArrayChecker class
//! calc zeros count in array
class ArrayChecker
{
public:
    ArrayChecker(Type *array, int const size)
        : mArray(array)
        , mSize(size)
    {
    }

    int zerosCount() const
    {
        int result = 0;
        for (int i = 0; i < mSize; i++)
        {
            if (mArray[i] == 0)
                result++;
        }
        return result;
    }
private:
    Type *mArray;
    int mSize;
};

