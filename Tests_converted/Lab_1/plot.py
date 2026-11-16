import pandas as pd
import matplotlib.pyplot as plt
import sys
import numpy as np

df = 0
name = ""

if len(sys.argv) > 1:
    df = pd.read_csv(sys.argv[1])
    name = sys.argv[1]
else:
    df = pd.read_csv("Test_oscilatory_decay(really_good).csv")

if len(sys.argv) > 2:
    name = sys.argv[2]

p_enc = df["p~"]
p_c = df["p_c"]
labels = [p_enc.name, p_c.name]
data = np.array([p_enc, p_c]).T
# print(data)

plt.plot(df.iloc[:, 0], data, label=labels)
plt.grid()
# plt.axhline(color="black", linestyle="dashed")
plt.legend(fontsize=16)
plt.xlabel("Time (s)", fontsize=16)
plt.ylabel("Pitch (rad)", fontsize=16)
plt.title(name, fontsize=20)
plt.show()
