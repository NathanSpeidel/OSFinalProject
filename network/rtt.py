from subprocess import Popen, PIPE
import numpy as np

from StringIO import StringIO

CYCLES_PER_SECOND = 800.078e6
CYCLES_PER_MS = 800.078e3

def measure_rtt(host, port, size, trials):
    process = Popen( ["./rtt.ex",
                      "c", host, str(port),
                      str(size), str(trials)], stdout = PIPE)
    (output, err) = process.communicate()
    return np.genfromtxt(StringIO(output), delimiter=",").transpose()

def plot_results(nbytes, avg_cycles):
    plt.semilogx(nbytes, 1000*avg_cycles/CYCLES_PER_SECOND, "o-",
                 color="#377eb8",
                 linewidth=3,
                 markeredgecolor="none")

# We can probably generate this with logspace
if __name__ == "__main__":
    size = 64
    trials = 100
    port = 27182

    local_rtt =  measure_rtt("0.0.0.0", port, size, trials)/CYCLES_PER_MS
    remote_rtt = measure_rtt("192.168.0.3", port, size, trials)/CYCLES_PER_MS

    np.savez("data/rtt.npz",
             local = local_rtt,
             remote = remote_rtt)

    with open("data/rtt.txt", "w") as outfile:
        outfile.write("# Time in milliseconds\n")
        outfile.write("#host, mean setup, mean rtt, mean teardown, std setup, std rtt, std teardown\n")
        outfile.write("local, "  + str( local_rtt[0].mean()) + ", "
                                 + str( local_rtt[1].mean()) + ", "
                                 + str( local_rtt[2].mean()) + ", "
                                 + str( local_rtt[0].std())  + ", "
                                 + str( local_rtt[1].std())  + ", "
                                 + str( local_rtt[2].std())  + "\n")
        outfile.write("remote, " + str(remote_rtt[0].mean()) + ", "
                                 + str(remote_rtt[1].mean()) + ", "
                                 + str(remote_rtt[2].mean()) + ", "
                                 + str(remote_rtt[0].std())  + ", "
                                 + str(remote_rtt[1].std())  + ", "
                                 + str(remote_rtt[2].std())  + "\n")
