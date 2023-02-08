#include <iostream>

#include "client/crashpad_client.h"
#include "client/crash_report_database.h"
#include "client/settings.h"

std::string getBinaryPath()
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string::size_type pos = std::string(path).find_last_of("\\/");
    return std::string(path).substr(0, pos);
}

std::wstring getPathRelativeToBinary(std::wstring path)
{
    std::string binPath = getBinaryPath();
    return std::wstring(binPath.begin(), binPath.end()) + L'/' + path;
}

int main(int argc, char *argv[])
{
    base::FilePath handler(getPathRelativeToBinary(L"crashpad_handler.exe"));
    base::FilePath database(getPathRelativeToBinary(L"crashpad_database"));
    std::string url = "";

    std::map<std::string, std::string> annotations = {
        {"format", "minidump"}
    };

    std::vector<std::string> arguments = {"--no-rate-limit"};

    crashpad::CrashpadClient client;
    bool success = client.StartHandler(
        handler,
        database,
        database,
        url,
        annotations,
        arguments,
        /* restartable */ true,
        /* asynchronous_start */ false);
    if (!success)
    {
        std::cerr << "Failed to start crashpad handler" << std::endl;
    }
    else
    {
        std::cout << "Crashpad handler started" << std::endl;
    }

    return 0;
}
