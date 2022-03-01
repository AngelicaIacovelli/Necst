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
PALETTE_GW2 = [COLORS[r] for r in ["blue_klein","bt1","b5"]]
PALETTE_GW = [PALETTE_GW1, PALETTE_GW2]
HATCHES = ['', '/'*4, '\\'*4]

data = pd.read_csv("../results_real.csv", sep=',')
data.rename(columns={'Number of nodes':'# Nodes'}, inplace=True)
FACE = data['Graph'] == 'facebook_combined.csv'
TWIT = data['Graph'] == 'twitter_combined.csv'
data.loc[FACE, 'Graph'] = 'Facebook'
data.loc[TWIT, 'Graph'] = 'Twitter'

# sns.set_theme(style="whitegrid")
sns.set_style("whitegrid", {"ytick.left": True})
plt.rcParams["font.family"] = ["serif"]
plt.rcParams["font.size"] = 18
plt.rcParams['hatch.linewidth'] = 0.6
plt.rcParams['axes.labelpad'] = 5 
plt.rcParams['pdf.fonttype'] = 42
plt.rcParams['ps.fonttype'] = 42

ylabels = {'Memory Usage (kB)':"RAM Usage (kB)", "Duration Dijkstra (µs)":"Run Time [µs]"}
# ylims = {'Wall_train': [(0,10000),(0,10000),(0,80000)], 'Peak_RAM':[(0,500)]*3, 'CPU_train':[(0,140000),(0,140000),(0,1800000)], 'Peak_RAM_load_graph':[(0,500)]*3}
conf = ['Adjacency Matrix', 'Adjacency List', 'Csr']
for k, var in enumerate(["Memory Usage (kB)","Duration Dijkstra (µs)"]): 
    g = sns.catplot(data=data, kind='bar', ci=99, x="# Nodes",
    y=var, col='Graph', hue='Data structure', hue_order=conf, 
    alpha=1, palette=PALETTE_GW[k], height=8, aspect=1.5, legend_out=False, 
    sharey=False, sharex=False, margin_titles=True)
    # g.set_axis_labels("Density (%)", ylabels[var])
    # g.set_axis_labels("# Nodes", ylabels[var])
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
#            g.set_axis_labels("Density (%)", ylabels[var])
            # g.set_axis_labels("# Nodes", ylabels[var])
            for j, bar in enumerate(ax.patches):
                bar.set_hatch(HATCHES[(j%15)//5])
                bar.set_edgecolor('k')
                
            for j, bar in enumerate([p for p in ax.patches if not pd.isna(p)]):
                bar.set_hatch(HATCHES[j // len(axes)])
    #     ax.yaxis.set_minor_locator(tkr.LogLocator(base=10, subs='all'))
    #     ax.yaxis.set_minor_formatter(tkr.NullFormatter())
    # if var == 'Wall_train':
    g.set(yscale='log')
        
    # Add legend;
    # g.legend.remove()  # Remove the existing legend again;
    custom_lines = [Patch(facecolor=PALETTE_GW[k][0], edgecolor="k", label=conf[0]),
                    Patch(facecolor=PALETTE_GW[k][1], edgecolor="k", label=conf[1]),
                    Patch(facecolor=PALETTE_GW[k][2], edgecolor="k", label=conf[2])] 
                    
    legend_data = {a:b for a,b in zip(conf,custom_lines)}
    g.add_legend(legend_data, conf, loc="upper center", bbox_to_anchor=(0.99, 0.98), fontsize=18, ncol=1, handletextpad=0.2, columnspacing=0.5, fancybox=True)
    g.legend.set_title("Graph Data Structure")
    # leg._legend_box.align = "left"
    g.legend.get_frame().set_facecolor('white')
    plt.subplots_adjust(left=0.1, bottom=0.1, right=0.94, top=0.88, hspace=0.75, wspace=0.20)
    # plt.savefig(f"Total{var}_Nodes.pdf")
    plt.savefig(f"Total{var}_Real.pdf")
    # plt.show()

