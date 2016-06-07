from subprocess import Popen, PIPE
import numpy as np

import matplotlib
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'
matplotlib.use('Agg')

import matplotlib.pyplot as plt

CYCLES_PER_SECOND = 800.078e6

def measure_cache(filename, blocksize, nblocks, trials):
    process = Popen( ["./measure_cache.ex",
                      filename, str(blocksize),
                      str(nblocks), str(trials)], stdout = PIPE)
    (output, err) = process.communicate()
    split = trials // 2
    return np.fromiter((float(x) for x in output.split()[split:]), dtype=int) 

def plot_results(nbytes, avg_cycles):
    plt.semilogx(nbytes, 1000*avg_cycles/CYCLES_PER_SECOND, "o-",
                 color="#377eb8",
                 linewidth=3,
                 markeredgecolor="none")

# We can probably generate this with logspace
if __name__ == "__main__":
    matplotlib.rcParams['mathtext.fontset'] = 'stix'
    matplotlib.rcParams['font.family'] = 'STIXGeneral'
    matplotlib.use('Agg')

    filename = "15625000.raw"
    nblocks = np.array([1000, 10000, 100000 , 1000000,
                        2000000 , 3000000])
    block_size = 4096
    trials = 50

    results = np.fromiter((measure_cache(filename, block_size, n, trials).mean()/n for n in nblocks), float)

    np.savez("data/filecache.npz",
             nblocks = nblocks,
             meancycles = results)

    plt.figure(1)
    plot_results(nblocks*block_size, results)
    plt.xlabel("Bytes Read",
               fontsize = 18,
               labelpad = 10)
    plt.ylabel("Average Read Time per Byte [ms]",
               fontsize = 18,
               labelpad = 10)
    plt.savefig("plots/filecache.pdf")
