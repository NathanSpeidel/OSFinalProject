from subprocess import Popen, PIPE
import numpy as np

import matplotlib
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'

import matplotlib.pyplot as plt
plt.ion()

def measure_bandwidth(op, stride, trials, size):
    process = Popen( ["./bandwidth.ex", op, size, stride, trials]
                   , stdout = PIPE)
    (output, err) = process.communicate()
    results = filter(lambda c : c not in ":[]~,", output).split()[1::]
    return map(float, results)


def map_bandwidth(sizes, block_sizes, trials):
    ops = map(lambda s: ("copy", str(s), str(trials)), block_sizes)
    ops += [ ("read",  "1", str(trials))
           , ("read",  "4", str(trials))
           , ("write", "1", str(trials))
           , ("write", "4", str(trials))
           ]
    means   = np.zeros((len(ops), len(sizes)), float)
    stdevs  = np.zeros((len(ops), len(sizes)), float)
    minvals = np.zeros((len(ops), len(sizes)), float)
    maxvals = np.zeros((len(ops), len(sizes)), float)

    for (r,op) in enumerate(ops):
        for (c,size) in enumerate(sizes):
            args = op + (str(size),)
            means[r,c], minvals[r,c], maxvals[r,c], stdevs[r,c] = measure_bandwidth(*args)

    return ops, means, minvals, maxvals, stdevs

def plot_results(sizes, means, stdevs, indices, labels):
    linecolors = ["#377eb8", "#e41a1c", "#4daf4a", "#984ea3", "#ff7f00"]
    facecolors = ["#9ecae1", "#fc9272", "#a1d99b", "#bcbddc", "#fdae6b"]
    handles = []
    plt.clf()
    for (i, k) in enumerate(indices):
        plt.fill_between( sizes
                        , means[k] - stdevs[k]
                        , means[k] + stdevs[k]
                        , edgecolor = "None"
                        , facecolor = facecolors[i]
                        , alpha = 0.2)

        h, = plt.semilogx( sizes, means[k]
                         , basex = 2
                         , color = linecolors[i]
                         , linewidth=2)
        handles.append(h)

    plt.legend( handles, labels
              , loc = "upper center"
              , bbox_to_anchor=(0.5, 1.10)
              , fancybox=True, ncol=len(indices)
              )


sizes   = np.power(2, range(5, 18))
block_sizes = np.power(2, range(0, 11))
ops, means, minvals, maxvals, stdevs = map_bandwidth(sizes, block_sizes, 500)

np.savez( "data/bandwidth.dat"
        , ops = ops
        , means = means
        , minvals = minvals
        , maxvals = maxvals
        , stdevs = stdevs
        )

plt.figure(1)
plot_results( sizes, means, stdevs
            , [0, 11, 13]
            , ( "Read" , "Write" , "memcpy (stride = 1 byte)"))
plt.xlabel( "Array Size [Byte]"
          , fontsize = 18
          , labelpad = 10
          )
plt.ylabel( "Memory Operation Speed [MB/s]"
          , fontsize = 18
          , labelpad = 10
          )
plt.savefig("plots/bandwidth_bytewise.pdf")

plt.figure(1)
plot_results( sizes, means, stdevs
            , [2, 12, 14]
            , ( "Read" , "Write" , "memcpy (stride = 4 byte)"))
plt.xlabel( "Array Size [Byte]"
          , fontsize = 18
          , labelpad = 10
          )
plt.ylabel( "Memory Operation Speed [MB/s]"
          , fontsize = 18
          , labelpad = 10
          )
plt.savefig("plots/bandwidth_quadword.pdf")

plt.figure(1)
plot_results( sizes, means, stdevs
            , [4, 7, 9, 10]
            , ( r"$\Delta$ = 16" , r"$\Delta$ = 128" , r"$\Delta$ = 512", r"$\Delta$ = 1024"))
plt.xlabel( "Array Size [Byte]"
          , fontsize = 18
          , labelpad = 10
          )
plt.ylabel( "Memory Operation Speed [MB/s]"
          , fontsize = 18
          , labelpad = 10
          )
plt.savefig("plots/bandwidth_compare_copy_blocksize.pdf")
