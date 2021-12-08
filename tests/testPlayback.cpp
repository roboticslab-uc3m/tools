#include "gtest/gtest.h"

#include <string>

#include <yarp/os/LogStream.h>
#include <yarp/conf/filesystem.h>

#include "Playback.hpp"

namespace roboticslab
{
namespace test
{

/**
 * @ingroup roboticslab-tools-tests
 * @brief Tests \ref Playback
 */
class PlaybackTest : public testing::Test
{
public:
    void SetUp() override
    {
        std::string fileName("resources");
        fileName += yarp::conf::filesystem::preferred_separator;
        fileName += "testPlayback.txt";

        if (!playback.fromFile(fileName))
        {
            yFatal() << "Bad Configuration";
        }

        yInfo() << "Configuration successful";
    }

    void TearDown() override
    {}

protected:
    Playback playback;
};

TEST_F(PlaybackTest, PlaybackTestGetNumRows)
{
    yInfo() << "Num rows:" << playback.getNumRows();
}

TEST_F(PlaybackTest, PlaybackTestGetNext)
{
    while (playback.hasNextRow())
    {
        yInfo() << "Row" << playback.getCurrentRowIndex() << playback.getNextRow();
    }
}

}
}
