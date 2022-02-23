import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns              
import matplotlib.ticker as tkr
import matplotlib.gridspec as gridspec
from matplotlib.patches import Patch
import os
import matplotlib.lines as lines
import matplotlib.ticker as ticker
from plot_utils import *

PALETTE = [COLORS["peach2"], COLORS["g1"]]
PALETTE_B = [COLORS["b3"], COLORS["b3"]]
PALETTE_GW1 = [COLORS[r] for r in ["gw3","gw2","gw1"]]
PALETTE_GW2 = [COLORS[r] for r in ["b1","b3","b5"]]
PALETTE_GW = [PALETTE_GW1, PALETTE_GW2]
HATCHES = ['', '/'*4, '\\'*4]

data = pd.read_csv("../results.csv", sep=',')

# sns.set_theme(style="whitegrid")
sns.set_style("whitegrid", {"ytick.left": True})
plt.rcParams["font.family"] = ["serif"]
plt.rcParams["font.size"] = 12
plt.rcParams['hatch.linewidth'] = 0.6
plt.rcParams['axes.labelpad'] = 5 
plt.rcParams['pdf.fonttype'] = 42
plt.rcParams['ps.fonttype'] = 42

ylabels = {'Memory Usage (kB)':"Memory Usage (kB)", "Duration Dijkstra (µs)":"Dijkstra Execution Time [µs]"}
# ylims = {'Wall_train': [(0,10000),(0,10000),(0,80000)], 'Peak_RAM':[(0,500)]*3, 'CPU_train':[(0,140000),(0,140000),(0,1800000)], 'Peak_RAM_load_graph':[(0,500)]*3}
conf = ['Adjacency Matrix', 'Adjacency List', 'Csr']
for i, var in enumerate(["Memory Usage (kB)","Duration Dijkstra (µs)"]): 
    g = sns.catplot(data=data, kind='point', ci=99, x="Density (%)",
    #g = sns.catplot(data=data, kind='point', ci=99, x="Number of nodes",
    y=var, hue='Data structure', hue_order=conf, 
    row='Number of nodes', row_order=[1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000],
    #row='Density (%)', row_order=[20, 40, 60, 80, 100], 
    alpha=1, palette=PALETTE_GW[i], height=3, aspect=5, legend_out=False, 
    sharey=False, sharex=False, margin_titles=True)
    g.set_axis_labels("Density (%)", ylabels[var])
    #g.despine(left=True)
    #  .set_titles("{col_name}")
    # .set_yticklabels(list(range(100,1000,100))+list(range(1000,10000,1000))+list(range(10000, 75000, 10000)))
    #  

    for i,axes in enumerate(g.axes):  
        for ii,ax in enumerate(axes):
            # ax.set(ylim=ylims[var][i])
            plt.sca(axes[ii])
        #if ii!=0:
            # a = list(range(0, ylims[var][i][1]+1,(ylims[var][i][1]+1)//4))
            # print(a)
            # plt.yticks(a)
            # if ii!=0:
            #     plt.yticks(a, ['']*5)
            g.set_axis_labels("Density (%)", ylabels[var])
            # for j, bar in enumerate(ax.patches):
            #     bar.set_hatch(HATCHES[(j%15)//5])
            #     bar.set_edgecolor('k')
                
            # for j, bar in enumerate([p for p in ax.patches if not pd.isna(p)]):
            #     bar.set_hatch(HATCHES[j // len(axes)])
    #     ax.yaxis.set_minor_locator(tkr.LogLocator(base=10, subs='all'))
    #     ax.yaxis.set_minor_formatter(tkr.NullFormatter())
    # if var == 'Wall_train':
    #     g.set(yscale='log')
        
    # Add legend;
    # g.legend.remove()  # Remove the existing legend again;
    custom_lines = [Patch(facecolor=PALETTE_GW[0], edgecolor="k", label=conf[0]),
                    Patch(facecolor=PALETTE_GW[1], edgecolor="k", label=conf[1]),
                    Patch(facecolor=PALETTE_GW[2], edgecolor="k", label=conf[2])] 
                    
    legend_data = {a:b for a,b in zip(conf,custom_lines)}
    g.add_legend(legend_data, conf, loc="upper center", bbox_to_anchor=(0.50, 0.95), fontsize=10, ncol=1, handletextpad=0.2, columnspacing=0.4, fancybox=True)
    g.legend.set_title("Graph Data Structure")
    # leg._legend_box.align = "left"
    g.legend.get_frame().set_facecolor('white')
    plt.subplots_adjust(left=0.15, bottom=0.065, right=0.95, top=0.96, hspace=0.5, wspace=0.14)
    plt.savefig(f"Total{var}_Density.pdf")
    # plt.show()

