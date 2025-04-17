/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */


// Generated by yarpDeviceParamParserGenerator (1.0)
// This is an automatically generated file. Please do not edit it.
// It will be re-generated if the cmake flag ALLOW_DEVICE_PARAM_PARSER_GERNERATION is ON.

// Generated on: Thu Apr 17 12:02:47 2025


#ifndef REALTOSIMCONTROLBOARD_PARAMSPARSER_H
#define REALTOSIMCONTROLBOARD_PARAMSPARSER_H

#include <yarp/os/Searchable.h>
#include <yarp/dev/IDeviceDriverParams.h>
#include <string>
#include <cmath>

/**
* This class is the parameters parser for class RealToSimControlBoard.
*
* These are the used parameters:
* | Group name | Parameter name | Type           | Units | Default Value | Required | Description                                        | Notes          |
* |:----------:|:--------------:|:--------------:|:-----:|:-------------:|:--------:|:--------------------------------------------------:|:--------------:|
* | -          | modePosVel     | int            | -     | 0             | 0        | position or velocity mode                          | 0: pos, 1: vel |
* | -          | remotes        | vector<string> | -     | -             | 1        | list of remotes to which this device connects      | -              |
* | -          | remotePrefix   | string         | -     | -             | 0        | global prefix to remote ports                      | -              |
* | -          | remoteSuffix   | string         | -     | -             | 0        | suffix for remote port of each remote_controlboard | -              |
* | -          | localSuffix    | string         | -     | -             | 0        | suffix for local port of each remote_controlboard  | -              |
*
* The device can be launched by yarpdev using one of the following examples (with and without all optional parameters):
* \code{.unparsed}
* yarpdev --device RealToSimControlBoard --modePosVel 0 --remotes <mandatory_value> --remotePrefix <optional_value> --remoteSuffix <optional_value> --localSuffix <optional_value>
* \endcode
*
* \code{.unparsed}
* yarpdev --device RealToSimControlBoard --remotes <mandatory_value>
* \endcode
*
*/

class RealToSimControlBoard_ParamsParser : public yarp::dev::IDeviceDriverParams
{
public:
    RealToSimControlBoard_ParamsParser();
    ~RealToSimControlBoard_ParamsParser() override = default;

public:
    const std::string m_device_classname = {"RealToSimControlBoard"};
    const std::string m_device_name = {"RealToSimControlBoard"};
    bool m_parser_is_strict = false;
    struct parser_version_type
    {
         int major = 1;
         int minor = 0;
    };
    const parser_version_type m_parser_version = {};

    const std::string m_modePosVel_defaultValue = {"0"};
    const std::string m_remotes_defaultValue = {""};
    const std::string m_remotePrefix_defaultValue = {""};
    const std::string m_remoteSuffix_defaultValue = {""};
    const std::string m_localSuffix_defaultValue = {""};

    int m_modePosVel = {0};
    std::vector<std::string> m_remotes = {}; //This default value is autogenerated. It is highly recommended to provide a suggested value also for mandatory parameters.
    std::string m_remotePrefix = {}; //This default value of this string is an empty string. It is highly recommended to provide a suggested value also for optional string parameters.
    std::string m_remoteSuffix = {}; //This default value of this string is an empty string. It is highly recommended to provide a suggested value also for optional string parameters.
    std::string m_localSuffix = {}; //This default value of this string is an empty string. It is highly recommended to provide a suggested value also for optional string parameters.

    bool          parseParams(const yarp::os::Searchable & config) override;
    std::string   getDeviceClassName() const override { return m_device_classname; }
    std::string   getDeviceName() const override { return m_device_name; }
    std::string   getDocumentationOfDeviceParams() const override;
    std::vector<std::string> getListOfParams() const override;
};

#endif
