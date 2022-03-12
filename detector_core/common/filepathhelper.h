#pragma once

using namespace std;
using namespace std::filesystem;
class FilePathHelper final {
public:
    explicit FilePathHelper(const std::string& path)
        : m_path(path) {}
    bool exist()
    {
        filesystem::path filePath(m_path);
        return exists(filePath);
    }

    file_type fileType()
    {
        filesystem::directory_entry entry(m_path);
        return entry.status().type();
    }

private:
    std::string m_path;
};
