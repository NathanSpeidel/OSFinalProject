from subprocess import Popen, PIPE
import numpy as np

from StringIO import StringIO

CYCLES_PER_SECOND = 800.078e6
CYCLES_PER_MS = 800.078e3

def measure_peak(host, port, size, trials):
    process = Popen( ["./peak_bandwidth.ex",
                      "c", host, str(port),
                      str(size), str(trials)], stdout = PIPE)
    (output, err) = process.communicate()
    return np.genfromtxt(StringIO(output)).transpose()

def plot_results(nbytes, avg_cycles):
    plt.semilogx(nbytes, 1000*avg_cycles/CYCLES_PER_SECOND, "o-",
                 color="#377eb8",
                 linewidth=3,
                 markeredgecolor="none")

# We can probably generate this with logspace
if __name__ == "__main__":
    size = 64
    trials = 1000
    port = 27182
    size = 2^20

    local_peak =  size*CYCLES_PER_SECOND/measure_peak("0.0.0.0", port, size, trials)
    remote_peak =  size*CYCLES_PER_SECOND/measure_peak("192.168.0.3", port, size, trials)

    np.savez("data/peak.npz",
             local = local_peak,
             remote = remote_peak)

    with open("data/peak.txt", "w") as outfile:
        outfile.write("#Bytes per second \n")
        outfile.write("#host, mean, std, max, min\n")
        outfile.write("local, "   + str( local_peak.mean()) + ", "
                                  + str( local_peak.std())  + ", "
                                  + str( local_peak.max())  + ", "
                                  + str( local_peak.min())  + "\n")
        outfile.write("remote, "  + str(remote_peak.mean()) + ", "
                                  + str(remote_peak.std())  + ", "
                                  + str(remote_peak.max())  + ", "
                                  + str(remote_peak.min())  + "\n")
