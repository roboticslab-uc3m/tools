| Group | Parameter |     Type    | Units | Default Value | Required |              Description              |         Notes         |
|:-----:|:---------:|:-----------:|:-----:|:-------------:|:--------:|:-------------------------------------:|:---------------------:|
|       |   file    |    string   |       |   test.txt    |    no    |               file name               |                       |
|       |  timeIdx  |     int     |       |       0       |    no    |          index of timestamp           |                       |
|       | timeScale |    double   |       |      1.0      |    no    |       time scaling of timestamp       |                       |
|       |   mask    | vector<int> |       |               |    yes   | filter to apply to each item in a row | 1: process, 0: ignore |
