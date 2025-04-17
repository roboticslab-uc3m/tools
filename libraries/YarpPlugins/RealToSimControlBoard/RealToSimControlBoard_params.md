| Group |  Parameter   |      Type      | Units | Default Value | Required |                    Description                     |     Notes      |
|:-----:|:------------:|:--------------:|:-----:|:-------------:|:--------:|:--------------------------------------------------:|:--------------:|
|       |  modePosVel  |      int       |       |       0       |    no    |             position or velocity mode              | 0: pos, 1: vel |
|       |   remotes    | vector<string> |       |               |    yes   |   list of remotes to which this device connects    |                |
|       | remotePrefix |     string     |       |               |    no    |           global prefix to remote ports            |                |
|       | remoteSuffix |     string     |       |               |    no    | suffix for remote port of each remote_controlboard |                |
|       | localSuffix  |     string     |       |               |    no    | suffix for local port of each remote_controlboard  |                |
