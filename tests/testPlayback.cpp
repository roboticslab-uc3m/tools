#include "gtest/gtest.h"

#include <string>

#include <yarp/os/ResourceFinder.h>

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

        yarp::os::ResourceFinder rf;
        rf.setVerbose(true);
        rf.setDefaultContext("Playback");
        std::string path = rf.findFileByName("txt/testPlayback.txt");

        bool ok = true;
        ok &= playback.fromFile(path);

        if(ok)
        {
            CD_SUCCESS("Configuration successful :)\n");
        }
        else
        {
            CD_ERROR("Bad Configuration\n");
            ::exit(1);
        }
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
