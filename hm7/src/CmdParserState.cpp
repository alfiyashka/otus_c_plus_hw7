#include "CmdParserState.hpp"

bool CmdParserState::modifyState(const std::string &tag)
{
    if (tag == "{")
    {
        m_dynamicModeCounter++;
        if (m_state == ParserModeState::STATIC)
        {
            m_state = ParserModeState::DYNAMIC_START;
            return true;
        }
        m_state = ParserModeState::DYNAMIC_RUNNING;

        return true;
    }
    else if (tag == "}")
    {
        m_dynamicModeCounter--;
        m_state = m_dynamicModeCounter == 0
                      ? ParserModeState::DYNAMIC_END
                      : ParserModeState::DYNAMIC_RUNNING;
        return true;
    }
    return false;
}

bool CmdParserState::tryEndDynamicMode()
{
    if (m_state == ParserModeState::DYNAMIC_END)
    {
        m_state = ParserModeState::STATIC;
        m_dynamicModeCounter = 0;
        return true;
    }
    return false;
}