
// demonstrate compile_assert checking two files, that are compiled separately
// then linked
//
// This is the api file

void log_api(const char * const str)
{
    __builtin_printf("log [%s]\n", str);
}
