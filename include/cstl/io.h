#pragma

#include <cstl/common.h>

#include <Windows.h>

namespace cstl
{
void print(const char *const str)
{
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), str, static_cast<uint32_t>(strlen(str)), nullptr, nullptr);
}
} // namespace cstl