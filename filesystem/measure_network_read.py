import sys
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

def measure_read(blocksize, nblocks, trials, mode):

    filename = "/home/nathan/NFSMount/" + str(blocksize*nblocks // 1024) + ".raw"
    process = Popen( ["./measure_read.ex", mode,
                      filename, str(blocksize),
                      str(nblocks), str(trials)], stdout = PIPE)
    (output, err) = process.communicate()
    return np.fromiter((float(x)/nblocks for x in output.split()), dtype=int) 

def plot_results(nbytes, cycles_s, cycles_r):
    plt.loglog(nbytes, np.mean(cycles_s[:,1:], 1)/CYCLES_PER_MS, "o-",
                 color="#377eb8",
                 linewidth=3,
                 markeredgecolor="none")
    plt.loglog(nbytes, cycles_s[:,0]/CYCLES_PER_MS, "o--",
                 color="#377eb8",
                 linewidth=3,
                 markeredgecolor="none")
    plt.loglog(nbytes, np.mean(cycles_r[:,1:], 1)/CYCLES_PER_MS, "o-",
                 color="#e41a1c",
                 linewidth=3,
                 markeredgecolor="none")
    plt.loglog(nbytes, cycles_r[:,0]/CYCLES_PER_MS, "o--",
                 color="#e41a1c",
                 linewidth=3,
                 markeredgecolor="none")
    plt.xlabel("File Size [bytes]",
               fontsize = 18,
               labelpad = 10)
    plt.ylabel("Average Read Time Per Block [ms]",
               fontsize = 18,
               labelpad = 10)
    plt.legend(("Sequential (Subsequent)", "Sequential (Initial)", "Random (Subsequent)", "Random (Initial)"), loc='upper center', bbox_to_anchor=(0.5, 1.12), ncol=2, fancybox=True)

# We can probably generate this with logspace
if __name__ == "__main__":
    matplotlib.rcParams['mathtext.fontset'] = 'stix'
    matplotlib.rcParams['font.family'] = 'STIXGeneral'
    matplotlib.use('Agg')

    fileblocks = np.array([100 , 1000 , 10000 , 100000 , 1000000])
    block_size = int(sys.argv[1])

    nblocks = 1024*fileblocks // block_size
    trials = 10

    os.system('sudo bash -c "sync; echo 3 > /proc/sys/vm/drop_caches"')
    os.system('ssh -t angel@192.168.0.3 "sudo purge"')
    results_s = np.stack((measure_read(block_size, n, trials, 's') for n in nblocks))

    os.system('sudo bash -c "sync; echo 3 > /proc/sys/vm/drop_caches"')
    os.system('ssh -t angel@192.168.0.3 "sudo purge"')

    results_r = np.stack((measure_read(block_size, n, trials, 'r') for n in nblocks))

    np.savez("data/filenfs_" + str(block_size) + ".npz",
             nblocks = nblocks,
             seqtimes = results_s,
             randtimes = results_r)

    plt.figure(1)
    plot_results(nblocks*block_size, results_s, results_r)
    plt.savefig("plots/filenfs_" + str(block_size) + ".pdf")
