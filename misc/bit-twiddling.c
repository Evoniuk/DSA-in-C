int get_bit(int number, int index)
{
    return number & (1 << index);
}

int set_bit(int number, int index)
{
    return number | (1 << index);
}

int clear_bit(int number, int index)
{
    return number & ~(1 << index);
}

int is_power_of_two(int number)
{
    return (number & (number - 1)) == 0;
}

int count_set_bits(int number) // Kernighan's algorithm
{
    int count = 0;
    while (number)
    {
        number &= number - 1;
        count++;
    }

    return count;
}
