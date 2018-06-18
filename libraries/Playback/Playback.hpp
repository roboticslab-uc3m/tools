// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __PLAYBACK__
#define __PLAYBACK__

#include <sstream>
#include <fstream>
#include <vector>

namespace roboticslab
{

/**
 * @ingroup roboticslab-tools-libraries
 * \defgroup Playback
 * @brief Contains roboticslab::Playback.
 */

 /**
 * @ingroup Playback
 * @brief Implementation for Playback.
 *
 */
class Playback
{

    public:

        Playback() {
            doublesOnFileIter = 0;
        }

        bool fromFile(const std::string& fileName);

        int getNumRows();
        int getIter();
        bool getNext(std::vector<double>& row);
        bool reset();

    private:

        std::ifstream file;

        bool parseFileLine(std::vector<double>& doublesOnFileLine);

        std::vector< std::vector<double> > doublesOnFile;
        int doublesOnFileIter;

};

}  // namespace roboticslab

#endif  // __PLAYBACK__
