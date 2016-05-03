import numpy as np
import time
from subprocess import Popen, PIPE

import matplotlib
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'
matplotlib.use('Agg')

import matplotlib.pyplot as plt

def trigger_page_faults(N, trials, output):
    process = Popen(["./page_fault.ex", str(N), str(trials), output ])
    exit_code = process.wait()
    return np.fromfile(output, dtype = np.uint64)

def find_page_faults(N, trials):
    timestamp = int(time.time())
    outputs = [ "data/tmp_N" + str(trials) + "_t" + str(timestamp) + ".bin"
              , "data/tmp_N" + str(trials) + "_t" + str(timestamp + 1) + ".bin" ]
    results = map( lambda f: trigger_page_faults(N, trials, f), outputs )
    plt.clf()
    for (i, cycles) in enumerate(results):
        n, bins = np.histogram(cycles, range=(0, 300000))
        nn, = np.nonzero(n)
        plt.subplot(221 + 2*i)
        plt.bar( bins[nn], n[nn]
               , width = bins[1] - bins[0]
               , ec = "None"
               , color = (["#377eb8"] + ["#e41a1c"]*(len(nn)-1))
               )
        plt.xticks(np.arange(0,400000,100000), np.arange(0,40,10))
        plt.yticks(np.arange(0,4000,1000))
        plt.xlabel(r"Cycle Count [$\times 10000$]")
        plt.ylabel("Occurance")

        n, bins = np.histogram(cycles, 25, range=(150000, 300000))
        nn, = np.nonzero(n)
        plt.subplot(222 + 2*i)
        plt.bar( bins[nn], n[nn]
               , width = bins[1] - bins[0]
               , ec = "None"
               , color = "#e41a1c"
               )
        plt.xticks(np.arange(150000,350000,50000), np.arange(15,35,5))
        plt.yticks(np.arange(0,160,40))
        plt.xlabel(r"Cycle Count [$\times 10000$]")
        plt.ylabel("Occurance")

    plt.subplots_adjust(hspace=0.5, wspace=0.4)

plt.figure(1)
find_page_faults(21, 3000)
plt.savefig("plots/page_fault_histogram.pdf")
