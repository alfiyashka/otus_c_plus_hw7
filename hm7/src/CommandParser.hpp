#ifndef _COMMAND_PARSER_HPP__
#define _COMMAND_PARSER_HPP__

#include <string>
#include <vector>

#include "CmdFileWriter.hpp"
#include "CmdParserState.hpp"


/**
 * parsers commands
 */
class CommandParser
{
private:
    const int m_packageSize; // defines package size
    std::vector<std::string> m_cmds; // list of parsed commands
    CmdFileWriter m_fileWriter; // writes command data into a file
    CmdParserState m_state; // current state

    /**
     * generates filename with current time
     */
    std::string generateFileNameWithCurrentTime() const;

    /**
     * writes data on file
     * @param data - data to write
     */
    void writeOnFile(const std::string& data);

    bool isStaticModeComplete() { return m_state.isStaticMode() && m_packageSize == m_cmds.size(); }

    /**
     * performs complete package operations
     */
    void completePackage();

    bool cmdIsOnlySpace(const std::string &cmd) const;

public:
    CommandParser(const int packageSize)
     : m_packageSize(packageSize)
    {
    }

    CommandParser(const int packageSize, const std::string& resultDir)
     : m_packageSize(packageSize)
       , m_fileWriter(resultDir)
    {        
    }

    ~CommandParser()
    {
        endJob();
    }
   
    /**
     * performs complete parse job
     */
    void endJob();

    /**
     * performs initialization actions
     */
    void init();    

    /**
     * parses commands
     * @param cmd - command
     */
    void parse(const std::string& cmd);
};



#endif