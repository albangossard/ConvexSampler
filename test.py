import numpy as np
import itertools, time
from scipy.spatial import ConvexHull
import convex_sampler


N = 5000
P = 7
nT = 9*np.ones(P, dtype=np.int)

# Generate points that define the convex C=Conv(points[i])
points = np.random.randn(N, P)


tic=time.time()
hull_cv = ConvexHull(points)
print('nb vertices = %i'%hull_cv.vertices.shape[0])
print('nb faces = %i'%hull_cv.simplices.shape[0])
print('ConvexHull computing time ',time.time()-tic)

box=np.array([np.min(points, axis=0), np.max(points, axis=0)])

# Generate points in the smallest box containing C
sampling = []
for p in range(P):
    T = np.linspace(box[0,p],box[1,p],nT[p])
    sampling.append(list(T))
T = list(itertools.product(*sampling))
T = np.array(T)
nb=np.prod(nT)
print("Number of points to test: %i"%nb)


# Test if the points T[i] are in C
tokeep = np.ones(T.shape[0], dtype=np.int16)
tic = time.time()
convex_sampler.is_in_cvx(hull_cv.equations.reshape(-1), P, T.reshape(-1), tokeep)
toc=time.time()-tic
print("Computing time = %3f"%toc)
print("Nb of points inside = %i"%np.sum(tokeep))
