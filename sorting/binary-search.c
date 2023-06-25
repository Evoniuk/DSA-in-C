int binary_search(int* haystack, int needle, int length)
{
    int* lo = haystack;
    int* hi = haystack + length; // hi is non-inclusive

    do 
    {
        int* mid = lo + (hi - lo) / 2;

        if (*mid == needle) return mid - haystack;
        if (*mid > needle)  hi = mid;
        if (*mid < needle)  lo = mid + 1;
    } while (lo < hi);

    return -1;
}
