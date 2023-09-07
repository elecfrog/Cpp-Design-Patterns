# Array

数组是存放在连续内存空间上的相同类型数据的集合。

**`Array` is a data structure that stores a fixed-size sequential collection of elements of the same type, with a
contiguous memory layout.**

In other words, an array is a collection of variables of the same type that are referenced
by a common name and are stored in a contiguous block of memory. Each element in the array can be accessed using an
index or a `subscript`, which indicates its position within the array. The size of an array is determined at the time of
declaration and cannot be changed during runtime.

- the index start from 0.
- the memory layout of the array of contiguous

Because the layout is contiguous, addresses of elements in the array have to be moved while deleting or adding elements into the array.

Besides, `std::vector` implemented by array. But strictly, it is a container but not an array.
```cpp
pointer _Myfirst; // pointer to beginning of array
pointer _Mylast; // pointer to current end of sequence
pointer _Myend; // pointer to end of array
```

```cpp

_Ty& EmplaceBackRV(_Valty&&... _Val) {
    // insert by perfectly forwarding into element at end, provide strong guarantee
    pointer& _Mylast = vectorData._Mylast;

    if (_Mylast != vectorData._Myend) {
        return EmplaceBackDirectly(_STD forward<_Valty>(_Val)...);
    }

    return *ReallocateAndEmplace(_Mylast, _STD forward<_Valty>(_Val)...);
}
    
_Ty& EmplaceBackDirectly(_Valty&&... _Val) {
    // ...
    _Construct_in_place(*_Mylast, _STD forward<_Valty>(_Val)...);
    // ...
    _Ty& _Result = *_Mylast;
    ++_Mylast;

    return _Result;
}
    
pointer ReallocateAndEmplace(const pointer _Whereptr, _Valty&&... _Val) {

    // ...
    CHECK(_Mylast == vectorData._Myend); // check that we have no unused capacity

    const auto _Whereoff = (_Whereptr - _Myfirst);
    const auto _Oldsize  = (_Mylast - _Myfirst);

    if (_Oldsize == max_size())
        // OVERFLOW ERROR

    const size_type _Newsize     = _Oldsize + 1;
    const size_type _Newcapacity = _Calculate_growth(_Newsize);

    // ....
    construct(_Al, _Unfancy(_Newvec + _Whereoff), _STD forward<_Valty>(_Val)...);
    // ... 
    return _Newvec + _Whereoff;
}
```