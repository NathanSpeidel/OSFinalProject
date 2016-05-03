import numpy as np
from subprocess import Popen, PIPE

import matplotlib
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'

import matplotlib.pyplot as plt
plt.ion()

def map_access_cycles(sizes, strides, load):
    results = np.zeros((len(strides), len(sizes)), float)
    for (r,stride) in enumerate(strides):
        for (c,size) in enumerate(sizes):
            process = Popen( ["./ram_access.ex", str(size), str(stride), "1000000"]
                           , stdout=PIPE)
            (output, err) = process.communicate()
            exit_code = process.wait()
            results[r,c] = float(output)

    return results

def plot_access_cycles(results, sizes, strides, indices):
    linecolors = ["#377eb8", "#e41a1c", "#4daf4a", "#984ea3", "#ff7f00"]
    plt.clf()
    for (i, k) in enumerate(indices):
        plt.semilogx( sizes, results[k,:]
                    , basex = 2
                    , color = linecolors[i]
                    , linewidth = 2
                    )
    plt.legend(map(lambda s: r"$\Delta$ = " + str(strides[s]), indices), loc = "upper left")

sizes   = np.power(2, range(5, 26))
strides = np.power(2, range(3, 11))
results = map_access_cycles(sizes, strides, 1000000)

np.save("data/ram_access.dat", results)

plt.figure(1)
plot_access_cycles(results, sizes, strides, [0, 2, 3, 4, 7])
plt.xlabel( "Array Size [Byte]"
          , fontsize = 18
          , labelpad = 10
          )
plt.ylabel( "Latency [Cycle]"
          , fontsize = 18
          , labelpad = 10
          )
plt.savefig("plots/access_latency.pdf")
