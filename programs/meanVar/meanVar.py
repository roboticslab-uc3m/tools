# -*- coding: utf-8 -*-
"""
Author: Raul Fernandez-Fernandez (rauferna@ing.uc3m.es)
Robotics Lab. Universidad Carlos III de Madrid
"""

################### GENERAL ##############################
import numpy as np

################### TO USE NOW ###########################

features1=[3,4] #column features to use from trajectory1

d1="data/Trajectory-IET-Iron.txt" #Trajectory 1 file name

##########################################################
def main():
    
    #Read Trajectory 1
    data1=np.loadtxt(d1)
    d1_clean=data1[:,features1]

    #Calculate mean and variance from trajectories, indeed we just need 1
    meanArray=[]
    varArray=[]
	
    for i in range(d1_clean.shape[1]):
        meanArray.append(np.mean(d1_clean[:][:,i]))
        varArray.append(np.var(d1_clean[:][:,i]))
    
    np.savetxt("results-mean.txt",meanArray,"%f")
    np.savetxt("results-var.txt",varArray, "%f")

if __name__ == "__main__":
    main()

