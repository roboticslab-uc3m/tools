#!/usr/bin/env python

'''
python-picker-loader.py program

Authors: Raul Fernandez-Fernandez

Universidad Carlos III de Madrid 
'''

try:
    import cPickle as pickle
except:
    import pickle

import pprint
import numpy as np
from stl import mesh


filename='/home/raul/repos/teo-openrave-models/openrave/teo/pp/convexdecomposition.pp'
modelversion,params = pickle.load(open(filename, 'r'))

#pprint.pprint(modelversion)
#pprint.pprint(params)

#links
linkcd, convexparams=params

print('processing '+str(len(linkcd))+' links')

iteration = 0
for linkcd_for in linkcd:
        for ig, hulls in linkcd_for:
            vertices = np.zeros((0, 3), np.float64)
            faces = np.zeros((0, 3), int)
            for hull in hulls:
                faces = np.r_[faces, hull[1] + len(vertices)]
                vertices = np.r_[vertices, hull[0]]
            #print vertices
            #print faces

            #Create cube mesh object
            mesh_object = mesh.Mesh(np.zeros(faces.shape[0], dtype=mesh.Mesh.dtype))
            for i, f in enumerate(faces):
                for j in range(3):
                    mesh_object.vectors[i][j] = vertices[f[j], :]

            #print(cube)

            # Write the mesh to file "cube.stl"
            mesh_object.save('link-'+str(iteration)+'.stl')
            iteration=iteration+1
            print ('link '+str(iteration))
