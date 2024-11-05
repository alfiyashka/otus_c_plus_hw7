#include "CommandParser.hpp"


#include <stdexcept>
#include <iostream>
#include <chrono>
#include <sstream>


std::string CommandParser::generateFileNameWithCurrentTime() const
{
    const auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    return "bulk" + std::to_string(current_time) + ".log";
}

void CommandParser::writeOnFile(const std::string &data)
{
    const auto filename = generateFileNameWithCurrentTime();
    m_fileWriter.write(filename, data);
}

void CommandParser::completePackage()
{
    bool needDelimiter = false;
    for (auto iCmd : m_cmds)
    {
        if (needDelimiter)
        {
            std::cout << ", ";
        }
        std::cout << iCmd;
        needDelimiter = true;
    }
    std::cout << std::endl;
    m_cmds.clear();
    if (m_state.tryEndDynamicMode())
    {
        m_cmds.shrink_to_fit();
        m_cmds.reserve(m_packageSize);
    }
}

void CommandParser::init()
{
    if (m_packageSize <= 0)
    {
        throw std::runtime_error("Incorrect package size");
    }
    m_cmds.reserve(m_packageSize);
    m_fileWriter.init();
}

void CommandParser::parse(const std::string &cmd)
{
    if (cmd.empty())
    {
        std::cerr << "Encountered empty command";
        return;
    }
    if (m_state.modifyState(cmd))
    {
        if (m_state.isDynamicModeStarting()
            || m_state.isDynamicModeCompleted())
        {
            completePackage();
        }
        return;
    }
    writeOnFile(cmd);
    m_cmds.emplace_back(cmd);

    if (isStaticModeComplete())
    {
        completePackage();
    }
}

void CommandParser::endJob()
{
    if (m_state.isStaticMode() || m_state.isDynamicModeCompleted())
    {
        completePackage();
    }
}