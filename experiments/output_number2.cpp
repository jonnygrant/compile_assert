//g++ -Wall -O2 -o output_number2 output_number2.cpp

template<int V>
[[gnu::error(__FILE__)]] void report_value();

int main()
{
    report_value<37>();
}
