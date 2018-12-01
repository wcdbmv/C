import ctypes

if __name__ == '__main__':
    libarr = ctypes.CDLL("./libarr.so")

    shift = libarr.shift
    shift.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.c_int)

    copy_squares = libarr.copy_squares
    copy_squares.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.POINTER(ctypes.c_int))
    copy_squares.restype = ctypes.c_size_t

    c_print = libarr.c_print
    c_print.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)

    arr = [i for i in range(6)]
    len_arr = len(arr)
    arr = (ctypes.c_int * len_arr)(*arr)
    c_print(arr, len_arr)
    shift(arr, len_arr, 2)
    print('== shift 2 ==')
    c_print(arr, len_arr)

    brr = (ctypes.c_int * len_arr)(*arr)
    brr_len = copy_squares(arr, len_arr, brr)
    print('== copy squares ==')
    c_print(brr, brr_len)
