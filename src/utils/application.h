#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>

class Application
{
public:
    static const std::string& data_path() {return m_data_path;};
    static void set_data_path(const std::string& data_path) {m_data_path = data_path;};

private:
    static std::string m_data_path;
};







#endif // APPLICATION_H