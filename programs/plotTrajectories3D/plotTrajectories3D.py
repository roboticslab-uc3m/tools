# -*- coding: utf-8 -*-
"""
Author: Raul Fernandez-Fernandez (rauferna@ing.uc3m.es)
Robotics Lab. Universidad Carlos III de Madrid
"""

################### GENERAL ##############################
import glob
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

font = {'family' : 'normal',
        'size'   : 18}

plt.rc('font', **font)


################### TO USE NOW ###########################

#3D
X_COL=0
Y_COL=1
Z_COL=2

##########################################################
def main():

    #Read Trajectory 1

    Traj1=np.loadtxt("Trajectory-generalized.txt")

    #Read Trajectory 2

    #Traj2= np.loadtxt("Trajectory2.txt")
    #Traj2= np.loadtxt("iron/Trajectory-OET.txt") #First line of OET is to specify the Time interval, not always T.

    #Traj3= np.loadtxt("iron/Trajectory-IET.txt")

    #Traj4= np.loadtxt("iron/Trajectory-FTE.txt")

    ############################### CHOOSE BEST RESULT #########################
    
    #TODO implement this to be automatic

    ############################### PLOT 3D ###########################################
    fig = plt.figure()
    ax = fig.gca(projection='3d')
 
    ax.plot(Traj1[:][:,X_COL],Traj1[:][:,Y_COL],Traj1[:][:,Z_COL])
    #ax.plot(Traj2[:][:,X_COL+1],Traj2[:][:,Y_COL+1],Traj2[:][:,Z_COL+1])
    #ax.plot(Traj3[:][:,X_COL],Traj3[:][:,Y_COL],Traj3[:][:,Z_COL])
    #ax.plot(Traj4[:][:,X_COL],Traj4[:][:,Y_COL],Traj4[:][:,Z_COL])


    ############################### PLOT ALL 2D #######################################

    #for i in range(4):  # features
#        plt.figure()
#	plt.xlabel('Force (N)') #Features
#	plt.ylabel('Time Interval')
#        plt.plot(np.linspace(0,9,Traj1.shape[0]),Traj1[:][:,i])
#        #plt.plot(Traj2[:][:,0]*1/8,Traj2[:][:,i+1])
#	plt.plot(Traj2[:][:,0],Traj2[:][:,i+1])
#	plt.plot(np.linspace(0,9,9),Traj3[:][:,i])
#        plt.plot(np.linspace(0,9,9),Traj4[:][:,i])
   


    plt.show()
    #plt.savefig('foo.png')




if __name__ == "__main__":
    main()
