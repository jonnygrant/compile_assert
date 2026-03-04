//g++ -Wall -O2 -o output_number output_number.cpp

template<int V>
struct temp;

template<int V>
void output()
{
    static_assert(false, "V output");
    temp<V> p;
}

int main() {
    output<37>();
}
