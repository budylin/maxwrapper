import numpy as np
import maxwrapper

argmax = maxwrapper.Argmax()
data = np.arange(12, dtype=float).reshape(2, -1)
print data
print argmax(data)
data = data.reshape(4, -1)
print data
print argmax(data)

