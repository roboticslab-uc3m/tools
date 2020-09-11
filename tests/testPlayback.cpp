#include "gtest/gtest.h"

#include <string>

#include <yarp/conf/filesystem.h>

#include <ColorDebug.h>

#include "Playback.hpp"

namespace roboticslab
{

/**
 * @ingroup roboticslab-tools-tests
 * @brief Tests \ref Playback
 */
class PlaybackTest : public testing::Test // -- inherit the Test class (gtest.h)
{

public:

    virtual void SetUp()
    {
        // -- code here will execute just before the test ensues
        std::string fileName("resources");
        fileName += yarp::conf::filesystem::preferred_separator;
        fileName += "testPlayback.txt";

        if(!playback.fromFile(fileName))
        {
            CD_ERROR("Bad Configuration\n");
            ::exit(1);
        }
        CD_SUCCESS("Configuration successful :)\n");
    }

    virtual void TearDown()
    {
        // -- code here will be called just after the test completes
        // -- ok to through exceptions from here if need be
    }

protected:

    /** Playback. */
    Playback playback;

};

TEST_F( PlaybackTest, PlaybackTestGetNumRows )
{
    std::cout << "Num rows: " << playback.getNumRows() << std::endl;
}

TEST_F( PlaybackTest, PlaybackTestGetNext )
{
    std::vector<double> row;

    while( playback.getNext(row) )
    {
        std::cout << "Row[" << playback.getIter() << "]: ";
        for(int i=0;i<row.size();i++)
        {
            std::cout << row[i] << " ";
        }
        std::cout << std::endl;
    }
}

}
