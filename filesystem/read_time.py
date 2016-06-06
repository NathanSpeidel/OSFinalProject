import os
from subprocess import Popen, PIPE
import numpy as np

import matplotlib
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'
matplotlib.use('Agg')

import matplotlib.pyplot as plt

CYCLES_PER_SECOND = 3.5e9

def measure_read(blocksize, nblocks, trials, mode):

    filename = str(1024*nblocks // blocksize) + ".raw"
    process = Popen( ["./measure_read.ex", mode,
                      filename, str(blocksize),
                      str(nblocks), str(trials)], stdout = PIPE)
    (output, err) = process.communicate()
    split = trials // 2
    return np.fromiter((float(x) for x in output.split()[split:]), dtype=int) 

def plot_results(nbytes, cycles_s, cycles_r):
    plt.semilogx(nbytes, 1000*cycles_s/CYCLES_PER_SECOND, "o-",
                 color="#377eb8",
                 linewidth=3,
                 markeredgecolor="none")
    plt.semilogx(nbytes, 1000*cycles_r/CYCLES_PER_SECOND, "o-",
                 color="#e41a1c",
                 linewidth=3,
                 markeredgecolor="none")
    plt.xlabel("File Size [bytes]",
               fontsize = 18,
               labelpad = 10)
    plt.ylabel("Average Read Time per Byte [ms]",
               fontsize = 18,
               labelpad = 10)
    plt.legend(("Sequential Access", "Random Access"), loc="upper left")

# We can probably generate this with logspace
if __name__ == "__main__":
    matplotlib.rcParams['mathtext.fontset'] = 'stix'
    matplotlib.rcParams['font.family'] = 'STIXGeneral'
    matplotlib.use('Agg')

    fileblocks = np.array([100 , 1000 , 10000 , 100000 , 1000000])
    block_size = 1024

    nblocks = (block_size // 1024)*fileblocks
    trials = 100

    results_s = np.fromiter((measure_read(block_size, n, trials, 's').mean()/n for n in nblocks), float)

    os.system('sudo bash -c "sync; echo 3 > /proc/sys/vm/drop_caches"')
    results_r = np.fromiter((measure_read(block_size, n, trials, 'r').mean()/n for n in nblocks), float)

    np.savez("data/fileread.npz",
             nblocks = nblocks,
             seqtimes = results_s,
             randtimes = results_r)

    plt.figure(1)
    plot_results(nblocks*block_size, results_s, results_r)
    plt.savefig("plots/fileread.pdf")
