import os
from subprocess import Popen, PIPE
import numpy as np

import matplotlib
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'
matplotlib.use('Agg')

import matplotlib.pyplot as plt

CYCLES_PER_SECOND = 800.078e6
CYCLES_PER_MS = CYCLES_PER_SECOND/1000

def measure_contention(nprocs, blocksize, nblocks):
    os.system('sudo bash -c "sync; echo 3 > /proc/sys/vm/drop_caches"')
    fileprefix = "contention_"
    process = Popen( ["./measure_contention.ex",
                      str(nprocs), fileprefix,
                      str(blocksize), str(nblocks)], stdout = PIPE)
    (output, err) = process.communicate()
    return np.fromiter((float(x)/nblocks for x in output.split()), dtype=int) 

def plot_results(nprocs, read_cycles):
    plt.errorbar(nprocs, np.mean(read_cycles, 1)/CYCLES_PER_MS,
                 np.std(read_cycles,1)/CYCLES_PER_MS ,
                 color="#377eb8",
                 linewidth=3,
                 markeredgecolor="none")
    plt.xlabel("Number of Processes",
               fontsize = 18,
               labelpad = 10)
    plt.ylabel("Read Time per Block [ms]",
               fontsize = 18,
               labelpad = 10)
    current_axis = plt.axis()
    plt.axis([0.5, 10.5, current_axis[2], current_axis[3]])

# We can probably generate this with logspace
if __name__ == "__main__":

    block_size = 4096
    nblocks    = 1000

    nprocs = np.arange(1,11)
    trials = [10, 5, 4, 3, 2, 2, 2, 2, 2, 1]
    results = []
    for (i, n) in enumerate(nprocs):
        base = np.array([], dtype=float)

        for t in range(trials[i]):
            base = np.append(base, measure_contention(n, block_size, nblocks))

        results.append(base[1:10])

    np.savez("data/filecontention.npz",
             nblocks = nprocs,
             readtimes = np.stack(results))
    plt.figure(1)
    plot_results(nprocs, results)
    plt.savefig("plots/filecontention.pdf")
