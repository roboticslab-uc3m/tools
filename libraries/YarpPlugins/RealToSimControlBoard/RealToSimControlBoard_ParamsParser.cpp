/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */


// Generated by yarpDeviceParamParserGenerator (1.0)
// This is an automatically generated file. Please do not edit it.
// It will be re-generated if the cmake flag ALLOW_DEVICE_PARAM_PARSER_GERNERATION is ON.

// Generated on: Thu Apr 17 12:02:47 2025


#include "RealToSimControlBoard_ParamsParser.h"
#include <yarp/os/LogStream.h>
#include <yarp/os/Value.h>

namespace {
    YARP_LOG_COMPONENT(RealToSimControlBoardParamsCOMPONENT, "yarp.device.RealToSimControlBoard")
}


RealToSimControlBoard_ParamsParser::RealToSimControlBoard_ParamsParser()
{
}


std::vector<std::string> RealToSimControlBoard_ParamsParser::getListOfParams() const
{
    std::vector<std::string> params;
    params.push_back("modePosVel");
    params.push_back("remotes");
    params.push_back("remotePrefix");
    params.push_back("remoteSuffix");
    params.push_back("localSuffix");
    return params;
}


bool      RealToSimControlBoard_ParamsParser::parseParams(const yarp::os::Searchable & config)
{
    //Check for --help option
    if (config.check("help"))
    {
        yCInfo(RealToSimControlBoardParamsCOMPONENT) << getDocumentationOfDeviceParams();
    }

    std::string config_string = config.toString();
    yarp::os::Property prop_check(config_string.c_str());
    //Parser of parameter modePosVel
    {
        if (config.check("modePosVel"))
        {
            m_modePosVel = config.find("modePosVel").asInt64();
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'modePosVel' using value:" << m_modePosVel;
        }
        else
        {
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'modePosVel' using DEFAULT value:" << m_modePosVel;
        }
        prop_check.unput("modePosVel");
    }

    //Parser of parameter remotes
    {
        if (config.check("remotes"))
        {
            {
                m_remotes.clear();
                yarp::os::Bottle* tempBot = config.find("remotes").asList();
                if (tempBot)
                {
                    std::string tempBots = tempBot->toString();
                    for (size_t i=0; i<tempBot->size(); i++)
                    {
                        m_remotes.push_back(tempBot->get(i).asString());
                    }
                }
                else
                {
                     yCError(RealToSimControlBoardParamsCOMPONENT) <<"parameter 'remotes' is not a properly formatted bottle";
                }
            }
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'remotes' using value:" << m_remotes;
        }
        else
        {
            yCError(RealToSimControlBoardParamsCOMPONENT) << "Mandatory parameter 'remotes' not found!";
            yCError(RealToSimControlBoardParamsCOMPONENT) << "Description of the parameter: list of remotes to which this device connects";
            return false;
        }
        prop_check.unput("remotes");
    }

    //Parser of parameter remotePrefix
    {
        if (config.check("remotePrefix"))
        {
            m_remotePrefix = config.find("remotePrefix").asString();
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'remotePrefix' using value:" << m_remotePrefix;
        }
        else
        {
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'remotePrefix' using DEFAULT value:" << m_remotePrefix;
        }
        prop_check.unput("remotePrefix");
    }

    //Parser of parameter remoteSuffix
    {
        if (config.check("remoteSuffix"))
        {
            m_remoteSuffix = config.find("remoteSuffix").asString();
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'remoteSuffix' using value:" << m_remoteSuffix;
        }
        else
        {
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'remoteSuffix' using DEFAULT value:" << m_remoteSuffix;
        }
        prop_check.unput("remoteSuffix");
    }

    //Parser of parameter localSuffix
    {
        if (config.check("localSuffix"))
        {
            m_localSuffix = config.find("localSuffix").asString();
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'localSuffix' using value:" << m_localSuffix;
        }
        else
        {
            yCInfo(RealToSimControlBoardParamsCOMPONENT) << "Parameter 'localSuffix' using DEFAULT value:" << m_localSuffix;
        }
        prop_check.unput("localSuffix");
    }

    /*
    //This code check if the user set some parameter which are not check by the parser
    //If the parser is set in strict mode, this will generate an error
    if (prop_check.size() > 0)
    {
        bool extra_params_found = false;
        for (auto it=prop_check.begin(); it!=prop_check.end(); it++)
        {
            if (m_parser_is_strict)
            {
                yCError(RealToSimControlBoardParamsCOMPONENT) << "User asking for parameter: "<<it->name <<" which is unknown to this parser!";
                extra_params_found = true;
            }
            else
            {
                yCWarning(RealToSimControlBoardParamsCOMPONENT) << "User asking for parameter: "<< it->name <<" which is unknown to this parser!";
            }
        }

       if (m_parser_is_strict && extra_params_found)
       {
           return false;
       }
    }
    */
    return true;
}


std::string      RealToSimControlBoard_ParamsParser::getDocumentationOfDeviceParams() const
{
    std::string doc;
    doc = doc + std::string("\n=============================================\n");
    doc = doc + std::string("This is the help for device: RealToSimControlBoard\n");
    doc = doc + std::string("\n");
    doc = doc + std::string("This is the list of the parameters accepted by the device:\n");
    doc = doc + std::string("'modePosVel': position or velocity mode\n");
    doc = doc + std::string("'remotes': list of remotes to which this device connects\n");
    doc = doc + std::string("'remotePrefix': global prefix to remote ports\n");
    doc = doc + std::string("'remoteSuffix': suffix for remote port of each remote_controlboard\n");
    doc = doc + std::string("'localSuffix': suffix for local port of each remote_controlboard\n");
    doc = doc + std::string("\n");
    doc = doc + std::string("Here are some examples of invocation command with yarpdev, with all params:\n");
    doc = doc + " yarpdev --device RealToSimControlBoard --modePosVel 0 --remotes <mandatory_value> --remotePrefix <optional_value> --remoteSuffix <optional_value> --localSuffix <optional_value>\n";
    doc = doc + std::string("Using only mandatory params:\n");
    doc = doc + " yarpdev --device RealToSimControlBoard --remotes <mandatory_value>\n";
    doc = doc + std::string("=============================================\n\n");    return doc;
}
