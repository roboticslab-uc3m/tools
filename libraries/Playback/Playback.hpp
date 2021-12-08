// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __PLAYBACK_HPP__
#define __PLAYBACK_HPP__

#include <fstream>
#include <vector>

namespace roboticslab
{

/**
 * @ingroup roboticslab-tools-libraries
 * @defgroup Playback
 * @brief Contains roboticslab::Playback.
 */

 /**
 * @ingroup Playback
 * @brief Implementation for Playback.
 */
class Playback
{
public:
    using row_t = std::vector<std::vector<double>>;

    bool fromFile(const std::string & fileName);
    std::size_t getNumRows() const;
    std::size_t getCurrentRowIndex() const;
    bool hasNextRow() const;
    const row_t::value_type & getNextRow();
    void reset();

private:
    static void parseFileLine(std::ifstream & file, std::vector<double> & row);

    row_t storage;
    row_t::const_iterator iter;
};

} // namespace roboticslab

#endif // __PLAYBACK_HPP__
